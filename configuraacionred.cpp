#include "configuraacionred.hpp"
#include "ui_configuraacionred.h"

ConfiguraacionRed::ConfiguraacionRed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfiguraacionRed)
{
    ui->setupUi(this);
}

ConfiguraacionRed::~ConfiguraacionRed()
{
    delete ui;
}
