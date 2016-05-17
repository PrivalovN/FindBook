#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

#include <iostream>
#include <QTextStream>
#include <QTextCodec>

using namespace std;//Подключение стандартной библиотеки функций


class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void onReady();

public slots:
    int getData(QString cur_URL);     // Метод инициализации запроса на получение данных
    void onResult(QNetworkReply *reply);    // Слот обработки ответа о полученных данных
    void slotReadyRead();



private:
    QNetworkAccessManager *manager; // менеджер сетевого доступа
    QString s_Find;
    QString p_File;
    QNetworkReply *reply;
    QFile outputFile;
};

#endif // DOWNLOADER_H
