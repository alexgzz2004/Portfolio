#include "InventoryManager.h"
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;

InventoryManager::InventoryManager(){
    products = {};
}

void InventoryManager::setProducts(vector<Product> newProducts){
    products = newProducts;
}
void InventoryManager::addProduct(Product newProduct) {
    //Intialize need variables
    int ID;
    string name;
    float price;
    int quantity;
    //Set all the new values for the new product
    cout << "Set an ID for this product: "; cin >> ID; newProduct.setProductID(ID);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Set a name for this product: "; getline(cin, name); newProduct.setProductName(name);
    cout << "Set a price for this product: "; cin >> price; newProduct.setPrice(price);
    cout << "Set the quantity for this product: "; cin >> quantity; newProduct.setQuantity(quantity);
    //Add the new product to the vector that has all the other products
    products.push_back(newProduct);
    cout << endl << newProduct.getProductName() << " has been added to the database." << endl << endl;
}

void InventoryManager::removeProduct(int productID) {
    //Find the product using its ID
    auto it = find_if(products.begin(), products.end(), [productID](Product& product) {
    return product.getProductID() == productID;});
    //Check if the product exists in the vector
    if (it != products.end()) {
        products.erase(it);
        cout << it->getProductName() << " with ID " << productID << " removed successfully." << endl << endl;
    } 
    else {
        cout << it->getProductName() << " with ID " << productID << " not found." << endl << endl;
    }

}

void InventoryManager::updateProduct(int productID) {
    //Find the product using its ID
    auto it = find_if(products.begin(), products.end(), [productID](Product& product) {
            return product.getProductID() == productID;
    });
    int choice;
    int quantity;
    float price;
    cout << "What would you like to update from " << it->getProductName() << " (Enter 1 -> Quantity | 2 -> Price): ";
    cin >> choice;
    //Check what decision the user made
    if (choice == 1){
        cout << "Enter the quantity you would like to add or subtract from " << it->getProductName() << " (enter negative # for subtraction): " ; 
        cin >> quantity;
        //Check if there is enough of the product
        if (it->getQuantity() + quantity < 0){
            cout << endl << "Not enough units. Try again." << endl << endl;
        }
        else{
        it->setQuantity(it->getQuantity() + quantity);
        cout << it->getProductName() << " now has " << it->getQuantity() << " units." << endl << endl;
        }
    }

    else if (choice == 2){
        cout << "Enter the new price of " << it->getProductName() << ": ";
        cin >> price;
        it->setPrice(price);
        cout << it->getProductName() << " now cost " << it->getPrice() << "." << endl << endl;
    }
    
}

void InventoryManager::placeOrder(){
    vector<Product> shoppingCart;
    char choice;
    float totalAmount = 0.0;
    do {
        cout << "Enter the product ID you would like to order: " ;
        int productId;
        cin >> productId; cout << endl;
        //Find the product using its ID
        auto it = find_if(products.begin(), products.end(), [productId](Product& product) {
            return product.getProductID() == productId;
        });
        //Check if the product exists
        if (it != products.end()) {
           if (it->getQuantity() == 0){
            cout << "Product ID" << productId << "out of stock." << endl;
           }
           else{
                //Add product selected to the shopping cart
                shoppingCart.push_back(*it);
                //Subtract 1 from the quantity of the product
                it->setQuantity(it->getQuantity() - 1);
                totalAmount += it->getPrice();
                cout << "Shopping Cart: " << endl;
                for (Product& item : shoppingCart){
                    cout << item.getProductName() << " " << item.getPrice() << endl;
                }
                cout << endl;
           }
        } else {
            cout << "Product ID " << productId << " not found. Please try again." << endl;
        }
        cout << "Do you want to order more products? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    //Display total money spent
    cout << "Total amount spent: $" << totalAmount << endl << endl;
}


void InventoryManager::generateReport(ostream& out) {
  //Print out the report to FinalReport.txt based on the products in the inventory
  for (Product& product : products) {
      out << "Product ID: " << product.getProductID() << endl;
      out << "Product Name: " << product.getProductName() << endl;
      out << "Quantity: " << product.getQuantity() << endl;
      out << "Price: " << product.getPrice() << endl;
      out << "------------------------" << endl;
    }
}