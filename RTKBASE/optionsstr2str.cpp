#include "optionsstr2str.h"
#include "ui_optionsstr2str.h"
#include "affichestr2str.h"
#include <QTextStream>
#include <QFile>
#include "affichestr2str.h"


int PositionMode;
int i;
char LongManual;
char LatManual;
char AltiManual;

QString Outbaudext;
QString OutSerialPortext;
QString OutFormatext;
QString Inbaudext;
QString InSerialPortext;
QString InFormatext;
QString RtcmMsgext;



OptionsStr2str::OptionsStr2str(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsStr2str)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonDefault1,SIGNAL(clicked()),this,SLOT(OuvreDefault1()));
    QObject::connect(ui->radioButtonPositionAuto,SIGNAL(checked() ),this,SLOT(on_radioButtonPositionAuto_clicked(bool checked)()) );
    QObject::connect(ui->radioButtonPositionManual,SIGNAL(checked() ),this,SLOT(on_radioButtonPositionManual_clicked(bool checked)()) );


    QObject::connect(ui->radioButtonPositionAuto,SIGNAL(checked() ),this,SLOT(AfficheOptionString()));



 // Set défault Base position mode (if not set it crashes at server start

    ui->radioButtonPositionAuto->setChecked(true);
 if (ui->radioButtonPositionAuto->isChecked())
 {
    PositionMode=1;
 }

   /* Load base position in files to display in ui
      Open, read line by line and then close file*/
{
int i=1;
QStringList list;
QString fileName = "sauvegardepourbaseManual.txt";
QFile fichier1(fileName);
fichier1.open(QIODevice::ReadOnly | QIODevice::Text);
//---------verifier ouverture fichier......
QTextStream flux(&fichier1);
QString ligne;
while(! flux.atEnd())
{
   ligne = flux.readLine();
   //traitement de la ligne
   qDebug()<<ligne;
   list<<ligne;
   i=i+1;
}

//  Display manual position
   ui->LatManualLine->setText(QString(list[0]));
   ui->LongManualLine->setText(QString(list[1]));
   ui->AltiManualLine->setText(QString(list[2]));

fichier1.close();

    }
{


/*Open, read line by line and then close file*/
int i=1;
QStringList list;
QString fileName = "sauvegardepourbase.txt";
QFile fichier1(fileName);
fichier1.open(QIODevice::ReadOnly | QIODevice::Text);
//---------verifier ouverture fichier......
QTextStream flux(&fichier1);
QString ligne;
while(! flux.atEnd())
{
ligne = flux.readLine();
//traitement de la ligne
qDebug()<<ligne;
list<<ligne;
i=i+1;
}

//  Display manual position
ui->LatAutoLine->setText(QString(list[0]));
ui->LongAutoLine->setText(QString(list[1]));
ui->AltiAutoLine->setText(QString(list[2]));

fichier1.close();

}


 // String displayed in the ui at startup

{

     QString LongAuto = ui->LongAutoLine->text();
     QString LatAuto = ui->LatAutoLine->text();
     QString AltiAuto = ui->AltiAutoLine->text();

     QString LongManual = ui->LongManualLine->text();
     QString LatManual = ui->LatManualLine->text();
     QString AltiManual = ui->AltiManualLine->text();




 QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
 Outbaudext = Outbaud;
 QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
 OutSerialPortext = OutSerialPort;
 QString OutFormat = ui->OutFormatcomboBox ->currentText();
 OutFormatext = OutFormat;
 QString Inbaud = ui->InBaudratecomboBox ->currentText();
 Inbaudext = Inbaud;
 QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
 InSerialPortext = InSerialPort;
 QString InFormat = ui->InFormatcomboBox ->currentText();
 InFormatext = InFormat;
 QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
 RtcmMsgext = RtcmMsg;



   QString DisplayRtkrcvStr= ("-in ");
   DisplayRtkrcvStr.append(&InSerialPortext);
   DisplayRtkrcvStr.append(":");
   DisplayRtkrcvStr.append(&Inbaudext);
   DisplayRtkrcvStr.append(":8:n:1:#");
   DisplayRtkrcvStr.append(&InFormatext);
   DisplayRtkrcvStr.append(" -out ");
   DisplayRtkrcvStr.append(&OutSerialPortext);
   DisplayRtkrcvStr.append(":");
   DisplayRtkrcvStr.append(&Outbaudext);
   DisplayRtkrcvStr.append(":8:n:1:#");
   DisplayRtkrcvStr.append(&OutFormatext);
   DisplayRtkrcvStr.append(" -msg ");
   DisplayRtkrcvStr.append(&RtcmMsgext);
   DisplayRtkrcvStr.append(" -p ");

   if (PositionMode==1)
   {
   DisplayRtkrcvStr.append(&LatAuto);
   DisplayRtkrcvStr.append(" ");
   DisplayRtkrcvStr.append(&LongAuto);
   DisplayRtkrcvStr.append(" ");
   DisplayRtkrcvStr.append(&AltiAuto);

   }
   if (PositionMode==2)
   {
   DisplayRtkrcvStr.append(&LatManual);
   DisplayRtkrcvStr.append(" ");
   DisplayRtkrcvStr.append(&LongManual);
   DisplayRtkrcvStr.append(" ");
   DisplayRtkrcvStr.append(&AltiManual);
   }


   ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

}



}

