#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "vector"
#include "QString"
#include "listitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::updateTextString(){
    std::vector<std::string> a;
    a.push_back("hello,world");
    QString Qa = QString::fromStdString(a[0]);
    QListWidgetItem *listItem1 = new QListWidgetItem();
    listItem1->setText("hello");
    ui->listWidget->addItem(listItem1);
}



void MainWindow::on_titelText_windowTitleChanged(const QString &title)
{

}

void MainWindow::on_importButton_clicked()
{
    updateTextString();
}

void MainWindow::on_importButton_destroyed(QObject *arg1)
{

}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString Title = "title";
    ui->titleText->setPlainText(Title);
}
