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

QPainterPath ItemTilePath(
		int width,
		int height,
		bool first,
		bool last) {
	const auto side = style::ConvertScale(6);
	const auto top = style::ConvertScale(first ? 2 : 1);
	const auto bottom = style::ConvertScale(last ? 2 : 1);
	const auto big = std::min(
		qreal(style::ConvertScale(14)),
		height * 0.34);
	const auto small = qreal(style::ConvertScale(5));
	const auto upper = first ? big : small;
	const auto lower = last ? big : small;
	const auto r = QRectF(side, top, width - 2 * side, height - top - bottom);
	auto path = QPainterPath();
	path.moveTo(r.left() + upper, r.top());
	path.lineTo(r.right() - upper, r.top());
	path.arcTo(QRectF(r.right() - 2 * upper, r.top(), 2 * upper, 2 * upper), 90, -90);
	path.lineTo(r.right(), r.bottom() - lower);
	path.arcTo(QRectF(r.right() - 2 * lower, r.bottom() - 2 * lower, 2 * lower, 2 * lower), 0, -90);
	path.lineTo(r.left() + lower, r.bottom());
	path.arcTo(QRectF(r.left(), r.bottom() - 2 * lower, 2 * lower, 2 * lower), 270, -90);
	path.lineTo(r.left(), r.top() + upper);
	path.arcTo(QRectF(r.left(), r.top(), 2 * upper, 2 * upper), 180, -90);
	path.closeSubpath();
	return path;
}

QImage ItemTileMask(
		QSize size,
		bool first,
		bool last) {
	const auto ratio = style::DevicePixelRatio();
	auto result = QImage(size * ratio, QImage::Format_ARGB32_Premultiplied);
	result.setDevicePixelRatio(ratio);
	result.fill(Qt::transparent);
	{
		auto p = QPainter(&result);
		auto hq = PainterHighQualityEnabler(p);
		p.setPen(Qt::NoPen);
		p.setBrush(Qt::white);
		p.drawPath(ItemTilePath(size.width(), size.height(), first, last));
	}
	return result;
}

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
	const auto path = ItemTilePath(width, height, first, last);
	p.fillRect(0, 0, width, height, st.itemBg);
	auto hq = PainterHighQualityEnabler(p);
	p.fillPath(path, anim::color(st.itemBg->c, st::windowFg->c, 0.06));
	if (selected) {
		p.fillPath(path, st.itemBgOver);
	}
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
