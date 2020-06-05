#include "tslistmodel.h"
#include "tsparser.h"
#include "fileapi.h"

#include <QDebug>
#include <QQmlFile>
#include <QQmlEngine>

class TsListModelPrivate
{
public:
    TsParser *m_parser = nullptr;
    QList<TsData *> m_tsData;
};

TsListModel::TsListModel(QObject *parent)
    : QAbstractListModel (parent)
{
    d = new TsListModelPrivate;
    d->m_parser = new TsParser(this);
}

TsListModel::~TsListModel()
{
    d->m_parser->cleanup();
    delete d;
}

int TsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->m_tsData.count();
}

int TsListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TsListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= d->m_tsData.count())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case TsRole::Source:
        return d->m_tsData[index.row()]->sourceText();

    case TsRole::FileName:
        return QVariant::fromValue<QList<QString>>(d->m_tsData[index.row()]->fileNames());

    case TsRole::Line:
        return QVariant::fromValue<QList<int>>(d->m_tsData[index.row()]->lines());

    case TsRole::Translate:
        return d->m_tsData[index.row()]->translateText();

    case TsRole::Comment:
        return d->m_tsData[index.row()]->commentsText();
    }

    return QVariant();
}

bool TsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    /**
     * @warning 对于 FileName/Line/Source 为只读，无需更改
     */
    switch (role) {
    case TsRole::Translate:
        d->m_tsData[index.row()]->setTranslateText(value.toString());
        return true;
    case TsRole::Comment:
        d->m_tsData[index.row()]->setCommentsText(value.toString());
        return true;
    }

    return QAbstractListModel::setData(index, value, role);
}

QHash<int, QByteArray> TsListModel::roleNames() const
{
    QHash<int, QByteArray> roles(QAbstractListModel::roleNames());
    roles[TsRole::FileName] = "fileNames";
    roles[TsRole::Line] = "lines";
    roles[TsRole::Source] = "sourceText";
    roles[TsRole::Translate] = "translateText";
    roles[TsRole::Comment] = "commentsText";

    return roles;
}

bool TsListModel::setData(int row, const QVariant &value, int role)
{
    auto i = index(row, 0);
    return TsListModel::setData(i, value, role);
}

bool TsListModel::load(const QUrl &url)
{
    const QString filename = QQmlFile::urlToLocalFileOrQrc(url);
    if (!d->m_parser->load(filename)) {
        qDebug() << d->m_parser->lastError();
        return false;
    } else {
        FileApi::instance()->setCurrent(filename);
        d->m_parser->parser();
        beginResetModel();
        d->m_tsData = d->m_parser->result();
        endResetModel();
        return true;
    }
}

bool TsListModel::save(const QUrl &url)
{
    const QString filename = QQmlFile::urlToLocalFileOrQrc(url);
    if (!d->m_parser->save(filename)) {
        qDebug() << d->m_parser->lastError();
        return false;
    }
}
