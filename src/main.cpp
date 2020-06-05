#include "documenthelper.h"
#include "fileapi.h"
#include "framelesswindow.h"
#include "tslistmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("MPS");

    qmlRegisterType<FramelessWindow>("an.window", 1, 0, "FramelessWindow");
    qmlRegisterType<DocumentHelper>("an.document", 1, 0, "DocumentHelper");
    qmlRegisterUncreatableType<TsListModel>("an.model", 1, 0, "TsModel", QObject::tr("Don't create TsModel Object!"));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("tsModel", new TsListModel);
    engine.rootContext()->setContextProperty("fileApi", FileApi::instance());
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
