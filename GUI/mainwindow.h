#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QProcess>
#include <string>
#include <iostream>
#include "editor.h"
#include "highlighter.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void newFile();
    void saveFile();
    void compileFile();

private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QMenu *file;
    QAction *quit;
    QToolBar *toolBar ;
    QTabWidget *tabWidget;
    QStatusBar *status;
    Editor *editor;
    Highlighter *highlight;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *compileAction;
    QAction *runAction;
    QAction *settingsAction;
    QString assemblyFilePath;
    QString assemblyFileName;
    QFile *assemblyFile;
    QProcess *assemblerProcess;
    void initToolBar();
    void initMenus();
};
#endif // MAINWINDOW_H
