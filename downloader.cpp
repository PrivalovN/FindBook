#include "downloader.h"

//QFile outputFile;

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    // Инициализируем менеджер ...
    manager = new QNetworkAccessManager();
    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);

   // Создание выходного файла
   QDate dateToday = QDate::currentDate();
   QString str_date = dateToday.toString("d_M_yy");
   QString m_FileO;
   m_FileO.append(str_date);
   m_FileO.append(".log");

   outputFile.setFileName(m_FileO);
   if(outputFile.open(QIODevice::Append | QIODevice::Text))
       {
           QTextStream out(&outputFile);
           out.setCodec("UTF-8");          // Установка кодека
           //out << "Thomas M. Disch: " << 334 << endl;

       }

       outputFile.close();



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
    //    qDebug() << reply->errorString();
    } else {

        int pos = 0;
        int pos1 = 0;
        QString r_Text;
        QString r_Itog;


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
                if (textTitle_n.cap(1)!= "0")
                {
                    r_Itog.append (textTitle_n.cap(1));
                    r_Itog.append (" - ");
                    r_Itog.append (textTitle.cap(1));
                    r_Itog.append("\n");
                    cout  << r_Itog.toStdString() << endl;
                 if (outputFile.open(QIODevice::Append | QIODevice::Text))
                 {
                  QTextStream writeStream(&outputFile); // Создаем объект класса QTextStream
                  writeStream << r_Itog; // Посылаем строку в поток для записи
                  outputFile.flush();
                 }
                }
            }

            if (outputFile.isOpen())
            {
                      outputFile.close(); // Закрываем файл   qDebug()<<r_Itog;
            }
        delete reply;
        emit onReady(); // Посылаем сигнал о завершении получения файла

    }
}


