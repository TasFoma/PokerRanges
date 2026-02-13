#ifndef RANGE_TABLE_MODEL_H
#define RANGE_TABLE_MODEL_H

#include "range/RangeManager.h"

#include <QAbstractTableModel>
#include <QColor>
#include <memory>
#include <vector>

class RangeTableModel : public QAbstractTableModel {
    Q_OBJECT
  public:
    struct ClusterData {
        QString name;
        float fold;
        float check;
        float bet;
        int handCount;
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    explicit RangeTableModel(QObject *parent = nullptr);
    void generateNewRange();

  private:
    std::unique_ptr<RangeManager> manager_;
    std::vector<std::vector<ClusterData>> clusterData_;

    void updateClusterData();
};

Q_DECLARE_METATYPE(RangeTableModel::ClusterData) // регистрируем структуру для QVariant

#endif // RANGE_TABLE_MODEL_H
