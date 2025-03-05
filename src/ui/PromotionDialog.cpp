#include <ui/PromotionDialog.hpp>

PromotionDialog::PromotionDialog(
  const PiecesConstants::PIECE_COLORS color, QWidget* parent):
  QDialog(parent), ui(), pieceColor(color)
{
  this->ui.setupUi(this);
  initPiecesIcons();
  connect(
    this->ui.Queen, &QPushButton::clicked,
    this, &PromotionDialog::onQueenClicked
  );
  connect(
    this->ui.Rook, &QPushButton::clicked,
    this, &PromotionDialog::onRookClicked
  );
  connect(
    this->ui.Knight, &QPushButton::clicked,
    this, &PromotionDialog::onKnightClicked
  );
  connect(
    this->ui.Bishop, &QPushButton::clicked,
    this, &PromotionDialog::onBishopClicked
  );
}


void PromotionDialog::initPiecesIcons() const {
  setIcon(this->ui.Queen,  ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::QUEEN]);
  setIcon(this->ui.Rook,   ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::ROOK]);
  setIcon(this->ui.Knight, ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::KNIGHT]);
  setIcon(this->ui.Bishop, ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::BISHOP]);
}


void PromotionDialog::setIcon(QPushButton* button, const QString& iconPath) {
  const auto icon = QIcon(iconPath);
  button->setIcon(icon);
  button->setIconSize(QSize(
    ConstantsUI::DIALOG_BTN_ICON_WIDTH,
    ConstantsUI::DIALOG_BTN_ICON_HEIGHT
  ));
}


void PromotionDialog::onQueenClicked() {
  this->selectedType = PiecesConstants::PIECE_TYPES::QUEEN;
  accept();
}


void PromotionDialog::onRookClicked() {
  this->selectedType = PiecesConstants::PIECE_TYPES::ROOK;
  accept();
}


void PromotionDialog::onKnightClicked() {
  this->selectedType = PiecesConstants::PIECE_TYPES::KNIGHT;
  accept();
}


void PromotionDialog::onBishopClicked() {
  this->selectedType = PiecesConstants::PIECE_TYPES::BISHOP;
  accept();
}