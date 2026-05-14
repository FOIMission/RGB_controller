#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置滑块范围
    ui->redSlider->setRange(0, 255);
    ui->greenSlider->setRange(0, 255);
    ui->blueSlider->setRange(0, 255);

    // 设置SpinBox范围
    ui->redSpinBox->setRange(0, 255);
    ui->greenSpinBox->setRange(0, 255);
    ui->blueSpinBox->setRange(0, 255);

    // 设置初始值
    ui->redSlider->setValue(0);
    ui->greenSlider->setValue(0);
    ui->blueSlider->setValue(0);

    // 初始颜色更新
    updateColor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ScanButton_clicked()
{
    ui->serial_comboBox->clear();
    QString currentPort = serial->isOpen() ? serial->portName() : "";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->serial_comboBox->addItem(info.portName());
        if (info.portName() == currentPort) {
            ui->serial_comboBox->setCurrentText(currentPort);
        }
    }
}//扫描串口

void MainWindow::on_OpenserialButton_clicked()
{
    if(!serial->isOpen())
    {
        Serial_Set();
        ui->OpenserialButton->setText("关闭");
    }
    else
    {
        serial->close();
        ui->OpenserialButton->setText("打开");
    }
}//打开串口


bool MainWindow::Serial_Set()
{
    serial->setPortName(ui->serial_comboBox->currentText());
    serial->setBaudRate(115200);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    return 1;
}//串口配置

void MainWindow::send_str(int rgb_int,uint16_t channel)
{
    if(!serial->isOpen())
    {
        return;
    }
    QByteArray my_arr = QByteArray::fromHex(QString("%1").arg(rgb_int, 4, 16, QChar('0')).toLatin1());
    QByteArray tmp = QByteArray::fromHex(QString("%1").arg(channel, 2, 16, QChar('0')).toLatin1());
    my_arr.prepend(tmp);
    my_arr.prepend(QByteArray::fromHex("1F"));
    my_arr.append(QByteArray::fromHex("FE"));
    serial->write(my_arr);
    qDebug()<<my_arr<<my_arr.size();
}

void MainWindow::on_redSlider_valueChanged(int value)
{
    ui->redSpinBox->setValue(value);
    updateColor();
    int r_int = static_cast<int>(value * 4095 + 127) / 255;
    qDebug()<<r_int;
    uint16_t channel=1;
    send_str(r_int,channel);

}

void MainWindow::on_greenSlider_valueChanged(int value)
{
    ui->greenSpinBox->setValue(value);
    updateColor();
    int g_int = static_cast<int>(value * 4095 + 127) / 255;
    uint16_t channel=2;
    send_str(g_int,channel);
}

void MainWindow::on_blueSlider_valueChanged(int value)
{
    ui->blueSpinBox->setValue(value);
    updateColor();
    int b_int = static_cast<int>(value * 4095 + 127) / 255;
    uint16_t channel=3;
    send_str(b_int,channel);
}

void MainWindow::on_redSpinBox_valueChanged(int value)
{
    ui->redSlider->setValue(value);
    updateColor();
}

void MainWindow::on_greenSpinBox_valueChanged(int value)
{
    ui->greenSlider->setValue(value);
    updateColor();
}

void MainWindow::on_blueSpinBox_valueChanged(int value)
{
    ui->blueSlider->setValue(value);
    updateColor();
}

void MainWindow::updateColor()
{
    // 获取当前RGB值
    int r = ui->redSlider->value();
    int g = ui->greenSlider->value();
    int b = ui->blueSlider->value();

    // 更新颜色预览
    QColor color(r, g, b);
    QString style = QString("background-color: %1; border: 1px solid black;").arg(color.name());
    ui->colorPreview->setStyleSheet(style);

    // 更新RGB值标签
    ui->rgbValueLabel->setText(QString("RGB: (%1, %2, %3)").arg(r).arg(g).arg(b));
    ui->hexValueLabel->setText(QString("HEX: %1").arg(color.name()));
}

void MainWindow::on_button_clicked()
{
    if(serial->isOpen()){
        serial->write("helloworld");
    }
}

