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
    _leModele->setEtatPartie(Modele::UnEtat::enJeu);
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
    timer->start();
    _leModele->setTempsDepart(30);
    _leModele->setTempsRestant(_leModele->getTempsDepart());
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
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
    if (_leModele->getScoreJoueur() >= _leModele->getScoreMax()){
        _leModele->setEtatPartie(Modele::UnEtat::accueil);
        _laVue->afficherFinScore(_leModele->getScoreJoueur(), "joueur", _leModele->getTempsRestant(), _leModele->getTempsDepart());
    }
    else if (_leModele->getScoreMachine() >= _leModele->getScoreMax() ){
        _leModele->setEtatPartie(Modele::UnEtat::accueil);
        _laVue->afficherFinScore(_leModele->getScoreMachine(), "Machine", _leModele->getTempsRestant(), _leModele->getTempsDepart());
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
    if (_leModele->getEtat() == Modele::enJeu){
        if (_leModele->getTempsRestant() > ZERO)
        {
            _leModele->setTempsRestant(_leModele->getTempsRestant() - 1);
            _laVue->majTimer(_leModele->getTempsRestant());
        }
        else
        {
            _leModele->setEtatPartie(Modele::UnEtat::accueil);
            if (_leModele->getScoreJoueur() > _leModele->getScoreMachine()){
                _laVue->afficherFinScore(_leModele->getScoreJoueur(), "joueur", _leModele->getTempsRestant(), _leModele->getTempsDepart());

            }
            else if (_leModele->getScoreMachine() > _leModele->getScoreJoueur() ){
                _laVue->afficherFinScore(_leModele->getScoreMachine(), "Machine", _leModele->getTempsRestant(), _leModele->getTempsDepart());
            }
            else {
                _laVue->afficherFinScore(_leModele->getScoreMachine(), "égalité", _leModele->getTempsRestant(), _leModele->getTempsDepart());
            }
        }
    }
}

void Presentation::demanderPause()
{
    if (_leModele->getEtat() == Modele::UnEtat::enJeu){
        timer->stop();
        _leModele->setEtatPartie(Modele::UnEtat::pause);
        _laVue->majInterface(_leModele->getEtat());
    }
    else if (_leModele->getEtat() == Modele::UnEtat::pause) {
        timer->start();
        _leModele->setEtatPartie(Modele::UnEtat::enJeu);
        _laVue->majInterface(_leModele->getEtat());
    }

}
