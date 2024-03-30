#ifndef PATIENT_H
#define PATIENT_H

#include "src/pedestrian/Pedestrian.h"
#include "src/walkability/Walkability.h"

class Patient : public Pedestrian {
private:
    Walkability walkability;
};

#endif