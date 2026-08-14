//
// Created by ricka on 8/2/26.
//

#pragma once

#include <string_view>
#include <vector>

namespace noi_engine
{
    class asset_provider
    {
    public:
        virtual ~asset_provider() = default;

        virtual auto read(std::string_view path) -> std::vector<std::byte> = 0;
    };
}
