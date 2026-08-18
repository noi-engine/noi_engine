//
// Created by ricka on 8/18/26.
//

#include "shader_loader.hpp"
#include "fbs/shader_generated.h"

auto noi_engine::c::shader_loader::load(resource_loader* resources,
                                     const std::span<const std::byte> data) -> std::unique_ptr<shader>
{
    const auto* fbs = fbs::GetShader(data.data());
    const auto vert_bytes = resources->load(fbs->vertex()->str());
    const auto frag_bytes = resources->load(fbs->fragment()->str());

    std::string vert_src(reinterpret_cast<const char*>(vert_bytes.data()),
                         vert_bytes.size());
    std::string frag_src(reinterpret_cast<const char*>(frag_bytes.data()),
                         frag_bytes.size());

    return std::make_unique<shader>(vert_src, frag_src);
}
