#include "VendingMachine.hpp"
#include <iostream>

int main() {
    VendingMachine vm;
    int choice {};

    while (true) {
        std::cout << "\n1. Insert Coin\n2. Show Products\n3. Buy Product\n"
                     "4. Add/Update Product (Admin)\n0. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                int coin;
                std::cout << "Enter coin (200, 500, or 1000): ";
                std::cin  >> coin;
                vm.insertCoin(coin);
                break;
            }
            case 2: vm.showProducts(); break;
            case 3: {
                vm.showProducts();
                int code;
                std::cout << "Enter product code: ";
                std::cin  >> code;
                vm.selectProduct(code);
                break;
            }
            case 4: vm.adminAddProduct(); break;
            default: std::cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}
