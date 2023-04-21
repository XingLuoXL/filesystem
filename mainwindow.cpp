#include "api.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
  QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){
        bool ok;
        QString tagname = QInputDialog::getText(this, tr("请输入标签名"),tr("标签名"),QLineEdit::Normal,"",&ok);
        if(ok&&!tagname.isEmpty()){
            string newfile_path=fileName.toStdString();
            std::filesystem::path newfile(newfile_path);
            string newfile_name=newfile.filename().string();
            File *file = fileinvec(newfile_name,newfile_path);
//            file.name=newfile_name;
//            file.address=newfile_path;



            string newtag = tagname.toStdString();
            Tag *tag=taginvec(newtag,"");


            fileaddtag(file,tag);
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit->clear();
    std::vector<string> taglist = showalltag();
    std::cout<<taglist.size()<<std::endl;
    for(auto &i : taglist){
        ui->plainTextEdit->appendPlainText(QString::fromStdString(i));
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){


        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file ;
        file.name =  newfile_name;
        file.address = newfile_path;
        std::vector<Tag*> taglist;
        taglist = fileshowtag(file);
        ui->plainTextEdit->clear();
        for(auto &it : taglist){
            ui->plainTextEdit->appendPlainText(QString::fromStdString(it->name));
        }
    }
}

