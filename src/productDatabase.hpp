#ifndef PRODUCT_DATABASE_H
#define PRODUCT_DATABASE_H

#include "../src/product.hpp"

#include <string>
#include <fstream>
#include <unordered_map>

class productDatabase{
    
    std::ifstream catalogFile;
    std::unordered_map<int, product> productList;

public:
    productDatabase(std::string catalogPath);
    ~productDatabase();
    std::unordered_map<int, product>  returnProductList();

};


#endif