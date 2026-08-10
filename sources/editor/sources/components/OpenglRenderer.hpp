#pragma once

#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickFramebufferObject>

namespace noi_engine_editor
{
	class OpenGLRenderer final : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
	{
	public:
		OpenGLRenderer();

		void render() override;

		QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;

	private:
		void initialize();

		bool initialized_ = false;

		QOpenGLShaderProgram program_;

		GLuint vao_ = 0;
		GLuint vbo_ = 0;
	};

}