#ifndef CONFIGURAACIONRED_HPP
#define CONFIGURAACIONRED_HPP

#include <QDialog>

namespace Ui {
class ConfiguraacionRed;
}

class ConfiguraacionRed : public QDialog
{
    Q_OBJECT

public:
    explicit ConfiguraacionRed(QWidget *parent = 0);
    ~ConfiguraacionRed();

public:
    Ui::ConfiguraacionRed *ui;
};

#endif // CONFIGURAACIONRED_HPP
