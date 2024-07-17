#include "barcodereader.h"
#include "ui_barcodereader.h"

BarcodeReader::BarcodeReader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BarcodeReader)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BarcodeReader::bringToFront);
    timer->start(5000); // 5000 milisegundos = 5 segundos

    connect(ui->pushClose, &QPushButton::clicked, this, &BarcodeReader::close);
    connect(ui->pushPause, &QPushButton::clicked, this, [=](){
        if (ui->pushPause->text() == "Pausar")
        {
            ui->pushPause->setText("Reanudar");
            timer->stop();
        }
        else
        {
            ui->pushPause->setText("Pausar");
            timer->start(5000);
        }
    });
}

BarcodeReader::~BarcodeReader()
{
    delete ui;
}

void BarcodeReader::bringToFront()
{
    // Código específico para macOS utilizando Qt
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    show();
    raise();
    activateWindow();
    setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();
    qDebug() << "Window brought to front";
}
