#ifndef TARGET_H
#define TARGET_H

#include <QtWidgets>
#include "shotdialog.h"

class Target : public QWidget
{
    Q_OBJECT
    friend class MainWindow;
private:
    Target(QWidget *parent = nullptr);
    double r1;
    double r2;
    double x;
    double y;

    QMenu *shotMenu;

    int ammo;
    int inTarget;
    int shots;

    void paintEvent(QPaintEvent*);
    bool eventFilter(QObject *obj,QEvent *event);
    void mousePressEvent (QMouseEvent *pe);
    void contextMenuEvent(QContextMenuEvent* pe);
    void nwGame();

    double oldWidth;
    double oldHeight;
    double newWidth;
    double newHeight;

    bool changeOrNot;

    double xPressed;
    double yPressed;
    QVector<QSize> dots;

    bool *keyHit;
    ShotDialog *shotDg;
signals:
    void statusInfo(QString s, int am, int inT, int sh, QSize, bool);
private slots:
    void keyShot(QAction *pAction);
};

#endif // TARGET_H
