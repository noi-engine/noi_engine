#include <QGuiApplication>
#include <QQmlApplicationEngine>

auto main(int argc, char* argv[]) -> int
{
    const QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() -> void { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("noi_engine_editor", "Main");

    return QGuiApplication::exec();
}
