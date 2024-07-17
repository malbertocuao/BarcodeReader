#ifndef BARCODEREADER_H
#define BARCODEREADER_H

#include <QMainWindow>
#include <QTimer>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#ifdef Q_OS_MAC
#include <objc/objc-runtime.h>
#endif


QT_BEGIN_NAMESPACE
namespace Ui {
class BarcodeReader;
}
QT_END_NAMESPACE

class BarcodeReader : public QMainWindow
{
    Q_OBJECT

public:
    BarcodeReader(QWidget *parent = nullptr);
    ~BarcodeReader();

private:
    Ui::BarcodeReader *ui;
    void bringToFront();

};
#endif // BARCODEREADER_H
