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
    for(int i = 0; i < evt.cb_counter; ++i) evt.cb[i](data);
}

bool EventSystem::subscribe(EventId id, EventCallback cb)
{
    if(id == EventId::EVENT_MAX) return false;
    auto& evt = events[static_cast<unsigned int>(id)];
    if(evt.cb_counter < EVT_CB_MAX)
    {
        evt.cb[evt.cb_counter] = cb;
        evt.cb_counter++;
        return true;
    }
    return false;
}

bool EventSystem::unsubscribe(EventId id, EventCallback cb)
{
    if(id == EventId::EVENT_MAX) return false;
    int i = 0;
    auto& evt = events[static_cast<unsigned int>(id)];
    while(i < evt.cb_counter && (evt.cb[i] != cb)) ++i; // search for callback pointer
    if(i < evt.cb_counter) // cb found
    {
        if(i < (evt.cb_counter - 1)) // not last in array
        {
            evt.cb[i] = evt.cb[evt.cb_counter - 1]; // reorder callbacks
            evt.cb[evt.cb_counter - 1] = nullptr;
        }
        else
        {
            evt.cb[i] = nullptr;
        }
        evt.cb_counter--;
        return true;
    }
    return false;
}
