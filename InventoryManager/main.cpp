/* CSCI 200: Final Project: Inventory Management System 
 * Author: Alejandro Gonzalez
 * The program performs a series of tasks using data file of products from a retail store
 *  to generate a report, add/remove products, or make an order.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Product.h"
#include "InventoryManager.h"

using namespace std;

int main() {
    vector<Product> products;
    ifstream file("data.txt");
    string line;
    //Read the file
    while (getline(file, line)) {
        istringstream iss(line);
        int productId;
        string productName;
        int quantity;
        float price;
        if (iss >> productId >> productName >> quantity >> price) {
        //Create a new product object with the read values and add to vector
            Product product;
            product.setProductID(productId);
            product.setProductName(productName);
            product.setQuantity(quantity);
            product.setPrice(price);
            products.push_back(product);

        }
    }
    file.close();
    //Create a inventory manager object with the vector created above
    InventoryManager manager;
    manager.setProducts(products);

    //Intialize variables and the output file
    int choice;
    int ID;
    Product newProduct;
    ofstream outputFile("FinalReport.txt");
    if (!outputFile.is_open()) {
                        cerr << "Error: Unable to open the file." << endl;
                        return 1; // Exit with error code
                    }

    //Write the intial report of products into FinalReport.txt
    outputFile << "Intial Report:" << endl;
    outputFile << "--------------------------------------------------" << endl;
    manager.generateReport(outputFile);

    //Loop for Inventory manager
    do {
         cout << "Menu:\n";
         cout << "1. Add Product" << endl;
         cout << "2. Remove Product" << endl;
         cout << "3. Update Product" << endl;
         cout << "4. Generate Report" << endl;
         cout << "5. Place Order" << endl;
         cout << "0. Exit" << endl;;
         cout << "Enter your choice: ";
         cin >> choice; cout << endl;
         switch (choice) {
             case 1:
                //Add product
                manager.addProduct(newProduct);
                break;
             case 2:
                //Remove product
                cout << "Enter the ID of the product you would like to erase from the database: ";
                cin >> ID;
                manager.removeProduct(ID);
                break;
             case 3:
                //Update a product
                cout << "Enter the ID of the product you want to update: "; cin >> ID; cout << endl;
                manager.updateProduct(ID);
                break;
             case 4:
                //Generate a new report
                outputFile << endl << "New Report:" << endl;
                outputFile << "--------------------------------------------------" << endl << endl;
                manager.generateReport(outputFile);
                cout << "Will output in FinalReport.txt file" << endl;
                break;
             case 5:
                //Place an order
                manager.placeOrder();
                break;
             case 0:
                //Exit the inventory manager loop and generate a final report
                 cout << "Exiting..." << endl;
                 cout << "Final report will be in FinalReport.txt file" << endl;
                 outputFile << endl << "Final Report:" << endl;
                 outputFile << "--------------------------------------------------" << endl;
                 manager.generateReport(outputFile);
                 break;
             default:
                 cout << "Invalid choice. Please try again.\n";
         }
     } while (choice != 0);
    //Close the output file
    outputFile.close();
    return 0;
}
