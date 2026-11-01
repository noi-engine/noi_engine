#include <gtest/gtest.h>

#include <memory>
#include <noi_engine/core/model/script.hpp>
#include <noi_engine/core/resources/resources.hpp>
#include <noi_engine/core/resources/resource_loader.hpp>

using namespace noi_engine;

namespace
{
    struct first_test_script : script
    {
    };

    struct second_test_script : script
    {
    };

    auto make_resources() -> std::unique_ptr<resources>
    {
        return std::make_unique<resources>(std::make_unique<source_resource_loader>("."));
    }
}

TEST(ScriptResourcesTest, FindOrLoadLoadsRegisteredScripts)
{
    auto res = make_resources();
    res->register_script<first_test_script>("first_test_script");
    res->register_script<second_test_script>("second_test_script");

    resource_handle<script> first{};
    resource_handle<script> second{};
    ASSERT_TRUE(res->find_or_load_script("first_test_script", first));
    ASSERT_TRUE(res->find_or_load_script("second_test_script", second));
    EXPECT_NE(first.m_id, second.m_id);
    EXPECT_EQ(res->get_label<script>(second), "second_test_script");

    // Already loaded: the same instance.
    resource_handle<script> again{};
    ASSERT_TRUE(res->find_or_load_script("first_test_script", again));
    EXPECT_EQ(again.m_id, first.m_id);
}

TEST(ScriptResourcesTest, UnknownScriptIsNotFound)
{
    auto res = make_resources();
    res->register_script<first_test_script>("first_test_script");
    resource_handle<script> first{};
    ASSERT_TRUE(res->find_or_load_script("first_test_script", first));

    // Must not fall back to the first loaded script.
    resource_handle<script> unknown{};
    EXPECT_FALSE(res->find_or_load_script("missing_test_script", unknown));
    EXPECT_THROW((void)res->load_from_path<script>("missing_test_script"), std::runtime_error);
}

TEST(ScriptResourcesTest, RegistryCanBeCleared)
{
    details::script_registry::instance().add("cleared_test_script", [] { return std::make_unique<first_test_script>(); });
    EXPECT_TRUE(details::script_registry::instance().contains("cleared_test_script"));
    details::script_registry::instance().clear();
    EXPECT_FALSE(details::script_registry::instance().contains("cleared_test_script"));
}

TEST(ScriptResourcesTest, LabelBelongsToOneResource)
{
    auto res = make_resources();
    res->register_script<first_test_script>("first_test_script");
    const auto old_handle = res->load_from_path<script>("first_test_script", "first_test_script");
    const auto new_handle = res->load_from_path<script>("first_test_script", "first_test_script");
    EXPECT_EQ(res->get_label<script>(new_handle), "first_test_script");
    EXPECT_EQ(res->get_label<script>(old_handle), "");
}

#include <noi_engine/core/components/script_component.hpp>
#include <noi_engine/core/scene.hpp>
#include <core/systems/script_runner_system.hpp>

namespace
{
    struct counting_script : script
    {
        int* created{nullptr};
        int* updated{nullptr};

        auto on_create(entity, const script_context&) -> void override { ++*created; }
        auto on_update(entity, const script_context&, float) -> void override { ++*updated; }
    };
}

TEST(ScriptResourcesTest, PausedScriptsDontRun)
{
    auto res = make_resources();
    int created = 0;
    int updated = 0;
    auto instance = std::make_unique<counting_script>();
    instance->created = &created;
    instance->updated = &updated;
    const auto handle = res->load_instance<script>(std::move(instance));

    scene s("test");
    const auto e = s.get_world().create_entity();
    s.get_world().add(e, script_component{.scripts = {handle}});

    const script_context ctx{.scene = &s, .resources = res.get()};
    script_runner_system runner;

    s.set_scripts_paused(true);
    runner.on_before_update(ctx, 0.1f);
    runner.on_update(ctx, 0.1f);
    EXPECT_EQ(created, 0);
    EXPECT_EQ(updated, 0);

    s.set_scripts_paused(false);
    runner.on_before_update(ctx, 0.1f);
    runner.on_update(ctx, 0.1f);
    EXPECT_EQ(created, 1);
    EXPECT_EQ(updated, 1);
}
