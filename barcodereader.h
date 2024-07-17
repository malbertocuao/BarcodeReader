#ifndef BARCODEREADER_H
#define BARCODEREADER_H

#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QMainWindow>

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
    QString getLastJpgFileName(const QString& dirPath);

};
#endif // BARCODEREADER_H
