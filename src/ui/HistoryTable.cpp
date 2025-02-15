#include <ui/HistoryTable.hpp>
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


QString HistoryTable::moveToStr(const MoveLog &log) {
  QString result;
  if (log.isCastling) {
    if (log.isKingSide) result = ConstantsUI::HISTORY_KINGSIDE_CASTLING;
    else result = ConstantsUI::HISTORY_QUEENSIDE_CASTLING;
  } else {
    result = QString(ConstantsUI::HISTORY_DEFAULT_MASK)
    .arg(getChar(log.from.col))
    .arg(BoardConstants::SQUARES_ROWS_COLS - log.from.row)
    .arg(getChar(log.to.col))
    .arg(BoardConstants::SQUARES_ROWS_COLS - log.to.row);

    if (log.promotionType.has_value()) {
      result += getPieceTypeInStr(log.promotionType.value());
    }
  }

  return result;
}


void HistoryTable::addWhiteMove(const MoveLog &log) {
  using namespace ConstantsUI;

  const int row = this->model->rowCount();
  this->model->insertRow(row);

  auto *itemNumber = new QStandardItem(QString::number(row + 1));
  itemNumber->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::NUMBER_OF_PAIR, itemNumber);

  auto *itemWhite = new QStandardItem(moveToStr(log));
  itemWhite->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::WHITE_MOVE, itemWhite);
  updateHighlighted(itemWhite);
  this->scrollToBottom();
}


void HistoryTable::addBlackMove(const MoveLog &log) {
  using namespace ConstantsUI;

  const int row = this->model->rowCount() - 1;

  auto *itemBlack = new QStandardItem(moveToStr(log));
  itemBlack->setTextAlignment(Qt::AlignCenter);
  this->model->setItem(row, HISTORY_TABLE_COLS::BLACK_MOVE, itemBlack);
  updateHighlighted(itemBlack);
  this->scrollToBottom();
}


void HistoryTable::cleanTable() {
  this->model->setRowCount(0);
  this->highlightedItem = nullptr;
}


QString HistoryTable::getPieceTypeInStr(const PiecesConstants::PIECE_TYPES type) {
  switch (type) {
    case PiecesConstants::PIECE_TYPES::QUEEN:
      return ConstantsUI::HISTORY_PROMOTION_TO_QUEEN;
    case PiecesConstants::PIECE_TYPES::ROOK:
      return ConstantsUI::HISTORY_PROMOTION_TO_ROOK;
    case PiecesConstants::PIECE_TYPES::KNIGHT:
      return ConstantsUI::HISTORY_PROMOTION_TO_KNIGHT;
    case PiecesConstants::PIECE_TYPES::BISHOP:
      return ConstantsUI::HISTORY_PROMOTION_TO_BISHOP;
    default:
      return ConstantsUI::HISTORY_PROMOTION_TO_QUEEN;
  }
}
