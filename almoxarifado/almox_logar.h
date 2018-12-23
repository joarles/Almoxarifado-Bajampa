#ifndef ALMOX_LOGAR_H
#define ALMOX_LOGAR_H

#include <QDialog>
#include "conexao.h"

namespace Ui {
class almox_logar;
}

class almox_logar : public QDialog
{
    Q_OBJECT

public:
    explicit almox_logar(QWidget *parent = nullptr);
    ~almox_logar();
    bool logado;
    Conexao con;
    QString nome, acesso;
    int id;



private slots:
    void on_btn_logar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::almox_logar *ui;
};

#endif // ALMOX_LOGAR_H
