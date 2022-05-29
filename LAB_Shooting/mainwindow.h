#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "target.h"
#include "input.h"
#include "shotdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Target *sTarget;
    QMenu *mnu;

    QLabel *shtAmount;
    QLabel *statistic;
    QLabel *radStatus;
    QLabel *hitCoordinates;
    QLabel *targetArea;
    Input *in;
    ShotDialog *shD;
public slots:
    void statusChangedSlot(QString s, int am, int inT, int sh, QSize, bool);
private slots:
    void slotNewGame();
};

#endif // MAINWINDOW_H
