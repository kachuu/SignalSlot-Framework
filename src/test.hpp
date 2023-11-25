#pragma once

#include "sigSlt.hpp"

class MyClass
{
public:
    MyClass(int v) : v(v) {}
    int v;
};

class R1
{
public:
    void slot_2param(int p1, string &p2) {
        printf("R1::%s(%d, %s)\n", __FUNCTION__, p1, p2.c_str());
    }
    void slot_3param(int p1, string &p2, MyClass &p3) {
        printf("R1::%s(%d, %s, %d)\n", __FUNCTION__, p1, p2.c_str(), p3.v);
    }
};

class R2
{
public:
    void slot_2param(int p1, string &p2) {
        printf("R2::%s(%d, %s)\n", __FUNCTION__, p1, p2.c_str());
    }
    void slot_3param(int p1, string &p2, MyClass &p3) {
        printf("R2::%s(%d, %s, %d)\n", __FUNCTION__, p1, p2.c_str(), p3.v);
    }
};

class S1
{
public:
    TSignal<int, string&> signal_2param;
    TSignal<int, string&, MyClass&> signal_3param;
};

class S2
{
public:
    TSignal<int, string&> signal_2param;
    TSignal<int, string&, MyClass&> signal_3param;
};

class SR
{
public:
    TSignal<int, string&> signal_2param;
    TSignal<int, string&, MyClass&> signal_3param;
    void slot_2param(int p1, string &p2) {
        printf("SR::%s(%d, %s)\n", __FUNCTION__, p1, p2.c_str());
        string sp = p2 + "B";
        signal_2param(p1 + 1, sp);
    }
    void slot_3param(int p1, string &p2, MyClass &p3) {
        printf("SR::%s(%d, %s, %d)\n", __FUNCTION__, p1, p2.c_str(), p3.v);
        string sp = p2 + "B";
        p3.v += 1;
        signal_3param(p1 + 1, sp, p3);
    }
};
