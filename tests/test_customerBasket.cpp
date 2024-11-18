#include <gtest/gtest.h>
#include "../src/customerBasket.hpp"
#include "../src/product.hpp"


TEST(BasketTest, EmptyBasket){
    std::unordered_map<int, struct product> productList;
    customerBasket myBasket = customerBasket(productList);
    EXPECT_EQ(myBasket.calculateTotal(),0.0);
}

TEST(BasketTest, addToBasket){
    std::unordered_map<int, struct product> productList;
    product myProduct = {123321,"Pear",1.99,false,""};
    productList[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productList);
    EXPECT_TRUE(myBasket.addToBasket(123321,1));
}

TEST(BasketTest, ClearBasket){
    std::unordered_map<int, struct product> productList;
    product myProduct = {123321,"Pear",1.99,false,""};
    productList[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productList);
    myBasket.addToBasket(123321,1);
    EXPECT_FLOAT_EQ(myBasket.calculateTotal(),1.99);
    myBasket.emptyBasket();
    EXPECT_FLOAT_EQ(myBasket.calculateTotal(),0.);
}

TEST(BasketTest, TotalFromOneProduct){
    std::unordered_map<int, struct product> productList;
    product myProduct = {123321,"Pear",1.99,false,""};
    productList[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productList);
    myBasket.addToBasket(123321,1);
    EXPECT_FLOAT_EQ(myBasket.calculateTotal(),1.99);
}

TEST(BasketTest, BarcodeNotInCatalog){
    std::unordered_map<int, struct product> productList;
    product myProduct = {123321,"Pear",1.99,false,""};
    productList[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productList);
    EXPECT_FALSE(myBasket.addToBasket(1233213,1));
}

TEST(BasketTest, TotalFromBTGO){
    std::unordered_map<int, struct product> productList;
    product myProduct = {123321,"Pear",1.99,true,""};
    productList[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productList);
    for(int i = 1; i < 7; i++){
        EXPECT_TRUE(myBasket.addToBasket(123321,1));
        EXPECT_FLOAT_EQ(myBasket.calculateTotal(),1.99*(i-(i/3))) << "\nWhen i=" << i << std::endl;
    }
}

TEST(BasketTest, TotalFromSales){
    std::unordered_map<int, struct product> productList;
    product product_pear = {123321,"Pear",2,false,"Fruit"};
    product product_apple = {123322,"Apple",3,false,"Fruit"};
    product product_grape = {123323,"Grape",4,false,"Fruit"};
    productList[product_apple.barcode] = product_apple;
    productList[product_pear.barcode] = product_pear;
    productList[product_grape.barcode] = product_grape;
    customerBasket myBasket = customerBasket(productList);
    myBasket.addToBasket(123322,1);
    myBasket.addToBasket(123321,1);
    EXPECT_FLOAT_EQ(myBasket.calculateTotal(),5.);
    myBasket.addToBasket(123323,1);
    EXPECT_FLOAT_EQ(myBasket.calculateTotal(),7.);
}

TEST(BasketTest, TwoLineItems){
    std::unordered_map<int, struct product> productList;
    std::vector<lineItem> itemList;
    product product_pear = {123321,"Pear",2,false,"Fruit"};
    product product_apple = {123322,"Apple",3,false,""};
    productList[product_apple.barcode] = product_apple;
    productList[product_pear.barcode] = product_pear;
    customerBasket myBasket = customerBasket(productList);
    myBasket.addToBasket(123321,1);
    itemList = myBasket.returnItemList();
    EXPECT_EQ(itemList.size(),1);
    myBasket.addToBasket(123322,1);
    itemList.clear();
    itemList = myBasket.returnItemList();
    EXPECT_EQ(itemList.size(),2);

}
