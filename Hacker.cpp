#include "Hacker.h"

//Constructor
Hacker::Hacker(int _id) {
    this->id = _id;
    this->numOfCodeCommits = 0;
    this->numOfGifts = 0;
}

//Copy constructor
Hacker::Hacker(const Hacker& hacker) {
    this->id = hacker.id;
    this->numOfCodeCommits = hacker.numOfCodeCommits;
    this->numOfGifts = hacker.numOfGifts;
    this->totalValidCommits = hacker.totalValidCommits;
    this->invalidEntries = hacker.invalidEntries;
    this->turnaroundTime = hacker.turnaroundTime;
    this->queueEnter = hacker.queueEnter;
    this->totalStickerTime = hacker.totalStickerTime;
    this->totalHoodieTime = hacker.totalHoodieTime;
}

//Assignment operator
Hacker& Hacker::operator=(const Hacker& hacker) {
    if (this == &hacker) {
        return *this;
    }

    this->id = hacker.id;
    this->numOfCodeCommits = hacker.numOfCodeCommits;
    this->numOfGifts = hacker.numOfGifts;
    this->totalValidCommits = hacker.totalValidCommits;
    this->invalidEntries = hacker.invalidEntries;
    this->turnaroundTime = hacker.turnaroundTime;
    this->queueEnter = hacker.queueEnter;
    this->totalStickerTime = hacker.totalStickerTime;
    this->totalHoodieTime = hacker.totalHoodieTime;

    return *this;
}