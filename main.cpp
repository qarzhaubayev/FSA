#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

enum State {
    IDLE,
    WAITING_FOR_OBJECT,
    DISPENSING
};

struct Product {
    string name;
    int price;
    int quantity;  // Added quantity field.
};

class VendingMachine {
private:
    unordered_map<int, Product> products;
    int balance;
    State state;
    const string ADMIN_PASSWORD = "admin123"; // Admin password

    // Private method to authenticate admin.
    bool authenticateAdmin() {
        string password;
        cout << "Enter admin password: ";
        cin >> password;
        if (password == ADMIN_PASSWORD) {
            return true;
        } else {
            cout << "Authentication failed. Access denied.\n";
            return false;
        }
    }

public:
    VendingMachine() {
        balance = 0;
        state = IDLE;

        // Initialize products with a default quantity.
        products[1] = {"Chips", 10, 10};
        products[2] = {"Soda", 15, 10};
        products[3] = {"Chocolate", 20, 10};
    }

    // Accept only coins of 200, 500, or 1000.
    void insertCoin(int money) {
        if (money != 200 && money != 500 && money != 1000) {
            cout << "Cannot detect required tenge. Only 200, 500, or 1000 are accepted.\n";
            return;
        }
        balance += money;
        state = WAITING_FOR_OBJECT;
        cout << "Inserted " << money << " tenge(s). Current balance: " << balance << " tenge.\n";
    }

    // Displays the product code, name, price, and quantity.
    void showProducts() {
        cout << "\n---- Products Available ----\n";
        for (const auto& p : products) {
            cout << p.first << ": " << p.second.name 
                 << " (" << p.second.price << " tenge) - Quantity: " 
                 << p.second.quantity << "\n";
        }
    }

    // Select and vend a product if available and balance is enough.
    void selectProduct(int code) {
        if (products.find(code) == products.end()) {
            cout << "Invalid product selection.\n";
            return;
        }

        // Check if product is in stock.
        if (products[code].quantity <= 0) {
            cout << "Product " << products[code].name << " is out of stock.\n";
            return;
        }

        Product p = products[code];
        if (balance >= p.price) {
            balance -= p.price;
            cout << "Dispensing " << p.name << ".\n";
            // Decrease the product's quantity.
            products[code].quantity--;
            if (balance > 0) {
                cout << "Returning change: " << balance << " tenge.\n";
            }
            reset();
        } else {
            cout << "Insufficient balance. " << p.name << " costs " << p.price << " tenge.\n";
        }
    }

    // Allows admin to add or update a product after successful authentication.
    void adminAddProduct() {
        if (!authenticateAdmin()) {
            return; // Abort if authentication fails.
        }

        int code;
        cout << "Enter product code (integer): ";
        cin >> code;
        // Check if product exists.
        if (products.find(code) != products.end()) {
            cout << "Product already exists. It will be updated.\n";
        }

        // Read new product details.
        string name;
        cout << "Enter product name: ";
        cin.ignore(); // Discard any newline leftover.
        getline(cin, name);

        int price;
        cout << "Enter price (tenge): ";
        cin >> price;

        int quantity;
        cout << "Enter quantity: ";
        cin >> quantity;

        products[code] = {name, price, quantity};
        cout << "Product added/updated successfully!\n";
    }

    void reset() {
        balance = 0;
        state = IDLE;
        cout << "Machine reset. Ready for next user.\n";
    }

    int getBalance() const {
        return balance;
    }
};

int main() {
    VendingMachine vm;
    int choice;

    while (true) {
        cout << "\n1. Insert Coin\n2. Show Products\n3. Buy Product\n4. Add/Update Product (Admin)\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                int coin;
                cout << "Enter coin (200, 500, or 1000): ";
                cin >> coin;
                vm.insertCoin(coin);
                break;
            }
            case 2:
                vm.showProducts();
                break;
            case 3: {
                vm.showProducts();
                int code;
                cout << "Enter product code: ";
                cin >> code;
                vm.selectProduct(code);
                break;
            }
            case 4:
                vm.adminAddProduct();
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
