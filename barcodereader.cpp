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
#ifdef Q_OS_WIN
    // Código específico para Windows
    HWND hwnd = (HWND)winId();
    SetForegroundWindow(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    qDebug() << "Window brought to front (Windows)";
#endif

#ifdef Q_OS_LINUX
    // Código específico para Linux con X11
    Display *display = XOpenDisplay(NULL);
    if (display) {
        Window window = (Window)winId();
        XRaiseWindow(display, window);
        XSetInputFocus(display, window, RevertToPointerRoot, CurrentTime);
        XFlush(display);
        XCloseDisplay(display);
        qDebug() << "Window brought to front (Linux)";
    } else {
        qDebug() << "Unable to open X display";
    }
#endif

#ifdef Q_OS_MAC
    // Código específico para macOS utilizando Qt
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    show();
    raise();
    activateWindow();
    setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();
    qDebug() << "Window brought to front (macOS)";
#endif
}
