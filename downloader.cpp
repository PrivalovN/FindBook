#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    // Инициализируем менеджер ...
    manager = new QNetworkAccessManager();

    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);


    //p_File.append ("E:/home/file.xml");
   // p_File.append ("/home/bat/file.xml");


}

void Downloader::slotReadyRead()
{
// qDebug() << "new data arrives";
}

int Downloader::getData(QString cur_URL)
{

    QUrl url(cur_URL); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    reply = manager->get(request);      // Выполняем запрос
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
   return 1;
}

void Downloader::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error()){
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {

        int pos = 0;
        int pos1 = 0;
    //    QStringList result;
        QString tTitle;    // Структура title_info
        QString r_Text;
        QString r_Itog;
        QFile filefb2;

        r_Text.append (";");
        r_Text.append ("\"");
        r_Text.append (">поиск (.*)</div>");


            QString textAll = reply->readAll();
            QRegExp textTitle("var itemCount = (.*); </script>");// Выбрали заголовок файла


            QRegExp textTitle_n(r_Text);// Выбрали заголовок файла
            textTitle_n.setMinimal(true);
            pos = textTitle.indexIn(textAll, pos);
            pos1 = textTitle_n.indexIn(textAll, pos1);

            if (textTitle.cap(1)!= "0")
            {
            //qDebug()<<" - "<<textTitle.cap(1);
                if (textTitle_n.cap(1)!= "0")
                {
                //qDebug()<<textTitle_n.cap(1);
                    r_Itog.append (textTitle_n.cap(1));
                    r_Itog.append (" - ");
                    r_Itog.append (textTitle.cap(1));
                    cout  << r_Itog.toStdString() << endl;
                    qDebug()<<r_Itog;

                }
            }

        delete reply;
        emit onReady(); // Посылаем сигнал о завершении получения файла

    }
}


