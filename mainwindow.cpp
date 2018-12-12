#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QComboBox>
#include<QMessageBox>
using namespace std;
#include<QStringList>
#include<QRegularExpressionMatchIterator>
 char r[500];
 string str2,str,str3,str4; size_t found,found2,found3,found4;string yut;int h2=0;
 bool oscuro=0,gtkwave=0;
    QString ubicacionActual,nombreActual;
    QStringList nombres_verticales_entradas,bits_lista,in_lista;
string proyecto,proyecto_copia;
void reemplazar( string &s, const string &search, const string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

string removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}

long long DtoB(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}
int BtoD(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
std::string nameFromFile(const std::string& fullPath)
{
  const size_t lastSlashIndex = fullPath.find_last_of("/\\");
  return fullPath.substr(lastSlashIndex + 1);
}
string get_component(string direccion_archivo){
    std::locale loc;
    ifstream file(direccion_archivo);
    string str, component, b;
    string signal_out,signal_out_nombres,signal_in,singla_in_nombres;
     while (getline(file, str))
     {
     b.clear();
     for (std::string::size_type i=0; i<str.length(); ++i)
     b+= std::toupper(str[i],loc);
     if (b.find("END") != std::string::npos){break;}
     else {
         component+=b;
         component+='\n';
    }
    }
    reemplazar(component,"ENTITY","COMPONENT");
    component+="END COMPONENT;\n";

    return component;
}
string testbench;
unsigned int sd=1;
QStringList signal_lista;
QString convertidorActual="decimal",signales_valores;
string name_actual,namePuro_actual,name_tb_actual,namePuro_tb_actual;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_3->setText("");
for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
    ui->textEdit_3->append(QString::number(sd));}
    connect(ui->textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->textEdit_3->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->textEdit_3->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->textEdit->verticalScrollBar(), SLOT(setValue(int)));
    connect(&process , SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));

    ui->textEdit->verticalScrollBar()->setValue(0); ui->textEdit_3->verticalScrollBar()->setValue(0);
    ui->textEdit_3->setReadOnly(true);
QMainWindow::showMaximized();
highlighter = new Highlighter(ui->textEdit->document());

ui->groupBox_2->setVisible(false);
ui->groupBox->setVisible(false);
ui->groupBox_5->setVisible(false);
ui->groupBox_4->setVisible(true);
oscuro=0;

QPixmap p("F.png"); // load pixmap



ui->label_5->setPixmap(p);



QMainWindow::showNormal();
QMainWindow::resize(800,500);

}
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   QPixmap p("F.png"); // load pixmap
   // get label dimensions
   int w = ui->groupBox_4->width();
   int h = ui->groupBox_4->height();

   // set a scaled pixmap to a w x h window keeping its aspect ratio
   ui->label_5->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    dir = QFileDialog::getOpenFileName( this,tr("Abrir .VHDL")," ",tr("VHDL (*.vhdl)"));
    file.setFileName(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
    else {
       i++;

        fileInfo=(file.fileName());
        nombre[i]=fileInfo.fileName();
        dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
        ui->listWidget->addItem(nombre[i]);
        in.setDevice(&file);
        codigo[i]=in.readAll();
      //  ui->textEdit->setText(codigo[i]);
        ui->textEdit_3->setText("");
            for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
                ui->textEdit_3->append(QString::number(sd));

            //
            }
ui->listWidget->setCurrentRow(i);
if(i==0)ui->textEdit->setText(codigo[0]);

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
    }



}

void MainWindow::on_pushButton_4_clicked()
{
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_actionGuardar_triggered()
{
    QString dir=ubicacionActual+nombreActual+".vhdl";
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
}

void MainWindow::on_actionGuardar_como_triggered()
{
    dir = QFileDialog::getSaveFileName(this, tr("Guardar"),"prueba",tr("VHDL (*.vhdl)"));
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
}

void MainWindow::on_pushButton_clicked()
{
   if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
   else {
      ui->textEdit_2->setTextColor(Qt::white);
   }

    ui->textEdit_2->setText("");
    ubicacionActual=dirPuro[ui->listWidget->currentRow()];
    nombreActual=nombre[ui->listWidget->currentRow()];
   nombreActual.replace(".vhdl","");

  QString dir=ubicacionActual+nombreActual+".vhdl";
    QFile file2(dir);
        if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
        QTextStream out(&file2);
        out << ui->textEdit->toPlainText();
        file2.flush();
        file2.close();
//        ui->textEdit_2->append("Compilando "+nombreActual);


process.setWorkingDirectory(ubicacionActual);
ui->textEdit_2->append("ghdl -a "+dir);
    process.start("ghdl -a "+dir);
    process.waitForFinished(-1); // will wait forever until finished

     Consola = process.readAllStandardOutput();
     errorConsola = process.readAllStandardError();
     if(errorConsola.isEmpty()){
         if(!oscuro)ui->textEdit_2->setTextColor(Qt::blue);
         else {
             ui->textEdit_2->setTextColor(Qt::green);
         }
         ui->textEdit_2->append("Compilado bien");}

    else{ui->textEdit_2->setTextColor(Qt::red);
        ui->textEdit_2->append(errorConsola);
}
ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());
}

