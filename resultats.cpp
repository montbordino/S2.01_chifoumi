#include "resultats.h"
#include "ui_resultats.h"

Resultats::Resultats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultats)
{
    ui->setupUi(this);

    //Adresser la connexion ODBC
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("S2.01");

    //ouverture de la base de donnée
    db.open();

    //executer la requete SQL
    QSqlQuery query;
    query.exec("SELECT Joueur.Nom ,Parties.scoreJoueur FROM Joueur JOIN Parties ON Joueur.ID=Parties.indexJoueur ORDER BY Parties.scoreJoueur DESC LIMIT 10");

    QStringList header; // nom des colonnes
    header << "Nom" << "Score" ;
    // On fixe le nombre de colonnes
    ui->tableWidgetResultats->setColumnCount(header.size());
    // On applique les noms des colonnes
    ui->tableWidgetResultats->setHorizontalHeaderLabels(header);
    // on cache les numéros de ligne
    ui->tableWidgetResultats->verticalHeader()->setHidden(true);
    QHeaderView * headerView = ui->tableWidgetResultats->horizontalHeader();
    // on redimensionne automatiquement la colonne pour occuper l'espacedisponible
    headerView->setSectionResizeMode(QHeaderView::Stretch);

    //Initialise compteur a zéro
    int rowCount = 0;
    while (query.next()) {

        //Insertion d'une colonne
        ui->tableWidgetResultats->insertRow(rowCount);
        QTableWidgetItem *nom = new QTableWidgetItem;
        QTableWidgetItem *score = new QTableWidgetItem;

        //mettre dans des variables le nom et le score
        nom->setText(query.value(0).toString());
        score->setText(query.value(1).toString());

        //insertion dans chaque ligne et colonne
        //Insertion du nom dans la colonne 1
        ui->tableWidgetResultats->setItem(rowCount, 0, nom);
        //Insertion du score dans la colonne 2
        ui->tableWidgetResultats->setItem(rowCount, 1, score);

        rowCount++;
    }

    //fermeture de la base donnée
}

Resultats::~Resultats()
{
    delete ui;
}
