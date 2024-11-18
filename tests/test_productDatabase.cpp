#include <gtest/gtest.h>
#include "../src/productDatabase.hpp"
#include "../src/product.hpp"

#include <string>
#include <unordered_map>

using std::string;


TEST(DatabaseTest, OpenFile){
    EXPECT_NO_THROW({productDatabase db("./tests/productCatalog.csv");});

}

TEST(DatabaseTest, ReturnsAnyData){
    productDatabase db = productDatabase("./tests/productCatalog.csv");
    std::unordered_map<int,  product> productList = db.returnProductList();
    EXPECT_TRUE(!productList.empty());
}