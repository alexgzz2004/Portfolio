#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include <fstream>
#include "Product.h"

class InventoryManager {
private:
std::vector<Product> products;
public:
/**
 * @brief Construct a new Inventory Manager object
 * 
 */
InventoryManager();

/**
 * @brief Set the vector of products
 * 
 * @param newProducts 
 */
void setProducts(std::vector<Product> newProducts);

/**
 * @brief Add a new product to the vector of products
 * 
 * @param newProduct 
 */
void addProduct(Product newProduct);

/**
 * @brief Remove a product from the vector of products
 * 
 * @param productID 
 */
void removeProduct(int productID);

/**
 * @brief Update an existing product from the vector of products
 * 
 * @param productID 
 */
void updateProduct(int productID);

/**
 * @brief Place an order using products in the vector and update the vector accordingly
 * 
 */
void placeOrder();

/**
 * @brief Generate a report based on the products in the vector
 * 
 * @param out 
 */
void generateReport(std::ostream& out);
};

#endif