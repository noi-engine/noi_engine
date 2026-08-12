//
// Created by ricka on 8/2/26.
//

#pragma once

#include <filesystem>
#include <noi_engine/core/assets/asset_provider.hpp>

namespace noi_engine
{
    class filesystem_asset_provider : public asset_provider
    {
        std::filesystem::path m_root;

    public:
        explicit filesystem_asset_provider(std::filesystem::path root);

        [[nodiscard]] auto read(std::string_view path) -> std::vector<std::byte> override;
    };
}
