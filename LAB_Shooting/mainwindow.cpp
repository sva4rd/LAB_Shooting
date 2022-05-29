#include "mainwindow.h"
#include <QDebug>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Target shooting");
    setMinimumSize(550, 550);
    move(0, 0);
    resize(QGuiApplication::screens().at(0)->geometry().width(),
           QGuiApplication::screens().at(0)->geometry().height());

    mnu = new QMenu("&Game");
    mnu->addAction("&Make a new target", this, SLOT(slotNewGame()), QKeySequence("CTRL+N"));
    mnu->addSeparator();
    mnu->addAction("&Quit", qApp, SLOT(quit()), QKeySequence("CTRL+Q"));
    menuBar()->addMenu(mnu);

    targetArea = new QLabel(this);
    shtAmount = new QLabel(this);
    statistic = new QLabel(this);
    radStatus = new QLabel(this);
    hitCoordinates = new QLabel(this);
    statusBar()->addWidget(targetArea);
    statusBar()->addWidget(radStatus);
    statusBar()->addWidget(shtAmount);
    statusBar()->addWidget(statistic);
    statusBar()->addWidget(hitCoordinates);

    sTarget = new Target(this);
    setCentralWidget(sTarget);

    in = new Input(this);
    in->setModal(true);

    shD = new ShotDialog(sTarget);
    shD->setModal(true);
    sTarget->shotDg = shD;
    shD->xCoord->setValidator(in->coorVal);
    shD->yCoord->setValidator(in->coorVal);
    shD->keyH = sTarget->keyHit;

    connect(sTarget, &Target::statusInfo, this, &MainWindow::statusChangedSlot);
}

void MainWindow::statusChangedSlot(QString area, int am, int inTar, int sh, QSize s, bool hit)
{
    targetArea->setText(QString("Target area: (%1)").arg(area));
    shtAmount->setText(QString("Ammo: %1").arg(am));
    statistic->setText(QString("Hit statistics: %1/%2").arg(inTar).arg(sh));
    if(hit)
        hitCoordinates->setText(QString("Hit Coordinates: (%1,%2)").arg(s.width()).arg(s.height()));
    else
        hitCoordinates->setText("");
}

void MainWindow::slotNewGame()
{
    in->height = sTarget->newHeight;
    in->width = sTarget->newWidth;
    if(in->exec() == QDialog::Accepted)
    {
        sTarget->nwGame();

        sTarget->x = in->xInp->text().toDouble();
        sTarget->y = in->yInp->text().toDouble();
        sTarget->r1 = in->r1Inp->text().toDouble();
        sTarget->r2 = in->r2Inp->text().toDouble();
        sTarget->ammo = in->ammoInp->text().toInt();

        shD->r1c = sTarget->r1;
        shD->r2c = sTarget->r2;
        shD->oX = sTarget->x;
        shD->oY = sTarget->y;

        if(2*sTarget->r2 + 70 < 550)
        {
            setMinimumSize(550, 2*sTarget->r2 + 70);
        }
        else
            setMinimumSize(2*sTarget->r2 + 70, 2*sTarget->r2 + 70);

        statusChangedSlot(QString("±%1,±%2").arg(sTarget->newWidth/2).arg(sTarget->newHeight/2), sTarget->ammo,
                          sTarget->inTarget, sTarget->shots, QSize(0,0), false);

        radStatus->setText(QString("R1: %1, R2: %2").arg(sTarget->r1).arg(sTarget->r2));
        sTarget->update();
        in->setFocus(Qt::NoFocusReason);
    }
}

MainWindow::~MainWindow()
{
    delete in;
    delete shD;
    delete sTarget;
}
