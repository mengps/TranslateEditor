#ifndef TSPASER_H
#define TSPASER_H

#include <QObject>

class TsData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<QString> fileNames READ fileNames WRITE setFileNames NOTIFY fileNamesChanged)
    Q_PROPERTY(QList<int> lines READ lines WRITE setLines NOTIFY linesChanged)
    Q_PROPERTY(QString sourceText READ sourceText WRITE setSourceText NOTIFY sourceTextChanged)
    Q_PROPERTY(QString translateText READ translateText WRITE setTranslateText NOTIFY translateTextChanged)
    Q_PROPERTY(QString commentsText READ commentsText WRITE setCommentsText NOTIFY commentsTextChanged)

public:
    TsData(QObject *parent = nullptr);
    TsData(const QString &name, const QList<QString> &fileNames
           , const QList<int> &lines, const QString &sourceText
           , const QString &translateText, const QString &commentsText
           , QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QList<QString> fileNames() const;
    void setFileNames(const QList<QString> &fileNames);

    QList<int> lines() const;
    void setLines(const QList<int> &lines);

    QString sourceText() const;
    void setSourceText(const QString &sourceText);

    QString translateText() const;
    void setTranslateText(const QString &translateText);

    QString commentsText() const;
    void setCommentsText(const QString &commentsText);

signals:
    void nameChanged();
    void fileNamesChanged();
    void linesChanged();
    void sourceTextChanged();
    void translateTextChanged();
    void commentsTextChanged();

private:
    QString m_name;
    QList<QString> m_fileNames;
    QList<int> m_lines;
    QString m_sourceText;
    QString m_translateText;
    QString m_commentsText;
};

QDebug operator<<(QDebug debug, const TsData &data);

class QXmlStreamReader;
class QXmlStreamWriter;
class TsParser : public QObject
{
    Q_OBJECT

public:
    TsParser(QObject *parent = nullptr);
    ~TsParser();

    bool load(const QString &filename);
    bool save(const QString &filename);
    void cleanup();

    void parser();
    QList<TsData *> result() const;

    QString lastError() const;

signals:
    void error();

private:
    void readTS();
    void readContext();
    void readSourceText(TsData *data);
    void readTranslateText(TsData *data);
    void readCommentsText(TsData *data);
    void readMessage(TsData *data);

private:
    QString m_lastError;
    QXmlStreamReader *m_tsReader = nullptr;
    QXmlStreamWriter *m_tsWriter = nullptr;
    QString m_tsVersion;
    QString m_tsLanguage;
    QList<TsData *> m_result;
};

#endif // TSPASER_H
