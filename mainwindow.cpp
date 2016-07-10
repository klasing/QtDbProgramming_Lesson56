#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // it's already a central widget, but who cares
    this->setCentralWidget(ui->tableView);
    // connect to db
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=(localdb)\\Projects;Database=test");
    db.setUserName("odbc");
    db.setPassword("odbc");
    db.setDatabaseName(dsn);

    if (!db.open()) qDebug() << db.lastError().text();
    // create a table model
    model = new QSqlTableModel(this);
    model->setTable("dbo.people");
    // select data from the table, and show
    if (!model->select()) qDebug() << model->lastError().text();
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
