#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>
#include <QGraphicsView>
#include <QString>
#include <QLabel>
#include <iostream>
#include "ctree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void insert();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizLayout;
    QWidget *mainWidget;
    QPushButton *insertButton;
    QSpinBox *valuesSpinBox;
    QLabel *titleLabel;
    QLabel *valuesLabel;
    QLabel *treeLabel;

    bool firstInsert;
    QPushButton *deleteKeyButton;
    QPushButton *sortButton;

    ctree<int> tree;
};

#endif // MAINWINDOW_H
