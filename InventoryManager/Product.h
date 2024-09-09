#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productID;
    std::string productName;
    int quantity;
    float price;
public:
  Product();
  int getProductID();
  std::string getProductName();
  int getQuantity();
  float getPrice();
  void setQuantity(int newQuantity);
  void setPrice(float newPrice);
  void setProductID(int newID);
  void setProductName(std::string newName);

};

#endif