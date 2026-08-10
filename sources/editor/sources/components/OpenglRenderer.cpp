#include "OpenglRenderer.hpp"

#include <QOpenGLContext>

namespace noi_engine_editor
{
	OpenGLRenderer::OpenGLRenderer()
	{
		initializeOpenGLFunctions();
	}

	void OpenGLRenderer::initialize()
	{
		if (initialized_) return;
		initialized_ = true;
	}

	void OpenGLRenderer::render()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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