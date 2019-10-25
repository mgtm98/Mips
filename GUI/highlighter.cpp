#include "highlighter.h"
#include <QDebug>
Highlighter::Highlighter(QTextDocument *parent):QSyntaxHighlighter(parent){
    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
            QStringLiteral("\\badd\\b"), QStringLiteral("\\baddi\\b"), QStringLiteral("\\bsub\\b"),
            QStringLiteral("\\bsubi\\b"), QStringLiteral("\\band\\b"), QStringLiteral("\\bandi\\b"),
            QStringLiteral("\\bor\\b"), QStringLiteral("\\bori\\b"), QStringLiteral("\\blw\\b"),
            QStringLiteral("\\bsw\\b"), QStringLiteral("\\jr\\b"), QStringLiteral("\\baddu\\b"),
            QStringLiteral("\\baddiu\\b"), QStringLiteral("\\bsll\\b"), QStringLiteral("\\bslt\\b"),
            QStringLiteral("\\bsra\\b"), QStringLiteral("\\bsrl\\b"), QStringLiteral("\\blui\\b"),
            QStringLiteral("\\bnor\\b"), QStringLiteral("\\bxor\\b"), QStringLiteral("\\bj\\b"),
            QStringLiteral("\\bjal\\b"), QStringLiteral("\\bbeq\\b"), QStringLiteral("\\bbne\\b"),
            QStringLiteral("\\blb\\b"), QStringLiteral("\\blh\\b"), QStringLiteral("\\bsb\\b"),
            QStringLiteral("\\bsh\\b"), QStringLiteral("\\bnop\\b"),
        };
    HighlightingRule rule;
    for (const QString &pattern : keywordPatterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
    }

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("#[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    assemblyLabelFormat.setForeground(Qt::darkRed);
    assemblyLabelFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("\\w+:"));
    rule.format = assemblyLabelFormat;
    highlightingRules.append(rule);

    numbersFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegularExpression(QStringLiteral("\\d*$"));
    rule.format = numbersFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text){
    for(const HighlightingRule &rule : qAsConst(highlightingRules)){
        QRegularExpressionMatchIterator iterator = rule.pattern.globalMatch(text);
        while(iterator.hasNext()){
            QRegularExpressionMatch match = iterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
