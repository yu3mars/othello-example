#include "search.hpp"
#include <tuple>
#include <utility>
#include "eval.hpp"

int search_eval(const Board &bd, const Turn &turn, int depth) {
  if (depth == 0) return eval(bd, turn);
  int max_score = -INF;
  for (int x = 1; x <= 8; ++x) {
    for (int y = 1; y <= 8; ++y) {
      if (movable(bd, turn, Position(x, y))) {
        Board next = move(bd, turn, Position(x, y));
        max_score = std::max(max_score, -search_eval(next, opponent(turn), depth-1));
      }
    }
  }
  if (max_score == -INF) {
    return -search_eval(bd, opponent(turn), depth-1);
  }
  return max_score;
}

Position search(const Board &bd, const Turn &turn) {
  int max_score = -INF;
  Position max_score_pos;
  for (int x = 1; x <= 8; ++x) {
    for (int y = 1; y <= 8; ++y) {
      if (movable(bd, turn, Position(x, y))) {
        Board next = move(bd, turn, Position(x, y));
        int score = -search_eval(next, opponent(turn), 3);
        if (score > max_score) {
          max_score = score;
          max_score_pos = Position(x, y);
        }
      }
    }
  }
  return max_score_pos;
}
