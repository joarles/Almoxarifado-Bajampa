#ifndef ALMOX_GESTAOCOLAB_H
#define ALMOX_GESTAOCOLAB_H

#include <QDialog>
#include "conexao.h"
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class almox_gestaoColab;
}

class almox_gestaoColab : public QDialog
{
    Q_OBJECT

public:
    explicit almox_gestaoColab(QWidget *parent = nullptr);
    ~almox_gestaoColab();
    Conexao con;
    void removerLinhas(QTableWidget *tw);

private slots:
    void on_btn_limpar_clicked();

    void on_btn_gravarColab_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_gc_colab_itemSelectionChanged();

    void on_btn_gc_excluir_clicked();

    void on_btn_gc_gravar_clicked();

private:
    Ui::almox_gestaoColab *ui;
};

#endif // ALMOX_GESTAOCOLAB_H
