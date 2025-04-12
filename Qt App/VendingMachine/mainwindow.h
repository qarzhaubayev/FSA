#include <QMainWindow>
#include "VendingMachine.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void insertCoinClicked();
    void buyClicked();
    void adminClicked();

private:
    void refreshProductList();
    void updateBalanceLabel();
    void log(const QString& line);          // <- add this private method

    Ui::MainWindow *ui;
    VendingMachine  vm_;
};
