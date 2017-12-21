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
    connect(ui->titleText, SIGNAL(textChanged()), SLOT(writeBackTitle()));
    connect(ui->journelText, SIGNAL(textChanged()), SLOT(writeBackJournel()));
    connect(ui->dateText, SIGNAL(textChanged()), SLOT(writeBackDate()));
    connect(ui->abstractText, SIGNAL(textChanged()), SLOT(writeBackAbstract()));
    connect(ui->tagText, SIGNAL(textChanged()), SLOT(writeBackTag()));
}


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::writeBackTitle(){
    if (isSelect) {
        QString changedText = ui->titleText->toPlainText();
        paperlist->at(globali).title = changedText.toStdString();
        globalItem->setText(changedText);
    }
}

void MainWindow::writeBackJournel(){
    if (isSelect) {
        QString changedText = ui->journelText->toPlainText();
        paperlist->at(globali).conference = changedText.toStdString();
    }
}

void MainWindow::writeBackDate(){
    if (isSelect) {
        QString changedText = ui->dateText->toPlainText();
        paperlist->at(globali).year = changedText.toInt();
    }
}

void MainWindow::writeBackAbstract(){
    if (isSelect) {
        QString changedText = ui->abstractText->toPlainText();
        paperlist->at(globali).abstract = changedText.toStdString();
    }
}


void MainWindow::writeBackTag(){
    if (isSelect) {
        QString changedText = ui->tagText->toPlainText();
        paperlist->at(globali).tag = changedText.toStdString();
    }
}


void MainWindow::itemClick(QListWidgetItem* item){
    isSelect = false;
    int i = 0;
    QString Name = item->text();
    for (int j = 0; j< paperlist->size();j++){
        if(paperlist->at(j).title == Name.toStdString()){
            i = j;
            break;
        }
    }
    globali = i;
    globalItem = item;
    QString Title = QString::fromStdString(paperlist->at(i).title);
    ui->titleText->setPlainText(Title);
//    QString Author = QString::fromStdString(paperlist->at(0).authors);
//    ui->authorText->setPlainText(Author);
    QString Journel = QString::fromStdString(paperlist->at(i).conference);
    ui->journelText->setPlainText(Journel);
    QString Date = QString::number(paperlist->at(i).year, 10);
    ui->dateText->setPlainText(Date);
    QString Tag = QString::fromStdString(paperlist->at(i).tag);
    ui->tagText->setPlainText(Tag);
    QString Abstract = QString::fromStdString(paperlist->at(i).abstract);
    ui->abstractText->setPlainText(Abstract);
    isSelect = true;
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



void MainWindow::on_importButton_clicked()
{
    ui->listWidget->clear();
    updateTextString();
}