void MainWindow::on_radioButton_clicked()
{
    QStringList nn;
    if(convertidorActual=="decimal"){
        for(int i=0;i<ui->tableWidget->model()->rowCount();i++){
            for(int j=0;j<ui->tableWidget->model()->columnCount();j++){
ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(DtoB(ui->tableWidget->item(i,j)->text().toLong()))));
            }
        }
    }
    convertidorActual="binario";
}

void MainWindow::on_radioButton_2_clicked()
{
    if(convertidorActual=="binario"){
        for(int i=0;i<ui->tableWidget->model()->rowCount();i++){
            for(int j=0;j<ui->tableWidget->model()->columnCount();j++){

    ui->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(BtoD(ui->tableWidget->item(i,j)->text().toLong()))));
            }
        }
    }
    convertidorActual="decimal";
}

void MainWindow::on_lineEdit_returnPressed()
{

}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{


 /*
    codigo[ui->listWidget->currentRow()]=ui->textEdit->toPlainText();
ui->textEdit->setText("");
    int n= ui->listWidget->currentRow();
i=n;
    ui->textEdit->setText(codigo[n]);
    name_actual=nombre[n].toUtf8().constData();
    QString tmp=name_actual.c_str();
    name_tb_actual = tmp.replace(".vhdl","_tb.vhdl").toUtf8().constData();
    namePuro_actual = tmp.replace(".vhdl"," ").toUtf8().constData();
    namePuro_tb_actual = tmp.replace(".vhdl","_tb").toUtf8().constData();


    dir=direccion[n];
*/


//    ui->listWidget->setPalette(this->style()->standardPalette());
//    QListWidgetItem *item= ui->listWidget->currentItem();
//    item->setBackgroundColor(QColor(255,196,0));
}

void MainWindow::on_textEdit_cursorPositionChanged()
{

}

void MainWindow::on_pushButton_6_clicked()
{
    dir = QFileDialog::getOpenFileName( this,tr("Abrir .VHDL")," ",tr("VHDL (*.vhdl)"));
    file.setFileName(dir);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
    else {
       i++;

        fileInfo=(file.fileName());
        nombre[i]=fileInfo.fileName();
        dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
        ui->listWidget->addItem(nombre[i]);
        in.setDevice(&file);
        codigo[i]=in.readAll();
      //  ui->textEdit->setText(codigo[i]);
        ui->textEdit_3->setText("");
            for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
                ui->textEdit_3->append(QString::number(sd));

            //
            }
ui->listWidget->setCurrentRow(i);
if(i==0)ui->textEdit->setText(codigo[0]);

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
    }


}

void MainWindow::on_checkBox_clicked()
{

}
 //string jaja3;


void MainWindow::on_tableWidget_cellPressed(int row, int column)
{
//    QModelIndex next_index = ui->tableWidget->model()->index(row + 1, 0);
//    ui->tableWidget->setCurrentIndex(next_index);

}

void MainWindow::on_pushButton_3_clicked()
{
ui->groupBox_4->setVisible(false);
ui->groupBox_2->setVisible(false);
ui->groupBox->setVisible(false);
ui->groupBox_5->setVisible(true);
int n = ui->lineEdit_7->text().toULong();

ui->tableWidget_2->setRowCount(n);
ui->tableWidget_2->setColumnCount(3);
QStringList lis2=(QStringList()<<"Puerto"<<"Direccion"<<"Bits");
ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

for(int i=0;i<n;i++){
QComboBox* combobox = new QComboBox();
ui->tableWidget_2->setCellWidget(i,1,combobox);
QStringList list=(QStringList()<<"in"<<"out"<<"inout");
combobox->addItems(list);

#if (defined (_WIN32) || defined (_WIN64))
 ui->lineEdit_5->setText("C:\Windows");
#endif
#if (defined (LINUX) || defined (__linux__))
 ui->lineEdit_5->setText("/home/"+qgetenv("USER")+"/");
#endif


}
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->groupBox_5->setVisible(false);

}

void MainWindow::on_tableWidget_pressed(const QModelIndex &index)
{

}

void MainWindow::on_radioButton_3_clicked()
{

}

void MainWindow::on_radioButton_4_clicked()
{

}

void MainWindow::on_actionmodo_Blanco_triggered()
{
    oscuro=0;
    highlighter->setcolor(1);

   ui->textEdit->setStyleSheet("");
   ui->textEdit_2->setStyleSheet("");

   ui->textEdit_3->setStyleSheet("");
   ui->listWidget->setStyleSheet("");
   ui->pushButton->setStyleSheet("");
      ui->tableWidget->setStyleSheet("");   ui->tableWidget_2->setStyleSheet("");
ui->centralWidget->setStyleSheet("");
}

