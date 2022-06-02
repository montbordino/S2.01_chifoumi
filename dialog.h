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
    QString getNom();
    int getScore();
    int getTemps();

private:
    Ui::Dialog *ui;
    QString nom;
    int scoreMax;
    int temp;


};

#endif // DIALOG_H
