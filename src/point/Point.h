#ifndef POINT_H
#define POINT_H

class Point 
{
private:
    double x, y;
public:
    void setPoint(double x, double y);
    double getX() {return x;}
    double getY() {return y;}
};

#endif