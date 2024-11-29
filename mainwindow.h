#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QTimer>
#include <QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>


QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonTemp_clicked();

    void on_pushButton_clicked();

    void on_pushButtonpH_clicked();

    void on_closeButtonTemp_clicked();

    void on_closeButtonTur_clicked();

    void on_closeButtonpH_clicked();

    void onSerialDataReceived();

    void on_closeButtonTDS_clicked();

    void on_clickButtonTDS_clicked();

private:
    Ui::MainWindow *ui;
     QSerialPort *serial;

     //temp
     QChart *chartTem;
     QLineSeries *seriesTem;
     int timeCountertem= 0;
     QValueAxis *axisXtem;
     QValueAxis *axisYtem;
     float temperature;


     //tur
     QValueAxis *axisXtur;
     QValueAxis *axisYtur;
     int timeCountertur= 0;
     QChart *chartTur;
     QLineSeries *seriesTur;
     float tur;

     //pH
     QValueAxis *axisXpH;
     QValueAxis *axisYpH;
     int timeCounterpH= 0;
     QChart *chartpH;
     QLineSeries *seriespH;
     float pH;

     //TDS
     QValueAxis *axisXTDS;
     QValueAxis *axisYTDS;
     int timeCounterTDS= 0;
     QChart *chartTDS;
     QLineSeries *seriesTDS;
     float TDS;

};
#endif // MAINWINDOW_H
