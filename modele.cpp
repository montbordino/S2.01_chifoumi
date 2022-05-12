/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "modele.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD�LE ---------------------------

Modele::Modele():
    scoreJoueur(0),
    scoreMachine(0),
    coupJoueur(rien),
    coupMachine(rien)
{
}

Modele::~Modele()
{
    delete[] this;
}

        /// Getters

Modele::UnCoup Modele::getCoupJoueur() {
    return (*this).coupJoueur;
}

Modele::UnCoup Modele::getCoupMachine() {
    return (*this).coupMachine;
}

unsigned int Modele::getScoreJoueur() {
    return (*this).scoreJoueur;
}

unsigned int Modele::getScoreMachine() {
    return (*this).scoreMachine;
}

char Modele::determinerGagnant()
{
    char gagnantARetourner = '\0';

    // avant de commencer : match nul
    if ((*this).coupJoueur == ((*this).coupMachine)){
        gagnantARetourner = 'N';
    }

    // il sera modifi� dans l'un des cas suivants
    else if (((*this).coupMachine == (*this).coupJoueur+1) || ((*this).coupMachine + 2 == (*this).coupJoueur)){
        gagnantARetourner = 'M';
    }
    else if (((*this).coupMachine+1 == (*this).coupJoueur) || ((*this).coupMachine == (*this).coupJoueur +2)){
        gagnantARetourner = 'J';
    }

    return gagnantARetourner;
}

         ///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Modele::UnCoup Modele::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur � retourner
    int nb_au_hasard = randMinMax(0, 3);
    switch (nb_au_hasard)
    {
    case 0:
        valeurGeneree = pierre;
        break;

    case 1:
        valeurGeneree = papier;
        break;

    case 2:
        valeurGeneree = ciseau;
        break;
    }

    return valeurGeneree;
}

        /// Setters

void Modele::setCoupJoueur(UnCoup p_coup) {
    (*this).coupJoueur=p_coup;
}

void Modele::setCoupMachine(UnCoup p_coup) {
    (*this).coupMachine=p_coup;
}

void Modele::setScoreJoueur(unsigned int p_score) {
    (*this).scoreJoueur=p_score;
}

void Modele::setScoreMachine(unsigned int p_score) {
    (*this).scoreMachine=p_score;
}

void Modele::majScores(char p_gagnant) {
    if (p_gagnant == 'J'){
        (*this).scoreJoueur++;
    }
    else if (p_gagnant == 'M'){
        (*this).scoreMachine++;
    }
}

void Modele::initScores() {
    (*this).scoreMachine=0;
    (*this).scoreJoueur=0;
}

void Modele::initCoups() {
    (*this).coupJoueur=rien;
    (*this).coupMachine=rien;
}

Modele::UnEtat Modele::getEtat()
{
    return _etat;
}