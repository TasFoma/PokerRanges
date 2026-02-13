#ifndef RANGE_WIDGET_H
#define RANGE_WIDGET_H

#include <QPushButton>
#include <QTableView>
#include <QWidget>

class RangeTableModel;
class RangeItemDelegate;

class RangeWidget : public QWidget {
    Q_OBJECT
  public:
    explicit RangeWidget(QWidget *parent = nullptr);
  private slots:
    void onGenerateClicked();

  private:
    QTableView *tableView_;
    RangeTableModel *model_;
    RangeItemDelegate *delegate_;
    QPushButton *generateButton_;
};

#endif // RANGE_WIDGET_H
