#ifndef PROMOTIONDIALOG_HPP
#define PROMOTIONDIALOG_HPP

#include <ui/ui_PromotionDialog.hpp>
#include <constants.hpp>

#include <memory>
#include <QDialog>
#include <QPushButton>
#include <QString>

class PromotionDialog final : public QDialog {
  std::unique_ptr<Ui::PromotionDialog> ui;
  PiecesConstants::PIECE_TYPES selectedType = QUEEN_TYPE;
  PiecesConstants::PIECE_COLORS pieceColor;

  static void setIcon(QPushButton* button, const QString& iconPath);
  void initPiecesIcons() const;

public:
  explicit PromotionDialog(PiecesConstants::PIECE_COLORS color, QWidget* parent = nullptr);
  [[nodiscard]] PiecesConstants::PIECE_TYPES getSelectedType() const { return this->selectedType; }

  ~PromotionDialog() override = default;
};

#endif //PROMOTIONDIALOG_HPP
