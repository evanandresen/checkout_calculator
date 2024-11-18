#include <iostream>
#include "product.hpp"
#include "lineItem.hpp"
#include "productDatabase.hpp"
#include "customerBasket.hpp"
#include "UI.hpp"
#include "printer.hpp"
#include <unordered_map>
#include <vector>
#include <string>


//Input cin, productDatabase, cout
int main(int argc, char *argv[]){

    std::string catalogPath = (argc == 1) ? "./productCatalog.csv" : argv[1];
    std::cout << "Using \"" << catalogPath << "\" catalog" << std::endl;


    productDatabase db = productDatabase(catalogPath);
    std::unordered_map<int, product> productList = db.returnProductList();

    customerBasket myBasket = customerBasket(productList);

    UI UI_loop = UI(myBasket);
    UI_loop.runLoop();     

    printer myPrinter(myBasket.returnItemList(), myBasket.calculateTotal());

    return 0;
}