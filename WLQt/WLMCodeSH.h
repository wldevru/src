#ifndef WLMCODEH_H
#define WLMCODEH_H

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class WLMCodeSH : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	WLMCodeSH(QTextDocument *parent = 0);
	~WLMCodeSH();

protected:
     void highlightBlock(const QString &text);

private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> highlightingRules;

     QRegExp commentStartExpression;
     QRegExp commentEndExpression;

     QTextCharFormat keywordFormat;
     QTextCharFormat classFormat;
     QTextCharFormat singleLineCommentFormat;
     QTextCharFormat multiLineCommentFormat;
     QTextCharFormat quotationFormat;
     QTextCharFormat functionFormat;
	
};

#endif // WLMCODEH_H
