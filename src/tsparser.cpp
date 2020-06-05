#include "tsparser.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

TsData::TsData(QObject *parent)
    : QObject (parent)
{

}

TsData::TsData(const QString &name
               , const QList<QString> &fileNames
               , const QList<int> &lines
               , const QString &sourceText
               , const QString &translateText
               , const QString &commentsText, QObject *parent)
    : QObject (parent)
    , m_name(name)
    , m_fileNames(fileNames)
    , m_lines(lines)
    , m_sourceText(sourceText)
    , m_translateText(translateText)
    , m_commentsText(commentsText)
{

}

QString TsData::name() const
{
    return m_name;
}

void TsData::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

QList<QString> TsData::fileNames() const
{
    return m_fileNames;
}

void TsData::setFileNames(const QList<QString> &fileNames)
{
    if (fileNames != m_fileNames) {
        m_fileNames = fileNames;
        emit fileNamesChanged();
    }
}

QList<int> TsData::lines() const
{
    return m_lines;
}

void TsData::setLines(const QList<int> &lines)
{
    if (lines != m_lines) {
        m_lines = lines;
        emit linesChanged();
    }
}

QString TsData::sourceText() const
{
    return m_sourceText;
}

void TsData::setSourceText(const QString &sourceText)
{
    if (sourceText != m_sourceText) {
        m_sourceText = sourceText;
        emit sourceTextChanged();
    }
}

QString TsData::translateText() const
{
    return  m_translateText;
}

void TsData::setTranslateText(const QString &translateText)
{
    if (translateText != m_translateText) {
        m_translateText = translateText;
        emit translateTextChanged();
    }
}

QString TsData::commentsText() const
{
    return m_commentsText;
}

void TsData::setCommentsText(const QString &commentsText)
{
    if (commentsText != m_commentsText) {
        m_commentsText = commentsText;
        emit commentsTextChanged();
    }
}

QDebug operator<<(QDebug debug, const TsData &data)
{
    debug << "[name: " << data.name() << "]" << endl
          << "[fileNames: " << data.fileNames() << "]" << endl
          << "[lines: " << data.lines() << "]" << endl
          << "[sourceText: " << data.sourceText() << "]" << endl
          << "[translateText: " << data.translateText() << "]" << endl
          << "[commentsText: " << data.commentsText() << "]" << endl;

    return debug;
}

TsParser::TsParser(QObject *parent)
    : QObject (parent)
{
    m_tsReader = new QXmlStreamReader;
    m_tsWriter = new QXmlStreamWriter;
    m_tsWriter->setAutoFormatting(true);
}

TsParser::~TsParser()
{
    if (m_tsReader) delete m_tsReader;
}

bool TsParser::load(const QString &filename)
{
    cleanup();

    QFile tsFile(filename);
    if (!tsFile.open(QIODevice::ReadOnly)) {
        m_lastError = tsFile.errorString();
        return false;
    }

    m_tsReader->clear();
    m_tsReader->addData(tsFile.readAll());
    tsFile.close();

    if (m_tsReader->error() != QXmlStreamReader::NoError) {
        m_lastError = m_tsReader->errorString();
        return false;
    }

    return true;
}

bool TsParser::save(const QString &filename)
{
    QFile tsFile(filename);
    if (!tsFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        m_lastError = tsFile.errorString();
        return false;
    }

    m_tsWriter->setDevice(&tsFile);
    m_tsWriter->writeStartDocument();
    m_tsWriter->writeDTD(QStringLiteral("<!DOCTYPE TS>"));
    m_tsWriter->writeStartElement("TS");
    m_tsWriter->writeAttribute("version", m_tsVersion);
    m_tsWriter->writeAttribute("language", m_tsLanguage);

    if (m_result.count() > 0) {
        QString currentName;
        m_tsWriter->writeStartElement("context");
        for (int i = 0; i < m_result.count(); ++i) {
            bool equal = currentName == m_result[i]->name();
            if (!equal) {
                m_tsWriter->writeTextElement("name", m_result[i]->name());
            }

            m_tsWriter->writeStartElement("message");
            QList<QString> fileNames = m_result[i]->fileNames();
            QList<int> lines = m_result[i]->lines();
            if (fileNames.count() != lines.count())
                return false;

            for (int j = 0; j < fileNames.count(); j++) {
                m_tsWriter->writeStartElement("location");
                m_tsWriter->writeAttribute("filename", fileNames[j]);
                m_tsWriter->writeAttribute("line", QString::number(lines[j]));
                m_tsWriter->writeEndElement();
            }
            m_tsWriter->writeTextElement("source", m_result[i]->sourceText());
            m_tsWriter->writeTextElement("translatorcomment", m_result[i]->commentsText());
            m_tsWriter->writeTextElement("translation", m_result[i]->translateText());

            //</message>
            m_tsWriter->writeEndElement();
            if (!equal) {
                currentName = m_result[i]->name();
                //</context>
                m_tsWriter->writeEndElement();
                m_tsWriter->writeStartElement("context");
            }
        }
    }

    //</TS>
    m_tsWriter->writeEndElement();
    m_tsWriter->writeEndDocument();
    tsFile.close();

    return true;
}

