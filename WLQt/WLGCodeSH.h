#ifndef WLGCODESH_H
#define WLGCODESH_H

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class WLGCodeSH : public QSyntaxHighlighter
{
	Q_OBJECT

public:
    WLGCodeSH(QTextDocument *parent = nullptr);
	~WLGCodeSH();

    void setLock(bool _lock=true) {lock=_lock;}

protected:
     void highlightBlock(const QString &text);

private:
	 bool lock;

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

#endif // WLGCODESH_H
