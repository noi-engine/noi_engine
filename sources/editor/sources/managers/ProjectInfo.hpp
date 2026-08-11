//
// Created by ricka on 8/10/26.
//

#pragma once

#include <QDateTime>

namespace noi_engine_editor
{
    struct ProjectInfo
    {
        QString name;
        QString path;
        QDateTime lastOpened;

        bool operator==(const ProjectInfo& other) const = default;
    };
}
