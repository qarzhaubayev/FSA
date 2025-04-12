#include "VendingMachine.hpp"

// ------------------ ctor ------------------
VendingMachine::VendingMachine() {
    products_[1] = {"Chips",     10, 10};
    products_[2] = {"Soda",      15, 10};
    products_[3] = {"Chocolate", 20, 10};
}

// ------------------ private ----------------
bool VendingMachine::authenticateAdmin() {
    std::string password;
    std::cout << "Enter admin password: ";
    std::cin  >> password;
    if (password == ADMIN_PASSWORD) return true;

    std::cout << "Authentication failed. Access denied.\n";
    return false;
}

// ------------------ public -----------------
void VendingMachine::insertCoin(int money) {
    if (money != 200 && money != 500 && money != 1000) {
        std::cout << "Cannot detect required tenge. "
                  << "Only 200, 500, or 1000 are accepted.\n";
        return;
    }
    balance_ += money;
    state_ = State::WAITING_FOR_OBJECT;
    std::cout << "Inserted " << money
              << " tenge(s). Current balance: " << balance_ << " tenge.\n";
}

void VendingMachine::showProducts() {
    std::cout << "\n---- Products Available ----\n";
    for (const auto& [code, p] : products_) {
        std::cout << code << ": " << p.name
                  << " (" << p.price << " tenge) - Quantity: "
                  << p.quantity << '\n';
    }
}

void VendingMachine::selectProduct(int code) {
    if (products_.find(code) == products_.end()) {   // C++17‑compatible
        std::cout << "Invalid product selection.\n";
        return;
    }
    auto& prod = products_[code];
    if (prod.quantity <= 0) {
        std::cout << "Product " << prod.name << " is out of stock.\n";
        return;
    }
    if (balance_ < prod.price) {
        std::cout << "Insufficient balance. "
                  << prod.name << " costs " << prod.price << " tenge.\n";
        return;
    }
    balance_ -= prod.price;
    --prod.quantity;
    std::cout << "Dispensing " << prod.name << ".\n";
    if (balance_ > 0) std::cout << "Returning change: "
                                << balance_ << " tenge.\n";
    reset();
}

void VendingMachine::adminAddProduct() {
    if (!authenticateAdmin()) return;

    int code;
    std::cout << "Enter product code (integer): ";
    std::cin  >> code;

    if (products_.find(code) != products_.end())
    std::cout << "Product already exists. It will be updated.\n";
    
    std::string name;
    std::cout << "Enter product name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    int price, quantity;
    std::cout << "Enter price (tenge): ";
    std::cin  >> price;
    std::cout << "Enter quantity: ";
    std::cin  >> quantity;

    products_[code] = {name, price, quantity};
    std::cout << "Product added/updated successfully!\n";
}

void VendingMachine::reset() {
    balance_ = 0;
    state_   = State::IDLE;
    std::cout << "Machine reset. Ready for next user.\n";
}

int VendingMachine::getBalance() const { return balance_; }
