#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    serial=new QSerialPort(this);

    serial->setPortName("/dev/ttyAMA0");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(serial->open(QIODevice::ReadOnly))
    {
        connect(serial,&QSerialPort::readyRead,this,&MainWindow::onSerialDataReceived);
        qDebug()<<"Open serial sucessfully!";
    }else{
        qDebug()<<"Fail to open serial!";
    }

    //TEM CHART
    seriesTem = new QLineSeries();
    chartTem = new QChart();
    chartTem->addSeries(seriesTem);
    chartTem->createDefaultAxes();


    QChartView *chartViewTem = new QChartView(chartTem);
    chartViewTem->setRenderHint(QPainter::Antialiasing);
    chartViewTem->setStyleSheet("border: none;");

    for (QAbstractAxis *axis : chartTem->axes(Qt::Horizontal)) {
        chartTem->removeAxis(axis);
    }
    for (QAbstractAxis *axis : chartTem->axes(Qt::Vertical)) {
        chartTem->removeAxis(axis);
    }
    QValueAxis *axisXtem = new QValueAxis();
    axisXtem->setRange(0, 10);
    axisXtem->setLabelFormat("%d");
    axisXtem->setTickCount(11);

    QValueAxis *axisYtem = new QValueAxis();
    axisYtem->setRange(8, 40);  // 数据范围设置
    axisYtem->setTickCount(11);
    chartTem->addAxis(axisXtem, Qt::AlignBottom);
    chartTem->addAxis(axisYtem, Qt::AlignLeft);
    seriesTem->attachAxis(axisXtem);
    seriesTem->attachAxis(axisYtem);

    auto *layoutTem = new QVBoxLayout();
    layoutTem->setContentsMargins(0, 0, 0, 0);  // 设置边距为0
    ui->chartWidgettem->setLayout(layoutTem);
    layoutTem->addWidget(chartViewTem);
    // 在chartWidget上设置布局并添加chartView
    ui->chartWidgettem->setLayout(new QVBoxLayout);  // 确保chartWidget有一个布局
    ui->chartWidgettem->layout()->addWidget(chartViewTem);
    chartViewTem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->chartWidgettem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    //tur chart
    seriesTur = new QLineSeries();
    chartTur = new QChart();
    chartTur->addSeries(seriesTur);
    chartTur->createDefaultAxes();


    QChartView *chartViewTur = new QChartView(chartTur);
    chartViewTur->setRenderHint(QPainter::Antialiasing);
    chartViewTur->setStyleSheet("border: none;");

    for (QAbstractAxis *axis : chartTur->axes(Qt::Horizontal)) {
        chartTur->removeAxis(axis);
    }
    for (QAbstractAxis *axis : chartTur->axes(Qt::Vertical)) {
        chartTur->removeAxis(axis);
    }
    QValueAxis *axisXtur = new QValueAxis();
    axisXtur->setRange(0, 10);
    axisXtur->setLabelFormat("%d");
    axisXtur->setTickCount(11);

    QValueAxis *axisYtur = new QValueAxis();
    axisYtur->setRange(0, 100);  // 数据范围设置
    axisYtur->setTickCount(6);
    chartTur->addAxis(axisXtur, Qt::AlignBottom);
    chartTur->addAxis(axisYtur, Qt::AlignLeft);
    seriesTur->attachAxis(axisXtur);
    seriesTur->attachAxis(axisYtur);
    // 在chartWidget上设置布局并添加chartView
    ui->chartWidgettur->setLayout(new QVBoxLayout);  // 确保chartWidget有一个布局
    ui->chartWidgettur->layout()->addWidget(chartViewTur);
    chartViewTur->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->chartWidgettur->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //ph chart

    seriespH = new QLineSeries();
    chartpH = new QChart();
    chartpH->addSeries(seriespH);
    chartpH->createDefaultAxes();

    QChartView *chartViewpH = new QChartView(chartpH);
    chartViewpH->setRenderHint(QPainter::Antialiasing);
    chartViewpH->setStyleSheet("border: none;");

    for (QAbstractAxis *axis : chartpH->axes(Qt::Horizontal)) {
        chartpH->removeAxis(axis);
    }
    for (QAbstractAxis *axis : chartpH->axes(Qt::Vertical)) {
        chartpH->removeAxis(axis);
    }
    QValueAxis *axisXpH = new QValueAxis();
    axisXpH->setRange(0, 10);
    axisXpH->setLabelFormat("%d");
    axisXpH->setTickCount(11);

    QValueAxis *axisYpH = new QValueAxis();
    axisYpH->setRange(0, 12);  // 数据范围设置
    axisYpH->setTickCount(13);
    chartpH->addAxis(axisXpH, Qt::AlignBottom);
    chartpH->addAxis(axisYpH, Qt::AlignLeft);
    seriespH->attachAxis(axisXpH);
    seriespH->attachAxis(axisYpH);
    // 在chartWidget上设置布局并添加chartView
    ui->chartWidgetpH->setLayout(new QVBoxLayout);  // 确保chartWidget有一个布局
    ui->chartWidgetpH->layout()->addWidget(chartViewpH);
    chartViewpH->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->chartWidgetpH->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //TDS chart

    seriesTDS = new QLineSeries();
    chartTDS = new QChart();
    chartTDS->addSeries(seriesTDS);
    chartTDS->createDefaultAxes();


    QChartView *chartViewTDS = new QChartView(chartTDS);
    chartViewTDS->setRenderHint(QPainter::Antialiasing);
    chartViewTDS->setStyleSheet("border: none;");

    for (QAbstractAxis *axis : chartTDS->axes(Qt::Horizontal)) {
        chartTDS->removeAxis(axis);
    }
    for (QAbstractAxis *axis : chartTDS->axes(Qt::Vertical)) {
        chartTDS->removeAxis(axis);
    }
    QValueAxis *axisXTDS = new QValueAxis();
    axisXTDS->setRange(0, 10);
    axisXTDS->setLabelFormat("%d");
    axisXTDS->setTickCount(11);

    QValueAxis *axisYTDS = new QValueAxis();
    axisYTDS->setRange(0, 1000);  // 数据范围设置
    axisYTDS->setTickCount(11);
    chartTDS->addAxis(axisXTDS, Qt::AlignBottom);
    chartTDS->addAxis(axisYTDS, Qt::AlignLeft);
    seriesTDS->attachAxis(axisXTDS);
    seriesTDS->attachAxis(axisYTDS);

    // 在chartWidget上设置布局并添加chartView
    ui->chartWidgetTDS->setLayout(new QVBoxLayout);  // 确保chartWidget有一个布局
    ui->chartWidgetTDS->layout()->addWidget(chartViewTDS);
    chartViewTDS->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->chartWidgetTDS->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonTemp_clicked()
{
    qDebug() << "Button clicked, switching to TempPage";  // 添加调试信息
    ui->stackedWidget->setCurrentWidget(ui->TempPage);
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Button clicked, switching to TurPage";  // 添加调试信息
    ui->stackedWidget->setCurrentWidget(ui->TurPage);
}


