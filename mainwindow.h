#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QSpacerItem>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton * button;
    QLabel * label;
    QLineEdit * LineEditEnterFunction;
    QLineEdit * LineEditEnterXMax;
    QLineEdit * LineEditEnterXMin;
    QLineEdit * LineEditEnterYMax;
    QLineEdit * LineEditEnterYMin;
    QLabel * labelXMax;
    QLabel * labelXMin;
    QLabel * labelYMax;
    QLabel * labelYMin;
    QHBoxLayout * Function;
    QHBoxLayout * X;
    QHBoxLayout * Y;
    QHBoxLayout * Build;
    QSpacerItem * item;



private slots:
    void my_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
