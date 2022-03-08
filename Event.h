#include <string>

using namespace std;

#ifndef CMPE250_PROJECT_2_EVENT_H
#define CMPE250_PROJECT_2_EVENT_H

class Event {

public:

    int hackerID;
    int codeCommit = -1;
    int whichDesk = -1;
    float timeStamp;
    string type;

    Event(int _hackerID, float _timeStamp, string _type);
    Event(const Event& event);
    Event& operator=(const Event& event);

};

struct Compare {
    bool operator()(const Event* event1, const Event* event2) {
        if (event1->timeStamp == event2->timeStamp) {
            return event1->hackerID > event2->hackerID;
        }
        return event1->timeStamp > event2->timeStamp;
    }
};

#endif //CMPE250_PROJECT_2_EVENT_H