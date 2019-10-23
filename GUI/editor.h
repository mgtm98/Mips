#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QtDebug>

class LineNumberArea;

class Editor : public QPlainTextEdit{
public:
    Editor(QWidget *parent = nullptr);
    void lineNumberPaintEvent (QPaintEvent *e);
    int lineNumberWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void updateNumAreaWidth(int);
    void highlightCurrentLine();
    void updateNumArea(const QRect &, int);

private:
    LineNumberArea *numArea;
};

class LineNumberArea : public QWidget{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberPaintEvent(event);
    }

private:
    Editor *codeEditor;
};


#endif // EDITOR_H
