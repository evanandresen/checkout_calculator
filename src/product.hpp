#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using std::string;

struct product{
    int barcode;
    string name;
    float price;
    bool BTGO; //buy two get one sale
    string bulkSale; //uses keyword for sale

    bool operator==(const product& other) const {
        return barcode == other.barcode;
    }

    bool operator<(const product& other) const {
        return barcode < other.barcode;
    }

} ;

namespace std {
    template <>
    struct hash<product> {
        size_t operator()(const product& p) const {
            return hash<int>()(p.barcode) ^ hash<std::string>()(p.name);
        }
    };
}

#endif