#ifndef WARD_H
#define WARD_H

#include "src/point/Point.h"
#include <string>

class Ward 
{
private:
    std::string name;
	Point *entry, *exit;
};

#endif