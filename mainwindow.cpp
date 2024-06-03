#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include "poland.h"
#include <QString>
#include <QKeyEvent>
#include <QValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 700);

    button = new QPushButton(this);
    label = new QLabel(this);
    LineEditEnterFunction = new QLineEdit(this);
    LineEditEnterXMax = new QLineEdit(this);
    LineEditEnterXMin = new QLineEdit(this);
    LineEditEnterYMax = new QLineEdit(this);
    LineEditEnterYMin = new QLineEdit(this);
    labelXMax = new QLabel(this);
    labelXMin = new QLabel(this);
    labelYMax = new QLabel(this);
    labelYMin = new QLabel(this);


    LineEditEnterFunction->setGeometry(5, 5, width() - 15, 40);

    button->setGeometry(width() - 210, LineEditEnterFunction->height() + 10, 200, 30);
    button->setText("Build");

    labelXMax->setGeometry(width() - 10 - button->width(), 5 + LineEditEnterFunction->height() + 5 + button->height() + 5, (button->width()) / 2 - 5, 30);
    labelXMax->setText("max x:");
    labelXMin->setGeometry(width() - 10 - (button->width()) / 2, 5 + LineEditEnterFunction->height() + 5 + button->height() + 5, (button->width()) / 2 - 5, 30);
    labelXMin->setText("min x:");

    LineEditEnterXMax->setGeometry(width() - 10 - button->width(), 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMax->height() + 5, (button->width()) / 2 - 5, 30);
    LineEditEnterXMin->setGeometry(width() - 10 - (button->width()) / 2, 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMax->height() + 5, (button->width()) / 2 - 5, 30);

    LineEditEnterXMax->setText("10.0");
    LineEditEnterXMin->setText("-10.0");


    labelYMax->setGeometry(width() - 10 - button->width(), 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMax->height() + 5 + LineEditEnterXMax->height() + 5, (button->width()) / 2 - 5, 30);
    labelYMax->setText("max y:");
    labelYMin->setGeometry(width() - 10 - (button->width()) / 2, 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMin->height() + 5 + LineEditEnterXMin->height() + 5, (button->width()) / 2 - 5, 30);
    labelYMin->setText("min y:");

    LineEditEnterYMax->setGeometry(width() - 10 - button->width(), 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMax->height() + 5 + LineEditEnterXMax->height() + 5 + labelYMax->height() + 5, (button->width()) / 2 - 5, 30);
    LineEditEnterYMin->setGeometry(width() - 10 - (button->width()) / 2, 5 + LineEditEnterFunction->height() + 5 + button->height() + 5 + labelXMax->height() + 5 + LineEditEnterXMax->height() + 5 + labelYMin->height() + 5, (button->width()) / 2 - 5, 30);

    LineEditEnterYMax->setText("10.0");
    LineEditEnterYMin->setText("-10.0");

    QRegularExpression rx(R"(^-?(([1-9]\d*\.?\d*)|(0\.\d*))$)");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx);

    LineEditEnterXMax->setValidator(validator);
    LineEditEnterXMin->setValidator(validator);
    LineEditEnterYMax->setValidator(validator);
    LineEditEnterYMin->setValidator(validator);

    Function = new QHBoxLayout;
    X = new QHBoxLayout;
    Y = new QHBoxLayout;
    Build = new QHBoxLayout;

    item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(button, SIGNAL(clicked()), this, SLOT(my_button_clicked()));



}

void MainWindow::my_button_clicked(){

    label->setGeometry(5, 5 + LineEditEnterFunction->height() + 5, width() - button->width() - 20, height() - 5 - LineEditEnterFunction->height() - 5);

    // double const pi = 3.14159265;

    double xMin = stod((LineEditEnterXMin->text()).toStdString()), xMax = stod((LineEditEnterYMax->text()).toStdString());
    double yMin = stod((LineEditEnterYMin->text()).toStdString()), yMax = stod((LineEditEnterYMax->text()).toStdString());

    int xGraphMin = 0, xGraphMax = label->width();
    int yGraphMin = 0, yGraphMax = label->height();

    double kx = (xGraphMax - xGraphMin) / (xMax - xMin);
    double ky = (yGraphMin - yGraphMax) / (yMax - yMin);

    double step = (xMax - xMin) / (xGraphMax - xGraphMin);

    int xGraph, yGraph;

    int x0 = xGraphMin - kx * xMin, y0 = yGraphMin - ky * yMax;



    QPixmap pm(label->width(), label->height());

    QPainter painter;
    QPainterPath path;
    QPen pen;




    pm.fill(Qt::white);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.begin(&pm);

    painter.drawLine(0, y0, label->width(), y0);
    painter.drawLine(x0, 0, x0, label->height());


    pen.setColor(Qt::green);
    painter.setPen(pen);

    QString expression;
    expression = LineEditEnterFunction->text();

    double x = xMin;
    expression.replace("x", "("+QString::number(x)+")");

    string a;
    a = expression.toStdString();
    double y = 0.0;

    bool hlp = false;
    step *= 0.01;

    if (a == "") LineEditEnterFunction->setText("Введите функцию");
    else {
        for (x = xMin; x < xMax; x+=step){
            expression = LineEditEnterFunction->text();
            expression.replace("x", "("+QString::number(x)+")");
            a = expression.toStdString();
            if (calculate(a, y)) {
                xGraph = xGraphMin + kx * (x - xMin);
                yGraph = yGraphMin + ky * (y - yMax);
                if (hlp) path.lineTo(xGraph, yGraph);
                else path.moveTo(xGraph, yGraph);

                if (yGraph >= yGraphMax || yGraph <= yGraphMin) hlp = false;
                else hlp = true;
            }
            else hlp = false;
        }
            painter.drawPath(path);
            label->setPixmap(pm);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
