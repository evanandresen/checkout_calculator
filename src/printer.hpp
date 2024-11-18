#ifndef PRINTER_H
#define PRINTER_H

#include "lineItem.hpp"

#include <vector>

#define NAME_WIDTH 16
#define QUANTITY_WIDTH 5
#define SALE_WIDTH 8
#define PRICE_WIDTH 8
#define TOTAL_WIDTH NAME_WIDTH + QUANTITY_WIDTH + SALE_WIDTH + PRICE_WIDTH

class printer{
    
    void printHeader();
    string centerText(const string text, int width);
    void printItems(std::vector<lineItem> itemList);
    void printTotal(float total);
    string trunc(const string str, int maxLen);

public:
    printer(std::vector<lineItem> itemList, float total);
};

#endif