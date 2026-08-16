#include <iostream>
#include <string>
#include <limits>

using namespace std;

class InventoryItem {
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
    InventoryItem();
    InventoryItem(int id, const string& name, const string& cat, int qty, int minStock, double pr,
                  const string& supName, const string& supContact, const string& batch,
                  const string& mfg, const string& exp, const string& loc);

    // Getters
    int getItemId() const;
    int getQuantity() const;
    int getMinimumStock() const;
    double getPrice() const;
    string getItemName() const;
    string getCategory() const;
    string getSupplierName() const;
    string getSupplierContact() const;
    string getBatchNumber() const;
    string getManufacturingDate() const;
    string getExpiryDate() const;
    string getStorageLocation() const;

    // Setters
    void setItemId(int id);
    void setQuantity(int qty);
    void setMinimumStock(int minStock);
    void setPrice(double pr);
    void setItemName(const string& name);
    void setCategory(const string& cat);
    void setSupplierName(const string& supName);
    void setSupplierContact(const string& supContact);
    void setBatchNumber(const string& batch);
    void setManufacturingDate(const string& mfg);
    void setExpiryDate(const string& exp);
    void setStorageLocation(const string& loc);

    // Operations
    void addStock(int qty);
    bool removeStock(int qty);
    bool isLowStock() const;
    bool isOutOfStock() const;

    // Console Interactive Operations (kept for compatibility)
    void addItem();
    void updateItem();
    void deleteItem();
    void searchItem();
    void addStock();
    void removeStock();
    void checkStock() const;
    void checkLowStock() const;
    void checkExpiry() const;
    void displayItemDetails() const;
};

static double inv_getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0.0) {
                return value;
            }
            cout << "Value cannot be negative. Please try again.\n";
        } else {
            cout << "Invalid numeric input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static int inv_getValidInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0) {
                return value;
            }
            cout << "Value cannot be negative. Please try again.\n";
        } else {
            cout << "Invalid numeric input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static string inv_getNonEmptyString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input cannot be empty. Please try again.\n";
    }
}

InventoryItem::InventoryItem()
    : itemId(0), quantity(0), minimumStock(0), price(0.0),
      itemName(""), category(""), supplierName(""), supplierContact(""),
      batchNumber(""), manufacturingDate(""), expiryDate(""), storageLocation("") {}

InventoryItem::InventoryItem(int id, const string& name, const string& cat, int qty, int minStock, double pr,
                             const string& supName, const string& supContact, const string& batch,
                             const string& mfg, const string& exp, const string& loc)
    : itemId(id), quantity(qty), minimumStock(minStock), price(pr),
      itemName(name), category(cat), supplierName(supName), supplierContact(supContact),
      batchNumber(batch), manufacturingDate(mfg), expiryDate(exp), storageLocation(loc) {}

int InventoryItem::getItemId() const { return itemId; }
int InventoryItem::getQuantity() const { return quantity; }
int InventoryItem::getMinimumStock() const { return minimumStock; }
double InventoryItem::getPrice() const { return price; }
string InventoryItem::getItemName() const { return itemName; }
string InventoryItem::getCategory() const { return category; }
string InventoryItem::getSupplierName() const { return supplierName; }
string InventoryItem::getSupplierContact() const { return supplierContact; }
string InventoryItem::getBatchNumber() const { return batchNumber; }
string InventoryItem::getManufacturingDate() const { return manufacturingDate; }
string InventoryItem::getExpiryDate() const { return expiryDate; }
string InventoryItem::getStorageLocation() const { return storageLocation; }

void InventoryItem::setItemId(int id) { itemId = id; }
void InventoryItem::setQuantity(int qty) { if (qty >= 0) quantity = qty; }
void InventoryItem::setMinimumStock(int minStock) { if (minStock >= 0) minimumStock = minStock; }
void InventoryItem::setPrice(double pr) { if (pr >= 0.0) price = pr; }
void InventoryItem::setItemName(const string& name) { itemName = name; }
void InventoryItem::setCategory(const string& cat) { category = cat; }
void InventoryItem::setSupplierName(const string& supName) { supplierName = supName; }
void InventoryItem::setSupplierContact(const string& supContact) { supplierContact = supContact; }
void InventoryItem::setBatchNumber(const string& batch) { batchNumber = batch; }
void InventoryItem::setManufacturingDate(const string& mfg) { manufacturingDate = mfg; }
void InventoryItem::setExpiryDate(const string& exp) { expiryDate = exp; }
void InventoryItem::setStorageLocation(const string& loc) { storageLocation = loc; }

void InventoryItem::addStock(int qty) {
    if (qty > 0) {
        quantity += qty;
    }
}

bool InventoryItem::removeStock(int qty) {
    if (qty > 0 && quantity >= qty) {
        quantity -= qty;
        return true;
    }
    return false;
}

bool InventoryItem::isLowStock() const {
    return quantity <= minimumStock;
}

bool InventoryItem::isOutOfStock() const {
    return quantity == 0;
}

