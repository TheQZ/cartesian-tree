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

    deleteKeyButton = new QPushButton("Delete Key");
    deleteKeyButton->setVisible(false);
    sortButton = new QPushButton("Sort Values");
    sortButton->setVisible(false);
    sortedValues = new QLabel();
    sortedValues->setVisible(false);
    sortedValues->setAlignment(Qt::AlignCenter);

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
    horizLayout->addWidget(deleteKeyButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(horizLayout);
    mainLayout->addWidget(sortButton);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteKeyButton, SIGNAL(clicked()), this, SLOT(removeKey()));
    connect(sortButton, SIGNAL(clicked()), this, SLOT(sortem()));

    treeWidget = new QWidget();


}

void MainWindow::insert()
{
    int i = valuesSpinBox->value();
    tree.insert(i);

    refresh();

    srand (time(NULL));

    valuesSpinBox->setValue(rand() % 30);
}

void MainWindow::refresh()
{
    sortedValues->setVisible(false);
    if (tree.size() >= 1) deleteKeyButton->setVisible(true);
    else deleteKeyButton->setVisible(false);
    if (tree.size() >= 2) sortButton->setVisible(true);
    else sortButton->setVisible(false);

    delete treeWidget;
    treeWidget = nullptr;
    treeWidget = new QWidget();

    QHBoxLayout *treeLayout = new QHBoxLayout();
    treeLayout->setAlignment(Qt::AlignCenter);

    tree.inOrder();
    std::vector<int> values = tree.getInorderVector();
    std::vector<int> heights = tree.getHeights();

    for (int i = 0; i < (int)values.size(); i++) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *ql = new QLabel(QString::fromStdString(std::to_string(values[i])));

        vl->addWidget(ql);

        ql->setAutoFillBackground(true);
        QPalette pal = ql->palette();
        int cval = (heights[i] * 15) % 125;
        pal.setColor(QPalette::Window, QColor(50+cval, 120+cval, 120+cval, 128));

        ql->setPalette(pal);

        for (int j = 0; j < heights[i]; j++) {
            QLabel *littlel = new QLabel(" ");
            vl->addWidget(littlel);
        }

        QFont f;
        f.setPointSize(17);
        f.setBold(true);
        ql->setFont(f);


        treeLayout->addLayout(vl);
    }
    treeWidget->setLayout(treeLayout);
    mainLayout->addWidget(treeWidget);
    mainLayout->addWidget(sortButton);
}

void MainWindow::removeKey()
{
    tree.deleteKey();
    refresh();
}

void MainWindow::sortem()
{
    sortedValues->clear();

    std::vector<node<int> *> vector = tree.sortedVector();
    std::string s;
    s += "{";
    for(node<int> *x : vector) {
            s += " " +std::to_string(x->data) +" ";
    }
    s += "}";
    sortedValues->setText(QString::fromStdString(s));
    refresh();
    mainLayout->addWidget(sortedValues);
    sortedValues->setVisible(true);

    // fill in sorted values vector with info
}

MainWindow::~MainWindow()
{
    delete ui;
}
