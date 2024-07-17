#pragma once

#include <QString>
#include <QStringList>

inline QString encodeString(const QString& sql) {

    QString sqla, sqlb, sqlc, tmp;

    sqla = sql.split(") VALUES (")[0];
    sqlb = sql.split(") VALUES (")[1];

    sqlb.replace(")", ";");
    sqlc = sqla + ") SELECT " + sqlb;

    for (int i = 0; i< sqlc.length(); i++) {
        int c = sqlc.at(i).toLatin1();
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
            switch (c) {
            case 90:
                tmp.append(QChar(65));
                break;
            case 122:
                tmp.append(QChar(97));
                break;
            default:
                tmp.append(QChar(c+1));
                break;
            }
        } else if (c >= 48 && c <= 57) {
            switch (c) {
            case 48:
                tmp.append(QString::number(9));
                break;
            case 49:
                tmp.append(QString::number(8));
                break;
            case 50:
                tmp.append(QString::number(7));
                break;
            case 51:
                tmp.append(QString::number(6));
                break;
            case 52:
                tmp.append(QString::number(5));
                break;
            case 53:
                tmp.append(QString::number(4));
                break;
            case 54:
                tmp.append(QString::number(3));
                break;
            case 55:
                tmp.append(QString::number(2));
                break;
            case 56:
                tmp.append(QString::number(1));
                break;
            case 57:
                tmp.append(QString::number(0));
                break;
            }
        } else {
            tmp.append(QChar(c));
        }
    }
    return tmp;
}
