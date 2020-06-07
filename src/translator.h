#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>


/**
 * @brief 翻译器，用于切换语言
 */

class QQmlEngine;
class QTranslator;
class Translator : public QObject
{
    Q_OBJECT
    Q_ENUMS(Language)

public:
    enum class Language
    {
        English = 1,
        Chinese
    };

public:
    static Translator* instance(QQmlEngine *engine);

    void retranslateUi();

    Q_INVOKABLE void loadLanguage(Language lang);

signals:
    void message(const QString &msg);

private:
    Translator(QQmlEngine *engine);

    QQmlEngine *m_engine = nullptr;
    QTranslator *m_translator = nullptr;
};

#endif // TRANSLATOR_H
