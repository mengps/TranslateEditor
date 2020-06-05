#ifndef DOCUMENTHELPER_H
#define DOCUMENTHELPER_H

#include <QObject>
#include <QTextCursor>

class QQuickTextDocument;
class DocumentHelper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)

public:
    DocumentHelper(QObject *parent = nullptr);

    /**
     * @brief 高亮指定行
     * @param line 行号
     */
    Q_INVOKABLE void highlightLine(int line);

    QQuickTextDocument *document() const;
    void setDocument(QQuickTextDocument *document);

    int cursorPosition() const;
    void setCursorPosition(int position);

    int selectionStart() const;
    void setSelectionStart(int position);

    int selectionEnd() const;
    void setSelectionEnd(int position);

    QColor highlightColor() const;
    void setHighlightColor(const QColor &color);

signals:
    void documentChanged();
    void cursorPositionChanged();
    void selectionStartChanged();
    void selectionEndChanged();
    void highlightColorChanged();

private:
    QTextCursor textCursor() const;
    QTextDocument *textDocument() const;

    QQuickTextDocument *m_document = nullptr;
    int m_cursorPosition;
    int m_selectionStart;
    int m_selectionEnd;
    QColor m_highlightColor;
};

#endif // DOCUMENTHELPER_H
