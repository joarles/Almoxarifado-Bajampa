#ifndef ALMOX_GESTAOESTOQUE_H
#define ALMOX_GESTAOESTOQUE_H

#include <QDialog>
#include "conexao.h"
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class almox_gestaoEstoque;
}

class almox_gestaoEstoque : public QDialog
{
    Q_OBJECT

public:
    explicit almox_gestaoEstoque(QWidget *parent = nullptr);
    ~almox_gestaoEstoque();
    Conexao con;
    void removerLinhas(QTableWidget *tw);

private slots:
    void on_btn_novoItem_clicked();

    void on_btn_gravarNovo_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_produtos_itemSelectionChanged();

    void on_btn_ge_excluir_clicked();

    void on_btn_ge_gravar_clicked();

private:
    Ui::almox_gestaoEstoque *ui;
};

#endif // ALMOX_GESTAOESTOQUE_H
