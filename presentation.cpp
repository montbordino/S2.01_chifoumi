#include "presentation.h"
#include "chifoumivue.h"

Presentation::Presentation(Modele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->setInterval(1000);
}

Modele *Presentation::getModele()
{
    return _leModele;
}

ChifoumiVue *Presentation::getVue()
{
    return _laVue;
}

void Presentation::setModele(Modele *m)
{
    _leModele = m;
}

void Presentation::setVue(ChifoumiVue *v)
{
    _laVue = v;
}

void Presentation::demanderLancerPartie(){
    // remise à zero des données
    _leModele->initCoups();
    _leModele->initScores();
    _laVue->majInterface(Modele::UnEtat::enJeu,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
    timer->start();
    tempsRestant=30;
}

void Presentation::demanderJouerCiseau(){
    // choix du coup joueur machine au hasard
    _leModele->setCoupJoueur(Modele::UnCoup::ciseau);
    (*this).demanderJouerTour();
}

void Presentation::demanderJouerPierre(){
    // choix du coup joueur machine au hasard
    _leModele->setCoupJoueur(Modele::UnCoup::pierre);
    (*this).demanderJouerTour();
}

void Presentation::demanderJouerPapier(){
    // choix du coup joueur machine au hasard
    _leModele->setCoupJoueur(Modele::UnCoup::papier);
    (*this).demanderJouerTour();
}

void Presentation::demanderJouerTour(){
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->determinerGagnant();
    _laVue->majInterface(Modele::UnEtat::enJeu,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
    if (_leModele->getScoreJoueur() >= _leModele->getScoreMax()){
        _laVue->afficherFinScore(_leModele->getScoreJoueur(), "joueur");
    }
    else if (_leModele->getScoreMachine() >= _leModele->getScoreMax() ){
        _laVue->afficherFinScore(_leModele->getScoreMachine(), "Machine");
    }
}

void Presentation::demanderQuitterApp(){
   //_laVue->supprConnexion(_laVue);
   _laVue->quitterApp();
}

void Presentation::demanderInfosApp(){
    _laVue->infosApp();
}

void Presentation::update()
{
    QString tempAfficher;
    if (tempsRestant>tempsFinal)
    {
        tempsRestant--;
        tempAfficher = QString::number(tempsRestant);
        _laVue->majTimer(tempAfficher);
    }
    else
    {
        _laVue->majInterface(Modele::UnEtat::accueil);
    }
}

void Presentation::demanderPause()
{
    timer->stop();
    _laVue->majInterface(Modele::UnEtat::pause);
}
