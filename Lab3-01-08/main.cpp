#include "dialog.h"

#include <QApplication>
#include <bignum.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
