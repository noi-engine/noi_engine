#include "OpenglRenderer.hpp"
#include <QOpenGLContext>
#include <noi_engine/core/game.hpp>

namespace noi_engine_editor
{
    OpenGLRenderer::OpenGLRenderer()
    {
        noi_engine::game::init(
            [](const char* name) -> void*
            {
                auto* currentCtx = QOpenGLContext::currentContext();
                if (!currentCtx) return nullptr;

                return reinterpret_cast<void*>(currentCtx->getProcAddress(name));
            });
    }

    void OpenGLRenderer::render()
    {
        update();
    }

    QOpenGLFramebufferObject* OpenGLRenderer::createFramebufferObject(const QSize& size)
    {
        QOpenGLFramebufferObjectFormat format;

        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setInternalTextureFormat(GL_RGBA8);

        return new QOpenGLFramebufferObject(size, format);
    }
}
