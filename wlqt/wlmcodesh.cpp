#include "wlmcodesh.h"

WLMCodeSH::WLMCodeSH(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
	 HighlightingRule rule;
	
	 keywordFormat.setForeground(Qt::darkGreen);
     keywordFormat.setFontWeight(QFont::Bold);

     QStringList keywordPatterns;
     keywordPatterns << "\\bDIALOG\\b" << "\\bAXIS\\b" << "\\bTIMER\\b"
                     << "\\bDIN\\b" << "\\bDOUT\\b" << "\\bK\\b"
                     << "\\bFILE\\b" << "\\bMACHINE\\b" ;
                     /*<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                     << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                     << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                     << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                     << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                     << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                     << "\\bvoid\\b" << "\\bvolatile\\b";*/
     foreach (const QString &pattern, keywordPatterns) {
         rule.pattern = QRegExp(pattern);
         rule.format = keywordFormat;
         highlightingRules.append(rule);
     }
	 
	 
     classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("function.+[)]");
     rule.format = classFormat;
     highlightingRules.append(rule);

	 classFormat.setFontWeight(QFont::Bold);
     classFormat.setForeground(Qt::magenta);
	 rule.pattern = QRegExp("return");
     rule.format = classFormat;
     highlightingRules.append(rule);
	 /*
	 classFormat.setFontWeight(QFont::Bold);
	 classFormat.setForeground(Qt::darkGreen);
	 //G[\s]*[-]?[\d]+([.]([\d]+)?)?
	 rule.pattern = QRegExp("[X,Y,Z][\\s]*[-]?[\\d]+([.]([\\d]+)?)?");
     rule.format = classFormat;
     highlightingRules.append(rule);

	 classFormat.setFontWeight(QFont::Bold);
	 classFormat.setForeground(Qt::darkYellow);
	 //G[\s]*[-]?[\d]+([.]([\d]+)?)?
	 rule.pattern = QRegExp("[I,J,K][\\s]*[-]?[\\d]+([.]([\\d]+)?)?");
     rule.format = classFormat;
     highlightingRules.append(rule);

	 classFormat.setFontWeight(QFont::Bold);
	 classFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("M[\\s]*[\\d]+");
     rule.format = classFormat;
     highlightingRules.append(rule);
	 
	 classFormat.setFontWeight(QFont::Bold);
	 classFormat.setForeground(Qt::darkYellow);
     rule.pattern = QRegExp("T[\\s]*[\\d]+");
     rule.format = classFormat;
     highlightingRules.append(rule);

	 classFormat.setFontWeight(QFont::Bold);
	 classFormat.setForeground(Qt::red);	 
     rule.pattern = QRegExp("[S,F][\\s]*[\\d]+");
     rule.format = classFormat;
     highlightingRules.append(rule);
	 */

	 singleLineCommentFormat.setForeground(Qt::gray);
     rule.pattern = QRegExp("//[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);

   

		 /*
	 quotationFormat.setFontWeight(QFont::Bold);
     quotationFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("\".*\"");
     rule.format = quotationFormat;
     highlightingRules.append(rule);
	 */
	 /*
     functionFormat.setFontItalic(true);
     functionFormat.setForeground(Qt::blue);
     rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
     rule.format = functionFormat;
     highlightingRules.append(rule);
	 */
	
    commentStartExpression = QRegExp("/\\*");
     commentEndExpression = QRegExp("\\*/");
	
}

WLMCodeSH::~WLMCodeSH()
{

}

 void WLMCodeSH::highlightBlock(const QString &text)
 {
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = commentStartExpression.indexIn(text);

     while (startIndex >= 0) {
         int endIndex = commentEndExpression.indexIn(text, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, multiLineCommentFormat);
         startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
     }
 }
