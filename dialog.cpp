#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getNom(){
    nom=ui->lineEditNom->text();
    return nom;
}

int Dialog::getScore(){
    scoreMax=ui->lineEditScore->text().toInt();
    return scoreMax;
}

int Dialog::getTemps(){
    temp=ui->lineEditTemps->text().toInt();
    return temp;
}
