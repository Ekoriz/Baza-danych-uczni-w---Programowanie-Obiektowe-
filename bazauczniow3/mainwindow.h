#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include <QMainWindow>
#include "seconddialog.h"
#include "baza_danych.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();               //Reakcja na kliknięcie przycisku zaloguj
signals:
    void info(QStringList);                     //Sygnał służący do komunikacji pomiędzy oknami
private:
    Ui::MainWindow *ui;                         //UI
    SecondDialog *secondDialog;                 //Odnośnik do drugiego okna
    baza_danych baza;                           //Odnośnik do bazy danych
};
#endif // MAINWINDOW_H
