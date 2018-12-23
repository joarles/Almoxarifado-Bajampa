#include "almox_gestaocolab.h"
#include "ui_almox_gestaocolab.h"

int id_colab =-1;

almox_gestaoColab::almox_gestaoColab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almox_gestaoColab)
{
    ui->setupUi(this);
    if(!con.abrir()){
        QMessageBox::warning(this, "ERRO", "Erro ao abrir o banco de Dados!");
    }else {
        QSqlQuery query;
        query.prepare("select * tb_colaboradores");
        if(query.exec()){}
    }
    ui->tw_gc_colab->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);

}

almox_gestaoColab::~almox_gestaoColab()
{
    delete ui;
    con.fechar();
}

void almox_gestaoColab::on_btn_limpar_clicked()
{
    ui->txt_nome->clear();
    ui->txt_username->clear();
    ui->txt_senha->clear();
    ui->txt_nome->setFocus();
}

void almox_gestaoColab::on_btn_gravarColab_clicked()
{
    QString nome = ui->txt_nome->text();
    QString user= ui->txt_username->text();
    QString senha = ui->txt_senha->text();
    QString acesso = ui->cb_acesso->currentText();

    QSqlQuery query;
    query.prepare("insert into tb_colaboradores (nome_colab, username_colab, senha_colab, acesso_colab) values"
        "('"+nome+"','"+user+"','"+senha+"', '"+acesso+"')");
    if(!query.exec()){
        QMessageBox::warning(this, "ERRO", "Erro ao inserir Colaborador!");
    }else {
        QMessageBox::information(this, "GRAVADO", "Gravação feita com Sucesso!");
        ui->txt_nome->clear();
        ui->txt_username->clear();
        ui->txt_senha->clear();
        ui->txt_nome->setFocus();
    }
}

void almox_gestaoColab::on_tabWidget_currentChanged(int index)
{
    if(index==1){
        removerLinhas(ui->tw_gc_colab);
        int contLinhas = 0;
        QSqlQuery query;
        query.prepare("select id_colab, nome_colab from tb_colaboradores order by nome_colab");
        if(query.exec()){
            while(query.next()){
                ui->tw_gc_colab->insertRow(contLinhas);
                ui->tw_gc_colab->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                ui->tw_gc_colab->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                ui->tw_gc_colab->setRowHeight(contLinhas, 20);
                contLinhas++;
            }
            ui->tw_gc_colab->setColumnWidth(0,50);
            ui->tw_gc_colab->setColumnWidth(1,230);
            QStringList cabecalhos={"Código", "Colaborador"};
            ui->tw_gc_colab->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_gc_colab->setStyleSheet("QTableView {selection-background-color:red");
            ui->tw_gc_colab->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_gc_colab->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_gc_colab->verticalHeader()->setVisible(false);
        }else{
            QMessageBox::warning(this, "ERRO - MUDANÇA DE ABA", "Erro ao listar Colaboradores!");
        }
    }
    ui->tw_gc_colab->setColumnCount(2);
}

void almox_gestaoColab::removerLinhas(QTableWidget *tw){
    while(tw->rowCount()>0){
        tw->removeRow(0);
    }
}

void almox_gestaoColab::on_tw_gc_colab_itemSelectionChanged()
{
    id_colab=ui->tw_gc_colab->item(ui->tw_gc_colab->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from tb_colaboradores where id_colab="+QString::number(id_colab));
    if(query.exec()){
        query.first();
        ui->txt_gc_codigo->setText(query.value(0).toString());
        ui->txt_gc_nome->setText(query.value(1).toString());
        ui->txt_gc_username->setText(query.value(2).toString());
        ui->txt_gc_senha->setText(query.value(3).toString());
        ui->comboBox_acesso->setCurrentIndex(ui->comboBox_acesso->findData(query.value(4).toString(), Qt::DisplayRole));
    }else {
        QMessageBox::warning(this, "ERRO", "Trotos!");
    }
}

void almox_gestaoColab::on_btn_gc_excluir_clicked()
{
    if(id_colab==-1){
        QMessageBox::warning(this, "ERRO", "Erro ao apagar Colaborador, Nenhum selecionado!");
    }else{
        QSqlQuery query;
        query.prepare("delete from tb_colaboradores where id_colab="+QString::number(id_colab));
        if(!query.exec()){
            QMessageBox::warning(this, "ERRO", "Erro ao apagar Colaborador!");
        }else {
            QMessageBox::information(this,"Apagado", "Colaborador apagado com sucesso!");
            removerLinhas(ui->tw_gc_colab);
            int contLinhas = 0;
            QSqlQuery query;
            query.prepare("select id_colab,nome_colab from tb_colaboradores order by nome_colab");
            if(query.exec()){
                while(query.next()){
                    ui->tw_gc_colab->insertRow(contLinhas);
                    ui->tw_gc_colab->setItem(contLinhas, 0, new QTableWidgetItem(query.value(0).toString()));
                    ui->tw_gc_colab->setItem(contLinhas, 1, new QTableWidgetItem(query.value(1).toString()));
                    ui->tw_gc_colab->setRowHeight(contLinhas, 20);
                    contLinhas++;
                }
                ui->tw_gc_colab->setColumnWidth(0,50);
                ui->tw_gc_colab->setColumnWidth(1,230);
                QStringList cabecalhos={"ID", "Nome"};
                ui->tw_gc_colab->setHorizontalHeaderLabels(cabecalhos);
                ui->tw_gc_colab->setStyleSheet("QTableView {selection-background-color:red");
                ui->tw_gc_colab->setEditTriggers(QAbstractItemView::NoEditTriggers);
                ui->tw_gc_colab->setSelectionBehavior(QAbstractItemView::SelectRows);
                ui->tw_gc_colab->verticalHeader()->setVisible(false);

            }else{
                QMessageBox::warning(this, "ERRO", "Erro ao listar produtos!");
            }
            ui->tw_gc_colab->setColumnCount(2);
        }
    }
}

void almox_gestaoColab::on_btn_gc_gravar_clicked()
{
    if(id_colab==-1){
        QMessageBox::warning(this, "ERRO", "Erro ao Salvar Colaborador, Nenhum selecionado!");
    }else{
        QString nome = ui->txt_gc_nome->text();
        QString user= ui->txt_gc_username->text();
        QString senha = ui->txt_gc_senha->text();
        QString acesso = ui->comboBox_acesso->currentText();

        QSqlQuery query;
        query.prepare("UPDATE tb_colaboradores set nome_colab='"+nome+"',"
            " username_colab='"+user+"', senha_colab='"+senha+"' , acesso_colab='"+acesso+"' where id_colab="+QString::number(id_colab));
        if(!query.exec()){
            QMessageBox::warning(this, "ERRO", "Erro ao Alterar Colaborador!");
        }else {
            QMessageBox::information(this, "GRAVADO", "Alteração feita com Sucesso!");
        }
    }
}
