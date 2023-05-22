#include "Point.hpp"
#include <cmath>
#include <stdexcept>
using namespace std;

namespace ariel
{
    // empty constructor
    Point::Point()
    {
        this->x_p = 0.0;
        this->y_p = 0.0;
    }

    // constructor
    Point::Point(double x_p, double y_p)
    {
        this->x_p = x_p;
        this->y_p = y_p;
    }

    // deep copy constructor
    Point::Point(Point *other)
    {
        x_p = other->getX();
        y_p = other->getY();
    }

// calcute the distance between two points
    double Point::distance(Point other)
    {
        double x = pow((other.x_p - this->x_p), 2);
        double y = pow((other.y_p - this->y_p), 2);
        return sqrt(x + y);
    }

// prints (x,y)
    string Point::print()
    {
        return "(" + to_string(x_p) + "," + to_string(y_p) + ")";
    }

    //move to dst the range of dis and if dis is greater than the distance between src and dst than return dst
    Point Point::moveTowards(Point src, Point dst, double dis)
    {
        if (dis < 0)
        {
            throw std::invalid_argument("distance to move is lower than 0");
        }
        double distance = src.distance(dst);

        if (distance <= dis)
        {
            return dst;
        }
        double ratio = dis / distance;
        double newX = src.x_p + (dst.x_p - src.x_p) * ratio;
        double newY = src.y_p + (dst.y_p - src.y_p) * ratio;

        return Point(newX, newY);
    }

    // returns x_p
    double Point::getX()
    {
        return x_p;
    }

    // returns y_p
    double Point::getY()
    {
        return y_p;
    }

}