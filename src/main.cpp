#include <ui/MainWindow.hpp>

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.init();
  window.show();

  return QApplication::exec();
}
