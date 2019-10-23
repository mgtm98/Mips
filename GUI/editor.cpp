#include "editor.h"

Editor::Editor(QWidget *parent):QPlainTextEdit(parent){
    numArea = new LineNumberArea(this);
    connect(this, &Editor::blockCountChanged, this, &Editor::updateNumAreaWidth);
    connect(this, &Editor::updateRequest, this, &Editor::updateNumArea);
    connect(this, &Editor::cursorPositionChanged, this, &Editor::highlightCurrentLine);

    setViewportMargins(lineNumberWidth(),0,0,0);

}

int Editor::lineNumberWidth(){
    int digits = 1;
    int max = qMax(1, blockCount());
    while(max >= 10){
        max /= 10;
        digits ++;
    }
    int space = 3 + digits * fontMetrics().horizontalAdvance("9");
    return space;
}

void Editor::updateNumAreaWidth(int number){
    setViewportMargins(lineNumberWidth(),0,0,0);
}

void Editor::updateNumArea(const QRect &rect, int dy){
    if (dy)
        numArea->scroll(0, dy);
    else
        numArea->update(0, rect.y(), numArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateNumAreaWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e){
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    numArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberWidth(), cr.height()));
}

void Editor::lineNumberPaintEvent(QPaintEvent *event){
    QPainter painter(numArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, numArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void Editor::highlightCurrentLine(){
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}
