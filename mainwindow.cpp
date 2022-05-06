#include "mainwindow.h"
#include "ui_ChifoumiVue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Chifoumi jeu;

    //connexions
    QObject::connect(ui->bNouvellePartie, SIGNAL(clicked()), this, SLOT(lancerPartie()));
    QObject::connect(ui->bPierre, SIGNAL(clicked()), this, SLOT(jouerPierre(jeu)));
    QObject::connect(ui->bFeuille, SIGNAL(clicked()), this, SLOT(jouerFeuille(jeu)));
    QObject::connect(ui->bCiseau, SIGNAL(clicked()), this, SLOT(jouerCiseaux(jeu)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lancerPartie(){
    ui->groupBox->setEnabled(true);
}

void MainWindow::jouerPierre(Chifoumi &jeu){
    jeu.setCoupJoueur(Chifoumi::pierre);
;}

void MainWindow::jouerFeuille(Chifoumi &jeu){
    jeu.setCoupJoueur(Chifoumi::papier);
;}

void MainWindow::jouerCiseaux(Chifoumi &jeu){
    jeu.setCoupJoueur(Chifoumi::ciseau);
;}



