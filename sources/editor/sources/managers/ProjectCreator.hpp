#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>

namespace noi_engine_editor
{
    class ProjectCreator : public QObject
    {
        Q_OBJECT
        QML_ELEMENT

    public:
        explicit ProjectCreator(QObject* parent = nullptr);

        Q_INVOKABLE [[nodiscard]] auto createProject(const QString& name, const QString& location) -> bool;

    signals:
        void projectCreated(const QString& name, const QString& path);
        void projectCreationFailed(const QString& reason);
    };
}