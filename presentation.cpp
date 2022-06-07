#include "presentation.h"
#include "chifoumivue.h"

Presentation::Presentation(Modele *m,ChifoumiVue *v,QObject *parent)
    : QObject{parent}, _leModele(m)
{
    //associe la vue avec le ui
    this->setVue(v);
    //connexion entre le timer et son slot
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    //définit l'interval à 1000ms
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
    //initialise les coups machine et coup joueur
    _leModele->initCoups();
    _leModele->initScores();
    //initialise le temps restant au temp de départ
    _leModele->setTempsRestant(_leModele->getTempsDepart());
    //initialise l'état de la partie
    _leModele->setEtatPartie(Modele::UnEtat::enJeu);
    //Mise à jour de l'interface
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(),_leModele->getScoreMax(),_leModele->getTempsDepart());
    //active le timer
    timer->start();
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
    //Génère un coup aléatoire pour la machine
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    //détermine le gagnant
    _leModele->determinerGagnant();
    //Mise à jour de l'interface
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());

    //si le joueur atteint le score maximal
    if (_leModele->getScoreJoueur() >= _leModele->getScoreMax()){
        _leModele->setEtatPartie(Modele::UnEtat::accueil);
        _laVue->afficherFinScore(_leModele->getScoreJoueur(), "joueur", _leModele->getTempsRestant(), _leModele->getTempsDepart());
    }

    //si la machine atteint le score maximal
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

        //si le temps restant n'est pas négatif
        if (_leModele->getTempsRestant() > ZERO)
        {
            //MAJ de l'affichage du timer et de sa valeure
            _leModele->setTempsRestant(_leModele->getTempsRestant() - 1);
            _laVue->majTimer(_leModele->getTempsRestant());
        }
        else
        {
            //L'état de la parite passe à l'accueil
            _leModele->setEtatPartie(Modele::UnEtat::accueil);

            //si le joueur à un score plus élevé
            if (_leModele->getScoreJoueur() > _leModele->getScoreMachine()){
                _laVue->afficherFinScore(_leModele->getScoreJoueur(), "joueur", _leModele->getTempsRestant(), _leModele->getTempsDepart());

            }

            //si la machine a un score plus élevé
            else if (_leModele->getScoreMachine() > _leModele->getScoreJoueur() ){
                _laVue->afficherFinScore(_leModele->getScoreMachine(), "Machine", _leModele->getTempsRestant(), _leModele->getTempsDepart());
            }

            //si il y a égalité
            else {
                _laVue->afficherFinScore(_leModele->getScoreMachine(), "égalité", _leModele->getTempsRestant(), _leModele->getTempsDepart());
            }
        }
    }
}

void Presentation::demanderPause()
{
    //l'état du jeu est enJeu
    if (_leModele->getEtat() == Modele::UnEtat::enJeu){
        //le timer est stoppé
        timer->stop();
        //l'état du jeu passe en pause
        _leModele->setEtatPartie(Modele::UnEtat::pause);
        //MAJ de l'interface
        _laVue->majInterface(_leModele->getEtat());
    }

    //l'état du jeu est en pause
    else if (_leModele->getEtat() == Modele::UnEtat::pause) {
        //le timer repart
        timer->start();
        //l'état du jeu passe enJeu
        _leModele->setEtatPartie(Modele::UnEtat::enJeu);
        //MAJ de l'interface
        _laVue->majInterface(_leModele->getEtat());
    }

}

void Presentation::demanderOuvrirParameres()
{
    //instenciation du questionnaire
    questionnaire = new Dialog(getVue());
    int retour = questionnaire->exec();
    switch (retour) {

    //si l'utilisateur clique sur OK
    case QDialog::Accepted:
        //l'état du jeu passe à l'accueil
        _leModele->setEtatPartie(Modele::UnEtat::accueil);
        //met dans la variable scoreMax ce que l'utilisateur a saisit
        _leModele->setScoreMax(questionnaire->getScore());
        //met dans la variable tempsDepart ce que l'utilisateur a saisit
        _leModele->setTempsDepart(questionnaire->getTemps());
        //met dans la variable tempsRestant ce que l'utilisateur a saisit
        _leModele->setTempsRestant(questionnaire->getTemps());
        //MAJ de l'interface
        _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(),questionnaire->getScore(),questionnaire->getTemps(),questionnaire->getNom());
        break;

    //si l'utilisateur clique sur cancel
    case QDialog::Rejected:
        break;
    }
}

void Presentation::afficherConnexion(){
    connexion=new Connexion(getVue());
    connexion->exec();
}
