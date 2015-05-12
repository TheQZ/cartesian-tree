#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    horizLayout = new QHBoxLayout();
    treeLayout = new QHBoxLayout();

    insertButton = new QPushButton("Insert Value");

    deleteKeyButton = new QPushButton("Delete Key");
    sortButton = new QPushButton("Sort Values");

    valuesSpinBox = new QSpinBox(this);
    valuesSpinBox->setMaximum(999);
    valuesSpinBox->setMinimum(-999);
    valuesSpinBox->setValue(42);

    QFont f;
    f.setPointSize(17);
    f.setBold(true);

    titleLabel = new QLabel("Jasper and Samuel David's\n Super-Cool Cartesian Tree Thingy");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(f);



    horizLayout->addWidget(valuesSpinBox);
    horizLayout->addWidget(insertButton);
    horizLayout->setAlignment(Qt::AlignCenter);


    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(horizLayout);
    mainLayout->addLayout(treeLayout);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteKeyButton, SIGNAL(clicked()), this, SLOT(removeKey()));
    connect(sortButton, SIGNAL(clicked()), this, SLOT(sortem()));
}

void MainWindow::insert()
{
    int i = valuesSpinBox->value();
    tree.insert(i);

    if (tree.size() == 1) horizLayout->addWidget(deleteKeyButton);
    if (tree.size() == 2) mainLayout->addWidget(sortButton);

    refresh();
}

void MainWindow::refresh()
{

}

void MainWindow::removeKey()
{


}

void MainWindow::sortem()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
