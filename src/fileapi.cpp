#include "fileapi.h"

#include <QDir>
#include <QDebug>
#include <QFile>

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
    qDebug() << QFileInfo(filename).path();
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
