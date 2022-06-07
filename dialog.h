#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    /**
     * @brief retourne le nom saisit par l'utilisateur
     * @return QString
     */
    QString getNom();

    /**
     * @brief retourne le score saisit par l'utilisateur
     * @return int
     */
    int getScore();

    /**
     * @brief retourne le temps saisit par l'utilisateur
     * @return int
     */
    int getTemps();

private:
    Ui::Dialog *ui;             //le ui du dialog
    QString nom;                //nom saisit
    int scoreMax;               //score saisit
    int temp;                   //temp saisit


};

#endif // DIALOG_H
