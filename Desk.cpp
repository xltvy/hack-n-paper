#include "Desk.h"

//Constructor
Desk::Desk(int _id, float _serviceTime) {
    this->id = _id;
    this->serviceTime = _serviceTime;
}

//Copy constructor
Desk::Desk(const Desk &desk) {
    this->id = desk.id;
    this->serviceTime = desk.serviceTime;
    this->isOccupied = desk.isOccupied;
    this->occupierID = desk.occupierID;
    this->timeUntilFree = desk.timeUntilFree;
}

//Assignment operator
Desk& Desk::operator=(const Desk &desk) {
    if (this == &desk) {
        return *this;
    }

    this->id = desk.id;
    this->serviceTime = desk.serviceTime;
    this->isOccupied = desk.isOccupied;
    this->occupierID = desk.occupierID;
    this->timeUntilFree = desk.timeUntilFree;

    return *this;
}