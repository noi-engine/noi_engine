<div align="center">

# Noi Engine

**No Idea Engine** — a small C++20 2D game engine with an ECS core, a JSON scene format, and a Qt editor to build games visually.

[Engine](https://github.com/noi-engine/noi_engine) ·
[Editor](https://github.com/noi-engine/noi_engine_editor) ·
[2D Template](https://github.com/noi-engine/template-basic-2d) ·
[Releases](https://github.com/noi-engine/noi_engine/releases)

![Noi Engine editor demo](https://raw.githubusercontent.com/noi-engine/template-basic-2d/main/.github/readme/demo.gif)

</div>

> [!NOTE]
> This project is **paused** for now. Everything works end to end (create a project → edit the scene → compile → play), but expect rough edges.

## Screenshots

| Home | Template marketplace |
| :---: | :---: |
| ![Home screen](https://raw.githubusercontent.com/noi-engine/template-basic-2d/main/.github/readme/home.png) | ![Template marketplace](https://raw.githubusercontent.com/noi-engine/template-basic-2d/main/.github/readme/marketplace.png) |

![Scene editor](https://raw.githubusercontent.com/noi-engine/template-basic-2d/main/.github/readme/editor.png)

## What's inside

### Engine — [`noi_engine`](https://github.com/noi-engine/noi_engine)

- **ECS core** with entities, components, systems and typed signals between scripts
- **Scenes as data**: scenes are written in JSON and compiled to FlatBuffers for release builds (source and compiled loaders)
- **OpenGL renderer** (SDL2 + glad): meshes, materials, shaders, textures, render layers, letterboxing, 2D and 3D cameras
- **C++ scripts** that register themselves, with `on_create` / `on_update` hooks and helper macros
- **Built-in modules you can turn on**: `physics_system` (gravity + AABB `box_collider`), `orbit_camera_system`, follow action
- **Resource manager** with handles, labels and listing, which the editor uses

### Editor — [`noi_engine_editor`](https://github.com/noi-engine/noi_engine_editor)

- Qt 6 / QML desktop app with recent projects and a project creator
- **Template marketplace**: install templates and older template versions
- **Live scene viewport** that runs the real engine through the prebuilt [editor bridge](https://github.com/noi-engine/noi_engine_editor_bridge), with pan, zoom, grid and gizmos
- **Hierarchy + Inspector**: create, edit and delete entities and components; add sprites, textures and scripts
- **Compile & Play** straight from the editor, with output, editor logs and loaded-resources panels
- Downloads the engine, the resources compiler and the editor bridge each template asks for, from their releases

### Template — [`template-basic-2d`](https://github.com/noi-engine/template-basic-2d)

A small platformer to start from: a player with gravity, jumping and collisions, a camera that follows the player, platforms, walls and a ground, all set up in `resources/scenes/main.scene`.

## A taste of the API

```cpp
auto noi_engine_game::player_script::on_create(
    const noi_engine::entity self, const noi_engine::script_context& context) -> void
{
    NOI_ENGINE_ADD(gravity{});
    NOI_ENGINE_ADD((box_collider{.half_extents = {0.5f, 0.5f}, .is_static = false}));
}

auto noi_engine_game::player_script::on_update(
    const noi_engine::entity self, const noi_engine::script_context& context, const float dt) -> void
{
    auto& g = NOI_ENGINE_GET(gravity);
    if (std::abs(g.velocity.y) < 0.01f && context.input->is_key_pressed(noi_engine::key_code::space))
    {
        g.velocity.y = 6.0f; // jump
    }
    NOI_ENGINE_EMIT(moved_signal{self}); // the camera script listens to this
}
```

```cpp
auto main(const int argc, char** argv) -> int
{
    noi_engine::sdl_game game(name, width, height, get_resource_loader());
    register_scripts(game);

    auto scene = game.resources().load_scene("scenes/main.scene");
    scene->add_system<noi_engine::physics_system>();
    game.set_scene(std::move(scene));

    return game.run(argc, argv);
}
```

## Getting started

**With the editor** (recommended): build or launch the editor, click **Create New Project**, pick the *2D Game Template*, then **Compile** and **Play**.

**Prebuilt engine**: Linux x64 and macOS arm64 builds are on the [releases page](https://github.com/noi-engine/noi_engine/releases).

**From source** (each repo has `debug` / `release` CMake presets):

```bash
export VCPKG_ROOT=/path/to/vcpkg
cmake --preset debug
cmake --build --preset debug
```

The editor also needs **Qt 6.10+**.

## Toolchain used

| Tool | Version |
| --- | --- |
| clang | 22.1.6 |
| cmake | 4.3.4 |
| ninja | 1.13.2 |
| vcpkg | 2026-07-13 |
| Qt (editor) | 6.10+ |

Dependencies come from vcpkg: SDL2, glm, stb, tinyobjloader, nlohmann-json, flatbuffers, gtest.

## Repositories

| Repo | What it is |
| --- | --- |
| [noi_engine](https://github.com/noi-engine/noi_engine) | The engine library (prebuilt releases on its [releases page](https://github.com/noi-engine/noi_engine/releases)) |
| [noi_engine_editor](https://github.com/noi-engine/noi_engine_editor) | The Qt/QML editor |
| [template-basic-2d](https://github.com/noi-engine/template-basic-2d) | Starter 2D platformer template (powered by [Templi](https://github.com/RickaPrincy/Templi)) |
| [resources_compiler](https://github.com/noi-engine/resources_compiler) | Compiles scenes and resources to FlatBuffers |
| [noi_engine_editor_bridge](https://github.com/noi-engine/noi_engine_editor_bridge) | Prebuilt library the editor uses to run a scene live (editor-only, never part of a game) |