void MainWindow::on_actionmodo_Dark_triggered()
{
    oscuro=1;
    highlighter->setcolor(0);

    ui->textEdit->setStyleSheet("color: white;"
                                     "background-color: rgb(30,30,30);;"
                                     "foreground-color: white;"
                                     "selection-background-color: rgb(90,90,90);");

/*
    ui->pushButton->setStyleSheet("color: white;"
                                     "background-color: rgb(40,40,40);"
                                     "border-style: outset;"
                                     "border-width: 1px;"
                                     "border-color: green;"
"border-radius: 10px;"
                                  "padding: 6px;"
                                  "selection-background-color: rgb(90,90,90);");
*/


    ui->textEdit_2->setStyleSheet("color: rgb(0,255,0);"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: rgb(0,255,0);"
                                  "selection-background-color: rgb(90,90,90);");



    ui->textEdit_3->setStyleSheet("color: white;"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgb(90,90,90);");

    ui->listWidget->setStyleSheet("color: white;"
                                  "background-color: rgb(30,30,30);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgb(90,90,90);");


    ui->tableWidget->setStyleSheet("color: white;"
                                  "background-color: rgb(40,40,40);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgb(90,90,90);");

    ui->tableWidget_2->setStyleSheet("color: white;"
                                  "background-color: rgb(40,40,40);"
                                  "foreground-color: white;"
                                  "selection-background-color: rgb(90,90,90);");


    ui->centralWidget->setStyleSheet("color: white;"
                                  "background-color: rgb(50,50,50);"
                                  "foreground-color: white;"

                                     "border-width: 1px;"
                                     "border-color: cyan;"
                                  "selection-background-color: rgb(90,90,90);");




}

void MainWindow::on_actionFuente_2_triggered()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok){ui->textEdit->setFont(font);ui->textEdit_3->setFont(font);}
    else return;
}

void MainWindow::on_textEdit_textChanged()
{
    ui->textEdit_3->setText("");
        for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
            ui->textEdit_3->append(QString::number(sd));
        }
}

void MainWindow::on_actionNuevo_triggered()
{
//nuevoproy.show();
    ui->groupBox_4->setVisible(false);
    ui->groupBox_2->setVisible(false);
    ui->groupBox->setVisible(false);
    ui->groupBox_5->setVisible(true);
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Nombres"<<"Puerto"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out");
    combobox->addItems(list);

    #if (defined (_WIN32) || defined (_WIN64))
     ui->lineEdit_5->setText("C:\Windows");
    #endif
    #if (defined (LINUX) || defined (__linux__))
     ui->lineEdit_5->setText("/home/"+qgetenv("USER")+"/");
    #endif

}
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->groupBox->setTitle("Proyecto actual: "+current->text());
if(i>=1){
  //  ui->textEdit_2->setText(current->text());
  //  ui->textEdit_2->append(previous->text());
    ui->textEdit_2->setText(QString::number(ui->listWidget->row(current)));
    ui->textEdit_2->append(QString::number(ui->listWidget->row(previous)));
codigo[ui->listWidget->row(previous)]=ui->textEdit->toPlainText();
ui->textEdit->setText(codigo[ui->listWidget->row(current)]);
ubicacionActual=dirPuro[ui->listWidget->row(current)];
nombreActual=nombre[ui->listWidget->row(current)];
}
}

void MainWindow::on_lineEdit_7_returnPressed()
{
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Nombres"<<"Puerto"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out");
    combobox->addItems(list);
}
}

void MainWindow::on_pushButton_9_clicked()
{
    int n = ui->lineEdit_7->text().toULong();

    ui->tableWidget_2->setRowCount(n);
    ui->tableWidget_2->setColumnCount(3);
    QStringList lis2=(QStringList()<<"Nombres"<<"Puerto"<<"Bits");
    ui->tableWidget_2->setHorizontalHeaderLabels(lis2);

    for(int i=0;i<n;i++){
    QComboBox* combobox = new QComboBox();
    ui->tableWidget_2->setCellWidget(i,1,combobox);
    QStringList list=(QStringList()<<"in"<<"out");
    combobox->addItems(list);
}
}

