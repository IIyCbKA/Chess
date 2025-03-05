#ifndef PROMOTIONDIALOG_HPP
#define PROMOTIONDIALOG_HPP

#include <ui/ui_PromotionDialog.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <QDialog>
#include <QPushButton>
#include <QString>

class PromotionDialog final : public QDialog {
  Q_OBJECT
  Ui::PromotionDialog ui;
  PiecesConstants::PIECE_TYPES selectedType = PiecesConstants::PIECE_TYPES::QUEEN;
  PiecesConstants::PIECE_COLORS pieceColor;

  static void setIcon(QPushButton* button, const QString& iconPath);
  void initPiecesIcons() const;

public:
  explicit PromotionDialog(PiecesConstants::PIECE_COLORS color, QWidget* parent = nullptr);
  [[nodiscard]] PiecesConstants::PIECE_TYPES getSelectedType() const { return this->selectedType; }

  ~PromotionDialog() override = default;

private slots:
  void onQueenClicked();
  void onRookClicked();
  void onKnightClicked();
  void onBishopClicked();
};

#endif //PROMOTIONDIALOG_HPP
