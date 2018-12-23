#ifndef ALMOX_NOVOITEM_H
#define ALMOX_NOVOITEM_H

#include <QDialog>
#include <QtSql>



namespace Ui {
class almox_novoItem;
}

class almox_novoItem : public QDialog
{
    Q_OBJECT

public:
    explicit almox_novoItem(QWidget *parent = nullptr);
    ~almox_novoItem();

private:
    Ui::almox_novoItem *ui;
    QSqlTableModel *model;
};

#endif // ALMOX_NOVOITEM_H