void MainWindow::on_pushButtonpH_clicked()
{
    qDebug() << "Button clicked, switching to pHPage";  // 添加调试信息
    ui->stackedWidget->setCurrentWidget(ui->pHPage);
}


void MainWindow::on_closeButtonTemp_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

        if (currentIndex > 0) {
            ui->stackedWidget->setCurrentIndex(0);
        }
}


void MainWindow::on_closeButtonTur_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

        if (currentIndex > 0) {
            ui->stackedWidget->setCurrentIndex(0);
        }
}


void MainWindow::on_closeButtonpH_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

        if (currentIndex > 0)
        {
            ui->stackedWidget->setCurrentIndex(0);
        }
}

void MainWindow::MainWindow::onSerialDataReceived()
{
    while(serial->bytesAvailable() > 0)
    {
        QByteArray data = serial->readAll();
        QString dataStr = QString::fromLatin1(data).trimmed();  // 将数据转换为字符串并去除首尾空格
        qDebug() << "Received data:" << dataStr;

        // 使用split方法解析字符串
        QStringList parts = dataStr.split(":");
        if (parts.size() == 2 && parts[0] == "tem")
        {
            bool ok;
            temperature = parts[1].toDouble(&ok);  // 转换为整数
            if (ok)
            {
                qDebug() << "Temperature:" << temperature;
                qDebug() << "timeCounter:" << timeCountertem;

                seriesTem->append(timeCountertem,temperature);

                if(timeCountertem>10)
                {
                    seriesTem->clear();
                    timeCountertem=-1;
                }
                timeCountertem++;


                chartTem->update();

                ui->labelTemp->setText(QString::number(temperature, 'f', 2)+"℃");
                QFont font = ui->labelTemp->font();
                font.setPointSize(16);
                ui->labelTemp->setFont(font);

            }
         }



        if (parts.size() == 2 && parts[0] == "tur")
        {
            bool ok;
            tur = parts[1].toDouble(&ok);  // 转换为整数
            if (ok)
            {
                qDebug() << "Tur:" <<tur;
                qDebug() << "timeCounter:" << timeCountertur;

                seriesTur->append(timeCountertur,tur);

                if(timeCountertur>10)
                {
                    seriesTur->clear();
                    timeCountertur=-1;
                }
                timeCountertur++;

                chartTur->update();

                ui->labelTur2->setText(QString::number(tur, 'f', 2)+"NTU");
                QFont fontTur = ui->labelTur2->font();
                fontTur.setPointSize(16);
                ui->labelTDS->setFont(fontTur);
            }
         }

        if (parts.size() == 2 && parts[0] == "pH")
        {
            bool ok;
            pH = parts[1].toDouble(&ok);  // 转换为整数
            if (ok)
            {
                qDebug() << "pH:" <<pH;
                qDebug() << "timeCounterpH:" << timeCounterpH;

                seriespH->append(timeCounterpH,pH);

                if(timeCounterpH>10)
                {
                    seriespH->clear();
                    timeCounterpH=-1;
                }
                timeCounterpH++;

                ui->labelpH->setText(QString::number(pH, 'f', 2));
                QFont font = ui->labelTemp->font();
                font.setPointSize(16);
                ui->labelpH->setFont(font);

                chartpH->update();

                ui->labelpH2->setText(QString::number(pH, 'f', 2));
                QFont fontpH = ui->labelpH2->font();
                fontpH.setPointSize(16);
                ui->labelpH2->setFont(fontpH);
            }
         }
        if (parts.size() == 2 && parts[0] == "TDS")
        {
            bool ok;
            TDS = parts[1].toDouble(&ok);  // 转换为整数
            if (ok)
            {
                qDebug() << "TDS:" <<TDS;
                qDebug() << "timeCounterTDS:" << timeCounterTDS;

                seriesTDS->append(timeCounterTDS,TDS);

                if(timeCounterTDS>10)
                {
                    seriesTDS->clear();
                    timeCounterTDS=-1;
                }
                timeCounterTDS++;
                ui->labelTDS->setText(QString::number(TDS, 'f', 2)+"TDS");
                QFont font = ui->labelTDS->font();
                font.setPointSize(16);
                ui->labelTDS->setFont(font);

                chartTDS->update();

                ui->labelTDS2->setText(QString::number(TDS, 'f', 2)+"TDS");
                QFont fontTDS = ui->labelTDS->font();
                fontTDS.setPointSize(12);
                ui->labelTDS2->setFont(fontTDS);
            }
         }

    }
}



void MainWindow::on_closeButtonTDS_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();

        if (currentIndex > 0)
        {
            ui->stackedWidget->setCurrentIndex(0);
        }
}





void MainWindow::on_clickButtonTDS_clicked()
{
    qDebug() << "Button clicked, switching to pHPage";  // 添加调试信息
    ui->stackedWidget->setCurrentWidget(ui->TDSPage);
}