void InventoryItem::addItem() {
    cout << "\n===== ADD INVENTORY ITEM =====\n";
    itemId = inv_getValidInteger("Enter Item ID: ");
    itemName = inv_getNonEmptyString("Enter Item Name: ");
    category = inv_getNonEmptyString("Enter Category: ");
    quantity = inv_getValidInteger("Enter Quantity: ");
    minimumStock = inv_getValidInteger("Enter Minimum Stock Level: ");
    price = inv_getValidDouble("Enter Price: ");
    supplierName = inv_getNonEmptyString("Enter Supplier Name: ");
    supplierContact = inv_getNonEmptyString("Enter Supplier Contact: ");
    batchNumber = inv_getNonEmptyString("Enter Batch Number: ");
    manufacturingDate = inv_getNonEmptyString("Enter Manufacturing Date: ");
    expiryDate = inv_getNonEmptyString("Enter Expiry Date: ");
    storageLocation = inv_getNonEmptyString("Enter Storage Location: ");
    cout << "\nItem added successfully.\n";
}

void InventoryItem::updateItem() {
    cout << "\n===== UPDATE INVENTORY ITEM =====\n";
    if (itemId == 0) {
        cout << "No item available to update.\n";
        return;
    }
    itemName = inv_getNonEmptyString("Enter New Item Name: ");
    category = inv_getNonEmptyString("Enter New Category: ");
    minimumStock = inv_getValidInteger("Enter New Minimum Stock Level: ");
    price = inv_getValidDouble("Enter New Price: ");
    supplierName = inv_getNonEmptyString("Enter New Supplier Name: ");
    supplierContact = inv_getNonEmptyString("Enter New Supplier Contact: ");
    storageLocation = inv_getNonEmptyString("Enter New Storage Location: ");
    cout << "\nItem updated successfully.\n";
}

void InventoryItem::deleteItem() {
    cout << "\n===== DELETE INVENTORY ITEM =====\n";
    if (itemId == 0) {
        cout << "No item available to delete.\n";
        return;
    }
    string choice;
    cout << "Are you sure you want to delete this item? (Y/N): ";
    getline(cin, choice);
    if (!choice.empty() && (choice[0] == 'Y' || choice[0] == 'y')) {
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
    } else {
        cout << "Delete operation cancelled.\n";
    }
}

void InventoryItem::searchItem() {
    cout << "\n===== SEARCH INVENTORY ITEM =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    int searchId = inv_getValidInteger("Enter Item ID to search: ");
    if (searchId == itemId) {
        cout << "\nItem found successfully.\n";
        displayItemDetails();
    } else {
        cout << "Item not found.\n";
    }
}

void InventoryItem::addStock() {
    cout << "\n===== ADD STOCK =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    cout << "Current Stock: " << quantity << endl;
    int stock = inv_getValidInteger("Enter quantity to add: ");
    if (stock <= 0) {
        cout << "Invalid quantity.\n";
        return;
    }
    addStock(stock);
    cout << "Stock added successfully.\n";
    cout << "Updated Stock: " << quantity << endl;
}

void InventoryItem::removeStock() {
    cout << "\n===== REMOVE STOCK =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    cout << "Current Stock: " << quantity << endl;
    int stock = inv_getValidInteger("Enter quantity to remove: ");
    if (stock <= 0) {
        cout << "Invalid quantity.\n";
        return;
    }
    if (removeStock(stock)) {
        cout << "Stock removed successfully.\n";
        cout << "Remaining Stock: " << quantity << endl;
    } else {
        cout << "Insufficient stock available.\n";
    }
}

void InventoryItem::checkStock() const {
    cout << "\n===== STOCK STATUS =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    cout << "Item Name: " << itemName << endl;
    cout << "Current Quantity: " << quantity << endl;
    cout << "Minimum Stock Level: " << minimumStock << endl;

    if (isOutOfStock()) {
        cout << "Status: OUT OF STOCK\n";
    } else if (isLowStock()) {
        cout << "Status: LOW STOCK\n";
    } else {
        cout << "Status: STOCK AVAILABLE\n";
    }
}

void InventoryItem::checkLowStock() const {
    cout << "\n===== LOW STOCK CHECK =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    if (isLowStock()) {
        cout << "WARNING: Item is low in stock.\n";
        cout << "Item Name: " << itemName << endl;
        cout << "Current Quantity: " << quantity << endl;
        cout << "Minimum Required: " << minimumStock << endl;
    } else {
        cout << "Stock level is sufficient.\n";
    }
}

void InventoryItem::checkExpiry() const {
    cout << "\n===== EXPIRY CHECK =====\n";
    if (itemId == 0) {
        cout << "No item available.\n";
        return;
    }
    cout << "Item Name: " << itemName << endl;
    cout << "Batch Number: " << batchNumber << endl;
    cout << "Manufacturing Date: " << manufacturingDate << endl;
    cout << "Expiry Date: " << expiryDate << endl;
    cout << "\nExpiry date should be verified against the current date.\n";
}

void InventoryItem::displayItemDetails() const {
    cout << "\n========== INVENTORY ITEM DETAILS ==========\n";
    if (itemId == 0) {
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