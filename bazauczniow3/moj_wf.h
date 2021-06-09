#ifndef MOJ_WF_H
#define MOJ_WF_H
#include <QDialog>
#include "baza_danych.h"
namespace Ui {
class moj_wf;
}

class moj_wf : public QDialog
{
    Q_OBJECT

public:
    explicit moj_wf(QWidget *parent = nullptr);
    ~moj_wf();
public slots:
    void tabela(QStringList lista);           //Tworzenie tabeli i wyświetlanie danych u uczniu
signals:
    void odswiez(QStringList);                      //Sygnał stworzony do przesyłania nowych danych do tabeli
private slots:
    void on_potw_clicked();                   //Reakcja na kliknięty guzik do potwierdzenia zmiany dyscypliny

private:
    Ui::moj_wf *ui;                 //Odnośnik do ui
    QStringList informacje;         //Globalna lista do ktróej zapisywane są informacje o uczniu
    baza_danych baza;               //Odnośnik do bazy danych
};

#endif // MOJ_WF_H