void MainWindow::on_pushButton_8_clicked()
{
    proyecto.clear();
 //   if(i>=0)codigo[i]=ui->textEdit->toPlainText();
    bool bien=true;
    proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\nentity ";
    proyecto+=ui->lineEdit_6->text().toUtf8().constData();
    proyecto+=" is\nport(\n";

  //  QString item_2,item_3;QStringList InputComboData;
for(int j=0;j<ui->tableWidget_2->model()->rowCount();j++){
    bien=true;
    QTableWidgetItem* item = ui->tableWidget_2->item(j,0);
    if (!item || item->text().isEmpty())
    {
      bien=false;
    }
    //if(ui->tableWidget_2->item(j,0)->text().isEmpty()){bien=false;break;}
    if(bien){
    proyecto+=ui->tableWidget_2->item(j,0)->text().toUtf8().constData();proyecto+=" : ";
    QComboBox *m = qobject_cast<QComboBox*>(ui->tableWidget_2->cellWidget(j,1));
   proyecto+=m->currentText().toUtf8().constData();proyecto+=" ";


    int num = ui->tableWidget_2->item(j,2)->text().toInt();
   //  int num=2;
   if(num>1){
   if(j==ui->tableWidget_2->model()->rowCount()-1)
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0)\n";
   else
       proyecto+="std_logic_vector("+to_string(num-1)+" downto 0);\n";
   }
   else{if(j==ui->tableWidget_2->model()->rowCount()-1)proyecto+="std_logic\n";
       else
           proyecto+="std_logic;\n";}

    //InputComboData << m->currentText();
    }}
//cout<<proyecto<<endl;

proyecto+=");\n";
proyecto+="end ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=";\n\n";
proyecto+="architecture arc of ";
proyecto+=ui->lineEdit_6->text().toUtf8().constData();
proyecto+=" is\n\nbegin\n\nend arc;";

if(i==-1)ui->textEdit->setText(proyecto.c_str());

ui->groupBox->setVisible(true);
ui->groupBox_2->setVisible(false);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
ui->textEdit_3->setText("");
for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
    ui->textEdit_3->append(QString::number(sd));}

//guardar
ubicacionActual=ui->lineEdit_5->text();
nombreActual=ui->lineEdit_6->text();
QString dir=ubicacionActual+nombreActual+".vhdl";
QFile file(dir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){return;}
    QTextStream out(&file);
out << proyecto.c_str();
    file.flush();
    file.close();


//cargar


file.setFileName(dir);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
return;
else {

   i++;

    fileInfo=(file.fileName());
    nombre[i]=fileInfo.fileName();
    dirPuro[i]=fileInfo.absolutePath();dirPuro[i]+='/';
    ui->listWidget->addItem(nombre[i]);
    in.setDevice(&file);
    codigo[i]=in.readAll();
  //  ui->textEdit->setText(codigo[i]);
    ui->textEdit_3->setText("");
        for(sd=1;sd<= ui->textEdit->document()->blockCount();sd++){
            ui->textEdit_3->append(QString::number(sd));
        //
        }
        file.flush();
        file.close();
ui->listWidget->setCurrentRow(i);
}




}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{

}

void MainWindow::on_pushButton_10_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Abrir carpeta"),
                                                "",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_5->setText(dir+"/");
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{

}

void MainWindow::on_pushButton_11_clicked()
{
    if(i<0){
        ui->groupBox->setVisible(false);
        ui->groupBox_2->setVisible(false);
        ui->groupBox_4->setVisible(true);
        ui->groupBox_5->setVisible(false);
    }else{
        ui->groupBox->setVisible(true);
        ui->groupBox_2->setVisible(false);
        ui->groupBox_4->setVisible(false);
        ui->groupBox_5->setVisible(false);
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    bits_lista.clear();QStringList c;in_lista.clear();
    bool compilado=0;
    //compilar
    if(!oscuro){ ui->textEdit_2->setTextColor(Qt::black);

    }
    else {
       ui->textEdit_2->setTextColor(Qt::white);

    }

     ui->textEdit_2->setText("");
     ubicacionActual=dirPuro[ui->listWidget->currentRow()];
     nombreActual=nombre[ui->listWidget->currentRow()];
    nombreActual.replace(".vhdl","");

   QString dir=ubicacionActual+nombreActual+".vhdl";
     QFile file2(dir);
         if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
         QTextStream out(&file2);
         out << ui->textEdit->toPlainText();
         file2.flush();
         file2.close();
 //        ui->textEdit_2->append("Compilando "+nombreActual);


 process.setWorkingDirectory(ubicacionActual);
 ui->textEdit_2->append("ghdl -a "+dir);
     process.start("ghdl -a "+dir);
     process.waitForFinished(-1); // will wait forever until finished

      Consola = process.readAllStandardOutput();
      errorConsola = process.readAllStandardError();
      if(errorConsola.isEmpty()){
          if(!oscuro){ui->textEdit_2->setTextColor(Qt::blue);

          }
          else {
              ui->textEdit_2->setTextColor(Qt::green);

          }
          ui->textEdit_2->append("Compilado bien");
          compilado=1;}

     else{ui->textEdit_2->setTextColor(Qt::red);
         ui->textEdit_2->append(errorConsola);

 }
 ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());
 if(compilado){
     proyecto.clear();
     QString nombre_puro=nombreActual.replace(".vhdl","");
     proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\n";
     proyecto+="entity "+nombre_puro.toStdString()+"_tb"+" is\n";
     proyecto+="end "+nombre_puro.toStdString()+"_tb;\n\n";
     proyecto+="architecture arc of "+nombre_puro.toStdString()+"_tb"+" is\n";
     proyecto+="component "+nombre_puro.toStdString()+"is port(\n";

     QString txt2,a2;int primer_parentesis2,segundo_parentesis2;QStringList lista2,b2;QString temp32;int tempo2=0,mas_sig2,menos_sig2;
     QString component;
     txt2=ui->textEdit->toPlainText();
     txt2=txt2.simplified();
     txt2.replace( " ", "" );
      primer_parentesis2=txt2.indexOf("port(");
      segundo_parentesis2=txt2.indexOf(");end");

     primer_parentesis2+=5;
     segundo_parentesis2+=0;
     r[0]='\0';

     for(i=primer_parentesis2;i<segundo_parentesis2;i++){
         r[i-primer_parentesis2]=txt2.toUtf8().constData()[i];
     }
     r[i]='\0';
      lista2=QString(r).split(';');

     for(i=0;i<lista2.length();i++){
     a2=lista2[i];
     if(a2.contains("in") || a2.contains("out") || a2.contains("inout")){
     b2=a2.split(':');

     component+=b2[0];
     component+=" : ";
      if(a2.contains("in")) component+="in ";
      if(a2.contains("out")) component+="out ";
      if(a2.contains("inout")) component+="inout ";


     if(b2[1].contains("downto")){
     QRegularExpression rx("[0-9]+");
     QRegularExpressionMatchIterator matches = rx.globalMatch(b2[1]);
     tempo2=0;
     while (matches.hasNext()) {

         QRegularExpressionMatch match = matches.next();
         if(tempo2==0){mas_sig2 = match.captured(0).toInt();tempo2=1;}else {
             menos_sig2 = match.captured(0).toInt();
         }
     }
     //nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";

     component+="std_logic_vector("+QString::number(mas_sig2)+" downto "+QString::number(menos_sig2)+");\n";
     }
     else{
  component+="std_logic;\n";

     }
     }
     }

     proyecto+=component.toStdString();


     QString h2=QString::fromStdString(proyecto);
     int h3=h2.lastIndexOf(";");
     h2.replace(h3,1,");");
     proyecto=h2.toStdString();

     proyecto+="end component;\n";
     ui->textEdit_2->setText(QString::fromStdString(proyecto));
 }

}

