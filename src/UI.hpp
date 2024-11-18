#ifndef UI_H
#define UI_H

#include "lineItem.hpp"
#include "customerBasket.hpp"

#include <vector>

class UI{

    customerBasket& myBasket;
    bool letLoopRun = false;


public:
    UI(customerBasket &myBasket);
    void runLoop();
    void killLoop();
};


#endif