OptionsStr2str::~OptionsStr2str()
{
    delete ui;
}






void OptionsStr2str::OuvreDefault1()
{

    QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
    Outbaudext = Outbaud;
    QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
    OutSerialPortext = OutSerialPort;
    QString OutFormat = ui->OutFormatcomboBox ->currentText();
    OutFormatext = OutFormat;
    QString Inbaud = ui->InBaudratecomboBox ->currentText();
    Inbaudext = Inbaud;
    QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
    InSerialPortext = InSerialPort;
    QString InFormat = ui->InFormatcomboBox ->currentText();
    InFormatext = InFormat;
    QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
    RtcmMsgext = RtcmMsg;


    arga={"carlep,remierargtoujorsleprog","-in","serial://ttyACM0:115200:8:n:1:#ubx","-out","serial://ttyUSB0:38400:8:n:1:#rtcm3","-p","48.2","2.2","120.23","-msg","1004,1019,1012,1020,1006,1008"};
 //   arga={""};
    //arga={"carlepremierargtoujorsleprog","-in","serial://ttyACM0:115200:8:n:1:#ubx","-out","serial://ttyUSB0:38400:8:n:1:#RTCM3","-msg",""1004,1019,1012,1020,1006,1008""};
    // crash arga={"carlepremierargtoujorsleprog","-in","serial://ttyACM0:115200:8:n:1:#ubx","-out","serial://ttyUSB0:38400:8:n:1:#RTCM3","-msg","1004,1019,1012,1020,1006,1008", "-p","48,12,120"};
    // crash arga={"carlepremierargtoujorsleprog","-in","serial://ttyACM0:115200:8:n:1:#ubx","-out","serial://ttyUSB0:38400:8:n:1:#RTCM3","-msg","1004,1019,1012,1020,1006,1008", "-p","48 12 120"};
    /* essayer avec:
    arga={"carlepremierargtoujorsleprog","-in","serial://ttyACM0:115200:8:n:1:#ubx","-out","serial://ttyUSB0:38400:8:n:1:#RTCM3","-msg","1004,1019,1012,1020,1006,1008", "-p","48", " 12", " 120"};*/

    AfficheStr2str affichesolutionsStr2str(arga);
    this->hide();
    affichesolutionsStr2str.exec();


}






void OptionsStr2str::on_radioButtonPositionAuto_clicked()
{
    PositionMode=1;

    // String displayed in the ui at startup

   {

        QString LongAuto = ui->LongAutoLine->text();
        QString LatAuto = ui->LatAutoLine->text();
        QString AltiAuto = ui->AltiAutoLine->text();

        QString LongManual = ui->LongManualLine->text();
        QString LatManual = ui->LatManualLine->text();
        QString AltiManual = ui->AltiManualLine->text();




    QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
    Outbaudext = Outbaud;
    QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
    OutSerialPortext = OutSerialPort;
    QString OutFormat = ui->OutFormatcomboBox ->currentText();
    OutFormatext = OutFormat;
    QString Inbaud = ui->InBaudratecomboBox ->currentText();
    Inbaudext = Inbaud;
    QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
    InSerialPortext = InSerialPort;
    QString InFormat = ui->InFormatcomboBox ->currentText();
    InFormatext = InFormat;
    QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
    RtcmMsgext = RtcmMsg;



      QString DisplayRtkrcvStr= ("-in ");
      DisplayRtkrcvStr.append(&InSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Inbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&InFormatext);
      DisplayRtkrcvStr.append(" -out ");
      DisplayRtkrcvStr.append(&OutSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Outbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&OutFormatext);
      DisplayRtkrcvStr.append(" -msg ");
      DisplayRtkrcvStr.append(&RtcmMsgext);
      DisplayRtkrcvStr.append(" -p ");

 //Display auto position
      DisplayRtkrcvStr.append(&LatAuto);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&LongAuto);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&AltiAuto);




      ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

}



}



