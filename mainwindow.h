#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "processall.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    vector<paper>*paperlist;
    ~MainWindow();

public slots:
    void updateTextString();
    void itemClick(QListWidgetItem*);
    void writeBackTitle();
    void writeBackJournel();
    void writeBackDate();
    void writeBackAbstract();
    void writeBackTag();
    void on_importButton_clicked();


private slots:


private:
    Ui::MainWindow *ui;
    bool isSelect;
    int globali;
    QListWidgetItem* globalItem;
};

#endif // MAINWINDOW_H
