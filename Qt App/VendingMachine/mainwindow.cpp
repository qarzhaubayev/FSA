#include "mainwindow.h"
#include "ui_mainwindow.h"   // correct for qmake


#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // fill coin combo box
    ui->comboCoin->addItems({"200", "500", "1000"});

    connect(ui->btnInsert, &QPushButton::clicked,
            this, &MainWindow::insertCoinClicked);
    connect(ui->btnBuy,    &QPushButton::clicked,
            this, &MainWindow::buyClicked);
    connect(ui->btnAdmin,  &QPushButton::clicked,
            this, &MainWindow::adminClicked);

    refreshProductList();
    updateBalanceLabel();
}

MainWindow::~MainWindow() { delete ui; }

/* ------------------------------------------------------------------ */

void MainWindow::refreshProductList()
{
    ui->listProducts->clear();

    for (const auto& [code, p] : vm_.products()) {
        QString line = QString("%1 — %2 (%3 ₸) [qty %4]")
                           .arg(code)
                           .arg(QString::fromStdString(p.name))
                           .arg(p.price)
                           .arg(p.quantity);
        ui->listProducts->addItem(line);
    }
}


void MainWindow::updateBalanceLabel()
{
    ui->labelBalance->setText(
        QString("Balance: %1 ₸").arg(vm_.getBalance()));
}

/* -------------------- slots --------------------------------------- */

void MainWindow::insertCoinClicked()
{
    int coin = ui->comboCoin->currentText().toInt();
    vm_.insertCoin(coin);

    log(QString("Inserted %1 ₸. Current balance: %2 ₸")
            .arg(coin).arg(vm_.getBalance()));

    updateBalanceLabel();
}
void MainWindow::buyClicked()
{
    // 1. Which list item is selected?
    auto *item = ui->listProducts->currentItem();
    if (!item) return;

    int code   = item->text().section(' ', 0, 0).toInt();
    int change = 0;

    // 2. Ask the vending machine to vend
    auto result = vm_.selectProduct(code, change);

    // 3. Act on the outcome
    switch (result) {
    case VendResult::Success: {
        const auto &prod = vm_.products().at(code);
        log(QString("Dispensed %1. Returning change: %2 ₸")
                .arg(QString::fromStdString(prod.name))
                .arg(change));
        break;
    }
    case VendResult::InsufficientFunds:
        log("Insufficient balance. Please insert more coins.");
        QMessageBox::warning(this,              // parent
                             "Vending Machine", // title
                             "Insufficient balance.\nInsert more coins.");
        break;
    case VendResult::OutOfStock:
        log("That product is out of stock.");
        QMessageBox::information(this, "Vending Machine",
                                 "Sorry, that product is out of stock.");
        break;
    case VendResult::NoSuchCode:
        log("Invalid product selection.");
        QMessageBox::information(this, "Vending Machine",
                                 "Invalid product code.");
        break;
    }

    // 4. Refresh UI no matter what happened
    updateBalanceLabel();
    refreshProductList();
}



void MainWindow::log(const QString& line)
{
    ui->txtLog->appendPlainText(line);  // QTextEdit? use append()
}

void MainWindow::adminClicked()
{
    bool ok;
    QString pwd = QInputDialog::getText(this, "Admin",
                                        "Password:", QLineEdit::Password, {}, &ok);
    if (!ok || pwd.toStdString() != "admin123") return;

    int code = QInputDialog::getInt(this, "Admin", "Product code:", 1, 1);
    QString name = QInputDialog::getText(this, "Admin", "Name:");
    int price = QInputDialog::getInt(this, "Admin", "Price (₸):", 10, 1);
    int qty   = QInputDialog::getInt(this, "Admin", "Quantity:",   10, 0);

    vm_.upsertProduct(code, name.toStdString(), price, qty);

    log(QString("Product %1 (code %2) set to price %3 ₸, qty %4")
            .arg(name).arg(code).arg(price).arg(qty));

    refreshProductList();
}

