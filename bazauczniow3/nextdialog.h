#ifndef NEXTDIALOG_H
#define NEXTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "baza_danych.h"
namespace Ui {
class NextDialog;
}

class NextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NextDialog(QWidget *parent = nullptr);
    ~NextDialog();


private slots:
    void on_pushButton_clicked();           //Reakcja na kliknięcie przycisk dodawania ucznia do bazy
    void on_Szukaj_clicked();       //Reakcja na kliknięcie przycisku szukania w bazie
    void on_zmien_clicked();        //Reakcja na kliknięcie przycisku zmiany dyscypliny

    void on_zapisz_clicked();       //Reakcja na kliknięcie przycisku zapisu do pliku

private:
    Ui::NextDialog *ui;                         //Odnośnik do ui
    baza_danych baza;                           //Odnośnik do bazy danych
    QSqlTableModel *tableModel;                 //Odnośnik do modelu tabeli
};

#endif // NEXTDIALOG_H
