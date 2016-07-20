#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

#define MINIMUM_FONTSIZE 10
#define MAXIMUM_FONTSIZE 40

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow),
    server(new Server)
{
    ui->setupUi(this);
    initWidgets();
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::initWidgets() {
    /* 初始化字号SpinBox */
    ui->SBox_FontSize->setMinimum(MINIMUM_FONTSIZE);
    ui->SBox_FontSize->setMaximum(MAXIMUM_FONTSIZE);
}
/*
 * 功能：更新输入框字体大小和样式
 * */
void mainwindow::updateFontStyle() {
    QFont currentFontStyle = ui->Comb_Font->currentFont();
    currentFontStyle.setPointSize(ui->SBox_FontSize->value());
    if (ui->CB_Italic->isChecked()) {
        currentFontStyle.setItalic(true);
    }
    if (ui->CB_Bold->isChecked()) {
        currentFontStyle.setBold(true);
    }
    ui->TextEdit_SendMsg->setFont(currentFontStyle);
}

/*
 * 功能：设置输入框字体颜色
 * */
void mainwindow::openColorSetting() {
    const QColor fontColor = QColorDialog::getColor();
    QPalette pl = ui->TextEdit_SendMsg->palette();
    pl.setColor(QPalette::Text, fontColor);
    ui->TextEdit_SendMsg->setPalette(pl);
}
