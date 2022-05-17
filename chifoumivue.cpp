#include "chifoumivue.h"
#include "ui_ChifoumiVue.h"
#include <QMessageBox>
ChifoumiVue::ChifoumiVue(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
    //création des QPixmap
    pierre=new QPixmap(":/chifoumi/images/pierre.gif");
    feuille=new QPixmap(":/chifoumi/images/papier.gif");
    ciseau=new QPixmap(":/chifoumi/images/ciseau.gif");
    rien=new QPixmap(":/chifoumi/images/rien.gif");

    // focus et ordre de parcours
    ui->bNouvellePartie->setFocus();
    ui->bNouvellePartie->setDefault(true);

    QWidget::setTabOrder(ui->bNouvellePartie, ui->bPierre);
    QWidget::setTabOrder(ui->bPierre, ui->bFeuille);
    QWidget::setTabOrder(ui->bFeuille, ui->bCiseau);
    QWidget::setTabOrder(ui->bCiseau, ui->bNouvellePartie);

    ui->groupBox->setEnabled(false);
}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

void ChifoumiVue::nvlleConnexion(QObject *c)
{
    //pour se connecter avec la presentation

    // Qboutons
    QObject::connect(ui->bNouvellePartie, SIGNAL(clicked()), c, SLOT(demanderLancerPartie()));
    QObject::connect(ui->bPierre, SIGNAL(clicked()), c, SLOT(demanderJouerPierre()));
    QObject::connect(ui->bFeuille, SIGNAL(clicked()), c, SLOT(demanderJouerPapier()));
    QObject::connect(ui->bCiseau, SIGNAL(clicked()), c, SLOT(demanderJouerCiseau()));

    // Qactions
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), c, SLOT(demanderQuitterApp()));
    QObject::connect(ui->actionInformationsApp, SIGNAL(triggered()), c, SLOT(demanderInfosApp()));
}

void ChifoumiVue::lancerPartie(){
    ui->groupBox->setEnabled(true);
    setBlue('J');

    // affichage à l'écran de la remise à zero
    ui->labelScoreJoueur->setText(QString::number(0));
    ui->labelScoreMachine->setText(QString::number(0));
    ui->labelImageJoueur->setPixmap(*rien);
    ui->labelImageMachine->setPixmap(*rien);
}

void ChifoumiVue::tourMachine(Modele::UnCoup m,int scoreJoueur,int scoreMachine){
    setBlue('M');
    // affichage du coup
    definirImageMachine(m);
    finManche(scoreJoueur,scoreMachine);
}

void ChifoumiVue::finManche(int scoreJoueur,int scoreMachine){
    // mise à jour des scores à l'écran
    ui->labelScoreMachine->setText(QString::number(scoreMachine));
    ui->labelScoreJoueur->setText(QString::number(scoreJoueur));

    setBlue('J');
}

void ChifoumiVue::setBlue(char cible){
    if (cible == 'M'){
        // joueur humain en noir
        ui->labelIntituleJoueur->setStyleSheet("color: #000000");
        ui->labelScoreJoueur->setStyleSheet("color: #000000");
        // joueur machine en bleu
        ui->labelIntituleMachine->setStyleSheet("color: #0000F0");
        ui->labelScoreMachine->setStyleSheet("color: #0000F0");
    }
    else if (cible == 'J'){
        // joueur humain en bleu
        ui->labelIntituleJoueur->setStyleSheet("color: #0000F0");
        ui->labelScoreJoueur->setStyleSheet("color: #0000F0");
        // joueur machine en noir
        ui->labelIntituleMachine->setStyleSheet("color: #000000");
        ui->labelScoreMachine->setStyleSheet("color: #000000");
    }
}

void ChifoumiVue::definirImageMachine(Modele::UnCoup coupMachine){
    switch (coupMachine) {
    case Modele::pierre:
        ui->labelImageMachine->setPixmap(*pierre);
        break;
    case Modele::ciseau:
        ui->labelImageMachine->setPixmap(*ciseau);
        break;
    default:
        ui->labelImageMachine->setPixmap(*feuille);
        break;
    }
}

void ChifoumiVue::quitterApp(){
    (*this).close();
}

void ChifoumiVue::infosApp(){
    QString infos = tr("version : V3\n"
                    "dernière modification : 14 mai 2022\n"
                    "les auteurs : Tom Montbord, Guillian Celle et Oier Cesat");
    QMessageBox::information(this, "A propos de cette application.", infos, QMessageBox::Ok);
}

void ChifoumiVue::majInterface(Modele::UnEtat e,Modele::UnCoup c,Modele::UnCoup m,int scoreJoueur,int scoreMachine){
    if(e == Modele::UnEtat::enJeu){
        switch (c) {

            case Modele::UnCoup::papier:
                ui->labelImageJoueur->setPixmap(*feuille);
                tourMachine(m,scoreJoueur,scoreMachine);
                break;

            case Modele::UnCoup::ciseau:
                ui->labelImageJoueur->setPixmap(*ciseau);
                tourMachine(m,scoreJoueur,scoreMachine);
                break;

            case Modele::UnCoup::pierre:
                ui->labelImageJoueur->setPixmap(*pierre);
                tourMachine(m,scoreJoueur,scoreMachine);
                break;

            case Modele::UnCoup::rien:
                lancerPartie();
                break;
        }
    }
}
