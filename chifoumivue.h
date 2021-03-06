#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "QPixmap"
#include "modele.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    ChifoumiVue(QMainWindow *parent = nullptr);
    ~ChifoumiVue();
public:
    // pour créer une connexion avec la présentation
    void nvlleConnexion(QObject *c);
    void supprConnexion(QObject *c);
    // ordres reçus par la présentation
    void majInterface (Modele::UnEtat, Modele::UnCoup=Modele::UnCoup::rien,Modele::UnCoup=Modele::UnCoup::rien,int=0,int=0,int=5,int=30,QString="Vous");

private:
    Ui::ChifoumiVue *ui;
    //ChifoumiVue jeu;
    QPixmap *pierre;
    QPixmap *feuille;
    QPixmap *ciseau;
    QPixmap *rien;

private slots:
    /**
     * @brief lance une nouvelle partie en effacant les données de la précédente et met la couleur bleu sur le joueur
     */

    void lancerPartie(QString="vous",int=5,int=30);

    /**
     * @brief permet de parametrer le jeux avec le nom, le score maximal et le temps max
     */
    void parametrerPartie(QString="vous",int=5,int=30);

    /**
     * @brief met la couleur bleu sur la machine, choisis son coup au hasard et l'affiche à l'écran puis lance finPartie()
     */
    void tourMachine(Modele::UnCoup,int=0,int=0);

    /**
     * @brief modifie le score et prénom du joueur cible en bleu et change ceux de l'autre joueur en noir
     * @arg caractère qui définis la cible: 'J' pour le joueur et 'M' pour la machine
     */
    void setBlue(char);

    /**
     * @brief definis l'image du joueur machine en fonction de son coup Chifoumi::UnCoup
     */
    void definirImageMachine(Modele::UnCoup);

    /**
     * @brief définis le joueur gagnant la manche, met à jour les scores, les affiches à l'écran et met la couleur bleu sur le joueur humain
     */
    void finManche(int=0,int=0);

public slots:
    void quitterApp();

    /**
     * @brief affiche une fenetre de dialogue donnant les informations sur la victoire
     *        et fini la partie
     */
    void afficherFinScore(int, QString, unsigned int, unsigned int);

    /**
     * @brief affiche la version de l’application, la date de création, les auteurs dans une messageBox
     */
    void infosApp();

    /**
     * @brief affiche à l'écran le timer représenté par un int
     */
    void majTimer(int);
};
#endif // CHIFOUMIVUE_H
