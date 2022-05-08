#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chifoumi.h"
#include "QPixmap"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Chifoumi jeu;
    QPixmap *pierre;
    QPixmap *feuille;
    QPixmap *ciseau;
    QPixmap *rien;

private slots:
    /**
     * @brief lance une nouvelle partie en effacant les données de la précédente et met la couleur bleu sur le joueur
     */
    void lancerPartie();

    /**
     * @brief change le coup du joueur, l'affiche à l'écran et lance tourMachine()
     */
    void jouerPierre();
    void jouerFeuille();
    void jouerCiseaux();

    /**
     * @brief met la couleur bleu sur la machine, choisis son coup au hasard et l'affiche à l'écran puis lance finPartie()
     */
    void tourMachine();

    /**
     * @brief modifie le score et prénom du joueur cible en bleu et change ceux de l'autre joueur en noir
     * @arg caractère qui définis la cible: 'J' pour le joueur et 'M' pour la machine
     */
    void setBlue(char);

    /**
     * @brief definis l'image du joueur machine en fonction de son coup Chifoumi::UnCoup
     */
    void definirImageMachine(Chifoumi::UnCoup);

    /**
     * @brief définis le joueur gagnant la manche, met à jour les scores, les affiches à l'écran et met la couleur bleu sur le joueur humain
     */
    void finManche();
};
#endif // MAINWINDOW_H
