#ifndef TSLISTMODEL_H
#define TSLISTMODEL_H

#include <QAbstractListModel>

/***
 * 后来意识到，也许使用QQmlListProperty会更好
 */
class TsListModelPrivate;
class TsListModel: public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(TsRole)

public:
    enum TsRole
    {
        FileName = Qt::UserRole + 1,
        Line = Qt::UserRole + 2,
        Source = Qt::UserRole + 3,
        Translate = Qt::UserRole + 4,
        Comment = Qt::UserRole + 5
    };

public:
    TsListModel(QObject *parent = nullptr);
    ~TsListModel() override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool setData(int row, const QVariant &value, int role);

    Q_INVOKABLE bool load(const QUrl &url);
    Q_INVOKABLE bool save(const QUrl &url);

private:
    TsListModelPrivate *d;
};

#endif // TSLISTMODEL_H
