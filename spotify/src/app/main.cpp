#include "main_window.h"
#include "src/ui/views/login/welcome.h"
#include "src/ui/views/admin/adminwindow.h"
#include "src/core/Database/databasemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DatabaseManager::instance()->openDatabase("/path")) {
        return -1;
    }
     Welcome w;
  //  AdminWindow w;
 //   NewAccount w;
    w.show();
    return a.exec();
}
