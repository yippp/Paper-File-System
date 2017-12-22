#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paper.h"
#include "ui_mainwindow.h"
#include "processall.h"

#include <QMainWindow>
#include <vector>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    vector<paper>*papersList;
    ~MainWindow();
    bool saveAs();
    bool saveFile(const QString &filename);

public slots:
    void updateTextString();
    void itemClick(QListWidgetItem*);
    void writeBackTitle();
    void writeBackJournel();
    void writeBackDate();
    void writeBackAbstract();
    void writeBackTag();
    void writeBackAuthors();
    void on_importButton_clicked();
    void on_exportButton_clicked();
    void findText();
    void showFindText();

private slots:

    void on_findButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isSelect;
    int globali;

    vector<string> txtList;
    QListWidgetItem* globalItem;
    QDialog *findDlg;
    QLineEdit *findLineEdit;
    QList<QListWidgetItem *> matchedStr;
    int matchedCount;

friend void saveToFile(vector<paper>* papersList, vector<string> txtList);
};

#endif // MAINWINDOW_H
