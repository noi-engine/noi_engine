#pragma once

#include <QQuickItem>
#include <QtQml/qqmlregistration.h>
#include <QQuickFramebufferObject>

namespace noi_engine_editor
{
	class OpenGLView : public QQuickFramebufferObject
	{
	Q_OBJECT
	QML_ELEMENT

	public:
		explicit OpenGLView(QQuickItem *parent = nullptr);

		[[nodiscard]] Renderer *createRenderer() const override;
	};
}