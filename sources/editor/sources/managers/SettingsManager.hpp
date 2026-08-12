#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>

namespace noi_engine_editor
{
    class SettingsManager : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON

        Q_PROPERTY(QString defaultProjectsPath READ defaultProjectsPath WRITE setDefaultProjectsPath NOTIFY defaultProjectsPathChanged)

    public:
        explicit SettingsManager(QObject* parent = nullptr);

        [[nodiscard]] auto defaultProjectsPath() const -> QString;

        auto setDefaultProjectsPath(const QString& path) -> void;

    signals:
        void defaultProjectsPathChanged();

    private:
        QString m_defaultProjectsPath;
    };
}
