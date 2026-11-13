// This file is part of Desktop App Toolkit,
// a set of libraries for developing nice desktop applications.
//
// For license and copyright information please follow this link:
// https://github.com/desktop-app/legal/blob/master/LEGAL
//
#include "ui/widgets/menu/menu_common.h"

#include "ui/effects/animation_value.h"
#include "ui/painter.h"
#include "styles/palette.h"
#include "styles/style_widgets.h"

// AyuGram includes
#include "ayu/ayu_ui_settings.h"

#include <QAction>
#include <QtGui/QPainterPath>

namespace Ui::Menu {

bool PaintItemTile(
		QPainter &p,
		int width,
		int height,
		const style::Menu &st,
		bool first,
		bool last,
		bool selected) {
	if (!AyuUiSettings::isMaterialMenus()) {
		return false;
	}
	(void)first;
	(void)last;
	// MD3 menu: items have no resting tile, only a rounded hover pill.
	p.fillRect(0, 0, width, height, st.itemBg);
	if (!selected) {
		return true;
	}
	const auto side = style::ConvertScale(6);
	const auto vertical = style::ConvertScale(1);
	const auto r = QRectF(
		side,
		vertical,
		width - 2 * side,
		height - 2 * vertical);
	const auto radius = std::min(
		r.height() / 2.,
		qreal(style::ConvertScale(18)));
	auto hq = PainterHighQualityEnabler(p);
	p.setPen(Qt::NoPen);
	p.setBrush(st.itemBgOver);
	p.drawRoundedRect(r, radius, radius);
	return true;
}

not_null<QAction*> CreateAction(
		QWidget *parent,
		const QString &text,
		Fn<void()> &&callback) {
	const auto action = new QAction(text, parent);
	parent->connect(
		action,
		&QAction::triggered,
		action,
		std::move(callback),
		Qt::QueuedConnection);
	return action;
}

} // namespace Ui::Menu
