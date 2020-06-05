#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QQuickWindow>

class FramelessWindow : public QQuickWindow
{
    Q_OBJECT

    Q_PROPERTY(bool movable READ movable WRITE setMovable NOTIFY movableChanged)
    Q_PROPERTY(bool resizable READ resizable WRITE setResizable NOTIFY resizableChanged)
    Q_PROPERTY(QString windowIcon READ windowIcon WRITE setWindowIcon NOTIFY windowIconChanged)

    enum MouseArea {
        TopLeft = 1,
        Top,
        TopRight,
        Left,
        Move,
        Right,
        BottomLeft,
        Bottom,
        BottomRight,
        Client
    };

public:
    explicit FramelessWindow(QWindow *parent = nullptr);

    bool movable() const;
    void setMovable(bool arg);

    bool resizable() const;
    void setResizable(bool arg);

    QString windowIcon() const;
    void setWindowIcon(const QString &icon);

protected:
    bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void entered();
    void exited();
    void movableChanged();
    void resizableChanged();
    void windowIconChanged();

private:
    MouseArea getArea(const QPoint &pos);
    void setWindowGeometry(const QPoint &pos);
    void setCursorIcon();

    bool m_movable = true;
    bool m_resizable = true;
    MouseArea m_currentArea = Move;
    QPoint m_startPos;
    QPoint m_oldPos;
    QSize m_oldSize;
    QString m_windowIcon;
};

#endif
