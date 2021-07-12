#include "Text.h"

#include <SDL_ttf.h>
#include <easyloggingpp/easylogging++.h>

void Text::Render() {
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("../../assets/cour.ttf", 48);

    if (!Sans) {
        LOG(ERROR) << "no font lmao";
    }

    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, m_message.data(), m_color); 

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(m_game->m_renderer, surfaceMessage);


    auto point = m_game->m_camera.WorldToScreenTransform(visitee.GetPosition());
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = point.x;  //controls the rect's x coordinate 
    Message_rect.y = point.y; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 50; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    SDL_RenderCopy(m_game->m_renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Sans);
}