#ifndef LINEITEM_H
#define LINEITEM_H

#include <string>

using std::string;

struct lineItem{
    string name;
    int quantity;
    float totalPrice;
    string bulkSale;
    
};

#endif