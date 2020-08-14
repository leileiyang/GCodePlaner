#include "gcodeplaner.h"
#include <QApplication>

#include <iostream>
#include "neomath/neomath.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GCodePlaner w;
    //GCodeLine line = {{10, 0}, {10, 10}};
    //GCodeCircle circle = {{2,0}, 3};
    //GCodeArc arc = {{0, 4}, {4,0}, {0, 0}, 4};
    //Point_2D point = IntersectPoint(arc, circle);
    //Point_2D p0 = { 530.12, 482.60};
    //Point_2D p1 = { 399.34, 962.60};
    //Point_2D p2 = { 850, 366.05};
    //Point_2D p3 = VerticalIntersection(p0, p1, p2);
    //std::cout << "x: " << p3.x << " y: " << p3.y << std::endl;

    //Point_2D s = { 25.57179, 60.37957 };
    //Point_2D e = { 31.53919, 57.14526 };
    //Point_2D o = { 30.84456, 62.98583 };
    //Point_2D d = { 25.5066, 60.6572 };
    //double ang1 = SpanCenterAngle(s, e, o, 0);
    //double ang2 = SpanCenterAngle(s, d, o, 0);
    //double ratio = ang2 / ang1;
    //std::cout << ratio << std::endl;

    w.show();

    return a.exec();
}
