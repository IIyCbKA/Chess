#ifndef HISTORYTABLE_HPP
#define HISTORYTABLE_HPP

#include <utils/moveLog.hpp>
#include <utils/position.hpp>

#include <QHeaderView>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>

class HistoryTable : public QTableView {
  QStandardItemModel *model = nullptr;
  QStandardItem *highlightedItem = nullptr;

public:
  explicit HistoryTable(QWidget *parent = nullptr);

  static QString moveToStr(const MoveLog &log);
  void addWhiteMove(const MoveLog &log);
  void addBlackMove(const MoveLog &log);
  void updateHighlighted(QStandardItem* newItem);
  void cleanTable();

  ~HistoryTable() override = default;
};

#endif
