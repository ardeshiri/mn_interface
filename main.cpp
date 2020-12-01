#include "mainwindow.h"

#include <QApplication>
#include "api_initializer.h"
#include "entering_signin_form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    API_initializer api_i{};

    entering_signin_form esf{};
    esf.exec();

    if(!esf.is_authorized())
        return 1;

    MainWindow w;
    w.show();
    return a.exec();
}