void MainWindow::on_pushButton_14_clicked()
{
QStringList clock;
int stop_time=ui->lineEdit_9->text().toInt();
int intervalo=ui->lineEdit_8->text().toInt();
int n_columnas=stop_time/intervalo;
for(int i=1;i<=n_columnas;i++){
    clock<<QString::number(i*intervalo)+" ns";
}
ui->tableWidget->setColumnCount(n_columnas);
   ui->tableWidget->setHorizontalHeaderLabels(clock);

//nombres_verticales_entradas<<"A"<<"B";
//ui->tableWidget->setVerticalHeaderLabels(nombres_verticales_entradas);
}


void MainWindow::on_pushButton_7_clicked()
{
    bits_lista.clear();QStringList c;in_lista.clear();
    bool compilado=0;
    //compilar
    if(!oscuro){ ui->textEdit_2->setTextColor(Qt::black);

    }
    else {
       ui->textEdit_2->setTextColor(Qt::white);

    }

     ui->textEdit_2->setText("");
     ubicacionActual=dirPuro[ui->listWidget->currentRow()];
     nombreActual=nombre[ui->listWidget->currentRow()];
    nombreActual.replace(".vhdl","");

   QString dir=ubicacionActual+nombreActual+".vhdl";
     QFile file2(dir);
         if(!file2.open(QFile::WriteOnly | QFile::Text)){return;}
         QTextStream out(&file2);
         out << ui->textEdit->toPlainText();
         file2.flush();
         file2.close();
 //        ui->textEdit_2->append("Compilando "+nombreActual);


 process.setWorkingDirectory(ubicacionActual);
 ui->textEdit_2->append("ghdl -a "+dir);
     process.start("ghdl -a "+dir);
     process.waitForFinished(-1); // will wait forever until finished

      Consola = process.readAllStandardOutput();
      errorConsola = process.readAllStandardError();
      if(errorConsola.isEmpty()){
          if(!oscuro){ui->textEdit_2->setTextColor(Qt::blue);

          }
          else {
              ui->textEdit_2->setTextColor(Qt::green);

          }
          ui->textEdit_2->append("Compilado bien");
          compilado=1;}

     else{ui->textEdit_2->setTextColor(Qt::red);
         ui->textEdit_2->append(errorConsola);

 }
 ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());
 if(compilado){


int  primer_parentesis,segundo_parentesis;
 QString txt;
 yut.clear();txt.clear();
 txt=ui->textEdit->toPlainText();
yut=ui->textEdit->toPlainText().toStdString();


 primer_parentesis+=5;
 segundo_parentesis+=0;


 txt=ui->textEdit->toPlainText();
yut=ui->textEdit->toPlainText().toStdString();
proyecto.clear();
QString nombre_puro=nombreActual.replace(".vhdl","");
proyecto+="library ieee;\nuse ieee.std_logic_1164.all;\n\n";
proyecto+="entity "+nombre_puro.toStdString()+"_tb"+" is\n";
proyecto+="end "+nombre_puro.toStdString()+"_tb;\n\n";
proyecto+="architecture arc of "+nombre_puro.toStdString()+"_tb"+" is\n";
proyecto+="component "+nombre_puro.toStdString()+" is port(\n";

QString txt2,a2;int primer_parentesis2,segundo_parentesis2;QStringList lista2,b2;QString temp32;int tempo2=0,mas_sig2,menos_sig2;
QString component;
txt2=ui->textEdit->toPlainText();
txt2=txt2.simplified();
txt2.replace( " ", "" );
 primer_parentesis2=txt2.indexOf("port(");
 segundo_parentesis2=txt2.indexOf(");end");

primer_parentesis2+=5;
segundo_parentesis2+=0;
r[0]='\0';

for(i=primer_parentesis2;i<segundo_parentesis2;i++){
    r[i-primer_parentesis2]=txt2.toUtf8().constData()[i];
}
r[i]='\0';
 lista2=QString(r).split(';');

for(i=0;i<lista2.length();i++){
a2=lista2[i];
if(a2.contains("in") || a2.contains("out") || a2.contains("inout")){
b2=a2.split(':');

component+=b2[0];
component+=" : ";
 if(a2.contains("in")) component+="in ";
 if(a2.contains("out")) component+="out ";
 if(a2.contains("inout")) component+="inout ";


if(b2[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b2[1]);
tempo2=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo2==0){mas_sig2 = match.captured(0).toInt();tempo2=1;}else {
        menos_sig2 = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";

component+="std_logic_vector("+QString::number(mas_sig2)+" downto "+QString::number(menos_sig2)+");\n";
}
else{
component+="std_logic;\n";

}
}
}

proyecto+=component.toStdString();


QString h2=QString::fromStdString(proyecto);
int h3=h2.lastIndexOf(";");
h2.replace(h3,1,");");
proyecto=h2.toStdString();

proyecto+="end component;\n";
ui->textEdit_2->setText(QString::fromStdString(proyecto));


txt=ui->textEdit->toPlainText();
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
QString u;
QStringList lista=QString(r).split(';');
QStringList temp,nombres_in;
QString temp3;
int mas_sig,menos_sig,tempo=0;
QStringList b;QString a;
for(i=0;i<lista.length();i++){
a=lista[i];
if(a.contains("in") || a.contains("out")){
b=a.split(':');

temp3=b[0];


if(b[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b[1]);
tempo=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo==0){mas_sig = match.captured(0).toInt();tempo=1;}else {
        menos_sig = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";


proyecto+="signal ";
u=temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";
proyecto+=u.toStdString();
proyecto+='\n';
}
else{
    //nombres_in<<temp3+" : std_logic;";


    proyecto+="signal ";
   u= temp3+" : std_logic;";
   proyecto+=u.toStdString();
   proyecto+='\n';
}
}
}

proyecto+="begin\n";
proyecto+="RSC: ";
proyecto+=nombre_puro.toStdString() + " port map (";
//asignacion de señales
signal_lista.clear();
txt=ui->textEdit->toPlainText();
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');

for(i=0;i<lista.length();i++){
mas_sig=0;menos_sig=0;
QString a=lista[i];
if(a.contains("in")||a.contains("out")){
QStringList b=a.split(':');

temp3=b[0];


if(temp3.contains(',')){

QStringList b=temp3.split(',');
for(int k=0;k<b.length();k++){
    signal_lista<<b[k];
    proyecto+='\n';
   proyecto+=b[k].toStdString();
   proyecto+=" => ";
   proyecto+=b[k].toStdString();

        proyecto+=",";
}
}
else{
    signal_lista<<temp3;
    proyecto+='\n';
    proyecto+=temp3.toStdString();
    proyecto+=" => ";
    proyecto+=temp3.toStdString();

           proyecto+=",";
}
}
}
proyecto[proyecto.size()-1] = ' ';
 proyecto+='\n';
 proyecto+=");\n";
  proyecto+="process\n";
    proyecto+="begin\n";

//ui->textEdit_2->setText("");
//for(int i=0;i<nombres_in.length();i++)ui->textEdit_2->append(nombres_in[i]);




//valores al tablewidget

txt=ui->textEdit->toPlainText();
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
 segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');



for(i=0;i<lista.length();i++){
mas_sig=0;menos_sig=0;
QString a=lista[i];
if(a.contains("in")){
QStringList b=a.split(':');

temp3=b[0];


if(temp3.contains(',')){

QStringList b=temp3.split(',');
for(int k=0;k<b.length();k++){
   nombres_in<<b[k];
}
}
else
nombres_in<<temp3;
}
}


in_lista=nombres_in;


QStringList clock;
int stop_time=ui->lineEdit_9->text().toInt();
int intervalo=ui->lineEdit_8->text().toInt();
int n_columnas=stop_time/intervalo;
for(int i=1;i<=n_columnas;i++){
clock<<QString::number(i*intervalo)+" ns";
}
ui->tableWidget->setColumnCount(n_columnas);
ui->tableWidget->setHorizontalHeaderLabels(clock);

/*
for(i=0;i<nombres_in.length();i++){
ui->textEdit_2->append(nombres_in[i]);
}
*/


ui->groupBox->setVisible(false);
ui->groupBox_2->setVisible(true);
ui->groupBox_4->setVisible(false);
ui->groupBox_5->setVisible(false);
 }



