#include <string>

#ifndef CMPE250_PROJECT_2_DESK_H
#define CMPE250_PROJECT_2_DESK_H

class Desk {

public:

    int id;
    int occupierID = -1;
    float serviceTime;
    float timeUntilFree = 0;
    bool isOccupied = false;

    Desk(int _id, float _serviceTime);
    Desk(const Desk& desk);
    Desk& operator=(const Desk& desk);

};

#endif //CMPE250_PROJECT_2_DESK_H