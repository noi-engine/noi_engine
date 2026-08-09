//
// Created by ricka on 8/9/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/components/component.hpp>
#include <noi_engine/core/scripts/script.hpp>

namespace noi_engine
{
    struct script_component : component
    {
        std::shared_ptr<script> instance{};
        bool created{false};
    };
}
