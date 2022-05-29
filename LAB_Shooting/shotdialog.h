#ifndef SHOTDIALOG_H
#define SHOTDIALOG_H

#include <QDialog>
#include <QtWidgets>

class ShotDialog : public QDialog
{
    friend class MainWindow;
    friend class Target;
private:
    ShotDialog(QWidget* pwgt = 0);
    QLabel *x;
    QLabel *y;
    QLineEdit *xCoord;
    QLineEdit *yCoord;

    double width;
    double height;
    double oX;
    double oY;
    double r1c;
    double r2c;

    bool *keyH;
private slots:
    void checkData();
};

#endif // SHOTDIALOG_H
