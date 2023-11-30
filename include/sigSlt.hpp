#pragma once

#include <list>

using namespace std;

template <class... TArgs>
class TSlot
{
public:
    virtual ~TSlot() {};
    virtual void slot(TArgs... args) = 0;
};

template <class TObject, class... TArgs>
class TReceiverSlot : public TSlot<TArgs...>
{
public:
    TReceiverSlot(TObject *obj, void (TObject::*fun)(TArgs...)) : obj(obj), fun(fun) {}
    void slot(TArgs... args) {
        (obj->*fun)(args...);
    }
    TObject *obj;
    void (TObject::*fun)(TArgs...);
};

template <class... TArgs>
class TSignal
{
public:
    template<class TObject>
    void addSlot(TObject *obj, void (TObject::*fun)(TArgs...)) {
        m_slots.push_back(make_shared<TReceiverSlot<TObject, TArgs...>>(obj, fun));
    }
    template<class TObject>
    void removeSlot(TObject *obj) {
        for (auto it = m_slots.begin(); it != m_slots.end();) {
            if (obj != ((TReceiverSlot<TObject, TArgs...>*)&*(*it))->obj) ++it;
            else it = m_slots.erase(it);
        }
    }
    void removeSlot(void *obj) {
        m_slots.clear();
    }
    void operator()(TArgs... args) {
        for (shared_ptr<TSlot<TArgs...>> &obj : m_slots) {
            obj->slot(args...);
        }
    }
private:
    list<shared_ptr<TSlot<TArgs...>>> m_slots;
};

#define connect(sender, signal, receiver, slot) (sender)->signal.addSlot(receiver, &slot)
#define disconnect(sender, signal, receiver) (sender)->signal.removeSlot(receiver)
