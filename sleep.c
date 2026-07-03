#include "sleep.h"

void sleep(int ms) {
    while (ms > 0) {
        volatile int c = 500000;  
        while (c--) {}
        ms--;
    }
}