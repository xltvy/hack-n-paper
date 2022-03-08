#include <string>

#ifndef CMPE250_PROJECT_2_HACKER_H
#define CMPE250_PROJECT_2_HACKER_H

class Hacker {

public:

    int id;
    int numOfGifts = 0;
    int numOfCodeCommits = 0;
    int totalValidCommits = 0;
    int invalidEntries = 0;
    float queueEnter = 0;
    float totalStickerTime = 0;
    float totalHoodieTime = 0;
    float turnaroundTime = 0;

    Hacker(int _id);
    Hacker(const Hacker& hacker);
    Hacker& operator=(const Hacker& hacker);

};

struct CompareHacker {
    bool operator()(const Hacker* hacker1, const Hacker* hacker2) {
        if (hacker1->totalValidCommits == hacker2->totalValidCommits) {
            if (abs(hacker1->queueEnter - hacker2->queueEnter) < 0.00001) {
                return hacker1->id > hacker2->id;
            }
            return (hacker1->queueEnter - hacker2->queueEnter) > 0.00001;
        }
        return hacker1->totalValidCommits < hacker2->totalValidCommits;
    }
};

#endif