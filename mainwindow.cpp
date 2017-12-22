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

    paperslist = new vector<paper>;
    txtList = readFromFile(paperslist);
    for(int i=0; i < (int)paperslist->size(); i++){
        QString paperName = QString::fromStdString(paperslist->at(i).title);
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(paperName);
        ui->listWidget->addItem(listItem);
    }
}


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::writeBackTitle(){
    if (isSelect) {
        QString changedText = ui->titleText->toPlainText();
        paperslist->at(globali).title = changedText.toStdString();
        globalItem->setText(changedText);
    }
}

void MainWindow::writeBackJournel(){
    if (isSelect) {
        QString changedText = ui->journelText->toPlainText();
        paperslist->at(globali).conference = changedText.toStdString();
    }
}

void MainWindow::writeBackDate(){
    if (isSelect) {
        QString changedText = ui->dateText->toPlainText();
        paperslist->at(globali).year = changedText.toInt();
    }
}

void MainWindow::writeBackAbstract(){
    if (isSelect) {
        QString changedText = ui->abstractText->toPlainText();
        paperslist->at(globali).abstract = changedText.toStdString();
    }
}


void MainWindow::writeBackTag(){
    if (isSelect) {
        QString changedText = ui->tagText->toPlainText();
        paperslist->at(globali).tag = changedText.toStdString();
    }
}


void MainWindow::itemClick(QListWidgetItem* item){
    isSelect = false;
    int i = 0;
    QString Name = item->text();
    for (int j = 0; j < (int)paperslist->size();j++){
        if(paperslist->at(j).title == Name.toStdString()){
            i = j;
            break;
        }
    }
    globali = i;
    globalItem = item;
    QString Title = QString::fromStdString(paperslist->at(i).title);
    ui->titleText->setPlainText(Title);
//    QString Author = QString::fromStdString(paperlist->at(0).authors);
//    ui->authorText->setPlainText(Author);
    QString Journel = QString::fromStdString(paperslist->at(i).conference);
    ui->journelText->setPlainText(Journel);
    QString Date = QString::number(paperslist->at(i).year, 10);
    ui->dateText->setPlainText(Date);
    QString Tag = QString::fromStdString(paperslist->at(i).tag);
    ui->tagText->setPlainText(Tag);
    QString Abstract = QString::fromStdString(paperslist->at(i).abstract);
    ui->abstractText->setPlainText(Abstract);
    isSelect = true;
}


void MainWindow::updateTextString(){

    vector<string> newTxtList;
    paperslist = process_all(paperslist, txtList, newTxtList);
    txtList = newTxtList;

    for(int i=0; i < (int)paperslist->size(); i++){
        QString paperName = QString::fromStdString(paperslist->at(i).title);
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



