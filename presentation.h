#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
#include <QTimer>
#include "dialog.h"
#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Modele *m,ChifoumiVue *v, QObject *parent = nullptr);
public:

    /**
     * @brief retourne le modèle associé à la présentation
     * @return Modele
     */
    Modele* getModele();

    /**
     * @brief retourne la vue associé à la présentation
     * @return ChifoumiVue
     */
    ChifoumiVue* getVue();

    /**
     * @brief permet de paramétrer le modele
     * @param m
     */
    void setModele(Modele *m);

    /**
     * @brief permet de paramétrer la vue
     * @param v
     */
    void setVue(ChifoumiVue *v);

    /**
     * @brief affiche et execute la dialog de connexion
     */
    void afficherConnexion();


private:
    Modele *_leModele;                      //Modele associé à la présentation grâce à un pointeur
    ChifoumiVue *_laVue;                    //Vue associé à la présentation grâce à un pointeur
    QTimer *timer = new QTimer(this);       //Instencie le timer
    Dialog * questionnaire;                 //Questionnaire associé à la présnetation
    Connexion *connexion;                   //connexion associé à la présentation
    QSqlDatabase db;                //base de donnée de la saé

    const unsigned short int ZERO = 0;
public slots:

    /**
     * @brief lance la partie grâce bouton bLancer
     */
    void demanderLancerPartie();

    /**
     * @brief joue pierre lorsque l'utilisateur clique sur pierre
     */
    void demanderJouerPierre();

    /**
     * @brief joue pierre lorsque l'utilisateur clique sur papier
     */
    void demanderJouerPapier();

    /**
     * @brief joue pierre lorsque l'utilisateur clique sur ciseau
     */
    void demanderJouerCiseau();

    /**
     * @brief met en pause l'application
     */
    void demanderPause();

    /**
     * @brief ferme l'application
     */
    void demanderQuitterApp();

    /**
     * @brief affiche les informations de l'application
     */
    void demanderInfosApp();

    /**
     * @brief sous-programme permetant de gnérer un coup machine ainsi que le coup joueur
     */
    void demanderJouerTour();

    /**
     * @brief ouvre la dialog permetant de paramétrer le jeu
     */
    void demanderOuvrirParameres();


    // decremente le QTimer et l'affiche à l'écran. S'occupe également de la fin de partie si le temps atteint ZERO
    void update();
};

#endif // PRESENTATION_H