void TsParser::cleanup()
{
    for (auto it : m_result) {
        delete it;
    }
    m_result.clear();
}

void TsParser::parser()
{
    if (m_tsReader->readNextStartElement()) {
        if (m_tsReader->name() == QLatin1String("TS")) {
            m_tsVersion = m_tsReader->attributes().value("version").toString();
            m_tsLanguage = m_tsReader->attributes().value("language").toString();
            readTS();
        } else {
            m_lastError = tr("This 'ts' file not have <TS> element!");
            emit error();
        }
    } else {
        m_lastError = tr("Parser start error!");
        emit error();
    }
}

QList<TsData *> TsParser::result() const
{
    return m_result;
}

void TsParser::readTS()
{
    Q_ASSERT(m_tsReader->isStartElement() && m_tsReader->name() == QLatin1String("TS"));

    while (m_tsReader->readNextStartElement()) {
        if (m_tsReader->name() == QLatin1String("context")) {
            readContext();
        } else m_tsReader->skipCurrentElement();
    }
}

void TsParser::readContext()
{
    Q_ASSERT(m_tsReader->isStartElement() && m_tsReader->name() == QLatin1String("context"));

    QString name;
    while (m_tsReader->readNextStartElement()) {
        if (m_tsReader->name() == QLatin1String("name")) {
            name = m_tsReader->readElementText();
        } else if (m_tsReader->name() == QLatin1String("message")) {
            TsData *data = new TsData;
            data->setName(name);
            readMessage(data);
            m_result.append(data);
        } else m_tsReader->skipCurrentElement();
    }
}

void TsParser::readSourceText(TsData *data)
{
    Q_ASSERT(m_tsReader->isStartElement() && m_tsReader->name() == QLatin1String("source"));

    data->setSourceText(m_tsReader->readElementText());
}


void TsParser::readTranslateText(TsData *data)
{
    Q_ASSERT(m_tsReader->isStartElement() && m_tsReader->name() == QLatin1String("translation"));

    data->setTranslateText(m_tsReader->readElementText());
}

void TsParser::readCommentsText(TsData *data)
{
    Q_ASSERT(m_tsReader->isStartElement() && m_tsReader->name() == QLatin1String("translatorcomment"));

    data->setCommentsText(m_tsReader->readElementText());
}

void TsParser::readMessage(TsData *data)
{
    QList<QString> filenames;
    QList<int> lines;
    while (m_tsReader->readNextStartElement()) {
        if (m_tsReader->name() == QLatin1String("location")) {
            do {
                if (m_tsReader->name() == QLatin1String("location")) {
                    filenames.append(m_tsReader->attributes().value("filename").toString());
                    lines.append(m_tsReader->attributes().value("line").toInt());
                }
            } while (m_tsReader->readNextStartElement());
        } else if (m_tsReader->name() == QLatin1String("source")) {
            readSourceText(data);
        } else if (m_tsReader->name() == QLatin1String("translation")) {
            readTranslateText(data);
        } else if (m_tsReader->name() == QLatin1String("translatorcomment")) {
            readCommentsText(data);
        } else m_tsReader->skipCurrentElement();
    }

    data->setFileNames(filenames);
    data->setLines(lines);
}

QString TsParser::lastError() const
{
    return m_lastError;
}
