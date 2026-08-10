#pragma once

#include <QQuickItem>
#include <QQuickFramebufferObject>

namespace noi_engine_editor
{
	class OpenGLView final : public QQuickFramebufferObject
	{
	Q_OBJECT
	QML_ELEMENT

	public:
		explicit OpenGLView(QQuickItem *parent = nullptr);

		[[nodiscard]] Renderer *createRenderer() const override;
	};
}