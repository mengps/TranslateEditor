#include "documenthelper.h"

#include <QDebug>
#include <QTextBlock>
#include <QQuickTextDocument>

DocumentHelper::DocumentHelper(QObject *parent)
    : QObject (parent)
{

}

void DocumentHelper::highlightLine(int line)
{
    QTextDocument *doc = textDocument();
    QTextBlock block = doc->findBlockByNumber(line - 1);

    if (block.isValid()) {
        QTextCursor cursor = textCursor();
        QTextCharFormat format;
        format.setBackground(highlightColor());
        int position = block.position();
        /**
         *  跳过行首空白
         *  @note 但是不好看-.-
         *        最终选择高亮整行
         */
        /*while (doc->characterAt(position).isSpace()) {
            position++;
        }
        cursor.setPosition(position);
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);*/
        cursor.setPosition(position);
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
        cursor.mergeCharFormat(format);
    }
}

QQuickTextDocument* DocumentHelper::document() const
{
    return m_document;
}

void DocumentHelper::setDocument(QQuickTextDocument *document)
{

    if (document == m_document)
        return;

    m_document = document;
    emit documentChanged();
}

int DocumentHelper::cursorPosition() const
{
    return m_cursorPosition;
}

void DocumentHelper::setCursorPosition(int position)
{
    if (position == m_cursorPosition)
        return;

    m_cursorPosition = position;
    emit cursorPositionChanged();
}

int DocumentHelper::selectionStart() const
{
    return m_selectionStart;
}

void DocumentHelper::setSelectionStart(int position)
{
    if (position == m_selectionStart)
        return;

    m_selectionStart = position;
    emit selectionStartChanged();
}

int DocumentHelper::selectionEnd() const
{
    return m_selectionEnd;
}

void DocumentHelper::setSelectionEnd(int position)
{
    if (position == m_selectionEnd)
        return;

    m_selectionEnd = position;
    emit selectionEndChanged();
}

QColor DocumentHelper::highlightColor() const
{
    return m_highlightColor;
}

void DocumentHelper::setHighlightColor(const QColor &color)
{
    if (color != m_highlightColor) {
        m_highlightColor = color;
        emit highlightColorChanged();
    }
}

QTextCursor DocumentHelper::textCursor() const
{
    QTextDocument *doc = textDocument();
    if (!doc)
        return QTextCursor();

    QTextCursor cursor = QTextCursor(doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }

    return cursor;
}

QTextDocument* DocumentHelper::textDocument() const
{
    if (m_document)
        return m_document->textDocument();

    return nullptr;
}
