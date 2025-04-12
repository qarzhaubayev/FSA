#include <unordered_map>
#include <string>
#include <iostream>

enum class State {
    IDLE,
    WAITING_FOR_OBJECT,
    DISPENSING
};

struct Product {
    std::string name;
    int  price {};
    int  quantity {};
};

class VendingMachine {
public:
    VendingMachine();

    // user operations
    void insertCoin(int money);
    void showProducts();
    void selectProduct(int code);

    // admin operation
    void adminAddProduct();

    // helpers
    void reset();
    [[nodiscard]] int getBalance() const;

private:
    std::unordered_map<int, Product> products_;
    int   balance_ {};
    State state_ {State::IDLE};
    static constexpr const char* ADMIN_PASSWORD = "admin123";

    bool authenticateAdmin();
};
