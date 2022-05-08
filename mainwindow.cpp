#include "mainwindow.h"
#include "ui_ChifoumiVue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //création des QPixmap
    pierre=new QPixmap(":/chifoumi/images/pierre.gif");
    feuille=new QPixmap(":/chifoumi/images/papier.gif");
    ciseau=new QPixmap(":/chifoumi/images/ciseau.gif");
    rien=new QPixmap(":/chifoumi/images/rien.gif");

    //connexions
    QObject::connect(ui->bNouvellePartie, SIGNAL(clicked()), this, SLOT(lancerPartie()));
    QObject::connect(ui->bPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));
    QObject::connect(ui->bFeuille, SIGNAL(clicked()), this, SLOT(jouerFeuille()));
    QObject::connect(ui->bCiseau, SIGNAL(clicked()), this, SLOT(jouerCiseaux()));

    // focus et ordre de parcours
    ui->bNouvellePartie->setFocus();
    ui->bNouvellePartie->setDefault(true);

    QWidget::setTabOrder(ui->bNouvellePartie, ui->bPierre);
    QWidget::setTabOrder(ui->bPierre, ui->bFeuille);
    QWidget::setTabOrder(ui->bFeuille, ui->bCiseau);
    QWidget::setTabOrder(ui->bCiseau, ui->bNouvellePartie);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lancerPartie(){
    ui->groupBox->setEnabled(true);
    setBlue('J');
    jeu.initScores();
    jeu.initCoups();
    ui->labelScoreJoueur->setText(QString::number(jeu.getScoreJoueur()));
    ui->labelScoreMachine->setText(QString::number(jeu.getScoreMachine()));
    ui->labelImageJoueur->setPixmap(*rien);
    ui->labelImageMachine->setPixmap(*rien);
}

void MainWindow::jouerPierre(){
    jeu.setCoupJoueur(Chifoumi::pierre);
    ui->labelImageJoueur->setPixmap(*pierre);
    tourMachine();
}

void MainWindow::jouerFeuille(){
    jeu.setCoupJoueur(Chifoumi::papier);
    ui->labelImageJoueur->setPixmap(*feuille);
    tourMachine();
}

void MainWindow::jouerCiseaux(){
    jeu.setCoupJoueur(Chifoumi::ciseau);
    ui->labelImageJoueur->setPixmap(*ciseau);
    tourMachine();
}

void MainWindow::tourMachine(){
    setBlue('M');
    jeu.setCoupMachine(jeu.genererUnCoup());
    definirImageMachine(jeu.getCoupMachine());
    finPartie();
}

void MainWindow::finPartie(){
    jeu.majScores(jeu.determinerGagnant());
    ui->labelScoreMachine->setText(QString::number(jeu.getScoreMachine()));
    ui->labelScoreJoueur->setText(QString::number(jeu.getScoreJoueur()));
    setBlue('J');
}

void MainWindow::setBlue(char cible){
    if (cible == 'M'){
        ui->labelIntituleJoueur->setStyleSheet("color: #000000");
        ui->labelIntituleMachine->setStyleSheet("color: #0000F0");
        ui->labelScoreJoueur->setStyleSheet("color: #000000");
        ui->labelScoreMachine->setStyleSheet("color: #0000F0");
    }
    else if (cible == 'J'){
        ui->labelIntituleJoueur->setStyleSheet("color: #0000F0");
        ui->labelIntituleMachine->setStyleSheet("color: #000000");
        ui->labelScoreJoueur->setStyleSheet("color: #0000F0");
        ui->labelScoreMachine->setStyleSheet("color: #000000");
    }
}

void MainWindow::definirImageMachine(Chifoumi::UnCoup coupMachine){
    switch (coupMachine) {
    case Chifoumi::pierre:
        ui->labelImageMachine->setPixmap(*pierre);
        break;
    case Chifoumi::ciseau:
        ui->labelImageMachine->setPixmap(*ciseau);
        break;
    default:
        ui->labelImageMachine->setPixmap(*feuille);
        break;
    }
}

