#include "chifoumivue.h"
#include "modele.h"
#include "presentation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // créer la vue
    ChifoumiVue *w=new ChifoumiVue;
    // créer le modèle
    Modele *m = new Modele();
    // créer la présentation et lui associer le modèle et la vue
    Presentation *p = new Presentation(m,w);
    // initialiser la vue en conformité avec l'état initial du modèle
    p->getVue()->majInterface(m->getEtat());
    // connexion des signaux de la vue avec les slots de la présentation
    w->nvlleConnexion(p);
    //affiche la fenetre de connexion
    p->afficherConnexion();
    // afficher la vue et démarrer la boucle d'attente des messages
    w->show();
    return a.exec();
}
