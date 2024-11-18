#include "productDatabase.hpp"
#include "product.hpp"

#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <sstream>
#include <vector>


productDatabase::productDatabase(string catalogPath){
    productList = std::unordered_map<int, product>();
    catalogFile.open(catalogPath);
    if(!catalogFile.is_open())
        throw std::invalid_argument("No catalog in given path");
    
    string lineItem;
    std::getline(catalogFile, lineItem);
    if(lineItem == "")
        return;

    while (std::getline(catalogFile, lineItem)){
        std::stringstream ss(lineItem);
        string token;
        std::vector<string> productData;
        if(lineItem[0]=='/') continue;

        while (getline(ss, token, ',')) {
            productData.push_back(token);
        }
        product newProduct;
        try{
            newProduct.barcode = stoi(productData[0]);
            newProduct.name = productData[1];
            newProduct.price = std::stof(productData[2]);
            newProduct.bulkSale = productData[3];
            newProduct.BTGO = stoi(productData[4]);
            productList[newProduct.barcode] = newProduct;
        }
        catch(...){
            throw std::invalid_argument("Catalog Data Corrupt");
        }
    }
}

std::unordered_map<int, product> productDatabase::returnProductList(){
    return productList;
}

productDatabase::~productDatabase(){
    catalogFile.close();
}
