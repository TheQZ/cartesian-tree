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

    insertButton = new QPushButton("Insert Value");

    valuesSpinBox = new QSpinBox(this);
    valuesSpinBox->setMaximum(999);
    valuesSpinBox->setMinimum(-999);
    valuesSpinBox->setValue(17);

    QFont f;
    f.setPointSize(17);
    f.setBold(true);

    titleLabel = new QLabel("Jasper and Samuel David's\n Super-Cool Cartesian Tree Thingy");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(f);
    valuesLabel = new QLabel("Value");
    treeLabel = new QLabel("");
    treeLabel->setAlignment(Qt::AlignCenter);

    horizLayout->addWidget(valuesSpinBox);
    horizLayout->addWidget(valuesLabel);
    horizLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(horizLayout);
    mainLayout->addWidget(insertButton);
    mainLayout->addWidget(treeLabel);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
}

void MainWindow::insert()
{
    int i = valuesSpinBox->value();
    tree.insert(i);
    treeLabel->setText("{ " + QString::fromStdString(tree.inOrder()) + " }");
    std::cout << i << " inserted into tree[" << tree.size() << "] => { "<< tree.inOrder() << " }" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
