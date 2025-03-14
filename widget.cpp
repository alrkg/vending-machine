#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    clearBtn();
}

Widget::~Widget()
{
    delete ui;
}

/*
void Widget::clearBtn(){
    ui->pbCoffee->setEnabled(false);
    ui->pbMilk->setEnabled(false);
    ui->pbTea->setEnabled(false);
}
*/

void Widget::clearBtn(){
    QVBoxLayout *layout = ui->loProduct;
    for (int i = 0; i < layout->count(); i++){
        QPushButton *btn = qobject_cast<QPushButton*>(layout->itemAt(i)->widget());
        btn->setEnabled(false);
    }
}

void Widget::increaseMoney(int coin){
    if(money + coin >= 0){
        money += coin;
        ui->lcdNumber->display(money);
    }
}

/*
void Widget::enableBtn(){
    ui->pbCoffee->setEnabled(money >= coffee);
    ui->pbMilk->setEnabled(money >= milk);
    ui->pbTea->setEnabled(money >= tea);
}
*/

void Widget::enableBtn(){
    QVBoxLayout *layout = ui->loProduct;
    for (int i = 0; i < layout->count(); i++){
        QPushButton *btn = qobject_cast<QPushButton*>(layout->itemAt(i)->widget());
        QString str = btn->text();
        int startIndex = str.indexOf('(');
        int endIndex = str.indexOf(')');
        int price = str.mid(startIndex + 1, endIndex - startIndex - 1).toInt();
        btn->setEnabled(money >= price);
    }
}

void Widget::clickedBtn(int coin){
    increaseMoney(coin);
    enableBtn();
}

/*
void Widget::returnCoin(){
    int coins[4] = {coin_500, coin_100, coin_50, coin_10};
    std::map<int, int> rtCoins;
    for (int i = 0; i < (sizeof(coins) / sizeof(int)); i++){
        rtCoins[coins[i]] += (money / coins[i]);
        money %= coins[i];
    }
    ui->lcdNumber->display(money);

    QString message;
    for (auto &pair : rtCoins) {
        if (pair.second > 0) {
            message += QString::number(pair.first) + "coin : " + QString::number(pair.second) + "pcs\n";
        }
    }
    QMessageBox::information(this, "Change", message);
}
*/

void Widget::returnCoin(){
    QVBoxLayout *layout = ui->loCoin;
    std::map<int, int, std::greater<int>> coins;
    for (int i = 0; i < layout->count(); i++){
        QPushButton *btn = qobject_cast<QPushButton*>(layout->itemAt(i)->widget());
        coins[btn->text().toInt()] = 0;
    }

    QString message;
    for (auto &pair : coins) {
        int cost = pair.first;
        coins[cost] = (money / cost);
        money %= cost;
        if (pair.second > 0) {
            message += QString::number(pair.first) + "coin : " + QString::number(pair.second) + "pcs\n";
        }
    }
    ui->lcdNumber->display(money);
    QMessageBox::information(this, "Change", message);
}

void Widget::on_pb10_clicked()
{
    clickedBtn(coin_10);
}

void Widget::on_pb50_clicked()
{
    clickedBtn(coin_50);
}

void Widget::on_pb100_clicked()
{
    clickedBtn(coin_100);
}


void Widget::on_pb500_clicked()
{
    clickedBtn(coin_500);
}

void Widget::on_pbCoffee_clicked()
{
    clickedBtn(-coffee);
}

void Widget::on_pbMilk_clicked()
{
    clickedBtn(-milk);
}

void Widget::on_pbTea_clicked()
{
    clickedBtn(-tea);
}

void Widget::on_pbReset_clicked()
{
    returnCoin();
    clearBtn();
}

