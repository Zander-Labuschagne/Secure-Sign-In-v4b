#include "securesignin.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SecureSignIn w;
    w.show();

    return a.exec();
}
