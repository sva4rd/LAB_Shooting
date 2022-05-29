#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QtWidgets>

class Input : public QDialog
{
    friend class MainWindow;
private:
    Input(QWidget* pwgt = 0);
    QLabel *r1;
    QLabel *r2;
    QLabel *x;
    QLabel *y;
    QLabel *ammo;

    QLineEdit *r1Inp;
    QLineEdit *r2Inp;
    QLineEdit *xInp;
    QLineEdit *yInp;
    QLineEdit *ammoInp;

    QPushButton* pcmdOk;
    QPushButton* pcmdCancel;

    double width;
    double height;
    QValidator *rVal;
    QValidator *coorVal;
    QValidator *ammoVal;
    QGridLayout *grid;

private slots:
    void getData();
};

#endif // INPUT_H
