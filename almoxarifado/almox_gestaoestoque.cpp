#include "almox_gestaoestoque.h"
#include "ui_almox_gestaoestoque.h"
#include "almox_logar.h"
#include "mainwindow.h"


#include <QtSql>

int id_estoque = -1;

almox_gestaoEstoque::almox_gestaoEstoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almox_gestaoEstoque)
{
    ui->setupUi(this);
    if(!con.abrir()){
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de Dados!");
    }else {
        QSqlQuery query;
        query.prepare("select * tb_itens");
        if(query.exec()){}
    }
    ui->tw_ge_produtos->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);
}

almox_gestaoEstoque::~almox_gestaoEstoque()
{
    delete ui;
    con.fechar();
}

void almox_gestaoEstoque::on_btn_novoItem_clicked()
{
    ui->txt_codigo->clear();
    ui->txt_produto->clear();
    ui->txt_valor->clear();
    ui->txt_quantidade->clear();
    ui->txt_codigo->setFocus();

}

void almox_gestaoEstoque::on_btn_gravarNovo_clicked()
{

    QString aux;
    QString codigo = ui->txt_codigo->text();
    QString produto = ui->txt_produto->text();

    aux = ui->txt_valor->text();
    std::replace(aux.begin(), aux.end(), ',', '.');
    QString valor = aux;

    aux = ui->txt_quantidade->text();
    std::replace(aux.begin(), aux.end(), ',', '.');
    QString quantidade = aux;

    QString a = QString::number(quantidade.toFloat()*valor.toFloat());

    QString unidade = ui->combBox_unidade->currentText();

    QSqlQuery query;
    query.prepare("insert into tb_itens (id_item, produto, qtde_estoque, unidade, valor, data_entrada, valor_total) values"
        "("+QString::number(codigo.toInt())+",'"+produto+"',"+QString::number(quantidade.toFloat())+",'"+unidade+"',"+QString::number(valor.toFloat())+", :datetime, "+QString::number(a.toFloat())+" )");

    QDateTime timestamp = QDateTime::currentDateTime();
    timestamp.addDays(1);
    query.bindValue(":datetime", timestamp);// 2017-09-05T11:50:39
    // Custom format
    query.bindValue(":datetime", timestamp.toString("hh:mm:ss dd-MM-yyyy"));

    if(!query.exec()){
        QMessageBox::warning(this, "ERRO", "Erro ao inserir produto!");
    }else {
        QMessageBox::information(this, "GRAVADO", "Gravação feita com Sucesso!");
        ui->txt_codigo->clear();
        ui->txt_produto->clear();
        ui->txt_valor->clear();
        ui->txt_quantidade->clear();
        ui->txt_codigo->setFocus();
    }
}

void almox_gestaoEstoque::on_tabWidget_currentChanged(int index)
{
    if(index==1){
        removerLinhas(ui->tw_ge_produtos);
        int contLinhas = 0;
        QSqlQuery query;
        query.prepare("select id_item, produto from tb_itens order by produto");
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_produtos->insertRow(contLinhas);
                ui->tw_ge_produtos->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_produtos->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_produtos->setRowHeight(contLinhas, 20);
                contLinhas++;
            }
            ui->tw_ge_produtos->setColumnWidth(0,50);
            ui->tw_ge_produtos->setColumnWidth(1,230);
            QStringList cabecalhos={"Código", "Produto"};
            ui->tw_ge_produtos->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_ge_produtos->setStyleSheet("QTableView {selection-background-color:red");
            ui->tw_ge_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_ge_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_ge_produtos->verticalHeader()->setVisible(false);
        }else{
            QMessageBox::warning(this, "ERRO", "Erro ao listar produtos!");
        }
    }
    ui->tw_ge_produtos->setColumnCount(2);

}

void almox_gestaoEstoque::removerLinhas(QTableWidget *tw){
    while(tw->rowCount()>0){
        tw->removeRow(0);
    }
}

void almox_gestaoEstoque::on_tw_ge_produtos_itemSelectionChanged()
{
    if(MainWindow::acesso_colab == "B"){
        ui->txt_ge_codigo->setEnabled(false);
        ui->txt_ge_produto->setEnabled(false);
        ui->txt_ge_unidade->setEnabled(false);
        ui->txt_ge_valor->setEnabled(false);
    }
    id_estoque = ui->tw_ge_produtos->item(ui->tw_ge_produtos->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from tb_itens where id_item="+QString::number(id_estoque));
    if(query.exec()){
        query.first();
        ui->txt_ge_valor->setText(query.value(4).toString());
        ui->txt_ge_codigo->setText(query.value(0).toString());
        ui->txt_ge_produto->setText(query.value(1).toString());
        ui->txt_ge_quantidade->setText(query.value(2).toString());
        ui->txt_ge_unidade->setText(query.value(3).toString());
    }else {
        QMessageBox::warning(this, "ERRO", "Trotos!");
    }
}

void almox_gestaoEstoque::on_btn_ge_excluir_clicked()
{
    if( id_estoque ==-1){
        QMessageBox::warning(this, "ERRO", "Erro ao apagar Produto, Nenhum item selecionado!");
    }else{
        QSqlQuery query;
        query.prepare("delete from tb_itens where id_item="+QString::number(id_estoque));
        if(!query.exec()){
            QMessageBox::warning(this, "ERRO", "Erro ao apagar Produto!");
        }else {
            QMessageBox::information(this,"Apagado", "Item apagado com sucesso!");
            removerLinhas(ui->tw_ge_produtos);
            int contLinhas = 0;
            QSqlQuery query;
            query.prepare("select id_item,produto from tb_itens order by produto");
            if(query.exec()){
                while(query.next()){
                    ui->tw_ge_produtos->insertRow(contLinhas);
                    ui->tw_ge_produtos->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                    ui->tw_ge_produtos->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                    ui->tw_ge_produtos->setRowHeight(contLinhas, 20);
                    contLinhas++;
                }
                ui->tw_ge_produtos->setColumnWidth(0,50);
                ui->tw_ge_produtos->setColumnWidth(1,230);
                QStringList cabecalhos={"Código", "Produto"};
                ui->tw_ge_produtos->setHorizontalHeaderLabels(cabecalhos);
                ui->tw_ge_produtos->setStyleSheet("QTableView {selection-background-color:red");
                ui->tw_ge_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
                ui->tw_ge_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
                ui->tw_ge_produtos->verticalHeader()->setVisible(false);

            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao listar produtos!");
            }
            ui->tw_ge_produtos->setColumnCount(2);
        }
    }
}

void almox_gestaoEstoque::on_btn_ge_gravar_clicked()
{
    if( id_estoque ==-1){
        QMessageBox::warning(this, "ERRO", "Erro ao Salvar Produto, Nenhum item selecionado!");
    }else{
        QString aux;
        aux = ui->txt_ge_valor->text();
        std::replace(aux.begin(), aux.end(), ',', '.');
        QString valor = aux;

        aux = ui->txt_ge_quantidade->text();
        std::replace(aux.begin(), aux.end(), ',', '.');
        QString quantidade = aux;

        QSqlQuery query;
        query.prepare("UPDATE tb_itens set qtde_estoque='"+quantidade+"', valor='"+valor+"' where id_item="+QString::number(id_estoque));
        if(!query.exec()){
            QMessageBox::warning(this, "ERRO", "Erro ao Salvar Produto!");
        }else {
            QMessageBox::information(this,"Apagado", "Alteração Salva com sucesso!");
        }
    }
}
