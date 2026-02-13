#include "RangeItemDelegate.h"
#include "RangeTableModel.h"

namespace {
constexpr int CELL_WIDTH = 100;
constexpr int CELL_HEIGHT = 58;
}

RangeItemDelegate::RangeItemDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void RangeItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const {
    painter->save();

    painter->fillRect(option.rect, Qt::white);
    auto data = index.data(Qt::UserRole).value<RangeTableModel::ClusterData>();
    QRect rect = option.rect;
    drawHorizontalBar(painter, rect, data.fold, data.check, data.bet);
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial", 11, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, data.name);

    if (data.handCount > 0) {
        painter->setFont(QFont("Arial", 8));
        painter->setPen(Qt::darkGray);
        painter->drawText(rect, Qt::AlignRight | Qt::AlignBottom, QString::number(data.handCount));
    }

    painter->restore();
}

void RangeItemDelegate::drawHorizontalBar(QPainter *painter, const QRect &rect, float fold,
                                          float check, float bet) const {
    if (fold + check + bet == 0)
        return;

    int totalWidth = rect.width();
    int foldWidth = static_cast<int>(totalWidth * fold);
    int checkWidth = static_cast<int>(totalWidth * check);

    int y = rect.y();
    int height = rect.height();

    if (foldWidth > 0)
        painter->fillRect(rect.x(), y, foldWidth, height, QColor(255, 147, 144));
    if (checkWidth > 0)
        painter->fillRect(rect.x() + foldWidth, y, checkWidth, height, QColor(130, 125, 200));
    if (foldWidth + checkWidth < totalWidth)
        painter->fillRect(rect.x() + foldWidth + checkWidth, y, totalWidth - foldWidth - checkWidth,
                          height, QColor(122, 216, 128));

    painter->setPen(Qt::black);
    painter->drawRect(rect);
}

QSize RangeItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {
    return QSize(CELL_WIDTH, CELL_HEIGHT);
}
