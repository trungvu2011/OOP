#ifndef VISITOR_H
#define VISITOR_H

#include "src/walkability/Walkability.h"
#include "src/pedestrian/Pedestrian.h"

class Visitor : public Pedestrian {
private:
    Walkability walkability;
public:
    void setVisitor(Walkability walkability);
    Walkability getVisitor() {return walkability;}
};

#endif