#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int money{0};
    void clearBtn();

    enum coin{
        coin_10 = 10,
        coin_50 = 50,
        coin_100 = 100,
        coin_500 = 500
    };

    enum product{
        coffee = 100,
        milk = 150,
        tea = 200
    };

    void increaseMoney(int coin);
    void enableBtn();
    void clickedBtn(int coin);
    void returnCoin();


private slots:
    void on_pb10_clicked();

    void on_pb50_clicked();

    void on_pb100_clicked();

    void on_pb500_clicked();

    void on_pbCoffee_clicked();

    void on_pbMilk_clicked();

    void on_pbTea_clicked();

    void on_pbReset_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
