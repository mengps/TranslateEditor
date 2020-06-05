#include "tsapi.h"
#include <QProcess>

TsApi::TsApi()
{

}

TsApi* TsApi::instance()
{
    static TsApi tsApi;
    return &tsApi;
}

void TsApi::createQmFile(const QString &filename)
{
    /**
     * @brief 如果设置了Qt-lrelease.exe的位置，则使用location
     *        否则使用
     */
    QProcess::execute(location() + "lrelease.exe");
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

