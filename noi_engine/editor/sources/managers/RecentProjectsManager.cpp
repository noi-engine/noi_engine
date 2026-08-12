#include "RecentProjectsManager.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QFile>

namespace noi_engine_editor
{
    static constexpr int MAX_RECENT_PROJECTS = 15;

    RecentProjectsManager::RecentProjectsManager(QObject* parent) : QObject(parent)
    {
        loadFromDisk();
    }

    auto RecentProjectsManager::getStorageFilePath() -> QString
    {
        const auto appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if (!QDir().mkpath(appData))
        {
            throw std::runtime_error("Cannot create Config file"); //TODO
        }
        return appData + "/recent_projects.json";
    }

    auto RecentProjectsManager::addProject(const QString& name, const QString& path) -> void
    {
        const auto cleanPath = QFileInfo(path).absoluteFilePath();
        m_projects.removeIf([&cleanPath](const ProjectInfo& proj)
            -> bool
            {
                return proj.path == cleanPath;
            });

        m_projects.prepend(ProjectInfo{
            .name = name,
            .path = cleanPath,
            .lastOpened = QDateTime::currentDateTime()
        });

        if (m_projects.size() > MAX_RECENT_PROJECTS)
        {
            m_projects.removeLast();
        }

        saveToDisk();
        emit projectsChanged();
    }

    auto RecentProjectsManager::projects() const -> QList<ProjectInfo>
    {
        return this->m_projects;
    }

    auto RecentProjectsManager::removeProject(const QString& path) -> void
    {
        const auto cleanPath = QFileInfo(path).absoluteFilePath();
        const auto removed = m_projects.removeIf([&cleanPath](const ProjectInfo& proj)
            -> bool
            {
                return proj.path == cleanPath;
            });

        if (removed > 0)
        {
            saveToDisk();
            emit projectsChanged();
        }
    }

    auto RecentProjectsManager::clearMissingProjects() -> void
    {
        const auto removed = m_projects.removeIf([](const ProjectInfo& proj)
            -> bool
            {
                return !QFileInfo::exists(proj.path);
            });

        if (removed > 0)
        {
            saveToDisk();
            emit projectsChanged();
        }
    }

    auto RecentProjectsManager::saveToDisk() -> void
    {
        QJsonArray array;
        for (const auto& [name, path, lastOpened] : m_projects)
        {
            QJsonObject obj;
            obj["name"] = name;
            obj["path"] = path;
            obj["lastOpened"] = lastOpened.toString(Qt::ISODate);
            array.append(obj);
        }

        if (QFile file(getStorageFilePath()); file.open(QIODevice::WriteOnly))
        {
            file.write(QJsonDocument(array).toJson());
        }
    }

    auto RecentProjectsManager::loadFromDisk() -> void
    {
        QFile file(getStorageFilePath());
        if (!file.open(QIODevice::ReadOnly)) return;

        m_projects.clear();
        const auto doc = QJsonDocument::fromJson(file.readAll());

        for (const auto array = doc.array(); const auto& value : array)
        {
            const auto obj = value.toObject();
            m_projects.append(ProjectInfo{
                .name = obj["name"].toString(),
                .path = obj["path"].toString(),
                .lastOpened = QDateTime::fromString(obj["lastOpened"].toString(), Qt::ISODate)
            });
        }
        emit projectsChanged();
    }
}
