#include "target.h"

Target::Target(QWidget *parent)
    : QWidget{parent}
{
    x=0;
    y=0;
    r1=0;
    r2=0;

    ammo=0;
    keyHit= new bool;
    *keyHit = false;

    oldWidth=0;
    oldHeight=0;
    newWidth=QGuiApplication::screens().at(0)->geometry().width();
    newHeight=QGuiApplication::screens().at(0)->geometry().height();

    changeOrNot = false;
    installEventFilter(this);
    setCursor(Qt::CrossCursor);
    nwGame();

    shotMenu = new QMenu(this);
    shotMenu->addAction("Shot");
    connect(shotMenu, SIGNAL(triggered(QAction*)), SLOT(keyShot(QAction*)));
}

void Target::paintEvent(QPaintEvent *event)
{
    QRect rec = event->rect();
    newWidth = rec.width();
    newHeight = rec.height();

    if(oldHeight == 0 && oldWidth==0)
    {
        oldHeight=newHeight;
        oldWidth=newWidth;
        return;
    }

    if(changeOrNot)
    {
        double propx = (oldWidth/2-x-r2)/(x+oldWidth/2-r2);
        double propy = (oldHeight/2-y-r2)/(y+oldHeight/2-r2);
        x = ((newWidth/2)*(1-propx)+r2*(propx-1))/(propx+1);
        y = ((newHeight/2)*(1-propy)+r2*(propy-1))/(propy+1);
        shotDg->width = newWidth;
        shotDg->height = newHeight;
    }

    QPainter painter(this);
    double currentX1 = x - r1;
    double currentY1 = y - r1;
    double currentX2 = x - r2;
    double currentY2 = y - r2;

    painter.setPen(QPen(Qt::black, 3));
    QColor col = this->palette().color(this->backgroundRole());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(newWidth/2, newHeight/2);
    painter.drawEllipse(currentX1, currentY1, 2*r1, 2*r1);
    painter.setBrush(QBrush(QColor(105, 105, 105), Qt::Dense3Pattern));
    painter.drawPie(QRect(currentX1, currentY1, 2*r1, 2*r1),90 * 16, 90 * 16);
    painter.drawPie(QRect(currentX2, currentY2, 2*r2, 2*r2),270 * 16, 90 * 16);
    painter.setBrush(QBrush(col));
    painter.drawPie(QRect(currentX1, currentY1, 2*r1, 2*r1),270 * 16, 90 * 16);

    oldHeight=newHeight;
    oldWidth=newWidth;
    changeOrNot = false;

    painter.setPen(QPen(Qt::red, 3));
    for(QSize dot : dots)
        painter.drawPoint(QPointF(dot.width()+x, dot.height()+y));
    painter.setPen(Qt::NoPen);
}

bool Target::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    if(event->type() == QEvent::Resize)
    {
        changeOrNot = true;
        if(r1!=0 && r2!=0)
            emit statusInfo(QString("±%1,±%2").arg(newWidth/2).arg(newHeight/2), ammo, inTarget, shots, QSize(0,0), false);
        update();
        return true;
    }
    return false;
}

void Target::mousePressEvent(QMouseEvent *pe)
{
    if(ammo!=0 && pe->buttons() == Qt::LeftButton)
    {
        bool hit = false;
        xPressed = pe->position().x() - newWidth/2 - x;
        yPressed = pe->position().y() - newHeight/2 - y;
        if((xPressed*xPressed+yPressed*yPressed<=r1*r1 && xPressed+x<=x && yPressed+y<=y)
                || (r1*r1<=xPressed*xPressed+yPressed*yPressed && xPressed*xPressed+yPressed*yPressed<=r2*r2
                    && xPressed+x>=x && yPressed+y>=y))
        {
            dots.push_back(QSize(xPressed,yPressed));
            inTarget++;
            hit = true;
            update();
        }
        shots++;
        ammo--;
        xPressed += x;
        yPressed += y;
        emit statusInfo(QString("±%1,±%2").arg(newWidth/2).arg(newHeight/2), ammo,
                        inTarget, shots, QSize(xPressed,yPressed), hit);
    }
    pe->accept();
}

void Target::contextMenuEvent(QContextMenuEvent *pe)
{
    shotMenu->exec(pe->globalPos());
}

void Target::nwGame()
{
    inTarget=0;
    shots=0;
    dots.clear();
}

void Target::keyShot(QAction* pAction)
{
    Q_UNUSED(pAction);
    if(r1 == 0 || r2 ==0)
    {
        QMessageBox::warning(0, "Error", "No target");
        return;
    }
    if(ammo == 0)
    {
        QMessageBox::warning(0, "Error", "No ammo");
        return;
    }
    if(shotDg->exec() == QDialog::Accepted)
    {
        if(*keyHit)
        {
            dots.push_back(QSize(shotDg->xCoord->text().toDouble()-x,shotDg->yCoord->text().toDouble()-y));
            inTarget++;
            update();
        }
        shots++;
        ammo--;
        emit statusInfo(QString("±%1,±%2").arg(newWidth/2).arg(newHeight/2), ammo, inTarget, shots,
                        QSize(shotDg->xCoord->text().toDouble(), shotDg->yCoord->text().toDouble()), *keyHit);
    }
    *keyHit=false;

}