void OptionsStr2str::on_radioButtonPositionManual_clicked()
{
    PositionMode=2;


    // String displayed in the ui at startup

   {

        QString LongAuto = ui->LongAutoLine->text();
        QString LatAuto = ui->LatAutoLine->text();
        QString AltiAuto = ui->AltiAutoLine->text();

        QString LongManual = ui->LongManualLine->text();
        QString LatManual = ui->LatManualLine->text();
        QString AltiManual = ui->AltiManualLine->text();




    QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
    Outbaudext = Outbaud;
    QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
    OutSerialPortext = OutSerialPort;
    QString OutFormat = ui->OutFormatcomboBox ->currentText();
    OutFormatext = OutFormat;
    QString Inbaud = ui->InBaudratecomboBox ->currentText();
    Inbaudext = Inbaud;
    QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
    InSerialPortext = InSerialPort;
    QString InFormat = ui->InFormatcomboBox ->currentText();
    InFormatext = InFormat;
    QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
    RtcmMsgext = RtcmMsg;



      QString DisplayRtkrcvStr= ("-in ");
      DisplayRtkrcvStr.append(&InSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Inbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&InFormatext);
      DisplayRtkrcvStr.append(" -out ");
      DisplayRtkrcvStr.append(&OutSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Outbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&OutFormatext);
      DisplayRtkrcvStr.append(" -msg ");
      DisplayRtkrcvStr.append(&RtcmMsgext);
      DisplayRtkrcvStr.append(" -p ");


// Disolay manual position
      DisplayRtkrcvStr.append(&LatManual);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&LongManual);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&AltiManual);



      ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

}


}


void OptionsStr2str::on_pushButtonManual_clicked()
{

    /*Open, read line by line and then close file*/
int i=1;
QStringList list;
QString fileName = "sauvegardepourbaseManual.txt";
QFile fichier1(fileName);
fichier1.open(QIODevice::ReadOnly | QIODevice::Text);
//---------verifier ouverture fichier......
QTextStream flux(&fichier1);
QString ligne;
while(! flux.atEnd())
{
   ligne = flux.readLine();
   //traitement de la ligne
   qDebug()<<ligne;
   list<<ligne;
   i=i+1;
}

fichier1.close();


/*Save Manual position. This position will be used in Manual Base Mode*/

 QString LongManual = ui->LongManualLine->text();
 QString LatManual = ui->LatManualLine->text();
 QString AltiManual = ui->AltiManualLine->text();

QFile CoordManual("sauvegardepourbaseManual.txt");

if (!CoordManual.open(QIODevice::WriteOnly | QIODevice::Text))
   return;


QTextStream out1(&CoordManual);
 if(i>1)
{
   out1<<LatManual<<endl;
   out1<<LongManual<<endl;
   out1<<AltiManual<<endl;
}



CoordManual.close();



// String displayed in the ui


if (PositionMode==1)
 {

QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
Outbaudext = Outbaud;
QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
OutSerialPortext = OutSerialPort;
QString OutFormat = ui->OutFormatcomboBox ->currentText();
OutFormatext = OutFormat;
QString Inbaud = ui->InBaudratecomboBox ->currentText();
Inbaudext = Inbaud;
QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
InSerialPortext = InSerialPort;
QString InFormat = ui->InFormatcomboBox ->currentText();
InFormatext = InFormat;
QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
RtcmMsgext = RtcmMsg;



  QString DisplayRtkrcvStr= ("-in ");
  DisplayRtkrcvStr.append(&InSerialPortext);
  DisplayRtkrcvStr.append(":");
  DisplayRtkrcvStr.append(&Inbaudext);
  DisplayRtkrcvStr.append(":8:n:1:#");
  DisplayRtkrcvStr.append(&InFormatext);
  DisplayRtkrcvStr.append(" -out ");
  DisplayRtkrcvStr.append(&OutSerialPortext);
  DisplayRtkrcvStr.append(":");
  DisplayRtkrcvStr.append(&Outbaudext);
  DisplayRtkrcvStr.append(":8:n:1:#");
  DisplayRtkrcvStr.append(&OutFormatext);
  DisplayRtkrcvStr.append(" -msg ");
  DisplayRtkrcvStr.append(&RtcmMsgext);
  DisplayRtkrcvStr.append(" -p ");

  DisplayRtkrcvStr.append(" test 1");

  ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

 }
if (PositionMode==2)
 {

QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
Outbaudext = Outbaud;
QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
OutSerialPortext = OutSerialPort;
QString OutFormat = ui->OutFormatcomboBox ->currentText();
OutFormatext = OutFormat;
QString Inbaud = ui->InBaudratecomboBox ->currentText();
Inbaudext = Inbaud;
QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
InSerialPortext = InSerialPort;
QString InFormat = ui->InFormatcomboBox ->currentText();
InFormatext = InFormat;
QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
RtcmMsgext = RtcmMsg;



  QString DisplayRtkrcvStr= ("-in ");
  DisplayRtkrcvStr.append(&InSerialPortext);
  DisplayRtkrcvStr.append(":");
  DisplayRtkrcvStr.append(&Inbaudext);
  DisplayRtkrcvStr.append(":8:n:1:#");
  DisplayRtkrcvStr.append(&InFormatext);
  DisplayRtkrcvStr.append(" -out ");
  DisplayRtkrcvStr.append(&OutSerialPortext);
  DisplayRtkrcvStr.append(":");
  DisplayRtkrcvStr.append(&Outbaudext);
  DisplayRtkrcvStr.append(":8:n:1:#");
  DisplayRtkrcvStr.append(&OutFormatext);
  DisplayRtkrcvStr.append(" -msg ");
  DisplayRtkrcvStr.append(&RtcmMsgext);
  DisplayRtkrcvStr.append(" -p ");

  DisplayRtkrcvStr.append(" test 2");

  ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

 }



}


