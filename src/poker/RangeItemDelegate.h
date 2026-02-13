#ifndef RANGE_ITEM_DELEGATE_H
#define RANGE_ITEM_DELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class RangeItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
  public:
    explicit RangeItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  private:
    void drawHorizontalBar(QPainter *painter, const QRect &rect, float fold, float check,
                           float bet) const;
};

#endif // RANGE_ITEM_DELEGATE_H
