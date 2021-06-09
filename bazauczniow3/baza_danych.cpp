#include "baza_danych.h"
#include <QSqlDatabase>

void baza_danych::wlaczenie(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/bazauczniow.db");

    bool ok = db.open();
    qDebug() <<  ok;
}
QStringList baza_danych::pobierz_dane(QString ID, QString haslo)
{
   QSqlQuery zapytanie;
   // Treść zapytania do bazy wraz z hasłem i id
   QString komenda = "SELECT ID, Haslo, status, Imie, Nazwisko, Klasa, Wiek, Dyscyplina FROM uczniowie WHERE ID = '" + ID + "' AND Haslo = '" + haslo + "';";
    zapytanie.exec(komenda);  //Wysłanie zapytania do bazy
    QStringList lista;
    if(zapytanie.size() == 0)             //Brak id w bazie danych
    {
       lista.append("bład");
       return lista;
    }
    else
    {
        while(zapytanie.next()){   //Przetwarzanie wszystkich pasujących elementów znalezionych w bazie danych
            for(int j=0; j<8;j++) {                                     //8 - liczba wartości pobranych z bazy danych
                lista.append(zapytanie.value(j).toString());  //Dodawanie wartości z bazy danych do listy
            }
        }
        return lista;
    }
}
void baza_danych::zmien(QString ID, QString dyscyplina)
{
   QSqlQuery zapytanie;
   QString komenda = "UPDATE uczniowie SET Dyscyplina = '" + dyscyplina + "' WHERE ID = '" + ID + "';"; //Zmiana dyscypliny ucznia o id
   zapytanie.exec(komenda);
}
QSqlTableModel* baza_danych::tabela_odswiez(QString filtr) //Funkcja zwracająca tablice bazy danych
{
    tableModel = new QSqlTableModel();
    tableModel->setTable("uczniowie");
    tableModel->setFilter("status = 'uczen'"+filtr); //Funkcja setFilter działa jak polecenie "WHERE". Kiedy wyszukujemy czegoś to parametr filtr ma wartość, a gdy wyświetlamy tylko tabele to jest pusty
    tableModel->select();
    tableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));  //Ustawianie nazw kolumn
    tableModel->setHeaderData(3, Qt::Horizontal, tr("Imię"));
    tableModel->setHeaderData(4, Qt::Horizontal, tr("Nazwisko"));
    tableModel->setHeaderData(5, Qt::Horizontal, tr("Klasa"));
    tableModel->setHeaderData(6, Qt::Horizontal, tr("Wiek"));
    tableModel->setHeaderData(7, Qt::Horizontal, tr("Dyscyplina"));
    return tableModel;

}
void baza_danych::dodaj(QStringList dodawanie)
{
    QSqlQuery zapytanie;
    //Dodanie nowego ucznia na podstawie danych wpisanych w formularzu
    zapytanie.exec("INSERT INTO `uczniowie` (`ID`, `haslo`, `status`, `Imie`, `Nazwisko`, `Klasa`, `Wiek`, `Dyscyplina`) VALUES ('" + dodawanie[0] + "', '" + dodawanie[1] + "', '" + dodawanie[2] + "', '" + dodawanie[3] + "', '" + dodawanie[4] + "', '" + dodawanie[5] + "', '" + dodawanie[6] + "', '" + dodawanie[7] + "');");  //Dodanie nowego ucznia na podstawie danych wpisanych w formularzu
}
