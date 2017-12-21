#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "vector"
#include "QString"
#include "processall.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemClick(QListWidgetItem*)));

}


MainWindow::~MainWindow()
{

    delete ui;
}
void MainWindow::itemClick(QListWidgetItem* item){
    int i = 0;
    QString Name = item->text();
    for (int j = 0; j< paperlist->size();j++){
        if(paperlist->at(j).title == Name.toStdString()){
            i = j;
        }
    }
    QString Title = QString::fromStdString(paperlist->at(i).title);
    ui->titleText->setPlainText(Title);
//    QString Author = QString::fromStdString(paperlist->at(0).authors);
//    ui->authorText->setPlainText(Author);
    QString Journel = QString::fromStdString(paperlist->at(i).conference);
    ui->journelText->setPlainText(Journel);
    QString Date = QString::number(paperlist->at(i).year, 10);
    ui->dateText->setPlainText(Date);
    QString Abstract = QString::fromStdString(paperlist->at(i).abstract);
    ui->abstractText->setPlainText(Abstract);
}


void MainWindow::updateTextString(){
//    std::vector<std::string> a;
//    a.push_back("hello,world");
    paperlist = process_all();
    for(int i=0; i< paperlist->size(); i++){
    QString paperName = QString::fromStdString(paperlist->at(i).title);
    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setText(paperName);
    ui->listWidget->addItem(listItem);
    }
}



void MainWindow::on_titelText_windowTitleChanged(const QString &title)
{

}


void MainWindow::on_importButton_clicked()
{
    ui->listWidget->clear();
    updateTextString();
}



void MainWindow::on_importButton_destroyed(QObject *arg1)
{

}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *LISTITEM_H)
{
//    QString Title = QString::fromStdString(paperlist->at(0).title);
//    ui->titleText->setPlainText(Title);
////    QString Author = QString::fromStdString(paperlist->at(0).authors);
////    ui->authorText->setPlainText(Author);
//    QString Journel = QString::fromStdString(paperlist->at(0).conference);
//    ui->journelText->setPlainText(Journel);
//    QString Date = QString::number(paperlist->at(0).year, 10);
//    ui->dateText->setPlainText(Date);
//    QString Abstract = QString::fromStdString(paperlist->at(0).abstract);
//    ui->abstractText->setPlainText(Abstract);
}

