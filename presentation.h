#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"

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
public slots:
    void demanderLancerPartie();
    void demanderJouerPierre();
    void demanderJouerPapier();
    void demanderJouerCiseau();
    void demanderQuitterApp();
    void demanderInfosApp();
};

#endif // PRESENTATION_H
