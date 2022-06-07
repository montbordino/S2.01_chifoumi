#include "connexion.h"
#include "ui_connexion.h"
#include <QMessageBox>
#include <QDebug>

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

    //Variables temporels
    //variables saisit par l'utilisateur
    QString idUtilisateur;
    QString mdpUtilisateur;
    //variables de la requete
    QString idRequete;
    QString mdpRequete;

    //Récupération des champs saisit par l'utilisateur
    idUtilisateur=this->getId();
    mdpUtilisateur=this->getMdp();

    //Requete permetant de récuperer tout les identifiants et mots de passe associés
    QSqlQuery query;
    query.prepare("SELECT * FROM Joueur WHERE nom=? and MDP=?");
    query.addBindValue(idUtilisateur);
    query.addBindValue(mdpUtilisateur);
    query.exec();

    //Vérification
    if(query.next()){
        this->close();
        id=query.value(1).toString();
        mdp=query.value(2).toString();
    }
    else {
        QMessageBox::information(this,"Erreur","L'identifiant ou le mot de passe sont incorrects",QMessageBox::Ok);
    }
}
