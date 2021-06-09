#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "nextdialog.h"
SecondDialog::SecondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondDialog)
{
    ui->setupUi(this);
}

SecondDialog::~SecondDialog()
{
    delete ui;
}

void SecondDialog::on_przegl_clicked()
{
    NextDialog nextdialog;          //Tworzenie nowego okna gdy użytkownik to nauczyciel
    nextdialog.setModal(true);
    nextdialog.exec();


}

void SecondDialog::sprawdz(QStringList lista)
{
    info = lista;           //Zapisuje listę otrzymaną z pierwszego okna do globalnej listy
    if(lista[2] == "nauczyciel"){ //Sprawdza czy status uzytkownika to nauczyciel czy uczen
        ui->wf->setText("Tryb Nauczyciela"); //Edytuje labelkę na "tryb nauczyciela"
        ui->przegl->show(); //Wyświetla przycisk "Przeglądaj bazę uczniów"
        ui->moj_wf->hide(); //Ukrywa Przycisk mój wf

    }
    else if(lista[2] == "uczen"){
        ui->wf->setText("Tryb Ucznia");     //Edytuje labelkę na "tryb ucznia"
        ui->moj_wf->show();     //Wyświetla przycisk mój wf
        ui->przegl->hide(); //ukrywa przycisk przeglądania bazy uczniów
    }
}

void SecondDialog::on_moj_wf_clicked()
{
    wf = new moj_wf(this); //Tworzy nowe okno moj wf
    wf->show();     //Wyswietla nowe okno
    connect(this, &SecondDialog::lista, wf, &moj_wf::tabela); //Łączenie sygnału z okna seconddialog ze slotem z okna moj_wf w celu przesłania danych
    emit lista(info); //Nadawanie sygnału z listą z informacjami o użytkowniku
}
