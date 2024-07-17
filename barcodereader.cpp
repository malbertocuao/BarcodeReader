#include "barcodereader.h"
#include "ui_barcodereader.h"
#include "qaesencryption.h"
#include "crypto-basic.h"


BarcodeReader::BarcodeReader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BarcodeReader)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BarcodeReader::bringToFront);
    timer->start(1000); // 5000 milisegundos = 5 segundos

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


    connect(ui->lineEdit, &QLineEdit::returnPressed, this, [=](){

        auto histoPath = QDateTime::currentDateTime().toString("yyyy/MM/dd/");
        auto folderName = qApp->applicationDirPath() + "/IMA_HISTO/" + histoPath;
        auto image = getLastJpgFileName(folderName);

        auto token = QStringLiteral("{90:BarCode}{code:%1}").arg(ui->lineEdit->text());
        auto date = QDateTime::currentDateTime();

        auto sql =
            QStringLiteral("INSERT INTO ASAi_StCommandsRegs "
                           "([StCommandID], [ai_binary], [file_path], [ai_tocken], [date], [hour], [cadence_rec], [ai_zone])"
                           " VALUES (0, 'detection', '%1', '%2', '%3', '%4', 0, %5)")
                .arg(image, token, date.toString("dd/MM/yyyy"), date.toString("HH:mm:ss"), "1");

        auto encoded = encodeString(sql);

        auto fileName = qApp->applicationDirPath() + "/DATA_BATCH/BATCH_TRANS_" +
                   date.toString("yyyy-MM-dd_HH-mm-ss-zzz") + ".bin";


        QByteArray buffer;
        buffer.append(encoded.toUtf8());
        buffer.append("\r\n");

        QAESEncryption encryption(QAESEncryption::AES_128, QAESEncryption::ECB, QAESEncryption::ZERO);
        QByteArray encodedText = encryption.encode(buffer, "ileande7df4404d08");

        QFile transFile(fileName);

        if (transFile.open(QFile::WriteOnly))
        {
            transFile.write(encodedText);
            transFile.flush();
            transFile.close();
        }

        ui->lineEdit->clear();
    });

}

BarcodeReader::~BarcodeReader()
{
    delete ui;
}

void BarcodeReader::bringToFront()
{
    if (this->isActiveWindow())
        return;

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    show();
    raise();
    activateWindow();
    setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();
    qDebug() << "Window brought to front";

    ui->lineEdit->setFocus();
}

QString BarcodeReader::getLastJpgFileName(const QString &dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        qWarning() << "La ruta no existe:" << dirPath;
        return QString();
    }

    // Configura el filtro para buscar archivos .jpg
    dir.setNameFilters(QStringList() << "*.jpg");
    dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Readable);
    dir.setSorting(QDir::Time | QDir::Reversed);

    // Obtiene la lista de archivos .jpg ordenada por fecha de modificación descendente
    QFileInfoList fileList = dir.entryInfoList();
    if (fileList.isEmpty()) {
        qWarning() << "No hay archivos .jpg en la ruta:" << dirPath;
        return QString();
    }

    // Obtiene el nombre del último archivo .jpg
    QFileInfo lastFile = fileList.first();
    return lastFile.fileName();
}
