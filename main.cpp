#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

enum State {
    IDLE,
    WAITING_FOR_OBJECT,
    DISPENSING
};

struct Product{
    string name;
    int price;
};

class VendingMachine{
    private:
        unordered_map<int, Product> products;
        int balance;
        State state;
    
    public:
        VendingMachine(){
            balance = 0;
            state = IDLE;


            // Initialize products
            products[1] = {"Chips", 10};
            products[2] = {"Soda", 15};
            products[3] = {"Chocolate", 20};
        }


        void insertCoin(int money){
            if(money != 200 or money != 500 or money != 1000){
                cout << "Cannot detect required unit. 200, 500 or 1000 can be accepted. \n";
                return;
            }

            balance += money;

            state = WAITING_FOR_OBJECT;

            cout << "Inserted " << money << " unit(s). Current balance: " << balance << ";\n";
        }

        void showProducts(){
            cout << "\n ----Products in stash ---- \n";

            for (const auto& p : products){
                cout << p.first << ": " << p.second.name << " (" << p.second.price << " units)\n";
            }
        }

        void selectProduct(int code) {
            if (products.find(code) == products.end()) {
                cout << "Invalid product selection.\n";
                return;
            }
    
            Product p = products[code];
            if (balance >= p.price) {
                balance -= p.price;
                cout << "Dispensing " << p.name << ".\n";
                if (balance > 0) {
                    cout << "Returning change: " << balance << " units.\n";
                }
                reset();
            } else {
                cout << "Insufficient balance. " << p.name << " costs " << p.price << " units.\n";
            }
        }
    
        void reset() {
            balance = 0;
            state = IDLE;
            cout << "Machine reset. Ready for next user.\n";
        }
    
        int getBalance() {
            return balance;
        }
    };
    
    int main() {
        VendingMachine vm;
        int choice;
    
        while (true) {
            cout << "\n1. Insert Coin\n2. Show Products\n3. Buy Product\n0. Exit\nChoice: ";
            cin >> choice;
    
            if (choice == 0) {
                cout << "Goodbye!\n";
                break;
            }
    
            switch (choice) {
                case 1: {
                    int coin;
                    cout << "Enter coin (1, 5, 10): ";
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
                default:
                    cout << "Invalid option. Try again.\n";
            }
        }
    
        return 0;
    }