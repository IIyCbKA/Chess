#include <constants.hpp>

QFont createFont(const int pointSize) {
  QFont font;
  font.setFamilies({QString::fromUtf8("Helvetica")});
  font.setPointSize(pointSize);
  font.setBold(true);

  return font;
}
