#include "moj_wf.h"
#include "ui_moj_wf.h"

moj_wf::moj_wf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::moj_wf)
{
    ui->setupUi(this);

}

moj_wf::~moj_wf()
{
    delete ui;
    baza.wlaczenie();
}
void moj_wf::tabela(QStringList lista)
{
    informacje = lista;                 //Zapisuje dane otrzymane z sygnałów do globalnej listy
    QString nazwy = "ID,Imie,Nazwisko,Klasa,Wiek,Dyscyplina"; //Nazwy kolumn w tabeli
    ui->tabela->insertColumn(0);//Tworzenie potrzebnej liczby kolumn
    ui->tabela->insertColumn(1);
    ui->tabela->insertColumn(2);
    ui->tabela->insertColumn(3);
    ui->tabela->insertColumn(4);
    ui->tabela->insertColumn(5);
    ui->tabela->insertRow(0);       //Tworzenie potrzebnej liczby wierszy
    ui->tabela->setHorizontalHeaderLabels(nazwy.split(","));  //Zapisuje nagłówki do tabeli. split(",") dzieli stringa nazwy po każdym przecinku
    ui->tabela->horizontalHeader()->show(); //Wyświetla nagłówki w tabeli
    for(int i = 0; i<8; i++){
        if(i == 0){
        QTableWidgetItem *element = new QTableWidgetItem(tr(lista[0].toUtf8().constData())); //Tworzy nowy element tabeli z id ucznia
        ui->tabela->setItem(0,i,element); //Dodaje element z ID ucznia do tabeli
        }
        else if(i > 2){ //Ponieważ w bazie danych w 2 i 3 kolumnie są hasło i status to pomijamy je i dodajemy kolejne informacje
            QTableWidgetItem *element = new QTableWidgetItem(tr(lista[i].toUtf8().constData())); //Tworzy nowy element tabeli z informacją o uczniu
            ui->tabela->setItem(0,i-2,element); //Dodaje element z informacją do tabeli
        }
    }
}

void moj_wf::on_potw_clicked()
{

    connect(this,&moj_wf::odswiez,this,&moj_wf::tabela);          //Łączy sygnał odswież z funkcją tabela żeby odswieżyć informacje w tabeli
    QString dyscyplina = ui->wybor->currentText();          //Pobiera dane z pola tekstowego
    baza.zmien(informacje[0], dyscyplina);                                              //Zmienia dyscypline w bazie danych
    QStringList odswiezone = baza.pobierz_dane(informacje[0],informacje[1]);                     //Pobiera odświeżone dane ponownie
    ui->tabela->setRowCount(0);            //Usuwa wszystkie rzędy z tabeli w celu ponownego stworzenia
    ui->tabela->setColumnCount(0);         //Usuwa wszystkie kolumny z tabeli w celu ponownego stworzenia
    emit odswiez(odswiezone);       //Sygnał przesyłający nowe dane do funkcji tabela

  }

