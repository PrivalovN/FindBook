#include <QCoreApplication>
#include <downloader.h>



Downloader *downloader; // Объявляем объект класса для скачивания данных по http
QString s_Find;
QString m_File; // Файл для обработки
QList<QString> s_ppf;

void delay( int millisecondsToWait );
void m_ReadF();
void readFile();
void m_CreateLists(QString m_File);
void m_Find();


int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

#ifdef Q_OS_WIN32
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif

#ifdef Q_OS_LINUX
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
   //QTextStream Qcout(stdout);

   downloader = new Downloader(); // Инициализируем Downloader

   // по нажатию кнопки запускаем получение данных по http
   //connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::m_ReadF);
   // connect(ui->pushButton, SIGNAL(clicked(bool)),SLOT(m_ReadF()));
   // по окончанию получения данных считываем данные из файл
   Downloader::connect(downloader, &Downloader::onReady,  readFile);




   if(argc!=2) {
      //printf("Не указан файл с названиями.\n");

      cout<< QString::fromUtf8("Не указан файл с названиями.\n").toLocal8Bit().data()  << endl;
      exit(1);
   }
   else
   {
      m_File.append(argv[1]);
      m_CreateLists(m_File);
   }

   qDebug()  <<m_File;
   m_ReadF();

   return a.exec();
}



void m_Find()
{
   QString cur_URL;
   //int result;


   for (int i = 0; i < s_ppf.size(); ++i)
   {

      //if (s_ppf.at(i) == "Jane")
      qDebug()  << s_ppf.at (i);


      cur_URL.append ("http://www.gornitsa.ru/items.php?search=");
      cur_URL.append (s_ppf.at (i));
      cur_URL.append ("&cat=buk");
      s_Find.append (s_ppf.at (i));
      //getData (cur_URL);
      downloader->getData(cur_URL);
      //         qDebug()  <<result;
      delay (10000);
      cur_URL.clear ();

   }

   cout << QString::fromUtf8("Поиск окончен!\n").toLocal8Bit().data()  << endl;
   qDebug()  << "Поиск окончен!";
   //downloader->destroyed ();
}




void delay( int millisecondsToWait )
{
   QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
   while( QTime::currentTime() < dieTime )
   {
      QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
   }
}

void m_ReadF()
{
   QString cur_URL;
//  int result;

   qDebug()  <<s_ppf.size();
   for (int i = 0; i < s_ppf.size(); ++i)
   {

      //if (s_ppf.at(i) == "Jane")
      //       qDebug()  << s_ppf.at (i);


      cur_URL.append ("http://www.gornitsa.ru/items.php?search=");
      cur_URL.append (s_ppf.at (i));
      cur_URL.append ("&cat=buk");
      s_Find.append (s_ppf.at (i));
      //getData (cur_URL);
      downloader->getData(cur_URL);
      //         qDebug()  <<result;
      delay (10000);
      cur_URL.clear ();

   }

   qDebug()  << "Поиск окончен!";
}

void readFile()
{
   QFile file("/home/bat/file.xml");
   if (!file.open(QIODevice::ReadOnly)) // Открваем файл, если это возможно
      return; // если открытие файла невозможно, выходим из слота
   // в противном случае считываем данные и устанавилваем их в textEdit
   //  ui->textEdit->setText(file.readAll());
}

void m_CreateLists(QString m_File)
{

   s_ppf.clear ();

   QFile inputFile(m_File);
   if (inputFile.open(QIODevice::ReadOnly))
   {
      QTextStream in(&inputFile);
      while (!in.atEnd())
      {
         s_ppf.append(in.readLine());
      }

      inputFile.close();
   }


//    QFile file(m_File);
//   // Путь откуда было запущено приложение
//   QString dir =  QCoreApplication::applicationDirPath ();
//   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//          return;
//      while (!file.atEnd()) {
//          s_ppf.append(file.readLine());
//         // process_line(line);
//      }




}
