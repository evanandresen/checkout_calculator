#include "customerBasket.hpp"
#include "lineItem.hpp"

#include <algorithm>
#include <unordered_map>



void customerBasket::noteSaleItem(string saleName, float productPrice, int quantity){
    if(!bulkSalePrices.contains(saleName))
        bulkSalePrices[saleName] = std::vector<float>();
    for(int i=0; i < quantity; i++){
        bulkSalePrices[saleName].push_back(productPrice);
    }
}

customerBasket::customerBasket(std::unordered_map<int, product> &productInfo){
    this->productList = productInfo;
    emptyBasket();
}

bool customerBasket::addToBasket(int barcode, int quantity){
    if(!productList.contains(barcode) || quantity<1) return false;    
    if(basketQuantites.contains(barcode))
        basketQuantites[barcode] += quantity;
    else
        basketQuantites[barcode] = quantity;
    if(!productList[barcode].bulkSale.empty())
        noteSaleItem(productList[barcode].bulkSale, productList[barcode].price, quantity);
    return true;
}

float customerBasket::calculateTotal(){
    float total = 0;
    for(auto& productQuantity : basketQuantites){
        total += productList[productQuantity.first].price * productQuantity.second;
        if(productList[productQuantity.first].BTGO){
            total -= productList[productQuantity.first].price * (productQuantity.second / 3); //apply BTGO deal
        }
    }
    for(auto& sale : bulkSalePrices){
        std::sort(sale.second.begin(), sale.second.end());
        float saleTotal = 0;
        for(int i=0; i<(int)(sale.second.size()/3); i++){                    //remove every third of cheapest within deal
            saleTotal -= sale.second[i];
        }
        total += saleTotal; 
    }
    return total;
}

void customerBasket::emptyBasket(){
    basketQuantites.clear();
    bulkSalePrices.clear();
}

std::vector<lineItem> customerBasket::returnItemList(){
    std::vector<lineItem> itemList;
    for(auto& productQuantity : basketQuantites){
        lineItem nextItem = {productList[productQuantity.first].name,
                            productQuantity.second,
                            productList[productQuantity.first].price * productQuantity.second,
                            productList[productQuantity.first].bulkSale};
        itemList.push_back(nextItem);

        if(productList[productQuantity.first].BTGO && productQuantity.second >= 3){
            lineItem nextItem = {"BTGO " + productList[productQuantity.first].name,
                    productQuantity.second / 3,
                    productList[productQuantity.first].price * (productQuantity.second / -3),
                    ""};
            itemList.push_back(nextItem);           
        }
    }
    for(auto& sale : bulkSalePrices){
        std::sort(sale.second.begin(), sale.second.end());
        float saleTotal = 0;
        for(int i=0; i<(int)(sale.second.size()/3); i++){
            saleTotal -= sale.second[i];
        }
        if(sale.second.size() >= 3){
            lineItem nextItem = {"PROMO " + sale.first,
                    (int)(sale.second.size()) / 3,
                    saleTotal,
                    ""};
            itemList.push_back(nextItem);
        }

    }
    return itemList;
}

string customerBasket::returnProductName(int barcode){
    if(productList.contains(barcode))
        return productList[barcode].name;
    return "";
}

bool customerBasket::isProductAvailable(int barcode){
    return productList.contains(barcode);
}