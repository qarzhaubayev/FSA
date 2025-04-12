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

enum class VendResult {
    Success,            // product dispensed
    NoSuchCode,         // invalid code
    OutOfStock,
    InsufficientFunds
};


class VendingMachine {
public:
    VendingMachine();

    // user operations
    void insertCoin(int money);
    void showProducts();
    VendResult selectProduct(int code, int &change);   // change == money returned


    // admin operation
    void adminAddProduct();

    // helpers
    void reset();
    [[nodiscard]] int getBalance() const;

    // NEW public helper ---------------------------------------------
    const std::unordered_map<int, Product>& products() const;

    // NEW public helper (GUI‑friendly, no cin/cout) ------------------
    void upsertProduct(int code,
                       const std::string& name,
                       int price,
                       int quantity);


private:
    std::unordered_map<int, Product> products_;
    int   balance_ {};
    State state_ {State::IDLE};
    static constexpr const char* ADMIN_PASSWORD = "admin123";

    bool authenticateAdmin();
};
