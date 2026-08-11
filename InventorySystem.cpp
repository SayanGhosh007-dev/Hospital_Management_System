#include <iostream>
#include <string>
#include <vector>

using namespace std;

class inventorysystem
{
    private:
        int itemId;
        int quantity;
        int minimumStock;
        double price;
        string itemName;
        string category;
        string supplierName;
        string supplierContact;
        string batchNumber;
        string manufacturingDate;
        string expiryDate;
        string storageLocation;

    public:
        inventorysystem();
        void addItem();
        void updateItem();
        void deleteItem();
        void searchItem();
        void addStock();
        void removeStock();
        void checkStock();
        void checkLowStock();
        void checkExpiry();
        void displayItemDetails();
};

// Constructor
inventorysystem::inventorysystem()
{
    itemId = 1;
    itemName = "";
    category = "";

    quantity = 0;
    minimumStock = 0;

    price = 0.0;

    supplierName = "";
    supplierContact = "";

    batchNumber = "";
    manufacturingDate = "";
    expiryDate = "";

    storageLocation = "";
}

// Add Item
void inventorysystem::addItem()
{
    cout << "\n===== ADD INVENTORY ITEM =====\n";

    cout << "Enter Item ID: ";
    cin >> itemId;
    cin.ignore();

    cout << "Enter Item Name: ";
    getline(cin, itemName);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Minimum Stock Level: ";
    cin >> minimumStock;

    cout << "Enter Price: ";
    cin >> price;
    cin.ignore();

    cout << "Enter Supplier Name: ";
    getline(cin, supplierName);

    cout << "Enter Supplier Contact: ";
    getline(cin, supplierContact);

    cout << "Enter Batch Number: ";
    getline(cin, batchNumber);

    cout << "Enter Manufacturing Date: ";
    getline(cin, manufacturingDate);

    cout << "Enter Expiry Date: ";
    getline(cin, expiryDate);

    cout << "Enter Storage Location: ";
    getline(cin, storageLocation);

    cout << "\nItem added successfully.\n";
}

// Update Item
void inventorysystem::updateItem()
{
    cout << "\n===== UPDATE INVENTORY ITEM =====\n";

    if (itemId == 0)
    {
        cout << "No item available to update.\n";
        return;
    }

    cin.ignore();

    cout << "Enter New Item Name: ";
    getline(cin, itemName);

    cout << "Enter New Category: ";
    getline(cin, category);

    cout << "Enter New Minimum Stock Level: ";
    cin >> minimumStock;

    cout << "Enter New Price: ";
    cin >> price;
    cin.ignore();

    cout << "Enter New Supplier Name: ";
    getline(cin, supplierName);

    cout << "Enter New Supplier Contact: ";
    getline(cin, supplierContact);

    cout << "Enter New Storage Location: ";
    getline(cin, storageLocation);

    cout << "\nItem updated successfully.\n";
}

// Delete Item
void inventorysystem::deleteItem()
{
    cout << "\n===== DELETE INVENTORY ITEM =====\n";

    if (itemId == 0)
    {
        cout << "No item available to delete.\n";
        return;
    }

    char choice;

    cout << "Are you sure you want to delete this item? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        itemId = 0;
        itemName = "";
        category = "";

        quantity = 0;
        minimumStock = 0;

        price = 0.0;

        supplierName = "";
        supplierContact = "";

        batchNumber = "";
        manufacturingDate = "";
        expiryDate = "";

        storageLocation = "";

        cout << "Item deleted successfully.\n";
    }
    else
    {
        cout << "Delete operation cancelled.\n";
    }
}

// Search Item
void inventorysystem::searchItem()
{
    cout << "\n===== SEARCH INVENTORY ITEM =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    int searchId;

    cout << "Enter Item ID to search: ";
    cin >> searchId;

    if (searchId == itemId)
    {
        cout << "\nItem found successfully.\n";
        displayItemDetails();
    }
    else
    {
        cout << "Item not found.\n";
    }
}

// Add Stock
void inventorysystem::addStock()
{
    cout << "\n===== ADD STOCK =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    int stock;

    cout << "Current Stock: " << quantity << endl;

    cout << "Enter quantity to add: ";
    cin >> stock;

    if (stock <= 0)
    {
        cout << "Invalid quantity.\n";
        return;
    }

    quantity += stock;

    cout << "Stock added successfully.\n";
    cout << "Updated Stock: " << quantity << endl;
}

// Remove Stock
void inventorysystem::removeStock()
{
    cout << "\n===== REMOVE STOCK =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    int stock;

    cout << "Current Stock: " << quantity << endl;

    cout << "Enter quantity to remove: ";
    cin >> stock;

    if (stock <= 0)
    {
        cout << "Invalid quantity.\n";
        return;
    }

    if (stock > quantity)
    {
        cout << "Insufficient stock available.\n";
        return;
    }

    quantity -= stock;

    cout << "Stock removed successfully.\n";
    cout << "Remaining Stock: " << quantity << endl;
}

// Check Stock
void inventorysystem::checkStock()
{
    cout << "\n===== STOCK STATUS =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    cout << "Item Name: " << itemName << endl;
    cout << "Current Quantity: " << quantity << endl;
    cout << "Minimum Stock Level: " << minimumStock << endl;

    if (quantity == 0)
    {
        cout << "Status: OUT OF STOCK\n";
    }
    else if (quantity <= minimumStock)
    {
        cout << "Status: LOW STOCK\n";
    }
    else
    {
        cout << "Status: STOCK AVAILABLE\n";
    }
}

// Check Low Stock
void inventorysystem::checkLowStock()
{
    cout << "\n===== LOW STOCK CHECK =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    if (quantity <= minimumStock)
    {
        cout << "WARNING: Item is low in stock.\n";
        cout << "Item Name: " << itemName << endl;
        cout << "Current Quantity: " << quantity << endl;
        cout << "Minimum Required: " << minimumStock << endl;
    }
    else
    {
        cout << "Stock level is sufficient.\n";
    }
}

// Check Expiry
void inventorysystem::checkExpiry()
{
    cout << "\n===== EXPIRY CHECK =====\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    cout << "Item Name: " << itemName << endl;
    cout << "Batch Number: " << batchNumber << endl;
    cout << "Manufacturing Date: " << manufacturingDate << endl;
    cout << "Expiry Date: " << expiryDate << endl;

    cout << "\nExpiry date should be verified against the current date.\n";
    cout << "Expiry Date: " << expiryDate << endl;
}

// Display Item Details
void inventorysystem::displayItemDetails()
{
    cout << "\n========== INVENTORY ITEM DETAILS ==========\n";

    if (itemId == 0)
    {
        cout << "No item available.\n";
        return;
    }

    cout << "Item ID              : " << itemId << endl;
    cout << "Item Name            : " << itemName << endl;
    cout << "Category             : " << category << endl;
    cout << "Quantity             : " << quantity << endl;
    cout << "Minimum Stock        : " << minimumStock << endl;
    cout << "Price                : " << price << endl;

    cout << "Supplier Name        : " << supplierName << endl;
    cout << "Supplier Contact     : " << supplierContact << endl;

    cout << "Batch Number         : " << batchNumber << endl;
    cout << "Manufacturing Date   : " << manufacturingDate << endl;
    cout << "Expiry Date          : " << expiryDate << endl;

    cout << "Storage Location     : " << storageLocation << endl;

    cout << "============================================\n";
}