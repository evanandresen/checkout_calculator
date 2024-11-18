#include "UI.hpp"
#include "lineItem.hpp"
#include "customerBasket.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;


UI::UI(customerBasket &myBasket) : myBasket(myBasket){
}

void UI::runLoop(){
    letLoopRun = true;
    while(letLoopRun){
        int barcode, quantity;
        bool badInput = false;

        string inputLine = "";
        cout << "Enter barcode (Press enter to end transaction): ";
        std::getline(cin, inputLine);
        if(inputLine == ""){
            letLoopRun = false;
            break;
        }
        try{
            barcode = std::stoi(inputLine);
        }
        catch(...){
            cout << "Bad barcode" << endl;
            badInput = true;
        }
        if(!myBasket.isProductAvailable(barcode)){
            cout << "Product not available" << endl;
            badInput = true;
        }
        if(!badInput){
            cout << "Enter quantity: ";
            std::getline(cin, inputLine);
            try{
                quantity = std::stoi(inputLine);
                if(quantity<1) {
                    cout << "Invalid quantity" << endl;
                    badInput = true;
                }
            }
            catch(...){
                cout << "Invalid quantity" << endl;
                badInput = true;
            }
        }
        if(!badInput){
            if(!myBasket.addToBasket(barcode,quantity))
                cout << "Product not found" << endl;
            else
                cout << "Added " << quantity << " " << myBasket.returnProductName(barcode) << endl;
        }
    }
}

void UI::killLoop(){
    letLoopRun = false;
}


