#include "almox_novoitem.h"
#include "ui_almox_novoitem.h"
#include <conexao.h>


almox_novoItem::almox_novoItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almox_novoItem)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("tb_itens");
    model->select();


    model->setHeaderData(0, Qt::Horizontal,"Código");
    model->setHeaderData(1, Qt::Horizontal,"Produto");
    model->setHeaderData(2, Qt::Horizontal,"Quantidade");
    model->setHeaderData(3, Qt::Horizontal,"Unidade");
    model->setHeaderData(4, Qt::Horizontal,"Valor [R$]");
    model->setHeaderData(5, Qt::Horizontal,"Data de Entrada");
    model->setHeaderData(6, Qt::Horizontal,"Valor Total [R$]");

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnWidth(0,50);
    ui->tableView->setColumnWidth(1,230);


}

almox_novoItem::~almox_novoItem()
{
    delete ui;
}
