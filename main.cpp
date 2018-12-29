#include "gcodeplaner.h"
#include <QApplication>

#include <iostream>
#include "neomath/neomath.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GCodePlaner w;
    //GCodeLine line = {{10, 0}, {10, 10}};
    GCodeCircle circle = {{2,0}, 3};
    GCodeArc arc = {{0, 4}, {4,0}, {0, 0}, 4};
    Point_2D point = IntersectPoint(arc, circle);
    std::cout << "x: " << point.x << " y: " << point.y << std::endl;

    w.show();

    return a.exec();
}
