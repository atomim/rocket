#include "multitrackview.h"
#include "trackview.h"

#include <QApplication>
#include <QHBoxLayout>

MultiTrackView::MultiTrackView(QWidget *parent) :
	QWidget(parent),
	currRow(-1),
	currCol(-1)
{
	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(1);
	setLayout(layout);

	// HACK: add some data!
	for (int i = 0; i < 10; ++i) {
		TrackView *trackView = new TrackView;
		trackViews.append(trackView);
		layout->addWidget(trackView);
	}
	setCol(0);
	setRow(0);
}

QRect MultiTrackView::getCurrentTrackRect() const
{
	if (currCol < 0)
		return QRect(0, 0, 0, 0);

	Q_ASSERT(trackViews.size());
	return trackViews[currCol]->geometry();
}

void MultiTrackView::setRow(int row)
{
	if (!trackViews.size())
		return;

	row = qMax(row, 0);
	if (currRow != row) {
		Q_ASSERT(currCol >= 0 && currCol < trackViews.size());
		trackViews[currCol]->setRowHilight(row);
		currRow = row;
	} else
		QApplication::beep();
}

void MultiTrackView::setCol(int col)
{
	if (!trackViews.size())
		return;

	col = qMin(qMax(col, 0), trackViews.size() - 1);
	if (currCol != col) {
		trackViews[currCol]->setRowHilight(-1);
		trackViews[col]->setRowHilight(currRow);
		currCol = col;
	} else
		QApplication::beep();
}
