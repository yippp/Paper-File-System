#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "vector"
#include "QString"
#include "export.h"
#include "processall.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "QDialog"
#include <QLineEdit>
#include "QMessageBox"


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
    connect(ui->authorText, SIGNAL(textChanged()), SLOT(writeBackAuthors()));
    connect(ui->exportButton,SIGNAL(clicked()), SLOT(setText()));

    //Creation and layout of the findDialog Window.
    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("Find"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *findNextBtn = new QPushButton(tr("Find Next"), findDlg);
    QVBoxLayout *findLayout = new QVBoxLayout(findDlg);
    findLayout->addWidget(findLineEdit);
    findLayout->addWidget(findNextBtn);
    connect(findNextBtn, &QPushButton::clicked, this, &MainWindow::showFindText);



    setWindowTitle(tr("Page File System"));

    // create the pdf folder
    int cratePath = mkdir("../../../pdf/", S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    if (cratePath) {
        perror("create pdf folder failed");
    }
    // create the temp folder
    cratePath = mkdir("../../../temp/", S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    if (cratePath) {
        perror("create temp folder failed");
    }


    papersList = new vector<paper>;
    txtList = readFromFile(papersList);
    for(int i=0; i < (int)papersList->size(); i++){
        QString paperName = QString::fromStdString(papersList->at(i).title);
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(paperName);
        ui->listWidget->addItem(listItem);
    }

}


MainWindow::~MainWindow()
{
    saveToFile(papersList, txtList);
    delete ui;
}


void MainWindow::setText(){
    QString Success = "SUCCESS!";
    ui->feedbackLabel->setText(Success);
//    QTime dieTime = QTime::currentTime().addMSecs(msec);
//    while( QTime::currentTime() < dieTime )
//    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    ui->feedbackLabel->setText("");

}

void MainWindow::writeBackTitle(){
    if (isSelect) {
        QString changedText = ui->titleText->toPlainText();
        papersList->at(globali).title = changedText.toStdString();
        globalItem->setText(changedText);
        //saveToFile(papersList, txtList);
    }
}

void MainWindow::writeBackJournel(){
    if (isSelect) {
        QString changedText = ui->journelText->toPlainText();
        papersList->at(globali).conference = changedText.toStdString();
    }
}

void MainWindow::writeBackAuthors(){
    if (isSelect) {
        QString changedText = ui->authorText->toPlainText();
        papersList->at(globali).authors = changedText.toStdString();
    }
}

void MainWindow::writeBackDate(){
    if (isSelect) {
        QString changedText = ui->dateText->toPlainText();
        papersList->at(globali).year = changedText.toInt();
    }
}

void MainWindow::writeBackAbstract(){
    if (isSelect) {
        QString changedText = ui->abstractText->toPlainText();
        papersList->at(globali).abstract = changedText.toStdString();
    }
}


void MainWindow::writeBackTag(){
    if (isSelect) {
        QString changedText = ui->tagText->toPlainText();
        papersList->at(globali).tag = changedText.toStdString();
    }
}


void MainWindow::itemClick(QListWidgetItem* item){
    isSelect = false;
    int i = 0;
    QString Name = item->text();
    for (int j = 0; j < (int)papersList->size();j++){
        if(papersList->at(j).title == Name.toStdString()){
            i = j;
            break;
        }
    }
    globali = i;
    globalItem = item;
    QString Title = QString::fromStdString(papersList->at(i).title);
    ui->titleText->setPlainText(Title);
    QString Author = QString::fromStdString(papersList->at(i).authors);
    ui->authorText->setPlainText(Author);
    QString Journel = QString::fromStdString(papersList->at(i).conference);
    ui->journelText->setPlainText(Journel);
    if (papersList->at(i).year > 0) {
        QString Date = QString::number(papersList->at(i).year, 10);
        ui->dateText->setPlainText(Date);
    } else {
        //prevent illegal string.
        QString Date = QString::fromStdString("");
        ui->dateText->setPlainText(Date);
    }
    QString Tag = QString::fromStdString(papersList->at(i).tag);
    ui->tagText->setPlainText(Tag);
    QString Abstract = QString::fromStdString(papersList->at(i).abstract);
    ui->abstractText->setPlainText(Abstract);
    isSelect = true;
}


void MainWindow::updateTextString(){

    vector<string> newTxtList;
    papersList = process_all(papersList, txtList, newTxtList);
    txtList = newTxtList;

    for(int i=0; i < (int)papersList->size(); i++){
        QString paperName = QString::fromStdString(papersList->at(i).title);
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


void MainWindow::on_exportButton_clicked()
{
    exportBibTeX(papersList);
}

void MainWindow::on_findButton_clicked()
{
    findDlg->show();
}

void MainWindow::showFindText(){
    QString str = findLineEdit->text();
    QList<QListWidgetItem *> matchedStr = ui->listWidget->findItems(str,Qt::MatchContains);
//    if (!ui->listWidget->findItems(str,Qt::MatchContains))
//    {
//        QMessageBox::warning(this, tr("Find"),
//                             tr("Not Found %1").arg(str));
//    }
}
