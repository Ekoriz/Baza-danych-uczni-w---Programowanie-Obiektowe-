#include "nextdialog.h"
#include "ui_nextdialog.h"

NextDialog::NextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NextDialog)
{
    ui->setupUi(this);
    baza.wlaczenie();                           //Włącza połączenie z bazą danych
    tableModel = baza.tabela_odswiez(nullptr);  //Pobiera model tabeli z uczniami z bazy danych.
                                                //nullptr to pusta wartość filtru bo chcemy wyświetlić wszystkich uczniów
    ui->tableView->setModel(tableModel);     //Ustawia model pobrany z bazy danych jako model naszej tabeli w ui
    ui->tableView->hideColumn(1);       //Ukrywa kolumne z hasłem
    ui->tableView->hideColumn(2);       //Ukrywa kolumne ze statusem

}

NextDialog::~NextDialog()
{
    delete ui;
}

void NextDialog::on_pushButton_clicked()
{
    QStringList update;         //Lista z informacjami o uczniu którego chcemy dodać do bazy
    update.append(ui->lineEdit_ID->text());     //Dodawanie ID do listy
    update.append("default");                   //Dodawanie hasła do listy
    update.append("uczen");                     //Dodawanie statusu uczen do listy
    update.append(ui->lineEdit_Imie->text());       //Dodawanie Imienia do listy
    update.append(ui->lineEdit_Nazwisko->text());   //Dodawanie Nazwiska do listy
    update.append(ui->lineEdit_Klasa->text());  //Dodawanie klasy do listy
    update.append(ui->lineEdit_Wiek->text());   //Dodawanie wieku do listy
    update.append(ui->lineEdit_Dyscyplina->text()); //Dodawanie dyscypliny do listy
    baza.dodaj(update);     //Wykorzystanie funkcji z klasy bazy danych do dodania listy z informacjami do bazy danych
    tableModel = baza.tabela_odswiez(nullptr); //Pobiera model tabeli z uczniami z bazy danych. nullptr jest puste bo chcemy wyświetlić wszystkich uczniów
    ui->tableView->setModel(tableModel);    //Ustawia model pobrany z bazy danych jako model naszej tabeli w ui
}
void NextDialog::on_Szukaj_clicked()
{
    QString po_czym = ui->sz_po->currentText(); //Pobiera z okienka wyboru filtr po jakim mają zostać wyświetlone informacje czyli np dana dyscyplina lub konkretny uczeń
    if(po_czym == "Wszystkie"){ //Pozwala na wyświetlenie ponownie całej tabeli bez żadnych filtrów
        tableModel = baza.tabela_odswiez(nullptr);  //Pobiera model tabeli z uczniami z bazy danych. nullptr jest puste bo chcemy wyświetlić wszystkich ucznioów
        ui->tableView->setModel(tableModel);    //Ustawia model pobrany z bazy danych jako model naszej tabeli w ui
    }
    else {
    QString wartosc = ui->sz_wartosc->text(); //Pobiera wartość filtra czyli np Siatkówka lub imie ucznia
    QString filtr = " AND " + po_czym + " = '" + wartosc + "';"; //Filtr jest wysłany do bazy danych jako polecenie WHERE więc musi odpowiednio wyglądać
                                                                 //np WHERE status = 'uczen' AND Dyscyplina = 'Siatkówka';
    tableModel = baza.tabela_odswiez(filtr);       //Pobiera model tabeli z uczniami z bazy danych. nullptr jest puste bo chcemy wyświetlić wszystkich ucznioów
    ui->tableView->setModel(tableModel);    //Ustawia model pobrany z bazy danych jako model naszej tabeli w ui
    }
}
void NextDialog::on_zmien_clicked()
{
    QString ID_zmiana = ui->ID_zmiana->text();      //Pobiera ID ucznia któremu chcemy zmienić dyscypline
    QString dysc_zmiana = ui->dysc_zmiana->currentText();   //Pobiera nową dyscyplinę z okna wyboru
    baza.zmien(ID_zmiana, dysc_zmiana);     //Zmienia dyscyplinę w bazie danych korzystając z funkcji zmien klasy baza_danych
    tableModel = baza.tabela_odswiez(nullptr); //Pobiera model tabeli z uczniami z bazy danych. nullptr jest puste bo chcemy wyświetlić wszystkich ucznioów
    ui->tableView->setModel(tableModel);    //Ustawia model pobrany z bazy danych jako model naszej tabeli w ui
}

void NextDialog::on_zapisz_clicked()
{
    QString tekst = "ID , Imie , Nazwisko , Klasa , Wiek , Dyscyplina\n"; //Nagłówki tabeli które będą zapisane do pliku
    int rzedy = tableModel->rowCount();     //Ilość rzędów w tabeli
    int kolumny = tableModel->columnCount(); //Ilość kolumn w tabeli
    for (int i = 0; i < rzedy; i++) {
        for (int j = 0; j < kolumny; j++) { //Pobieranie wartości każdej komórki tabeli po kolei i dodawanie jej do tekst

                tekst = tekst + tableModel->data(tableModel->index(i,j)).toString();
                tekst = tekst + ","; //Dodawanie przecinka po każdym elemencie
        }
        tekst = tekst + "\n"; //Dodawanie znaku nowej linii po każdym rzędzie
    }
    QFile plik("C:\Users\tomek\Desktop\bazauczniow3-20200615T185021Z-001 (1)\bazauczniow3"); //Adres pliku
    if(plik.open(QIODevice::ReadWrite)) //Sprawdzadznie czy plik jest otwarty do zapisu
    {
        plik.write(tekst.toUtf8()); //Zapisywanie tekst do pliku
        plik.close(); //Zamknięcie pliku
    }
}
