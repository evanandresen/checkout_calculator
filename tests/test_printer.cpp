#include <gtest/gtest.h>
#include "../src/printer.hpp"
#include "../src/lineItem.hpp"

#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;

TEST(PrinterTest, NOTTESTOutputReceipt){
    float total = 0.00;
    std::vector<lineItem> receiptList;
    receiptList.push_back(lineItem("Pear", 4, -100.99,"Fruit"));
    receiptList.push_back(lineItem("Apple", 2, 4.23,"Fruit"));
    receiptList.push_back(lineItem("Grapes", 1, 1.49,""));
    EXPECT_NO_THROW(printer myPrinter(receiptList, total));
}

TEST(PrinterTest, WorkingConstructor){
    std::stringstream redirectOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(redirectOutput.rdbuf());

    float total = 0;
    std::vector<lineItem> receiptList;
    EXPECT_NO_THROW(printer myPrinter(receiptList, total));

    std::cout.rdbuf(originalCoutBuffer);
}

TEST(PrinterTest, PrintsAnything){
    std::stringstream redirectOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(redirectOutput.rdbuf());

    float total = 0;
    std::vector<lineItem> receiptList;
    printer myPrinter(receiptList, total);
    string receiptLine;
    EXPECT_TRUE(std::getline(redirectOutput, receiptLine));

    std::cout.rdbuf(originalCoutBuffer);
}

TEST(PrinterTest, ShowHeader){
    std::stringstream redirectOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(redirectOutput.rdbuf());

    float total = 0;
    std::vector<lineItem> receiptList;
    printer myPrinter(receiptList, total);
    string receiptLine;
    std::getline(redirectOutput, receiptLine);
    EXPECT_EQ(0, receiptLine.size());    
    std::getline(redirectOutput, receiptLine);
    EXPECT_EQ(TOTAL_WIDTH, receiptLine.size());
    EXPECT_NE(receiptLine.find("SUPERMARKET"), string::npos);

    std::cout.rdbuf(originalCoutBuffer);
}

TEST(PrinterTest, MaxWidth){
    std::stringstream redirectOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(redirectOutput.rdbuf());

    float total = 0;
    std::vector<lineItem> receiptList;
    receiptList.push_back(lineItem("Pear", 4, 1.99,"Fruit"));
    printer myPrinter(receiptList, total);
    string receiptLine;
    while(std::getline(redirectOutput, receiptLine)){
        EXPECT_LE(receiptLine.size(), TOTAL_WIDTH) << "*Make clean for #defines to reset*";
    }
    std::cout.rdbuf(originalCoutBuffer);
}

TEST(PrinterTest, PrintItem){
    std::stringstream redirectOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(redirectOutput.rdbuf());

    float total = 0.00;
    std::vector<lineItem> receiptList;
    receiptList.push_back(lineItem("Pear", 4, 1.99,"Fruit"));
    EXPECT_NO_THROW(printer myPrinter(receiptList, total));
    bool foundName=false, foundCNT=false, foundPrice=false, foundSale=false;
    string receiptLine;
    while(std::getline(redirectOutput, receiptLine)){
        if(receiptLine.find("Pear") != string::npos)
            foundName=true;
        if(receiptLine.find("4") != string::npos)
            foundCNT=true;
        if(receiptLine.find("1.99") != string::npos)
            foundPrice=true;
        if(receiptLine.find("Fruit") != string::npos)
            foundSale=true;
    }
    EXPECT_TRUE(foundName);
    EXPECT_TRUE(foundCNT);
    EXPECT_TRUE(foundPrice);
    EXPECT_TRUE(foundSale);

    std::cout.rdbuf(originalCoutBuffer);
}