void OptionsStr2str::on_UpdateOptionspushButton_clicked()
{


    // String displayed in the ui


        QString LongAuto = ui->LongAutoLine->text();
        QString LatAuto = ui->LatAutoLine->text();
        QString AltiAuto = ui->AltiAutoLine->text();

        QString LongManual = ui->LongManualLine->text();
        QString LatManual = ui->LatManualLine->text();
        QString AltiManual = ui->AltiManualLine->text();




    QString Outbaud = ui->OutBaudRatecomboBox ->currentText();
    Outbaudext = Outbaud;
    QString OutSerialPort = ui->OutSerialPortcomboBox ->currentText();
    OutSerialPortext = OutSerialPort;
    QString OutFormat = ui->OutFormatcomboBox ->currentText();
    OutFormatext = OutFormat;
    QString Inbaud = ui->InBaudratecomboBox ->currentText();
    Inbaudext = Inbaud;
    QString InSerialPort = ui->InSerialPortcomboBox ->currentText();
    InSerialPortext = InSerialPort;
    QString InFormat = ui->InFormatcomboBox ->currentText();
    InFormatext = InFormat;
    QString RtcmMsg = ui->RtcmMsgcomboBox ->currentText();
    RtcmMsgext = RtcmMsg;



      QString DisplayRtkrcvStr= ("-in ");
      DisplayRtkrcvStr.append(&InSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Inbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&InFormatext);
      DisplayRtkrcvStr.append(" -out ");
      DisplayRtkrcvStr.append(&OutSerialPortext);
      DisplayRtkrcvStr.append(":");
      DisplayRtkrcvStr.append(&Outbaudext);
      DisplayRtkrcvStr.append(":8:n:1:#");
      DisplayRtkrcvStr.append(&OutFormatext);
      DisplayRtkrcvStr.append(" -msg ");
      DisplayRtkrcvStr.append(&RtcmMsgext);
      DisplayRtkrcvStr.append(" -p ");

      if (PositionMode==1)
      {
      DisplayRtkrcvStr.append(&LatAuto);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&LongAuto);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&AltiAuto);

      }
      if (PositionMode==2)
      {
      DisplayRtkrcvStr.append(&LatManual);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&LongManual);
      DisplayRtkrcvStr.append(" ");
      DisplayRtkrcvStr.append(&AltiManual);
      }


      ui->RtkrcvOptionstextBrowser->setText(DisplayRtkrcvStr);

}


