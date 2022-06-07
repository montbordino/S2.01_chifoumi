#include "connexion.h"
#include "ui_connexion.h"
#include <QMessageBox>

Connexion::Connexion(QWidget *v) :
    QDialog(v),
    ui(new Ui::Connexion)
{
    //connexion à l'UI connexion
    ui->setupUi(this);

    //Adresser la connexion ODBC
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("S2.01");

    //connexion au bouton valider
    QObject::connect(ui->bValider,SIGNAL(clicked()),this,SLOT(valider()));

}

Connexion::~Connexion()
{
    delete ui;
}

QString Connexion::getId(){
    id = ui->lineEditId->text();
    return id;
}

QString Connexion::getMdp(){
    mdp = ui->lineEditMdp->text();
    return mdp;
}

void Connexion::setMdp(QString newMdp){
    mdp = newMdp;
}

void Connexion::setId(QString newId){
    id = newId;
}

void Connexion::valider(){

    //Ouverture de la base de donnée
    this->db.open();

    //Requete permetant de récuperer tout les identifiants et mots de passe associés
    QSqlQuery query("SELECT * FROM Joueur");

    //Variables temporels
    QString idRequete;
    QString mdpRequete;
    bool valide = false;

    //Vérification
    while(query.next()){
        idRequete = query.value(1).toString();          //Vérification de l'identifiant
        mdpRequete = query.value(2).toString();         //Vérification du mot de passe

        //Si les champs saisit correspondent à ceux de la requete
        if (idRequete==this->getId() && mdpRequete==this->getMdp()){

            //Fermeture de cette boite de dialog
            this->close();
            valide = true;
        }
    }
    if (!(valide)){
        QMessageBox::information(this,"Erreur","L'identifiant ou le mot de passe sont incorrects",QMessageBox::Ok);

    }
}
