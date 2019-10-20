#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    QWidget *w = new QWidget();
    this->setCentralWidget(w);
    QMenu *file;
    file = menuBar()->addMenu("&File");
      QAction *quit = new QAction("&Quit", this);
    file->addAction(quit);
    QToolBar *t = addToolBar("main tool bar");
    QPixmap openpix("/home/mgtm/Pictures/icons/open.svg");
    QPixmap newpix("/home/mgtm/Pictures/icons/new.svg");
    QPixmap savepix("/home/mgtm/Pictures/icons/save.svg");
    QPixmap compilepix("/home/mgtm/Pictures/icons/compile.svg");
    QPixmap runpix("/home/mgtm/Pictures/icons/run.svg");
    QPixmap settingpix("/home/mgtm/Pictures/icons/setting.svg");
    t->addAction(QIcon(newpix),"New");
    t->addAction(QIcon(openpix),"Open");
    t->addAction(QIcon(savepix),"Save");
    t->addAction(QIcon(compilepix),"Compile");
    t->addAction(QIcon(runpix),"Run");
    t->addAction(QIcon(settingpix),"Settings");
    t->setStyleSheet("QToolButton {padding: 5px 5px 15px 15px;}");
    t->setMovable(false);
    QTabWidget *tabWidget;
    editor = new Editor();
    editor->zoomIn(3);
    highlight = new Highlighter(editor->document());
    tabWidget = new QTabWidget;
        tabWidget->addTab(editor, tr("Editor"));
        tabWidget->addTab(new  QWidget(), tr("Output"));
//        tabWidget->addTab(new  QWidget(), tr("Applications"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
       mainLayout->addWidget(tabWidget);
       QStatusBar *status = new QStatusBar();
       status->showMessage("Compiling c++ file ...");
       mainLayout->addWidget(status);
       w->setLayout(mainLayout);

}

MainWindow::~MainWindow(){

}

