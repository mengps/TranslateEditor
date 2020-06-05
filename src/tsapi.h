#ifndef TSAPI_H
#define TSAPI_H

#include <QObject>

class TsApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

public:
    static TsApi* instance();

    Q_INVOKABLE void createQmFile(const QString &filename);

    QString location() const;
    void setLocation(const QString &loc);

signals:
    void locationChanged();

private:
    TsApi();

    QString m_location;
};

#endif // TSAPI_H
