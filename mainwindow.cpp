#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "connection not start!";
    }
    else
    {
        qDebug() << "connection started!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

int rowcount;

void MainWindow::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->waitForBytesWritten(3000);
    socket->waitForReadyRead(3000);
 //  qDebug() << "Reading: " << socket->bytesAvailable();
   QString data=socket->readAll();
    QStringList datas=data.split("\n");
    int i=0;
 while(datas[i]!="")
   {
       ui->tableWidget->setRowCount(rowcount+1);
       ui->tableWidget->setColumnCount(4);

       ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(datas[i++]));

       ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(datas[i++]));

       ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(datas[i++]));

       ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(datas[i++]));


         rowcount++;
   }
    rowcount=0;
    socket->close();
    socket->disconnect();
}
