#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    initWidgets();
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::initWidgets() {
    QStringList fontSizeList;
    fontSizeList << "1" << "2";
    ui->Comb_FontSize->addItems(fontSizeList);
}
