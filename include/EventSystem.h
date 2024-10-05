#pragma once
#include <Singleton.h>

typedef void (*EventCallback)(void*);
static constexpr unsigned int EVT_CB_MAX = 8;

enum class EventId
{
    EVENT1,
    EVENT2,
    EVENT_MAX // do not use ! only for internal purposes
};

struct Event
{
    EventId id;
    EventCallback cb[EVT_CB_MAX];
};

class EventSystem : public Singleton<EventSystem>
{
public:
    EventSystem();
    void init();
    void emit(EventId id, void* data);
    bool subscribe(EventId id, EventCallback cb);
    bool unsubscribe(EventId id, EventCallback cb);
private:
    Event events[static_cast<unsigned int>(EventId::EVENT_MAX)];
};