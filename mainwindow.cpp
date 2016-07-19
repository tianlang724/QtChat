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
    for (int i = 1; i < 50; i++) {
        fontSizeList << QString::number(i, 10);
    }
    ui->Comb_FontSize->addItems(fontSizeList);
    /* 初始化字号ComboBox */
}

void mainwindow::updateFontStyle() {
    ui->TextEdit_SendMsg->selectAll();
    bool ok;
//    QPalette pl = ui->TextEdit_SendMsg->palette();
//    pl.setColor(QPalette::Text, QColor(Qt::blue));
//    ui->TextEdit_SendMsg->setPalette(pl);
    ui->TextEdit_SendMsg->setFontPointSize(ui->Comb_FontSize->currentText().toInt(&ok, 10));
    ui->TextEdit_SendMsg->setFontFamily(ui->Comb_Font->currentFont().family());
}
