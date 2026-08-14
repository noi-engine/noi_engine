//
// Created by ricka on 8/9/26.
//

#pragma once

#include <memory>
#include <noi_engine/core/game.hpp>
#include <noi_engine/sdl/sdl_window.hpp>
#include <noi_engine/core/assets/filesystem_asset_provider.hpp>

namespace noi_engine
{
    struct sdl_game_conf : game_conf
    {
        int max_fps{60};
        bool v_sync{false};
    };

    class sdl_game : public game
    {
        bool m_running{false};

        virtual auto process_events() -> void;

    protected:
        sdl_game_conf m_conf{};
        std::unique_ptr<sdl_window> m_window{nullptr};

    public:
        explicit sdl_game(
            const std::string& title,
            int width,
            int height,
            const std::shared_ptr<asset_provider>& asset_provider = std::make_shared<filesystem_asset_provider>(
                std::filesystem::current_path()),
            const sdl_game_conf& game_conf = {});

        virtual auto run(int argc, char** argv) -> int;

        [[nodiscard]] auto get_window() -> sdl_window&;
        [[nodiscard]] auto get_window() const -> const sdl_window&;

        ~sdl_game() override;
    };
}
