//
// Created by ricka on 2026-09-04.
//

#include <gtest/gtest.h>

#include <noi_engine/core/scene.hpp>

#include <core/systems/camera_system.hpp>
#include <core/systems/render_system.hpp>
#include <core/systems/script_runner_system.hpp>
#include <core/systems/transform_system.hpp>

using namespace noi_engine;

namespace
{
    class dummy_system_a : public system
    {
    public:
        [[nodiscard]] auto name() const -> std::string_view override { return "dummy_system_a"; }
    };

    class dummy_system_b : public system
    {
    public:
        [[nodiscard]] auto name() const -> std::string_view override { return "dummy_system_b"; }
    };

    class dummy_system_c : public system
    {
    public:
        [[nodiscard]] auto name() const -> std::string_view override { return "dummy_system_c"; }
    };

    auto names(const scene& s) -> std::vector<std::string_view>
    {
        std::vector<std::string_view> result;
        for (const auto& [name, priority] : s.systems())
            result.push_back(name);
        return result;
    }
}  // namespace

TEST(SceneSystemTest, DefaultPipelineIsRegisteredInOrder)
{
    const scene s{"test"};

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "camera_system", "render_system"
    }));
}

TEST(SceneSystemTest, AddSystemAppendsAtDefaultPriority)
{
    scene s{"test"};

    s.add_system<dummy_system_a>();

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "camera_system", "render_system", "dummy_system_a"
    }));
}

TEST(SceneSystemTest, LowerPriorityRunsFirst)
{
    scene s{"test"};

    s.add_system<dummy_system_a>(-100);

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "dummy_system_a", "script_runner_system", "transform_system", "camera_system", "render_system"
    }));
}

TEST(SceneSystemTest, AddSystemBeforeAnchorInsertsImmediatelyBefore)
{
    scene s{"test"};

    s.add_system_before<render_system, dummy_system_a>();

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "camera_system", "dummy_system_a", "render_system"
    }));
}

TEST(SceneSystemTest, AddSystemAfterAnchorInsertsImmediatelyAfter)
{
    scene s{"test"};

    s.add_system_after<transform_system, dummy_system_a>();

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "dummy_system_a", "camera_system", "render_system"
    }));
}

TEST(SceneSystemTest, GetAndRemoveSystem)
{
    scene s{"test"};

    s.add_system<dummy_system_a>();

    ASSERT_NE(s.get_system<dummy_system_a>(), nullptr);

    s.remove_system<dummy_system_a>();

    EXPECT_EQ(s.get_system<dummy_system_a>(), nullptr);
    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "camera_system", "render_system"
    }));
}

TEST(SceneSystemTest, SetSystemPriorityReordersSystem)
{
    scene s{"test"};

    s.add_system<dummy_system_a>();
    s.set_system_priority<dummy_system_a>(-100);

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "dummy_system_a", "script_runner_system", "transform_system", "camera_system", "render_system"
    }));
}

TEST(SceneSystemTest, MultipleSystemsAtSamePriorityKeepInsertionOrder)
{
    scene s{"test"};

    s.add_system<dummy_system_a>();
    s.add_system<dummy_system_b>();
    s.add_system<dummy_system_c>();

    EXPECT_EQ(names(s), (std::vector<std::string_view>{
        "script_runner_system", "transform_system", "camera_system", "render_system",
        "dummy_system_a", "dummy_system_b", "dummy_system_c"
    }));
}
