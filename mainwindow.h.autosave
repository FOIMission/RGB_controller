#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *serial =new QSerialPort(this);
private slots:
    //rgb slots
    void on_redSlider_valueChanged(int value);
    void on_greenSlider_valueChanged(int value);
    void on_blueSlider_valueChanged(int value);
    void on_redSpinBox_valueChanged(int value);
    void on_greenSpinBox_valueChanged(int value);
    void on_blueSpinBox_valueChanged(int value);

    //serial button slots
    void on_ScanButton_clicked();
    void on_OpenserialButton_clicked();
    void on_button_clicked();


private:
    //rgb
    void updateColor();

    void send_str(int r_int,uint16_t channel);

    //serial
    bool Serial_Set();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
