#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char *argv[])
{
#ifdef QT_QML_DEBUG
    qDebug() << "QML debugging enabled";
#endif

#ifdef QML_IMPORT_TRACE
    qDebug() << "QML import tracing:" << QML_IMPORT_TRACE;
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("../qml");
    engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

    return app.exec();
}
