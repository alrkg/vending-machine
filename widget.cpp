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

void Widget::clearBtn(){
    ui->pbCoffee->setEnabled(false);
    ui->pbMilk->setEnabled(false);
    ui->pbTea->setEnabled(false);
}

void Widget::increaseMoney(int coin){
    if(money + coin >= 0){
        money += coin;
        ui->lcdNumber->display(money);
    }
}

void Widget::enableBtn(){
    ui->pbCoffee->setEnabled(money >= coffee);
    ui->pbMilk->setEnabled(money >= milk);
    ui->pbTea->setEnabled(money >= tea);
}

void Widget::clickedBtn(int coin){
    increaseMoney(coin);
    enableBtn();
}

void Widget::returnCoin(){
    QMessageBox mb;
    int coins[4] = {coin_500, coin_100, coin_50, coin_10};
    std::map<int, int> rtCoins;
    for (int i = 0; i < 4; i++){
        while(money >= coins[i]){
            money -= coins[i];
            rtCoins[coins[i]] += 1;
        }
    }
    ui->lcdNumber->display(money);
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

