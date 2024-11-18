#include "printer.hpp"

#include <iostream>
#include <iomanip>

using std::cout;
using std::setw;
using std::string;
using std::endl;


printer::printer(std::vector<lineItem> itemList, float total){
    printHeader();
    printItems(itemList);
    printTotal(total);
}

void printer::printHeader(){
    string header = centerText("SUPERMARKET", TOTAL_WIDTH);
    cout << endl << setw(TOTAL_WIDTH) << header << endl << endl;
    cout << std::left << setw(NAME_WIDTH) << trunc("ProductName",NAME_WIDTH)
         << std::left << setw(SALE_WIDTH) << trunc("Sale", SALE_WIDTH)
         << std::right << setw(QUANTITY_WIDTH) << trunc("CNT",QUANTITY_WIDTH)
         << std::right << setw(PRICE_WIDTH) << trunc("Price", PRICE_WIDTH)
         << endl
         << setw(TOTAL_WIDTH) << string(TOTAL_WIDTH, '-')
         << endl;
}

string printer::centerText(const string text, int width) {
    int padding = width - text.size();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return std::string(padLeft, ' ') + text + std::string(padRight, ' ');
}

void printer::printItems(std::vector<lineItem> itemList){
    for(auto& item: itemList){
        cout << std::left << setw(NAME_WIDTH) << trunc(item.name, NAME_WIDTH)
        << std::left << setw(SALE_WIDTH) << trunc(item.bulkSale, SALE_WIDTH)
        << std::right << setw(QUANTITY_WIDTH) << item.quantity
        << std::right << setw(PRICE_WIDTH) << std::fixed << std::setprecision(2) << item.totalPrice
        << endl;
    }
}

void printer::printTotal(float total){
    cout << setw(TOTAL_WIDTH) << string(TOTAL_WIDTH, '-')
    << endl
    << std::left << setw(NAME_WIDTH+QUANTITY_WIDTH+SALE_WIDTH) << trunc("Total:", NAME_WIDTH+QUANTITY_WIDTH+SALE_WIDTH)
    << std::right << setw(PRICE_WIDTH) << std::fixed << std::setprecision(2) << total
    << endl;
}

string printer::trunc(const string str, int maxLen){
    return ((int)(str.length()) > maxLen) ? str.substr(0, maxLen) : str;
}