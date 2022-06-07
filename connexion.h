#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();

    /**
     * @brief retourne l'identifiant de l'utilisateur
     * @return QString
     */
    QString getId();

    /**
     * @brief retourne le mot de passe de l'utilisateur
     * @return QString
     */
    QString getMdp();

    /**
     * @brief configure le mot de passe
     */
    void setMdp(QString);

    /**
     * @brief configure l'identifiant
     */
    void setId(QString);

private:
    Ui::Connexion *ui;              // UI de la connexion
    QString id;                     // identifiant de la connexion
    QString mdp;                    // Mot de passe de la connexion
    QSqlDatabase db;                //base de donnée de la saé
public slots:

    /**
     * @brief vérifie l'identifiant et le mot de passe saisit par l'utilisateur
     */
    void valider();
};

#endif // CONNEXION_H
