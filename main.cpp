#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <downloader.h>


//#include <cleanexit.h>


Downloader *downloader; // Объявляем объект класса для скачивания данных по http
QString s_Find;
QString m_File; // Файл для обработки
QList<QString> s_ppf;
int d_time;

void delay( int millisecondsToWait );
void m_ReadF();
//void readFile();
void m_CreateLists(QString m_File);
void m_Find();


int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   QCoreApplication::setApplicationName("Find_books");
   QCoreApplication::setApplicationVersion("1.0");

   QCommandLineParser parser;
   parser.addHelpOption();
   parser.addVersionOption();
   parser.setApplicationDescription(QCoreApplication::translate("main","Find books from Gornica.ru."));


   parser.addPositionalArgument("s_file", QCoreApplication::translate("main", "Source file from read."));
   parser.addPositionalArgument("t_delay", QCoreApplication::translate("main", "Delay time."));

   parser.process(app);

   QList<QString> args = parser.positionalArguments();

   d_time=0;


#ifdef Q_OS_WIN32
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
#endif

#ifdef Q_OS_LINUX
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
   //QTextStream Qcout(stdout);

   downloader = new Downloader(); // Инициализируем Downloader

   if (((args.size() < 1))) {
      printf("%s\n", qPrintable(QCoreApplication::translate("main", "Error: Must specify one filename argument.")));
      parser.showHelp(1);
   }
   else
   {

      m_File.append(args.value(0));
      d_time = args.value(1,"8000").toInt();
      m_CreateLists(m_File);
   }

   qDebug()  <<m_File;

   m_ReadF();
   app.exit();
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

   qDebug()  <<s_ppf.size();
   for (int i = 0; i < s_ppf.size(); ++i)
   {

      cur_URL.append ("http://www.gornitsa.ru/items.php?search=");
      cur_URL.append (s_ppf.at (i));
      cur_URL.append ("&cat=buk");
      downloader->getData(cur_URL);
      delay (d_time);
      cur_URL.clear ();
   }

   qDebug()  << "Поиск окончен!";
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
}

