#include "input.h"

Input::Input(QWidget* pwgt):QDialog(pwgt)
{
    setWindowTitle("Enter target data");
    r1 = new QLabel("&R1:", this);
    r2 = new QLabel("&R2:", this);
    x = new QLabel("&X(center):", this);
    y = new QLabel("&Y(center):", this);
    ammo = new QLabel("&Ammo:", this);

    r1Inp = new QLineEdit(this);
    r2Inp = new QLineEdit(this);
    xInp = new QLineEdit(this);
    yInp = new QLineEdit(this);
    ammoInp = new QLineEdit(this);    

    r1->setBuddy(r1Inp);
    r2->setBuddy(r2Inp);
    x->setBuddy(xInp);
    y->setBuddy(yInp);
    ammo->setBuddy(ammoInp);

    grid = new QGridLayout(this);
    grid->addWidget(r1, 0, 0);
    grid->addWidget(r2, 1, 0);
    grid->addWidget(x, 2, 0);
    grid->addWidget(y, 3, 0);
    grid->addWidget(ammo, 4, 0);
    grid->addWidget(r1Inp, 0, 1, 1, 3);
    grid->addWidget(r2Inp, 1, 1, 1, 3);
    grid->addWidget(xInp, 2, 1, 1, 3);
    grid->addWidget(yInp, 3, 1, 1, 3);
    grid->addWidget(ammoInp, 4, 1, 1, 3);

    pcmdOk = new QPushButton("&Ok", this);
    pcmdCancel = new QPushButton("&Cancel", this);

    grid->addWidget(pcmdOk, 5, 2);
    grid->addWidget(pcmdCancel, 5, 3);

    connect(pcmdOk, &QPushButton::clicked, this, &Input::getData);
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

    rVal = new QRegularExpressionValidator(QRegularExpression("^([1-9][0-9]*[.]?[0-9]*)|(0[.][0-9]*)$"));
    coorVal = new QRegularExpressionValidator(QRegularExpression("^([-]?)([1-9][0-9]*[.]?[0-9]*)|(0[.][0-9]*)$"));
    ammoVal = new QRegularExpressionValidator(QRegularExpression("^[1-9][0-9]*$"));
    r1Inp->setValidator(rVal);
    r2Inp->setValidator(rVal);
    xInp->setValidator(coorVal);
    yInp->setValidator(coorVal);
    ammoInp->setValidator(ammoVal);
}

void Input::getData()
{
    QString s;

    if(r1Inp->text().isEmpty() || r2Inp->text().isEmpty() || xInp->text().isEmpty()
            || yInp->text().isEmpty() || ammoInp->text().isEmpty())
        s = "You didn't fill out the data!";
    else if(r1Inp->text() == "0" || r2Inp->text() == "0")
        s = "Radiuses cannot be zero!";
    else if(r1Inp->text().toDouble() >=  r2Inp->text().toDouble())
        s = "The first radius must be smaller than the second!";
    else if(abs(xInp->text().toDouble())>width/2-30 || abs(yInp->text().toDouble())>height/2-30
            || abs(xInp->text().toDouble())+r1Inp->text().toDouble() > width/2-30
            || abs(yInp->text().toDouble())+r1Inp->text().toDouble() > height/2-30
            || abs(xInp->text().toDouble())+r2Inp->text().toDouble() > width/2-30
            || abs(yInp->text().toDouble())+r2Inp->text().toDouble() > height/2-30)
        s = "This target is outside the window!";
    else
    {
        accept();
        return;
    }
    QMessageBox::warning(0, "Error", s);
}

