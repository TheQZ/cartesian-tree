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
#include <stdlib.h>
#include <time.h>
#include "ctree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void insert();
    void refresh();
    void removeKey();
    void sortem();

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

    bool firstInsert;
    QPushButton *deleteKeyButton;
    bool secondInsert;
    QPushButton *sortButton;

    ctree<int> tree;
    QWidget *treeWidget;
    QLabel *sortedValues;

};

#endif // MAINWINDOW_H
