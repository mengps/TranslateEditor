#include "translator.h"

#include <QDebug>
#include <QCoreApplication>
#include <QQmlEngine>
#include <QTranslator>

Translator::Translator(QQmlEngine *engine)
{
    m_engine = engine;
    m_translator = new QTranslator(this);
    QCoreApplication::installTranslator(m_translator);
}

Translator *Translator::instance(QQmlEngine *engine)
{
    static Translator controller(engine);
    return &controller;
}

void Translator::retranslateUi()
{
    m_engine->retranslate();
}

void Translator::loadLanguage(Translator::Language lang)
{
    switch (lang) {
    case Language::Chinese:
        if (m_translator->load(QCoreApplication::applicationDirPath() + "/lang/TranslateEditor_zh_CN.qm")) {
            emit message(tr("--- Language changed to Chinese"));
        }
        break;
    case Language::English:
        m_translator->load("");
        emit message(tr("--- Language changed to English"));
        break;
    }

    retranslateUi();
}


