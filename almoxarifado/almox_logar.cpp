#include "almox_logar.h"
#include "ui_almox_logar.h"
#include <QMessageBox>
#include "mainwindow.h"

almox_logar::almox_logar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almox_logar)
{
    ui->setupUi(this);
    logado=false;

}

almox_logar::~almox_logar()
{
    delete ui;
}

void almox_logar::on_btn_logar_clicked()
{
    if(!con.abrir())
        QMessageBox::warning(this, "ERRO", "Erro ao abrir Banco de Dados!");
    else {
        QString username, senha;
        username = ui->txt_username->text();
        senha = ui->txt_psswd->text();
        QSqlQuery query;
        query.prepare("select * from tb_colaboradores where username_colab='"+username+"' and senha_colab='"+senha+"'");
        if(query.exec()){
            query.first();
            if(query.value(1).toString()!=""){
                MainWindow::logado= true;
                MainWindow::nome_colab = query.value(1).toString();
                MainWindow::id_colab = query.value(0).toInt();
                MainWindow::acesso_colab = query.value(4).toString();
                con.fechar();
                close();
            }
            else {
                QMessageBox::warning(this, "ERRO", "Senha/Usuário incorreto!");
            }
        }
        else {
            QMessageBox::warning(this, "ERRO", "Falha no Login!");
        }
    }
    con.fechar();
}

void almox_logar::on_btn_cancelar_clicked()
{
    logado=false;
    close();
}


