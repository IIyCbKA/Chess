#ifndef HISTORYTABLE_HPP
#define HISTORYTABLE_HPP

#include <utils/moveLog.hpp>

#include <QHeaderView>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>

class HistoryTable final : public QTableView {
  QStandardItemModel* model = nullptr;
  QStandardItem* highlightedItem = nullptr;

  static QString moveToStr(const MoveLog& log);
  void updateHighlighted(QStandardItem* newItem);

public:
  explicit HistoryTable(QWidget* parent = nullptr);

  void addWhiteMove(const MoveLog& log);
  void addBlackMove(const MoveLog& log);
  void cleanTable();

  ~HistoryTable() override = default;
};

#endif
