#ifndef STOCKFISHENGINE_HPP
#define STOCKFISHENGINE_HPP

#include <QObject>
#include <QProcess>

class StockfishEngine final : public QObject {
  Q_OBJECT
  QProcess engineProcess;
  size_t depth;

public:
  explicit StockfishEngine(QObject* parent = nullptr);

  void start();
  void calculateBestMove();
  void setPosition(const QString& fen);
  void updateDepth(const size_t depth) { this->depth = depth; }

signals:
  void bestMoveReady(const QString& move);

private slots:
  void readOutput();
};

#endif //STOCKFISHENGINE_HPP
