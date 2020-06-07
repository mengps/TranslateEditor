#include "tsapi.h"

#include <QDebug>
#include <QFile>
#include <QQmlFile>
#include <QProcess>

TsApi::TsApi()
{

}

TsApi* TsApi::instance()
{
    static TsApi tsApi;
    return &tsApi;
}

void TsApi::createQmFile(const QString &tsName, const QString &qmName)
{
    /**
     * @brief 如果设置了Qt-lrelease.exe的位置，则使用location
     *        否则依靠系统环境变量
     */
    QString ts = QQmlFile::urlToLocalFileOrQrc(tsName);
    QString qm = QQmlFile::urlToLocalFileOrQrc(qmName);

    QString cmdLine = "lrelease.exe " + ts + " -qm " + qm;

    if (!QFile::exists(ts)) {
        qDebug() << "not exists" << ts;
        return;
    }

    if (!m_location.isEmpty()) {
        cmdLine = location() + "/" + cmdLine;
    }

    QProcess::startDetached(cmdLine);
}

QString TsApi::location() const
{
    return m_location;
}

void TsApi::setLocation(const QString &loc)
{
    if (m_location != loc) {
        m_location = loc;
        emit locationChanged();
    }
}

