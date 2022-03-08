#include "Event.h"

//Constructor
Event::Event(int _hackerID, float _timeStamp, string _type) {
    this->hackerID = _hackerID;
    this->timeStamp = _timeStamp;
    this->type = _type;
}
//Copy constructor
Event::Event(const Event &event) {
    this->hackerID = event.hackerID;
    this->timeStamp = event.timeStamp;
    this->type = event.type;
    this->codeCommit = event.codeCommit;
    this->whichDesk = event.whichDesk;
}
//Assignment operator
Event& Event::operator=(const Event &event) {
    if (this == &event) {
        return *this;
    }

    this->hackerID = event.hackerID;
    this->timeStamp = event.timeStamp;
    this->type = event.type;
    this->codeCommit = event.codeCommit;
    this->whichDesk = event.whichDesk;

    return *this;
}