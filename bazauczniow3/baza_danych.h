#ifndef BAZA_DANYCH_H
#include <QWidget>
#include <QtSql>
#define BAZA_DANYCH_H


class baza_danych: public QObject{
    Q_OBJECT

public slots:
    void wlaczenie();                                                //Uruchomienie połączenia z bazą danych
    QStringList pobierz_dane(QString ID, QString haslo);             //Pobiera dane z bazy na podstawie id i hasla
    void zmien(QString ID, QString dyscyplina);                      //Służy do zmiany dyscypliny ucznia o podanym id
    QSqlTableModel* tabela_odswiez(QString filtr);                   //Służy do odświeżania danych z bazy w tabeli oraz do wyszukiwania
    void dodaj(QStringList dodawanie);                               //Dodaje nowego ucznia do bazy
private:
    QSqlTableModel *tableModel;                                      //Model tabeli z pobieranej z bazy danych
};

#endif // BAZA_DANYCH_H
