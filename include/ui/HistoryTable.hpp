#ifndef HISTORYTABLE_HPP
#define HISTORYTABLE_HPP

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

  static QString moveToStr(Position from, Position to);
  void addWhiteMove(Position from, Position to);
  void addBlackMove(Position from, Position to);
  void updateHighlighted(QStandardItem* newItem);
  void cleanTable();

  ~HistoryTable() override = default;
};

#endif
