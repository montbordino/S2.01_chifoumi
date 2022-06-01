#include "chifoumivue.h"
#include "ui_ChifoumiVue.h"
#include <QMessageBox>
#include <QDialog>
#include <QTimer>

ChifoumiVue::ChifoumiVue(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
    this->setWindowTitle("Chifoumi");

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
    QObject::connect(ui->bPause, SIGNAL(clicked()),c, SLOT(demanderPause()));

    // Qactions
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), c, SLOT(demanderQuitterApp()));
    QObject::connect(ui->actionInformationsApp, SIGNAL(triggered()), c, SLOT(demanderInfosApp()));
    QObject::connect(ui->actionParametrer, SIGNAL(triggered()), c, SLOT(demanderOuvrirParameres()));
}

void ChifoumiVue::lancerPartie(){
    ui->actionParametrer->setEnabled(false);
    ui->groupBox->setEnabled(true);
    setBlue('J');
    majTimer(30);
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
    QString infos = tr("version : V5\n"
                    "dernière modification : 30 mai 2022\n"
                    "les auteurs : Tom Montbord, Guillian Celle et Oier Cesat");
    QMessageBox::information(this, "A propos de cette application.", infos, QMessageBox::Ok);
}

void ChifoumiVue::afficherFinScore(int score, QString nom, unsigned int tempsRestant, unsigned int tempsDepart) {
    ui->groupBox->setEnabled(false);
    QString titre;
    QString contenu;
    if (tempsRestant <= 0){
        titre = "Fin de partie temps fini";
        if (nom == "égalité"){
            contenu = "Helas chers joueurs, temps de jeu fini ! Les deux joueurs finissent exaequo avec chacun " + QString::number(score) + " points.";
        }
        else {
            contenu = "Helas chers joueurs, temps de jeu fini ! " + nom +" termine toutefois mieux avec " + QString::number(score) + " points.";
        }
    }
    else {
        titre = "Fin de partie gagnant";
        contenu = "Bravo " + nom + "! Vous gagnez la partie avec " + QString::number(score) + " points en " + QString::number(tempsDepart - tempsRestant) + " secondes.";
    }
    QMessageBox::information(this, titre, contenu);
}

void ChifoumiVue::majInterface(Modele::UnEtat e,Modele::UnCoup c,Modele::UnCoup m,int scoreJoueur,int scoreMachine){
    switch(e) {
        case Modele::UnEtat::enJeu:
            if (ui->bPause->text() == "Reprise jeu") {
                ui->groupBox->setEnabled(true);
                ui->bPause->setText("Pause");
            }
            else {
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
            break;
        case  Modele::UnEtat::accueil:
            majTimer(30);
            break;
        case  Modele::UnEtat::pause:
            ui->groupBox->setEnabled(false);
            ui->bPause->setText("Reprise jeu");
            break;
    }
}

void ChifoumiVue::majTimer(int tempsRestant)
{
    ui->labelTimeInt->setText(QString::number(tempsRestant));
}
