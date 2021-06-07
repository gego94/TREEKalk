#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Gview *m=new Gview();

    m->show();
    cout << " tutto ok " << endl ;

    return app.exec();
}
