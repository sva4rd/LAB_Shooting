#include "shotdialog.h"
#include "input.h"

ShotDialog::ShotDialog(QWidget* pwgt):QDialog(pwgt)
{
    setWindowTitle("Enter shot coordinates");
    resize(300, 80);
    x = new QLabel("&X:", this);
    y = new QLabel("&Y:", this);

    xCoord = new QLineEdit(this);
    yCoord = new QLineEdit(this);

    x->setBuddy(xCoord);
    y->setBuddy(yCoord);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(x, 0, 0, 1, 1);
    grid->addWidget(xCoord, 0, 1, 1, 2);
    grid->addWidget(y, 1, 0, 1, 1);
    grid->addWidget(yCoord, 1, 1, 1, 2);

    QPushButton *pcmdOk = new QPushButton("&Ok", this);
    QPushButton *pcmdCancel = new QPushButton("&Cancel", this);

    grid->addWidget(pcmdOk, 2, 1);
    grid->addWidget(pcmdCancel, 2, 2);

    connect(pcmdOk, &QPushButton::clicked, this, &ShotDialog::checkData);
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));
}

void ShotDialog::checkData()
{
    QString s;
    int xP = xCoord->text().toDouble() - oX;
    int yP = yCoord->text().toDouble() - oY;

    if(xCoord->text().isEmpty() || yCoord->text().isEmpty())
        s = "You didn't fill out the data!";
    else if(abs(xCoord->text().toDouble())>width/2   || abs(yCoord->text().toDouble())>height/2)
        s = "This target is outside the window!";
    else if((xP*xP+yP*yP<=r1c*r1c && xP+oX<=oX && yP+oY<=oY)
                    || (r1c*r1c<=xP*xP+yP*yP && xP*xP+yP*yP<=r2c*r2c
                        && xP+oX>=oX && yP+oY>=oY))
    {
        *keyH = true;
        accept();
        return;
    }
    else
    {
        accept();
        return;
    }
    QMessageBox::warning(0, "Error", s);
}
