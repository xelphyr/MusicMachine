#pragma once

#include <functional>
#include <vector>

namespace MM::Systems
{
    class EventBus
    {
        public:
            static EventBus& Instance()
            {
                static EventBus nfm;
                return nfm;
            }
            EventBus(const EventBus&) = delete;
            EventBus& operator = (const EventBus&) = delete;


            template<typename EventType>
            void Subscribe(std::function<void(const EventType&)> listener);

            template<typename EventType>
            void Emit(const EventType& event);
        private:
            EventBus(){};
            ~EventBus(){};
            std::unordered_map<const char*, std::vector<std::function<void(const void*)>>> listeners;
    };
}

template<typename EventType>
void MM::Systems::EventBus::Subscribe(std::function<void(const EventType&)> listener)
{
    listeners[typeid(EventType).name()].push_back(
        [listener](const void* event){
            listener(*static_cast<const EventType*>(event));
        }
    );
}

template<typename EventType>
void MM::Systems::EventBus::Emit(const EventType& event)
{
    const char* typeName = typeid(EventType).name();
    for (auto& func : listeners[typeName])
    {
        func(&event);
    }
}

