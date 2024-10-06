#pragma once
#include <Singleton.h>

typedef void (*EventCallback)(void*);
static constexpr unsigned int EVT_CB_MAX = 8;

enum class EventId
{
    QUIT,
    KEY_DOWN,
    KEY_UP,
    MOUSE_LEFT,
    MOUSE_RIGHT,
    WINDOW_RESIZED,
    EVENT_MAX // do not change ! only for internal purposes
};

struct Event
{
    EventId id;
    EventCallback cb[EVT_CB_MAX];
    unsigned int cb_counter = 0;
};

class EventSystem : public Singleton<EventSystem>
{
public:
    EventSystem();
    void init();
    void emit(EventId id);
    void emit(EventId id, void* data);
    bool subscribe(EventId id, EventCallback cb);
    bool unsubscribe(EventId id, EventCallback cb);
private:
    Event events[static_cast<unsigned int>(EventId::EVENT_MAX)];
};