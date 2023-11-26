#pragma once

#include <list>

using namespace std;

template <class... Args>
class TSlot
{
public:
    virtual ~TSlot() {};
    virtual void slot(Args... args) = 0;
};

template <class TObject, class... Args>
class TReceiverSlot : public TSlot<Args...>
{
public:
    TReceiverSlot(TObject *obj, void (TObject::*fun)(Args...)) : obj(obj), fun(fun) {}
    void slot(Args... args) {
        (obj->*fun)(args...);
    }
    TObject *obj;
    void (TObject::*fun)(Args...);
};

template <class... Args>
class TSignal
{
public:
    template<class TObject>
    void addSlot(TObject *obj, void (TObject::*fun)(Args...)) {
        m_slots.push_back(make_shared<TReceiverSlot<TObject, Args...>>(obj, fun));
    }
    template<class TObject>
    void removeSlot(TObject *obj) {
        for (auto it = m_slots.begin(); it != m_slots.end();) {
            if (obj != ((TReceiverSlot<TObject, Args...>*)&*(*it))->obj) ++it;
            else it = m_slots.erase(it);
        }
    }
    void removeSlot(void *obj) {
        m_slots.clear();
    }
    void operator()(Args... args) {
        for (shared_ptr<TSlot<Args...>> &obj : m_slots) {
            obj->slot(args...);
        }
    }
private:
    list<shared_ptr<TSlot<Args...>>> m_slots;
};

#define connect(sender, signal, receiver, slot) (sender)->signal.addSlot(receiver, &slot)
#define disconnect(sender, signal, receiver) (sender)->signal.removeSlot(receiver)
