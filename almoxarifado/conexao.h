#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>

class Conexao{
public:
    QSqlDatabase bancoDeDados;
    QString local;
    QString banco;
    Conexao(){
        local = qApp->applicationDirPath();     //Local da pasta que contem o bando de dados
        banco = local+"/db/controlAlmox.db";       //Endereço completo do banco de dados
        bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    }
    void fechar(){
        bancoDeDados.close();
    }
    bool abrir(){
        bancoDeDados.setDatabaseName(banco);            //Define o nome do banco de dados
        if(!bancoDeDados.open())
            return false;
        else
            return true;
    }

    bool aberto(){
        if(bancoDeDados.isOpen())
            return true;
        else
            return false;
    }
};

#endif // CONEXAO_H
