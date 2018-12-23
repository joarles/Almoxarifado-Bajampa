#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "almox_logar.h"
#include "almox_novoitem.h"
#include "almox_gestaocolab.h"
#include "almox_gestaoestoque.h"

int MainWindow::id_colab;
QString MainWindow::nome_colab;
QString MainWindow::acesso_colab;
QString MainWindow::username_colab;
bool MainWindow::logado;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logado = false;     //Estado do login
    cadFechado.addFile(":/imagens/imgs/cadeado_fechado.png");   //Atribui as imagens dos cadeados
    cadAberto.addFile(":/imagens/imgs/cadeado_aberto.png");

    ui->btn_bloquear->setText("");
    ui->btn_bloquear->setIcon(cadFechado);
    ui->statusBar->addWidget(ui->btn_bloquear);     //Adciona o botão de bloquear na barra de status
    ui->statusBar->addWidget(ui->lb_nome);     //Adciona o botão de bloquear na barra de status
    ui->statusBar->addWidget(ui->lb_acesso);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_bloquear_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    if(logado){
        almox_novoItem a_novoItem;
        a_novoItem.exec();
    }else {
        QMessageBox::information(this, "Login", "Usuário não Logado!");
    }
}

void MainWindow::on_actionEstoque_triggered()
{
    if(logado){
        if(acesso_colab=="A" || acesso_colab == "B"){
            almox_gestaoEstoque a_gestaoEstoque;
            a_gestaoEstoque.exec();
        }else {
            QMessageBox::information(this, "Acesso", "Acesso não Permitido!");
        }
    }else {
        QMessageBox::information(this, "Login", "Usuário não Logado!");
    }
}


void MainWindow::on_actionColaboradores_triggered()
{
    if(logado){
        if(acesso_colab=="A"){
            almox_gestaoColab a_gestaoColab;
            a_gestaoColab.exec();
        }else {
            QMessageBox::information(this, "Acesso", "Acesso não Permitido!");
        }
    }else {
        QMessageBox::information(this, "Login", "Usuário não Logado!");
    }
}



void MainWindow::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox::information(this, "SOBRE", "Almoxarifado BAJAMPA \nFeito por Joarles Macêdo\n24/12/2018.");
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!logado){
        almox_logar a_logar;
        a_logar.exec();

        if(logado){
            ui->pushButton_2->setText("Logout");
            ui->btn_bloquear->setIcon(cadAberto);
            ui->lb_nome->setText(nome_colab);
            ui->lb_acesso->setText("Acesso: "+acesso_colab);
        }
    }else {
        logado = false;
        ui->pushButton_2->setText("Login");
        ui->btn_bloquear->setIcon(cadFechado);
        ui->lb_nome->setText("Sem Colaborador");
        ui->lb_acesso->setText("");
    }
}
