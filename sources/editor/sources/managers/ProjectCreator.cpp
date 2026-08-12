#include "ProjectCreator.hpp"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace noi_engine_editor
{
    namespace
    {
        auto createFolderStructure(const QDir& root) -> bool
        {
            static const QStringList folders = {
                "assets/2d",
                "assets/3d",
                "assets/audio",
                "assets/scripts",
                "scenes",
                "cache"
            };

            for (const auto& folder : folders)
            {
                if (!root.mkpath(folder))
                {
                    return false;
                }
            }

            return true;
        }

        auto writeProjectFile(const QDir& root, const QString& name) -> bool
        {
            QJsonObject project;
            project["name"] = name;
            project["engineVersion"] = "0.0.1";
            project["createdAt"] = QDateTime::currentDateTime().toString(Qt::ISODate);

            QFile file(root.filePath("project.noiproj"));
            if (!file.open(QIODevice::WriteOnly))
            {
                return false;
            }

            file.write(QJsonDocument(project).toJson());
            return true;
        }
    }

    ProjectCreator::ProjectCreator(QObject* parent) : QObject(parent)
    {
    }

    auto ProjectCreator::createProject(const QString& name, const QString& location) -> bool
    {
        const auto projectPath = QDir(location).filePath(name);
        const QDir root(projectPath);

        if (root.exists())
        {
            emit projectCreationFailed(tr("A folder with this name already exists"));
            return false;
        }

        if (!QDir().mkpath(projectPath))
        {
            emit projectCreationFailed(tr("Cannot create project folder"));
            return false;
        }

        if (!createFolderStructure(root) || !writeProjectFile(root, name))
        {
            emit projectCreationFailed(tr("Cannot write project files"));
            return false;
        }

        emit projectCreated(name, projectPath);
        return true;
    }
}