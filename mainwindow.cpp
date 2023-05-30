#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <cmath>

static int getNewVal(int &oldVal){
    double newVal=100-std::pow(10-0.1*oldVal,2);///std::sqrt((double)oldVal);
    newVal=std::floor(newVal);
    return ((int) newVal);
}


static QTimer * timer=NULL;
volatile bool b1,b2;

void MainWindow::specialRun(){
    if(b1&&b2)
    {
        b1=false;b2=false;
        qDebug()<<"adasd";
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);
    }
}

QProgressBar *qbr =NULL;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    //connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, ui->progressBar, &QProgressBar::setValue);
    //qDebug() << 33;
    qbr=ui->progressBar;
    connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, ui->progressBar/*for bypassing Warning*/,
            [=](int value) { qDebug() << value;ui->progressBar->setValue(getNewVal(value));});
    timer=new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,this, &MainWindow::specialRun);///[]() { qDebug() << "Lambda"; });
    timer->start(300);
}

MainWindow::~MainWindow()
{
    disconnect(ui->horizontalScrollBar, &QScrollBar::valueChanged, ui->progressBar, NULL);
    timer->stop();
    delete timer;
    delete ui;
}




void MainWindow::on_checkBox_stateChanged(int state)
{
    b1=false;
    if (state)
    {
        b1=true;
        qDebug()<<"b1";
    }
}

void MainWindow::on_checkBox_2_stateChanged(int state)
{
    b2=false;
    if (state)
    {
        b2=true;
        qDebug()<<"b2";
    }
}



