#include "presentation.h"
#include "chifoumivue.h"

Presentation::Presentation(Modele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
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
    _laVue->majInterface(Modele::UnEtat::lance,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
}

void Presentation::demanderJouerCiseau(){
    // choix du coup joueur machine au hasard
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->setCoupJoueur(Modele::UnCoup::ciseau);
    _leModele->determinerGagnant();
    _laVue->majInterface(Modele::UnEtat::lance,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
}

void Presentation::demanderJouerPierre(){
    // choix du coup joueur machine au hasard
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->setCoupJoueur(Modele::UnCoup::pierre);
    _leModele->determinerGagnant();
    _laVue->majInterface(Modele::UnEtat::lance,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
}

void Presentation::demanderJouerPapier(){
    // choix du coup joueur machine au hasar
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->setCoupJoueur(Modele::UnCoup::papier);
    _leModele->determinerGagnant();
    _laVue->majInterface(Modele::UnEtat::lance,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
}

void Presentation::demanderQuitterApp(){
    _laVue->majInterface(Modele::UnEtat::termine,_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
}

void Presentation::demanderInfosApp(){
    _laVue->infosApp();
}
