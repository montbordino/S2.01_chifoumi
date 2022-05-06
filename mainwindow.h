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

private slots:
    void lancerPartie();
    void jouerPierre();
    void jouerFeuille();
    void jouerCiseaux();
};
#endif // MAINWINDOW_H
