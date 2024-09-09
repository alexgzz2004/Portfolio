 #include "Product.h"
 using namespace std;

    Product::Product(){
        productID = 0;
        productName = "";
        quantity = 0;
        price = 0;
    }
 
    int Product::getProductID() {
        return productID;
    }
    string Product::getProductName() {
        return productName;
    }
    int Product::getQuantity() {
        return quantity;
    }
    float Product::getPrice() {
        return price;
    }
    void Product::setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void Product::setPrice(float newPrice){
        price = newPrice;
    }

    void Product::setProductID(int newID){
        productID = newID;
    }
    void Product::setProductName(string newName){
        productName = newName;
    }