proyecto_copia=proyecto;

//obtener bits y guardarlos en bits_lista

QString txt,a;int primer_parentesis,segundo_parentesis;QStringList lista,b,m;QString temp3;int tempo=0,mas_sig,menos_sig;
txt=ui->textEdit->toPlainText();
txt=txt.simplified();
txt.replace( " ", "" );
 primer_parentesis=txt.indexOf("port(");
 segundo_parentesis=txt.indexOf(");end");

primer_parentesis+=5;
segundo_parentesis+=0;
r[0]='\0';

for(i=primer_parentesis;i<segundo_parentesis;i++){
    r[i-primer_parentesis]=txt.toUtf8().constData()[i];
}
r[i]='\0';
 lista=QString(r).split(';');

for(i=0;i<lista.length();i++){
a=lista[i];
if(a.contains("in") || a.contains("out")){
b=a.split(':');

temp3=b[0];


if(b[1].contains("downto")){
QRegularExpression rx("[0-9]+");
QRegularExpressionMatchIterator matches = rx.globalMatch(b[1]);
tempo=0;
while (matches.hasNext()) {

    QRegularExpressionMatch match = matches.next();
    if(tempo==0){mas_sig = match.captured(0).toInt();tempo=1;}else {
        menos_sig = match.captured(0).toInt();
    }
}
//nombres_in<<temp3+" : std_logic_vector("+QString::number(mas_sig)+" downto "+QString::number(menos_sig)+");";
 if(b[0].contains(",")){
 m=b[0].split(",");
for(int i=0;i<m.length();i++){
    bits_lista<<QString::number(mas_sig-menos_sig+1);
}
m.clear();
 }
else bits_lista<<QString::number(mas_sig-menos_sig+1);

}
else{
    if(b[0].contains(",")){
    m=b[0].split(",");
   for(int i=0;i<m.length();i++){
       bits_lista<<QString::number(1);
   }
   m.clear();
    }
    else bits_lista<<QString::number(1);

}
}
}
QStringList valores_finales;
for(int i=0;i<in_lista.length();i++){
    valores_finales<<in_lista[i]+" ["+bits_lista[i]+" bit]";
}
ui->tableWidget->setRowCount(valores_finales.length());
ui->tableWidget->setVerticalHeaderLabels(valores_finales);

