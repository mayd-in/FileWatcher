#include "mainwindow.h"
#include "watchedpathsmodel.h"
#include "watchedpathsview.h"
#include "eventmodel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QTableView>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Add Layout
    auto pathLineEdit = new QLineEdit;
    auto addPathButton = new QPushButton;
    addPathButton->setText(tr("Add"));

    auto addPathLayout = new QHBoxLayout;
    addPathLayout->addWidget(pathLineEdit, 1);
    addPathLayout->addWidget(addPathButton);
    addPathLayout->setAlignment(Qt::AlignTop);

    // Watched Paths
    auto watchedPathsModel = new WatchedPathsModel(this);
    auto watchedPathsView = new WatchedPathsView;
    watchedPathsView->setModel(watchedPathsModel);
    watchedPathsView->setSelectionBehavior(QTableView::SelectRows);
    watchedPathsView->setSelectionMode(QTableView::NoSelection);
    watchedPathsView->verticalHeader()->hide();
    watchedPathsView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    watchedPathsModel->addPath("Path 1");
    watchedPathsModel->addPath("Path 2");
    watchedPathsModel->addPath("Path 3");

    // Events
    auto eventModel = new EventModel(this);
    auto tableView = new QTableView;
    tableView->setModel(eventModel);
    tableView->setSelectionBehavior(QTableView::SelectRows);
    tableView->setSelectionMode(QTableView::SingleSelection);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->resizeColumnsToContents();

    // Buttons
    auto clearButton = new QPushButton(tr("Clear"));
    auto startButton = new QPushButton(tr("Start"));
    auto stopButton = new QPushButton(tr("Stop"));

    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignLeft);
    buttonsLayout->addWidget(clearButton);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(stopButton);

    // Main Structure
    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(addPathLayout);
    mainLayout->addWidget(watchedPathsView);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonsLayout);

    auto centralWidget = new QWidget;
    centralWidget->setMinimumWidth(600);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connections
    connect(addPathButton, &QPushButton::clicked, this, [pathLineEdit, watchedPathsModel]{
        watchedPathsModel->addPath(pathLineEdit->text());
    });
}

MainWindow::~MainWindow()
{
}

