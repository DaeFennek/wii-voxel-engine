#include "eventmanager.h"
#include "../utils/lockguard.h"
#include "../utils/Debug.h"
#include <assert.h>

std::unordered_map<uint32_t, std::vector<IEventListener*>> EventManager::s_eventListeners;
SafeQueue<Event> EventManager::s_eventQueue;

EventManager::EventManager() {}

void EventManager::AddListener(IEventListener *listener, uint32_t eventId)
{
    auto listenerEvent = s_eventListeners.find(eventId);
    if (listenerEvent == s_eventListeners.end())
    {
        s_eventListeners.insert({eventId, {listener}});
    }
    else
    {
        listenerEvent->second.push_back(listener);
    }
}

void EventManager::RemoveListener(IEventListener *listener, uint32_t eventId)
{
    auto listenerEvent = s_eventListeners.find(eventId);
    if (listenerEvent == s_eventListeners.end())
        ERROR("EventManager::RemoveListener: assert failed listenerEvent != s_eventListeners.end()");
    assert(listenerEvent != s_eventListeners.end());
    for (auto listenerEventIt = listenerEvent->second.begin(); listenerEventIt != listenerEvent->second.end(); ++listenerEventIt)
    {
        if ((*listenerEventIt) == listener)
        {
            listenerEvent->second.erase(listenerEventIt);
            return;
        }
    }
}

void EventManager::Dispatch(uint32_t eventId, void* payload)
{
    s_eventQueue.Push({eventId, payload});
}

void EventManager::PullEvents()
{
    // lock whole queue so no other thread can push new events
    lock_guard guard(s_eventQueue.GetMutex());
    while (!s_eventQueue.IsEmpty())
    {
        const Event event = s_eventQueue.Pop();
        auto listenerEvent = s_eventListeners.find(event.ID);
        if (listenerEvent == s_eventListeners.end())
            ERROR("EventManager::PullEvents: assert failed listenerEvent != s_eventListeners.end()");
        assert(listenerEvent != s_eventListeners.end());
        for (IEventListener* listener : listenerEvent->second)
        {
            listener->OnEvent(event);
        }
    }
}