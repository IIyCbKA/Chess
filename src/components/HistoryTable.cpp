#include <components/HistoryTable.hpp>
#include <utils/utils.hpp>
#include <constants.hpp>

HistoryTable::HistoryTable(QWidget *parent) : QTableView(parent) {
  this->model = new QStandardItemModel(0, 3, this);
  this->setFont(ConstantsUI::FONT_TEXT);

  this->model->setHorizontalHeaderLabels({
    ConstantsUI::FIRST_HISTORY_TITLE,
    ConstantsUI::SECOND_HISTORY_TITLE,
    ConstantsUI::THIRD_HISTORY_TITLE
  });

  QTableView::setModel(this->model);

  verticalHeader()->setVisible(false);
  this->horizontalHeader()->setSectionResizeMode(
    ConstantsUI::HISTORY_TABLE_COLS::NUMBER_OF_PAIR,
    QHeaderView::Fixed
  );
  this->horizontalHeader()->setSectionResizeMode(
    ConstantsUI::HISTORY_TABLE_COLS::WHITE_MOVE,
    QHeaderView::Stretch
  );
  this->horizontalHeader()->setSectionResizeMode(
    ConstantsUI::HISTORY_TABLE_COLS::BLACK_MOVE,
    QHeaderView::Stretch
  );
  this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  setColumnWidth(0, 64);

  this->setSelectionMode(QAbstractItemView::NoSelection);
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->setFocusPolicy(Qt::NoFocus);
}


void HistoryTable::updateHighlighted(QStandardItem* newItem) {
  if (this->highlightedItem) this->highlightedItem->setBackground(QBrush());

  this->highlightedItem = newItem;
  this->highlightedItem->setBackground(Colors::MIDNIGHT);
}


QString HistoryTable::moveToStr(const Position from, const Position to) {
  return QString("%1%2%3%4")
    .arg(getChar(from.col))
    .arg(BoardConstants::SQUARES_ROWS_COLS - from.row)
    .arg(getChar(to.col))
    .arg(BoardConstants::SQUARES_ROWS_COLS - to.row);
}


void HistoryTable::addWhiteMove(const Position from, const Position to) {
  using namespace ConstantsUI;

  const int row = this->model->rowCount();
  this->model->insertRow(row);

  auto *itemNumber = new QStandardItem(QString::number(row + 1));
  itemNumber->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::NUMBER_OF_PAIR, itemNumber);

  auto *itemWhite = new QStandardItem(moveToStr(from, to));
  itemWhite->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::WHITE_MOVE, itemWhite);
  updateHighlighted(itemWhite);
}


void HistoryTable::addBlackMove(const Position from, const Position to) {
  using namespace ConstantsUI;

  const int row = this->model->rowCount() - 1;

  auto *itemBlack = new QStandardItem(moveToStr(from, to));
  itemBlack->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::BLACK_MOVE, itemBlack);
  updateHighlighted(itemBlack);
}


void HistoryTable::cleanTable() {
  this->model->setRowCount(0);
  this->highlightedItem = nullptr;
}
