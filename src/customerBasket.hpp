#ifndef CUSTOMER_BASKET_H
#define CUSTOMER_BASKET_H

#include "product.hpp"
#include "lineItem.hpp"

#include <unordered_map>
#include <vector>
#include <string>

using std::string;

class customerBasket{

    std::unordered_map<int, product> productList;
    std::unordered_map<int, int> basketQuantites;
    std::unordered_map<string, std::vector<float>> bulkSalePrices;  //sale given by string and all prices
    void noteSaleItem(string saleName, float productPrice, int quantity);

public:
    customerBasket(std::unordered_map<int, product> &productInfo);
    float calculateTotal();
    void emptyBasket();
    bool addToBasket(int barcode, int quantity);
    std::vector<lineItem> returnItemList();
    string returnProductName(int barcode);
    bool isProductAvailable(int barcode);

    
};

#endif