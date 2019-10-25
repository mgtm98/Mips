#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    mainWidget = new QWidget();
    tabWidget = new QTabWidget();
    mainLayout = new QVBoxLayout();
    status = new QStatusBar();
    QDesktopWidget dw;
    mainWidget->setLayout(mainLayout);
    mainWidget->setFixedSize(dw.width()*0.8,dw.height()*0.8);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(status);
    this->setCentralWidget(mainWidget);

    initMenus();
    initToolBar();
    assemblyFilePath = "";
    assemblyFile = new QFile();

    editor = new Editor();
    editor->zoomIn(3);
    highlight = new Highlighter(editor->document());
    tabWidget->addTab(editor, tr("Editor"));
}

void MainWindow::initToolBar(){
    toolBar = addToolBar("main tool bar");
    QPixmap openpix("/home/mgtm/Pictures/icons/open.svg");
    QPixmap newpix("/home/mgtm/Pictures/icons/new.svg");
    QPixmap savepix("/home/mgtm/Pictures/icons/save.svg");
    QPixmap compilepix("/home/mgtm/Pictures/icons/compile.svg");
    QPixmap runpix("/home/mgtm/Pictures/icons/run.svg");
    QPixmap settingpix("/home/mgtm/Pictures/icons/setting.svg");
    newAction = toolBar->addAction(QIcon(newpix),"New");
    openAction = toolBar->addAction(QIcon(openpix),"Open");
    saveAction = toolBar->addAction(QIcon(savepix),"Save");
    compileAction = toolBar->addAction(QIcon(compilepix),"Compile");
    runAction = toolBar->addAction(QIcon(runpix),"Run");
    settingsAction = toolBar->addAction(QIcon(settingpix),"Settings");
    toolBar->setStyleSheet("QToolButton {padding: 5px 5px 15px 15px;}");
    toolBar->setMovable(false);

    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(compileAction,SIGNAL(triggered()),this,SLOT(compileFile()));
}

void MainWindow::initMenus(){
    file = menuBar()->addMenu("&File");
    quit = new QAction("&Quit",file);
    file->addAction(quit);
}

void MainWindow::openFile(){
    if(assemblyFile->isOpen()){
        saveFile();
        assemblyFile->close();
        delete  assemblyFile;
    }
    assemblyFilePath = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/", tr("Assembly Files (*.asm)"));
    if(!assemblyFilePath.isEmpty()){
        std::string name = assemblyFilePath.toStdString();
        size_t index1 = name.find_last_of('/');
        size_t index2 = name.find_last_of(".asm");
        assemblyFileName =  QString::fromStdString(name.substr(index1+1,index2-index1-4));
        assemblyFile = new QFile(assemblyFilePath,this);
        assemblyFile->open(QIODevice::Text | QIODevice::ReadWrite);
        QString content;
        while(!assemblyFile->atEnd())content.append(assemblyFile->readLine());
        editor->setPlainText(content);
    }
}

void MainWindow::newFile(){
    if(assemblyFile->isOpen()){
        saveFile();
        assemblyFile->close();
        delete  assemblyFile;
    }
    bool ok;
    QString newFileName = QInputDialog::getText(this, tr("Create new File"),tr("File name :"), QLineEdit::Normal,"newAsemblyFile", &ok);
    if (ok && !newFileName.isEmpty()){
        assemblyFileName = newFileName;
        newFileName += ".asm";
        qDebug() << newFileName;
        QString newFilePath = QFileDialog::getExistingDirectory(this,tr("Save File Location"), "/home/",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
        if(!newFilePath.isEmpty()){
            assemblyFilePath = newFilePath+"/"+newFileName;
            assemblyFile = new QFile(assemblyFilePath,this);
            assemblyFile->open(QIODevice::Text | QIODevice::ReadWrite);
            editor->setPlainText("");
        }
    }
}

void MainWindow::saveFile(){
    assemblyFile->resize(0);
    assemblyFile->write(editor->toPlainText().toUtf8());
    assemblyFile->close();
    assemblyFile->open(QIODevice::Text | QIODevice::ReadWrite);
}

void MainWindow::compileFile(){
    qDebug() << " here";
    assemblerProcess = new QProcess();
    assemblerProcess->setProcessChannelMode(QProcess::MergedChannels);
    assemblerProcess->start("./../assembler_python/assembler.py "+assemblyFilePath+" ../biteCode/"+assemblyFileName+".txt");
    assemblerProcess->waitForFinished(-1);
    qDebug() << assemblerProcess->readAll();
}

MainWindow::~MainWindow(){

}

