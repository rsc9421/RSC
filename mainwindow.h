#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QWidget>
#include <QFile>
#include <QMainWindow>
#include <QTextStream>
#include<QFileDialog>
#include<QProcess>
#include<QCursor>
#include<QTextCursor>
#include<QScrollBar>
#include<QListWidgetItem>
#include<QFontDialog>
#include<QFont>
#include<QMessageBox>
#include<QDir>
#include<QStringList>
#include<QListWidgetItem>
#include<QDebug>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include<locale>
#include"highlighter.h"
#include"nuevoproy.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString dir;
    QFile file;
    QFileInfo fileInfo;
    QTextStream in;
    QString errorConsola="nada";
    QString Consola;
    QString codigo[50];
    QString direccion[50];
    QString nombre[50];
    QString dirPuro[50];
    int i=-1,ii=-1,j=0;
    QProcess process;
    QString convertidorActual="decimal";
    QString dirPuro_actual;
private slots:
    void on_actionAbrir_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_actionGuardar_triggered();

    void on_actionGuardar_como_triggered();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_textEdit_cursorPositionChanged();

    void on_pushButton_6_clicked();

    void on_checkBox_clicked();
void processFinished(int code , QProcess::ExitStatus status);
    void on_pushButton_7_clicked();

    void on_tableWidget_cellPressed(int row, int column);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_tableWidget_pressed(const QModelIndex &index);

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_actionmodo_Blanco_triggered();

    void on_actionmodo_Dark_triggered();

    void on_actionFuente_2_triggered();

    void on_textEdit_textChanged();

    void on_actionNuevo_triggered();
void resizeEvent(QResizeEvent* event);
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_lineEdit_7_returnPressed();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void on_pushButton_10_clicked();

    void on_textEdit_copyAvailable(bool b);

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
NuevoProy nuevoproy;
};

#endif // MAINWINDOW_H
