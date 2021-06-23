#pragma once

template <typename TMessage>
class IMessageSubscriber {
public:
    virtual void OnMessage(const TMessage& message) = 0;

    virtual ~IMessageSubscriber() = default;
};

template <typename TMessage>
class IMessageSource {
public:
    virtual void Subscribe(IMessageSubscriber<TMessage>* subscriber) = 0;

    virtual ~IMessageSource() = default;
};
