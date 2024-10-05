#include <EventSystem.h>

EventSystem::EventSystem()
{
    init();
}

void EventSystem::init()
{
    for(int i = 0; i < static_cast<unsigned int>(EventId::EVENT_MAX); ++i)
    {
        events[i].id = static_cast<EventId>(i);
        for(auto c : events[i].cb)
        {
            c = nullptr;
        }
    }
}

void EventSystem::emit(EventId id, void *data)
{
    auto& evt = events[static_cast<unsigned int>(id)];
    for(int i = 0; i < EVT_CB_MAX; ++i)
    {
        if(evt.cb[i]) evt.cb[i](data);
    }
}

bool EventSystem::subscribe(EventId id, EventCallback cb)
{
    int i = 0;
    auto& evt = events[static_cast<unsigned int>(id)];
    while(i < EVT_CB_MAX && (evt.cb[i] != nullptr)) ++i;
    if(i < EVT_CB_MAX)
    {
        evt.cb[i] = cb;
        return true;
    } 
    return false;
}

bool EventSystem::unsubscribe(EventId id, EventCallback cb)
{
    int i = 0;
    auto& evt = events[static_cast<unsigned int>(id)];
    while(i < EVT_CB_MAX && (evt.cb[i] != cb)) ++i;
    if(i < EVT_CB_MAX)
    {
        evt.cb[i] = nullptr;
        return true;
    } 
    return false;
}
