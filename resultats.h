#ifndef RESULTATS_H
#define RESULTATS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Resultats;
}

class Resultats : public QDialog
{
    Q_OBJECT

public:
    explicit Resultats(QWidget *parent = nullptr);
    ~Resultats();

private:
    Ui::Resultats *ui;
    QSqlDatabase db;                //base de donnée de la saé
};

#endif // RESULTATS_H
