#include "mainwindow.h"
#include "ui_ChifoumiVue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pierre=new QPixmap(":/chifoumi/images/pierre.gif");
    feuille=new QPixmap(":/chifoumi/images/papier.gif");
    ciseau=new QPixmap(":/chifoumi/images/ciseau.gif");

    //connexions
    QObject::connect(ui->bNouvellePartie, SIGNAL(clicked()), this, SLOT(lancerPartie()));
    QObject::connect(ui->bPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));
    QObject::connect(ui->bFeuille, SIGNAL(clicked()), this, SLOT(jouerFeuille()));
    QObject::connect(ui->bCiseau, SIGNAL(clicked()), this, SLOT(jouerCiseaux()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lancerPartie(){
    ui->groupBox->setEnabled(true);

}

void MainWindow::jouerPierre(){
    jeu.setCoupJoueur(Chifoumi::pierre);
    ui->labelImageJoueur->setPixmap(*pierre);
}

void MainWindow::jouerFeuille(){
    jeu.setCoupJoueur(Chifoumi::papier);
    ui->labelImageJoueur->setPixmap(*feuille);
}

void MainWindow::jouerCiseaux(){
    jeu.setCoupJoueur(Chifoumi::ciseau);
    ui->labelImageJoueur->setPixmap(*ciseau);
}



