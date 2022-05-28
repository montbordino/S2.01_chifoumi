#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
#include <QTimer>

class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Modele *m, QObject *parent = nullptr);
public:
    Modele* getModele();
    ChifoumiVue* getVue();
    void setModele(Modele *m);
    void setVue(ChifoumiVue *v);

private:
    Modele *_leModele;
    ChifoumiVue *_laVue;
    QTimer *timer = new QTimer(this);

    const unsigned short int ZERO = 0;
public slots:
    void demanderLancerPartie();
    void demanderJouerPierre();
    void demanderJouerPapier();
    void demanderJouerCiseau();
    void demanderPause();
    void demanderQuitterApp();
    void demanderInfosApp();
    void update();
    void demanderJouerTour();
};

#endif // PRESENTATION_H
