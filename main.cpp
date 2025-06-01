#include <QApplication>
#include <QPushButton>
#include "src/service/Service.h"
#include "src/gui/MainWindow.h"

//#include "QTGUI.h"
int main(int argc, char *argv[]) {
    /*Service service;
     UI ui(service);
     ui.run();
     QApplication a(argc, argv);
     QPushButton button("Hello world!", nullptr);
     button.resize(200, 100);
     button.show();
     return QApplication::exec();*/

     QApplication app(argc, argv);
      Service service;
      MainWindow w(service);
      w.show();
      return app.exec();
   /* QApplication app(argc, argv);
    QTGUI window;
    window.show();
    return app.exec();
*/



}