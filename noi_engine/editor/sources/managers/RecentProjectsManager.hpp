#pragma once

#include <QQmlEngine>
#include <QList>
#include <QDir>
#include "ProjectInfo.hpp"

namespace noi_engine_editor
{
    class RecentProjectsManager : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON

    public:
        explicit RecentProjectsManager(QObject* parent = nullptr);

        Q_INVOKABLE auto clearMissingProjects() -> void;

        Q_INVOKABLE auto removeProject(const QString& path) -> void;

        Q_INVOKABLE auto addProject(const QString& name, const QString& path) -> void;

        [[nodiscard]] auto projects() const -> QList<ProjectInfo>;

    signals:
        void projectsChanged();

    private:
        auto loadFromDisk() -> void;

        auto saveToDisk() -> void;

        [[nodiscard]] static auto getStorageFilePath() -> QString;

        QList<ProjectInfo> m_projects;
    };
}
