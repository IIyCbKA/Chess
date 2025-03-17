#include <ui/PromotionDialog.hpp>

PromotionDialog::PromotionDialog(
  const PiecesConstants::PIECE_COLORS color, QWidget* parent)
  : QDialog(parent), ui(std::make_unique<Ui::PromotionDialog>()), pieceColor(color)
{
  this->ui->setupUi(this);
  initPiecesIcons();
  connect(
    this->ui->Queen, &QPushButton::clicked,
    this, [this]() -> void {
      this->selectedType = PiecesConstants::PIECE_TYPES::QUEEN;
      accept();
    }
  );
  connect(
    this->ui->Rook, &QPushButton::clicked,
    this, [this]() -> void {
      this->selectedType = PiecesConstants::PIECE_TYPES::ROOK;
      accept();
    }
  );
  connect(
    this->ui->Knight, &QPushButton::clicked,
    this, [this]() -> void {
      this->selectedType = PiecesConstants::PIECE_TYPES::KNIGHT;
      accept();
    }
  );
  connect(
    this->ui->Bishop, &QPushButton::clicked,
    this, [this]() -> void {
      this->selectedType = PiecesConstants::PIECE_TYPES::BISHOP;
      accept();
    }
  );
}


void PromotionDialog::initPiecesIcons() const {
  setIcon(this->ui->Queen,  ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::QUEEN]);
  setIcon(this->ui->Rook,   ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::ROOK]);
  setIcon(this->ui->Knight, ResourcesConstants::PIECES_PATHS[
    this->pieceColor][PiecesConstants::PIECE_TYPES::KNIGHT]);
  setIcon(this->ui->Bishop, ResourcesConstants::PIECES_PATHS[
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
