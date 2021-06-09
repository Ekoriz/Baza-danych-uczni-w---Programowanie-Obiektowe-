#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    baza.wlaczenie();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString id = ui->lineEdit_id->text();                   //Pobieranie ID i hasła z pól tekstowych
    QString haslo = ui->lineEdit_haslo->text();
    QStringList lista = baza.pobierz_dane(id,haslo);        //Wykorzystanie funkcji z klasy baza danych do pobrania danych o użytkowniku z id i hasłem
    if(id == lista[0] && haslo == lista[1] ) {      //Reakcja na udane zalogowanie
        QMessageBox::information(this, "Login", "Hasło jest poprawne");
        hide();
        secondDialog = new SecondDialog(this);
        secondDialog->show();               //Wyświetlenie drugiego okna
        connect(this, &MainWindow::info, secondDialog, &SecondDialog::sprawdz); //Łączenie sygnału z okna mainwindow ze slotem z okna secondDialog
        emit info(lista);       //Nadawanie sygnału z listą z informacjami o użytkowniku
    }
    else {          //Reakcja na niepoprawne zalogowanie
        QMessageBox::information(this, "Login", "Hasło jest niepoprawne");
    }
}