//ui->textEdit_2->setText("");for(int i=0;i<bits_lista.length();i++){ui->textEdit_2->append(bits_lista[i]);}
}

void MainWindow::on_pushButton_12_clicked()
{
    proyecto=proyecto_copia;
//check si hay items nulos, si los hay ponerles 0
    for(int i=0;i<ui->tableWidget->model()->columnCount();i++){
        for(int j=0;j<ui->tableWidget->model()->rowCount();j++){
//QMessageBox::information(this,"hola",ui->tableWidget->item(j,i)->text());
            QTableWidgetItem *item1(ui->tableWidget->item(j,i));
            if(!item1)ui->tableWidget->setItem(j, i, new QTableWidgetItem("0"));
        }
        }

    //get valores del tablewidget
signales_valores.clear();
    for(int i=0;i<ui->tableWidget->model()->columnCount();i++){
        for(int j=0;j<ui->tableWidget->model()->rowCount();j++){


    if(convertidorActual=="binario"){
    if(ui->tableWidget->item(j,i)->text().length()>1){
    signales_valores+=signal_lista[j];signales_valores+=" <= \"";signales_valores+=ui->tableWidget->item(j,i)->text();signales_valores+="\";";
    }
    else
    {signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=ui->tableWidget->item(j,i)->text();signales_valores+="';";}

    }

            if(convertidorActual=="decimal"){

      /*
            //   if(QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).length()>1){
                        signales_valores+=signal_lista[j];signales_valores+=" <= ";
                               string kk=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).toUtf8().constData();
                               signales_valores+="(";
                               for(int i=0;i<kk.length();i++){
                               signales_valores+=QString::number(i);signales_valores+=" => '";signales_valores+=kk[kk.length()-i-1];signales_valores+="',";
                               }
                               signales_valores+="others => '0'); ";
            //      }
              //    else {signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong()));signales_valores+="';";}
            }
*/
                if(bits_lista[j].toInt()==1)
                {
                    signales_valores+=signal_lista[j];signales_valores+=" <= '";signales_valores+=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong()));signales_valores+="';";
                }

                else if(bits_lista[j].toInt()>1 ){
                    signales_valores+=signal_lista[j];signales_valores+=" <= ";
                           string kk=QString::number(DtoB(ui->tableWidget->item(j,i)->text().toLong())).toUtf8().constData();
                           signales_valores+="(";
                           for(int i=0;i<kk.length();i++){
                           signales_valores+=QString::number(i);signales_valores+=" => '";signales_valores+=kk[kk.length()-i-1];signales_valores+="',";
                           }
                           signales_valores+="others => '0'); ";
                }
                else QMessageBox::information(this,"Error en la tabla","Solo se admiten decimales positivos(los negativos ponerlos en binario)\nHexadecimal todavia no desarrollado");


                }

        }signales_valores+="WAIT FOR 10 ns; \n";
    }


 proyecto+=signales_valores.toStdString();
 proyecto+="\nwait;";
 proyecto+="end process;\nend;";

 QString name_testbench=nombreActual+"_tb";
 QString dir=ubicacionActual+name_testbench+".vhdl";
 QFile file(dir);
     if(!file.open(QFile::WriteOnly | QFile::Text)){return;}
     QTextStream out(&file);
     out << QString::fromStdString(proyecto);
     file.flush();
     file.close();


     if(!oscuro) ui->textEdit_2->setTextColor(Qt::black);
     else {
        ui->textEdit_2->setTextColor(Qt::white);
     }
  //compilando tb
  process.setWorkingDirectory(ubicacionActual);
  ui->textEdit_2->append("ghdl -a "+name_testbench+".vhdl");
      process.start("ghdl -a "+name_testbench+".vhdl");
      process.waitForFinished(-1); // will wait forever until finished

       Consola = process.readAllStandardOutput();
       errorConsola = process.readAllStandardError();
       if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){
                // -e
           ui->textEdit_2->append("ghdl -e "+name_testbench);
               process.start("ghdl -e "+name_testbench);
               process.waitForFinished(-1); // will wait forever until finished

                Consola = process.readAllStandardOutput();
                errorConsola = process.readAllStandardError();
                if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){

                    // -r
                    ui->textEdit_2->append("ghdl -r "+name_testbench);
                        process.start("ghdl -r "+name_testbench+" --vcd=ondas.vcd");
                        process.waitForFinished(-1); // will wait forever until finished

                         Consola = process.readAllStandardOutput();
                         errorConsola = process.readAllStandardError();
                       if((!errorConsola.isEmpty() && errorConsola.contains("warning"))||errorConsola.isEmpty()){

                             // gtkwave
                             ui->textEdit_2->append("gtkwave ondas.vcd");
                                 process.start("gtkwave ondas.vcd");
gtkwave=1;
ui->centralWidget->setEnabled(false);




                                  Consola = process.readAllStandardOutput();
                                  errorConsola = process.readAllStandardError();
                         }
                        else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
                    }

                }
               else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
           }

       }
      else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);

           /*
       Consola = process.readAllStandardOutput();
       errorConsola = process.readAllStandardError();
       if(errorConsola.isEmpty()){
                // -e
           ui->textEdit_2->append("ghdl -e "+name_testbench);
               process.start("ghdl -e "+name_testbench);
               process.waitForFinished(-1); // will wait forever until finished

                Consola = process.readAllStandardOutput();
                errorConsola = process.readAllStandardError();
                if(errorConsola.isEmpty()){

                    // -r
                    ui->textEdit_2->append("ghdl -r "+name_testbench);
                        process.start("ghdl -r "+name_testbench+" --vcd=ondas.vcd");
                        process.waitForFinished(-1); // will wait forever until finished

                         Consola = process.readAllStandardOutput();
                         errorConsola = process.readAllStandardError();
                         if(errorConsola.isEmpty()){

                             // gtkwave
                             ui->textEdit_2->append("gtkwave ondas.vcd");
                                 process.start("gtkwave ondas.vcd");
gtkwave=1;
ui->centralWidget->setEnabled(false);




                                  Consola = process.readAllStandardOutput();
                                  errorConsola = process.readAllStandardError();
                         }
                        else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
                    }

                }
               else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
           }

       }
      else{QMessageBox::critical(this,"Error compilando"+nombreActual+"_tb.vhdl",errorConsola);
*/
  }








  ui->textEdit_2->verticalScrollBar()->setValue(ui->textEdit_2->verticalScrollBar()->maximum());

//ui->textEdit_4->setText(QString::fromStdString(proyecto));
}

void MainWindow::processFinished(int code , QProcess::ExitStatus status)
{
if(gtkwave){
ui->centralWidget->setEnabled(true);
    //QMessageBox::information(this,"se termino","se termino");
    gtkwave=0;}
}
