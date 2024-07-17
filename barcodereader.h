#ifndef BARCODEREADER_H
#define BARCODEREADER_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include <QDebug>

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
