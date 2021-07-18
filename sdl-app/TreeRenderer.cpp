#include "TreeRenderer.h"

#include "Game.h"
#include "Camera.h"

#include <antgame/WorldTree.h>

#include <easyloggingpp/easylogging++.h>
#include <SDL.h>

namespace bg = boost::geometry;
namespace bgi = bg::index;

namespace {

// simplified with boost 1.76, compared to 1.72, but not present in Github CI Runners (Ubuntu Focal)
template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
struct TreeTraverser : public bgi::detail::rtree::visitor<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag, true>::type {
    using internal_node = typename bgi::detail::rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type;
    using leaf = typename bgi::detail::rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type;
    using internal_node_elements_type = typename bgi::detail::rtree::elements_type<internal_node>::type;
    using leaf_elements_type = typename bgi::detail::rtree::elements_type<leaf>::type;

    inline TreeTraverser(Translator const& t, const Visitor* visitor)
        : m_visitor(visitor)
        , tr(t)
        , level_f(0)
        , level_l((std::numeric_limits<size_t>::max)())
        , level(0)
    {}

    inline void operator()(const internal_node& n) {
        const auto& elements = bgi::detail::rtree::elements(n);

        for (auto it = elements.begin(); it != elements.end(); ++it) {
            m_visitor->Visit(it->first);
        }

        const size_t level_backup = level;
        ++level;
        if ( level < level_l ) {
            for (auto it = elements.begin(); it != elements.end(); ++it) {
                bgi::detail::rtree::apply_visitor(*this, *it->second);
            }
        }
        level = level_backup;
    }

    inline void operator()(leaf const& n) {
        // Do not render leafs, as we query these separately in order to not
        // render leafs outside the camera frustrum

        /*
        const auto& elements = bgi::detail::rtree::elements(n);

        if ( level_f <= level ) {
            for (auto it = elements.begin(); it != elements.end(); ++it) {
                tr(*it).Accept(*m_visitor);
            }
        }
        */
    }

    const Visitor* m_visitor;
    Translator const& tr;
    size_t level_f;
    size_t level_l;
    size_t level;
};

}

void TreeRenderer::RenderNodes() const {
    namespace RTreeUtils = boost::geometry::index::detail::rtree::utilities;
    const auto rtree = m_game->m_world.GetWorldTree().GetRTree();

    using RTV = RTreeUtils::view<WorldTree::WorldObjectRTree>;
    RTV rtv(rtree);

    if ( !rtree.empty()) {
        m_worldObjectRenderer.Visit(rtree.bounds());
    }

    TreeTraverser<
        typename RTV::value_type,
        typename RTV::options_type,
        typename RTV::translator_type,
        typename RTV::box_type,
        typename RTV::allocators_type
    > traverser(rtv.translator(), &m_worldObjectRenderer);

    rtv.apply_visitor(traverser);
}

void TreeRenderer::Render() const {
    if(m_game->m_debugMode) {
        RenderNodes();
    }

    const auto& wt = m_game->m_world.GetWorldTree();

    const auto frustrum = m_game->m_camera.GetFrustrum();
    const auto objectsItEnd = wt.QEnd();
    for (auto objectsIt = wt.QueryBox(frustrum); objectsIt != objectsItEnd; objectsIt++) {
        (*objectsIt)->Accept(m_worldObjectRenderer);
    }
}
