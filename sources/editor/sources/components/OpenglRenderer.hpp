#pragma once

#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>

namespace noi_engine_editor
{
    class OpenGLRenderer final : public QQuickFramebufferObject::Renderer
    {
    public:
        OpenGLRenderer();

        void render() override;

        QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;
    };
}
