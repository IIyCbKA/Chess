#ifndef HISTORYTABLE_HPP
#define HISTORYTABLE_HPP

#include <QTableView>

class HistoryTable : public QTableView {
public:
  explicit HistoryTable(QFrame *parent = nullptr) : QTableView(parent) {}
  ~HistoryTable() override = default;
};

#endif
