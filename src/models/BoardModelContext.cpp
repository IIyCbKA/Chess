#include <models/BoardModelContext.hpp>
#include <models/BoardModel.hpp>

bool BoardModelContext::isOccupied(const Position pos) const {
  return this->model.getPiece(pos) != nullptr;
}


bool BoardModelContext::isUnderAttack(const Position pos) const {
  return this->model.isUnderAttack(pos);
}


const Piece* BoardModelContext::getPieceAt(const Position pos) const {
  return this->model.getPiece(pos);
}
