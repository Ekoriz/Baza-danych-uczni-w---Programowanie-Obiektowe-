#ifndef SECONDDIALOG_H
#define SECONDDIALOG_H

#include <QDialog>
#include "baza_danych.h"
#include "moj_wf.h"

namespace Ui {
class SecondDialog;
}

class SecondDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecondDialog(QWidget *parent = nullptr);
    ~SecondDialog();
public slots:
    void sprawdz(QStringList lista);         //Odbiera sygnał z pierwszego okna i sprawdza czy uzytkownik to uczen czy nauczyciel
private slots:
    void on_przegl_clicked();          //Widoczny tylko jeśli użytkownik to nauczyciel i wyświetla okno przeglądania bazy danych
    void on_moj_wf_clicked();         //Widoczny tylko jeśli użytkownik to uczen i wyświetla okno WF-u
signals:
    void lista(QStringList);        //Sygnał przesyłany do okna mojego wf z informacjami o zalogowanym użytkowniku
private:
    Ui::SecondDialog *ui;           //Odnośnik do ui
    baza_danych baza;               //Odnośnik do bazy danych
    QStringList info;               //Globalna lista z informacja pobrana z bazy danych w pierwszym oknie
    moj_wf *wf;                     //Odnośnik do okna moj_wf
};

#endif // SECONDDIALOG_H
