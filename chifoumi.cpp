/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD�LE ---------------------------

Chifoumi::Chifoumi():
    scoreJoueur(0),
    scoreMachine(0),
    coupMachine(rien),
    coupJoueur(rien)
{
}

Chifoumi::~Chifoumi()
{
    delete[] this;
}

        /// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
	return (*this).coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return (*this).coupJoueur;
}

unsigned int Chifoumi::getScoreJoueur() {
    return (*this).scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return (*this).scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi� dans l'un des cas suivants
    if ((*this).scoreJoueur > ((*this).scoreMachine)){
        gagnantARetourner = 'J';
    }
    else if (((*this).scoreMachine > (*this).scoreJoueur)){
        gagnantARetourner = 'M';
    }

    return gagnantARetourner;
}

         ///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur � retourner
    int nb_au_hasard = randMinMax(0, 2);
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

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    (*this).coupJoueur=p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    (*this).coupMachine=p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    (*this).scoreJoueur=p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    (*this).scoreMachine=p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    if (p_gagnant == 'J'){
        (*this).scoreJoueur++;
    }
    else if (p_gagnant == 'M'){
        (*this).scoreMachine;
    }
}

void Chifoumi::initScores() {
    (*this).scoreMachine=0;
    (*this).scoreJoueur=0;
}

void Chifoumi::initCoups() {
    (*this).coupJoueur=rien;
    (*this).coupMachine=rien;
}
