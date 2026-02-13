#include "RangeTableModel.h"

RangeTableModel::RangeTableModel(QObject *parent)
    : QAbstractTableModel(parent), manager_(std::make_unique<RangeManager>()),
      clusterData_(13, std::vector<ClusterData>(13)) {
    generateNewRange();
}

int RangeTableModel::rowCount(const QModelIndex &) const { return 13; }
int RangeTableModel::columnCount(const QModelIndex &) const { return 13; }

void RangeTableModel::generateNewRange() {
    manager_->generate();
    updateClusterData();
    emit dataChanged(index(0, 0), index(12, 12), {Qt::DisplayRole, Qt::UserRole});
}

void RangeTableModel::updateClusterData() {
    const auto &clusters = manager_->getClusters();
    const auto &range = manager_->getRange();

    for (int row = 0; row < 13; ++row) {
        for (int col = 0; col < 13; ++col) {
            int idx = row * 13 + col;
            if (idx < clusters.size()) {
                const auto &cluster = clusters[idx];
                float fold, check, bet;
                cluster.getAverageStrategy(range, fold, check, bet); // среднее значеине
                clusterData_[row][col] = {QString::fromStdString(cluster.getName()), fold, check,
                                          bet, cluster.getHandCount()};
            }
        }
    }
}

QVariant RangeTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();
    if (role == Qt::DisplayRole) {
        return clusterData_[row][col].name;
    } else if (role == Qt::UserRole) {
        QVariant v;
        v.setValue(clusterData_[row][col]);
        return v;
    } else if (role == Qt::ToolTipRole) {
        const auto &data = clusterData_[row][col];
        return QString("%1\n Fold:%2%\n Check:%3%\n Bet:%4%\n Hands: %5")
            .arg(data.name)
            .arg(data.fold * 100, 0, 'f', 1)
            .arg(data.check * 100, 0, 'f', 1)
            .arg(data.bet * 100, 0, 'f', 1)
            .arg(data.handCount);
    }
    return QVariant();
}
