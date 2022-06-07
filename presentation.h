#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
#include <QTimer>
#include "dialog.h"
#include "connexion.h"

class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Modele *m,ChifoumiVue *v, QObject *parent = nullptr);
public:
    Modele* getModele();
    ChifoumiVue* getVue();
    void setModele(Modele *m);
    void setVue(ChifoumiVue *v);
    void afficherConnexion();


private:
    Modele *_leModele;
    ChifoumiVue *_laVue;
    QTimer *timer = new QTimer(this);
    Dialog * questionnaire;
    Connexion *connexion;

    const unsigned short int ZERO = 0;
public slots:
    void demanderLancerPartie();
    void demanderJouerPierre();
    void demanderJouerPapier();
    void demanderJouerCiseau();
    void demanderPause();
    void demanderQuitterApp();
    void demanderInfosApp();
    void demanderJouerTour();
    void demanderOuvrirParameres();


    // decremente le QTimer et l'affiche à l'écran. S'occupe également de la fin de partie si le temps atteint ZERO
    void update();
};

#endif // PRESENTATION_H
