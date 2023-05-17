#pragma once
#include <string>
using namespace std;

namespace ariel
{
    class Point
    {
        double x_p;
        double y_p;

    public:
        Point();
        Point(double x_p, double y_p); // constructor
        Point(Point *other);           // deep copy constructor
        double distance(Point other);  // calcute the distance between two points
        string print();                // prints (x,y)
        static Point moveTowards(Point src, Point dst, double dis);
        double getX(); // returns x_p
        double getY(); // return y_p
    };

}