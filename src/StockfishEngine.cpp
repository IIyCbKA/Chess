#include <constants.hpp>
#include <StockfishEngine.hpp>

#include <QCoreApplication>
#include <QDebug>
#include <QFile>

StockfishEngine::StockfishEngine(QObject* parent)
  : QObject(parent), depth(StockfishConstants::EASY_DEPTH)
{
  connect(
    &this->engineProcess, &QProcess::readyReadStandardOutput,
    this, &StockfishEngine::readOutput
  );
  start();
}


void StockfishEngine::start() {
  const QString enginePath = QCoreApplication::applicationDirPath() +
    ResourcesConstants::STOCKFISH_PATH_IN_BUILD;
  this->engineProcess.start(enginePath);
  if (!this->engineProcess.waitForStarted()) {
    qWarning() << StockfishConstants::STOCKFISH_ERROR;
  }
}


void StockfishEngine::setPosition(const QString& fen) {
  const QString cmd = QString(StockfishConstants::SET_POSITION_MASK).arg(fen);
  this->engineProcess.write(cmd.toUtf8());
}


void StockfishEngine::calculateBestMove() {
  const QString cmd = QString(StockfishConstants::CALCULATE_MOVE_MASK).arg(this->depth);
  this->engineProcess.write(cmd.toUtf8());
}


void StockfishEngine::readOutput() {
  while (this->engineProcess.canReadLine()) {
    QString line = this->engineProcess.readLine().trimmed();
    qDebug() << StockfishConstants::DEBUG_TITLE << line;
    if (line.startsWith(StockfishConstants::BESTMOVE_LINE_START)) {
      QStringList tokens = line.split(StockfishConstants::BESTMOVE_SEPARATOR);
      if (tokens.size() >= StockfishConstants::MIN_VALID_BESTMOVE_TOKENS) {
        const QString& bestMove = tokens[StockfishConstants::BESTMOVE_TOKEN_IND];
        emit bestMoveReady(bestMove);
      }
    }
  }
}