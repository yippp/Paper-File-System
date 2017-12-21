#ifndef LISTITEM_H
#define LISTITEM_H
#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class customItem1;
}

class customItem1 : public QWidget
{
    Q_OBJECT
public:
    explicit customItem1(QWidget *parent, const QString& text1, const QString& text2);

signals:

public slots:

private:
    QLabel text1;
    QLabel text2;
};
#endif // LISTITEM_H
