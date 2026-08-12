#include "OpenglView.hpp"
#include "OpenglRenderer.hpp"

namespace noi_engine_editor
{
	OpenGLView::OpenGLView(QQuickItem* parent) : QQuickFramebufferObject(parent)
	{}

	QQuickFramebufferObject::Renderer* OpenGLView::createRenderer() const
	{
		return new OpenGLRenderer();
	}
}