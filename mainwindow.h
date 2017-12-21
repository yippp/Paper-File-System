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
    vector<paper>*paperlist = process_all();
    ~MainWindow();

public slots:
    void updateTextString();

    void on_titelText_windowTitleChanged(const QString &title);

    void on_importButton_clicked();

private slots:
    void on_importButton_destroyed(QObject *arg1);



    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    bool plainText;

};



#endif // MAINWINDOW_H
