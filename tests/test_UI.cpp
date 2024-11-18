#include <gtest/gtest.h>
#include "../src/UI.hpp"
#include "../src/customerBasket.hpp"
#include "../src/product.hpp"

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <future>
#include <chrono>
#include <thread>

using std::string;



TEST(UItest, CanCreateUI){
    std::unordered_map<int, struct product> productInfo;
    product myProduct = {123321,"Pear",1.99,false,""};
    productInfo[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productInfo);
    EXPECT_NO_THROW({UI myUI = UI(myBasket);});
}

TEST(UItest, ReturnFromUI){
    std::unordered_map<int, struct product> productInfo;
    product myProduct = {123321,"Pear",1.99,false,""};
    productInfo[myProduct.barcode] = myProduct;
    customerBasket myBasket = customerBasket(productInfo);
    UI myUI = UI(myBasket);

    string input = "\n";

    std::istringstream testInput(input);
    std::stringstream testOutput;
    std::streambuf* originalCinBuffer = std::cin.rdbuf();
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cin.rdbuf(testInput.rdbuf());
    std::cout.rdbuf(testOutput.rdbuf());
    
    std::chrono::milliseconds timeout(600);
    auto future = std::async(std::launch::async, &UI::runLoop, &myUI);
    EXPECT_TRUE(future.wait_for(timeout) == std::future_status::ready);
    myUI.killLoop();
    std::cin.rdbuf(originalCinBuffer);
    std::cout.rdbuf(originalCoutBuffer);
}
