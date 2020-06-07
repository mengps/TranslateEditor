#ifndef FILEAPI_H
#define FILEAPI_H

#include <QObject>

class FileApi : public QObject
{
    Q_OBJECT
public:
    static FileApi* instance();

    Q_INVOKABLE void setCurrent(const QString &filename);
    Q_INVOKABLE QString openFile(const QString &filename);
    Q_INVOKABLE QString baseName(const QString &filename);
    Q_INVOKABLE QString toString(const QUrl &filename);
    Q_INVOKABLE QString fileName(const QString &filename);

private:
    FileApi();
};

#endif // FILEAPI_H
