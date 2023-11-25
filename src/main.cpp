#include <iostream>
#include "sigSlt.hpp"
#include "test.hpp"

void test1()
{
    printf("*%s*\n", __FUNCTION__);
    int p1 = 1;
    string p2("A");
    MyClass p3(3);
    S1 s1;
    S2 s2;
    R1 r1;
    R2 r2;

    connect(&s1, signal_2param, &r1, R1::slot_2param);
    connect(&s1, signal_3param, &r1, R1::slot_3param);
    connect(&s1, signal_3param, &r1, R1::slot_3param);

    connect(&s1, signal_3param, &r2, R2::slot_3param);

    connect(&s2, signal_3param, &r1, R1::slot_3param);

    s1.signal_2param(p1, p2);
    s1.signal_3param(p1, p2, p3);
    s2.signal_3param(p1 + 1, p2, p3);
    printf("==============================\n\n");

    printf("=== remove R1 slot_3param()\n");
    disconnect(&s1, signal_3param, &r1);
    s1.signal_2param(p1, p2);
    s1.signal_3param(p1, p2, p3);
    printf("==============================\n\n");

    printf("=== remove R1 all slot_2param()\n");
    disconnect(&s1, signal_2param, 0);
    s1.signal_2param(p1, p2);
    s1.signal_3param(p1, p2, p3);
    printf("==============================\n\n");

    printf("=== append R1 slot_2param()\n");
    connect(&s1, signal_2param, &r1, R1::slot_2param);
    printf("=== remove R2 slot_3param()\n");
    disconnect(&s1, signal_3param, &r2);
    s1.signal_2param(p1, p2);
    s1.signal_3param(p1, p2, p3);
    printf("==============================\n\n");
}

void test2()
{
    printf("*%s*\n", __FUNCTION__);
    int p1 = 1;
    string p2("A");
    MyClass p3(3);
    S1 s1;
    SR sr;
    R1 r1;

    printf("=== connect S1 signal -> SR slot/signal -> R1 slot\n");
    connect(&s1, signal_3param, &sr, SR::slot_3param);
    connect(&sr, signal_3param, &r1, R1::slot_3param);
    s1.signal_3param(p1, p2, p3);
    printf("==============================\n\n");
}

int main(int argc, char *argv[])
{
    test1();
    test2();
    return 0;
}
