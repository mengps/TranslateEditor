#include "fileapi.h"

#include <QDir>
#include <QDebug>
#include <QFile>
#include <QQmlFile>

FileApi::FileApi()
{

}

FileApi *FileApi::instance()
{
    static FileApi api;
    return &api;
}

void FileApi::setCurrent(const QString &filename)
{
    QDir::setCurrent(QFileInfo(filename).path());
}

QString FileApi::openFile(const QString &filename)
{
    if (filename.isEmpty()) return QString();

    QFile file(filename);
    QString data;
    if (file.open(QIODevice::ReadOnly)) {
        data = file.readAll();
    }
    file.close();

    return data;
}

QString FileApi::baseName(const QString &filename)
{
    return QFileInfo(filename).baseName();
}

QString FileApi::toString(const QUrl &filename)
{
    return QQmlFile::urlToLocalFileOrQrc(filename);
}

QString FileApi::fileName(const QString &filename)
{
    return QFileInfo(filename).fileName();
}
