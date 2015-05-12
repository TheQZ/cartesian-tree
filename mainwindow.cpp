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
    sortedValues->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

    searchButton = new QPushButton("Search!");
    searchButton->setVisible(false);
    found = false;
    foundVal = 0;

    valuesSpinBox = new QSpinBox(this);
    valuesSpinBox->setMaximum(999);
    valuesSpinBox->setMinimum(-999);
    valuesSpinBox->setValue(42);

    QFont f;
    f.setPointSize(17);
    f.setBold(true);

    titleLabel = new QLabel("Jasper and Samuel David's\n Super-Cool Cartesian Tree Thingy");
    titleLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    titleLabel->setFont(f);

    horizLayout->addWidget(insertButton);
    horizLayout->addWidget(valuesSpinBox);
    horizLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    horizLayout->addWidget(searchButton);
    horizLayout->addWidget(deleteKeyButton);

    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(horizLayout);
    mainLayout->addWidget(sortButton);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteKeyButton, SIGNAL(clicked()), this, SLOT(removeKey()));
    connect(sortButton, SIGNAL(clicked()), this, SLOT(sortem()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchVal()));
    treeWidget = new QWidget();

    srand (time(NULL));
}

void MainWindow::insert()
{
    int i = valuesSpinBox->value();
    tree.insert(i);

    refresh();

    valuesSpinBox->setValue(rand() % 99);
}

void MainWindow::refresh()
{
    sortedValues->setVisible(false);
    if (tree.size() >= 1) {
        deleteKeyButton->setVisible(true);
        searchButton->setVisible(true);
    } else {
        deleteKeyButton->setVisible(false);
        searchButton->setVisible(false);
    }
    if (tree.size() >= 2) sortButton->setVisible(true);
    else sortButton->setVisible(false);

    delete treeWidget;
    treeWidget = nullptr;
    treeWidget = new QWidget();

    QHBoxLayout *treeLayout = new QHBoxLayout();
    treeLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    tree.inOrder();
    std::vector<int> values = tree.getInorderVector();
    std::vector<int> heights = tree.getHeights();

    for (int i = 0; i < (int)values.size(); i++) {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *ql = new QLabel(QString::fromStdString(std::to_string(values[i])));

        vl->addWidget(ql);
        vl->setAlignment(Qt::AlignTop);
        vl->setSpacing(0);

        QPalette pal = ql->palette();
        int cval = (heights[i] * 10) % 125;
        pal.setColor(QPalette::Window, QColor(50+cval, 120+cval, 100+(cval *1.01), 128));

        if(heights[i]-1 == 0) {
            pal.setColor(QPalette::Window, QColor(200,200,50,128));
        }
        if(found && values[i] == foundVal) {
            pal.setColor(QPalette::Window, QColor(150,122, 200, 128));
            found = false;
        }
        ql->setAutoFillBackground(true);
        ql->setPalette(pal);
        ql->setFixedHeight(20);

        for (int j = 0; j < heights[i]-1; j++) {
            QLabel *littlel = new QLabel(" ");
            vl->addWidget(littlel);
            littlel->setAutoFillBackground(true);
            littlel->setPalette(pal);
            littlel->setFixedHeight(20);
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

void MainWindow::searchVal()
{
    foundVal = valuesSpinBox->value();
    if(tree.search(foundVal) == true) {
        found = true;
        refresh();
        sortedValues->setText("Value found.");
        mainLayout->addWidget(sortedValues);
        sortedValues->setVisible(true);
    } else {
        refresh();
        sortedValues->setText("Value not found.");
        mainLayout->addWidget(sortedValues);
        sortedValues->setVisible(true);
    }

    found = false;
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
