/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "modele.h"
#include <cstdlib>
#include <QDebug>

    ///* ---- PARTIE MOD�LE ---------------------------

Modele::Modele():
    scoreJoueur(0),
    scoreMachine(0),
    coupJoueur(rien),
    coupMachine(rien),
    scoreMax(5),
    tempsRestant(30),
    tempsDepart(30)

{
    //Adresser la connexion ODBC

    //db=QSqlDatabase::addDatabase("QODBC");
    //db.setDatabaseName("S2.01");
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

unsigned int Modele::getScoreMax() {
    return (*this).scoreMax;
}

unsigned int Modele::getTempsDepart() {
    return (*this).tempsDepart;
}

unsigned int Modele::getTempsRestant() {
    return (*this).tempsRestant;
}

void Modele::determinerGagnant()
{
    int score;
    // avant de commencer : match nul
    if ((*this).coupJoueur == ((*this).coupMachine)){
        (*this).setScoreJoueur((*this).getScoreJoueur());
        (*this).setScoreMachine((*this).getScoreMachine());
    }

    // il sera modifi� dans l'un des cas suivants
    else if (((*this).coupMachine == (*this).coupJoueur+1) || ((*this).coupMachine + 2 == (*this).coupJoueur)){
        score=(*this).getScoreMachine()+1;
        (*this).setScoreMachine(score);
    }
    else if (((*this).coupMachine+1 == (*this).coupJoueur) || ((*this).coupMachine == (*this).coupJoueur +2)){
        score=(*this).getScoreJoueur()+1;
        (*this).setScoreJoueur(score);
    }

}

         ///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Modele::UnCoup Modele::genererUnCoup()
{
    UnCoup valeurGeneree = rien;   // valeur � retourner
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

void Modele::setEtatPartie(UnEtat etatPartie) {
    (*this)._etat=etatPartie;
}

void Modele::setTempsDepart(unsigned int temps) {
    (*this).tempsDepart=temps;
}

void Modele::setTempsRestant(unsigned int temps) {
    (*this).tempsRestant=temps;
}

void Modele::setScoreMax(unsigned int score) {
    (*this).scoreMax=score;
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

void Modele::enregistrerPartie(const int &indexJoueur){
    //lié la connexion ODBC
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("S2.01");

    //Ouvre la base donnée
    this->db.open();

    //Déclaration des query
    QSqlQuery query1;
    QSqlQuery query2;
    int index;

    //Récupère l'index maximal
    query1.exec("SELECT MAX(Parties.Index) FROM Parties");
    query1.next();
    index=query1.value(0).toInt();

    //Prépare la query
    query2.prepare("INSERT INTO Parties VALUES(?,?,?,?)");

    //ajout de l'index, l'indexJoueur et les scrores
    query2.addBindValue(index+1);
    query2.addBindValue(indexJoueur);
    query2.addBindValue(scoreJoueur);
    query2.addBindValue(scoreMachine);

    //éxécution de la requete
    query2.exec();

    //fermeture de la base de donnée
    this->db.close();
}
