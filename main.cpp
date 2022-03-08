#include "Hacker.h"
#include "Event.h"
#include "Desk.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    //Stores the information about average commit length
    float avgCommitLength = 0;
    //Stores every operation given in the input
    vector<string> operations;
    string line;
    ifstream input(argv[1]);
    if (input.is_open()) {
        while (getline(input, line)) {
            operations.push_back(line);
        }
    }
    input.close();

    string arrival = operations.at(0);
    stringstream processHackers(arrival);

    int numOfHackers = 0;
    vector<Hacker*> hackers;
    processHackers >> numOfHackers;

    priority_queue<Event*, vector<Event*>, Compare> simulation;

    for (int i=0; i<numOfHackers; i++) {
        Hacker* h = new Hacker(i+1);
        hackers.push_back(h);
        float timeStamp = 0;
        processHackers >> timeStamp;
        Event* a = new Event(i+1, timeStamp, "ARRIVAL");
        simulation.push(a);
    }

    operations.erase(operations.begin());

    string totalCommits = operations.at(0);
    stringstream processTotalCommits(totalCommits);

    int numOfCommits = 0;
    processTotalCommits >> numOfCommits;

    operations.erase(operations.begin());

    for (int i=0; i<numOfCommits; i++) {

        string commitLine = operations.at(i);
        stringstream processCommitLine(commitLine);

        int hackerID = 0;
        int codeCommit = 0;
        float timeStamp = 0;
        processCommitLine >> hackerID;
        processCommitLine >> codeCommit;
        processCommitLine >> timeStamp;

        Event* c = new Event(hackerID, timeStamp, "CODE-COMMIT");
        c->codeCommit = codeCommit;
        simulation.push(c);

        avgCommitLength+=codeCommit;

    }

    operations.erase(operations.begin(), operations.begin()+numOfCommits);

    string totalQueueEntrances = operations.at(0);
    stringstream processTQE(totalQueueEntrances);

    int numOfTQE = 0;
    processTQE >> numOfTQE;

    operations.erase(operations.begin());

    for (int i=0; i<numOfTQE; i++) {

        string commitLine = operations.at(i);
        stringstream processCommitLine(commitLine);

        int hackerID = 0;
        float timeStamp = 0;
        processCommitLine >> hackerID;
        processCommitLine >> timeStamp;

        Event* q = new Event(hackerID, timeStamp, "QUEUE-ENTRANCE");
        simulation.push(q);

    }

    operations.erase(operations.begin(), operations.begin()+numOfTQE);

    string sDeskLine = operations.at(0);
    stringstream processSDL(sDeskLine);

    int numOfSDesks = 0;
    vector<Desk*> stickerDesks;
    processSDL >> numOfSDesks;

    for (int i=0; i<numOfSDesks; i++) {
        float serviceTime = 0;
        processSDL >> serviceTime;
        Desk* sd = new Desk(i+1, serviceTime);
        stickerDesks.push_back(sd);
    }

    operations.erase(operations.begin());

    string hDeskLine = operations.at(0);
    stringstream processHDL(hDeskLine);

    int numOfHDesks = 0;
    vector<Desk*> hoodieDesks;
    processHDL >> numOfHDesks;

    for (int i=0; i<numOfHDesks; i++) {
        float serviceTime = 0;
        processHDL >> serviceTime;
        Desk* hd = new Desk(i+1, serviceTime);
        hoodieDesks.push_back(hd);
    }

    operations.erase(operations.begin());

    int tempSQ = 0;
    int maxStickerQueue = 0;
    int tempHQ = 0;
    int maxHoodieQueue = 0;
    int totalGifts = 0;
    float avgCodeCommits = (float) numOfCommits/numOfHackers;
    avgCommitLength = avgCommitLength/numOfCommits;
    int invalidAttempts3Gifts = 0;
    float lastEvent = 0;

    float currentTime = 0;
    float previousTime = 0;
    queue<Hacker*> stickerQueue;
    priority_queue<Hacker*, vector<Hacker*>, CompareHacker> hoodieQueue;
    while (simulation.size()!=0) {

        Event* tempE = simulation.top();
        simulation.pop();
        currentTime = tempE->timeStamp;
        Hacker* tempH;

        for (int i=0; i<hackers.size(); i++) {
            if (hackers.at(i)->id==tempE->hackerID) {
                tempH = hackers.at(i);
                break;
            }
        }

        if (tempE->type == "CODE-COMMIT") {
            if (tempE->codeCommit >= 20) {
                tempH->totalValidCommits++;
            }
        }

        if (tempE->type == "QUEUE-ENTRANCE") {
            if (tempH->numOfGifts==3) {
                invalidAttempts3Gifts++;
            } else {
                if (tempH->totalValidCommits>=3) {

                    int empty_s_desk = -1;
                    for (int i=0; i<stickerDesks.size(); i++) {
                        if (!(stickerDesks.at(i)->isOccupied)) {
                            empty_s_desk = i;
                            break;
                        }
                    }

                    if (empty_s_desk>=0) {
                        stickerDesks.at(empty_s_desk)->isOccupied = true;
                        stickerDesks.at(empty_s_desk)->occupierID = tempH->id;
                        stickerDesks.at(empty_s_desk)->timeUntilFree = stickerDesks.at(empty_s_desk)->serviceTime;
                        Event* ls = new Event(tempH->id, currentTime+stickerDesks.at(empty_s_desk)->serviceTime, "LEAVE-STICKER-DESK");
                        ls->whichDesk = stickerDesks.at(empty_s_desk)->id;
                        simulation.push(ls);
                    } else {
                        stickerQueue.push(tempH);
                        tempH->queueEnter = currentTime;
                    }
                } else {
                    tempH->invalidEntries++;
                }
            }

        }

        if (tempE->type == "LEAVE-STICKER-DESK") {
            //The hacker at this sticker desk is served, and leaves the desk to get hoodie
            int idx1 = 0;
            for (int i=0; i<stickerDesks.size(); i++) {
                if (stickerDesks.at(i)->id == tempE->whichDesk) {
                    idx1 = i;
                    break;
                }
            }
            stickerDesks.at(idx1)->isOccupied = false;
            stickerDesks.at(idx1)->timeUntilFree = 0;
            stickerDesks.at(idx1)->occupierID = -1;
            tempH->turnaroundTime+=stickerDesks.at(idx1)->serviceTime;

            int empty_h_desk = -1;
            for (int i=0; i<hoodieDesks.size(); i++) {
                if (!(hoodieDesks.at(i)->isOccupied)) {
                    empty_h_desk = i;
                    break;
                }
            }
            //If there is an empty hoodie desk, the frontrunner of hoodie queue enters that empty hoodie desk
            if (empty_h_desk>=0) {
                hoodieDesks.at(empty_h_desk)->isOccupied = true;
                hoodieDesks.at(empty_h_desk)->occupierID = tempH->id;
                hoodieDesks.at(empty_h_desk)->timeUntilFree = hoodieDesks.at(empty_h_desk)->serviceTime;
                Event* lhd = new Event(tempH->id, currentTime+hoodieDesks.at(empty_h_desk)->serviceTime, "LEAVE-HOODIE-DESK");
                lhd->whichDesk = hoodieDesks.at(empty_h_desk)->id;
                simulation.push(lhd);
            } else {
                //Else enters the hoodie queue
                hoodieQueue.push(tempH);
                tempH->queueEnter = currentTime;
            }
            //After desk is empty, if there is someone in the sticker desk queue, they move to the desk
            if (stickerQueue.size()>0) {
                Hacker* temp = stickerQueue.front();
                stickerQueue.pop();

                stickerDesks.at(idx1)->isOccupied = true;
                stickerDesks.at(idx1)->occupierID = temp->id;
                stickerDesks.at(idx1)->timeUntilFree = stickerDesks.at(idx1)->serviceTime;
                temp->turnaroundTime+=(currentTime-temp->queueEnter);
                temp->totalStickerTime+=(currentTime-temp->queueEnter);
                temp->queueEnter=-1;
                //The event of them leaving the desk is created
                Event* ls1 = new Event(temp->id, currentTime+stickerDesks.at(idx1)->serviceTime, "LEAVE-STICKER-DESK");
                ls1->whichDesk = stickerDesks.at(idx1)->id;
                simulation.push(ls1);

                //Update the temp hacker
                for (int i=0; i<hackers.size(); i++) {
                    if (hackers.at(i)->id==temp->id) {
                        *hackers.at(i) = *temp;
                    }
                }
            }
            //If no one is in the sticker desk queue, nothing extra happens

        }
        if (tempE->type == "LEAVE-HOODIE-DESK") {
            //Finds the hoodie desk that will be empty in this event
            int idx2 = 0;
            for (int i=0; i<hoodieDesks.size(); i++) {
                if (hoodieDesks.at(i)->id == tempE->whichDesk) {
                    idx2 = i;
                    break;
                }
            }
            //That hoodie desk is free now
            hoodieDesks.at(idx2)->isOccupied = false;
            hoodieDesks.at(idx2)->timeUntilFree = 0;
            hoodieDesks.at(idx2)->occupierID = -1;
            tempH->turnaroundTime+=hoodieDesks.at(idx2)->serviceTime;
            tempH->numOfGifts++;
            //If someone waits in the hoodie desk queue, frontrunner of the queue moves to the now-empty hoodie desk
            if (hoodieQueue.size()>0) {

                Hacker* temp1 = hoodieQueue.top();
                hoodieQueue.pop();

                hoodieDesks.at(idx2)->isOccupied = true;
                hoodieDesks.at(idx2)->occupierID = temp1->id;
                hoodieDesks.at(idx2)->timeUntilFree = hoodieDesks.at(idx2)->serviceTime;
                temp1->turnaroundTime+=(currentTime-temp1->queueEnter);
                temp1->totalHoodieTime+=(currentTime-temp1->queueEnter);
                temp1->queueEnter=-1;

                Event* lh1 = new Event(temp1->id, currentTime+hoodieDesks.at(idx2)->serviceTime, "LEAVE-HOODIE-DESK");
                lh1->whichDesk = hoodieDesks.at(idx2)->id;
                simulation.push(lh1);

                //Update the temp hacker
                for (auto & hacker : hackers) {
                    if (hacker->id==temp1->id) {
                        *hacker = *temp1;
                    }
                }
            }

        }
        //Update the hacker
        for (auto & hacker : hackers) {
            if (hacker->id == tempH->id) {
                *hacker = *tempH;
                break;
            }
        }
        //Checks the size of the sticker queue after every event to find maximum length of the sticker queue
        tempSQ = stickerQueue.size();
        if (tempSQ > maxStickerQueue) {
            maxStickerQueue = tempSQ;
        }
        //Checks the size of the hoodie queue after every event to find maximum length of the hoodie queue
        tempHQ = hoodieQueue.size();
        if (tempHQ > maxHoodieQueue) {
            maxHoodieQueue = tempHQ;
        }
        //Updates the time
        previousTime = tempE->timeStamp;
        //Checks if the event is the last one or not
        if (simulation.size()==1) {
            lastEvent = simulation.top()->timeStamp;
        }
        //Deletes the event tempE that happened and will not be used in the simulation anymore
        delete tempE;
    }

    FILE* outputF;
    outputF = fopen(argv[2], "w");
    fprintf(outputF, "%d \n", maxStickerQueue);
    fprintf(outputF, "%d \n", maxHoodieQueue);

    float totalWaitedSticker = 0;
    float totalWaitedHoodie = 0;
    float totalTurnaroundTime = 0;
    int totalInvalid = 0;
    for (auto & hacker: hackers) {
        totalGifts+=hacker->numOfGifts;
        totalWaitedSticker+=hacker->totalStickerTime;
        totalWaitedHoodie+=hacker->totalHoodieTime;
        totalTurnaroundTime+=hacker->turnaroundTime;
        totalInvalid+=hacker->invalidEntries;
    }
    int spentMostID = 1;
    float fm = hackers.at(0)->totalHoodieTime+hackers.at(0)->totalStickerTime;
    for (auto & hacker: hackers) {
        if ((hacker->totalStickerTime+hacker->totalHoodieTime) - fm > 0.00001) {
            spentMostID = hacker->id;
            fm = hacker->totalStickerTime+hacker->totalHoodieTime;
        } else if (abs((hacker->totalStickerTime+hacker->totalHoodieTime) - fm) < 0.00001) {
            if (spentMostID > hacker->id) {
                spentMostID = hacker->id;
                fm = hacker->totalStickerTime+hacker->totalHoodieTime;
            }
        }
    }
    int spentLeastID = -1;
    float fl = -1;
    for (auto & hacker: hackers) {
        if (hacker->numOfGifts==3) {
            spentLeastID = hacker->id;
            fl = hacker->totalStickerTime+hacker->totalHoodieTime;
            break;
        }
    }
    if (spentLeastID>=0) {
        for (auto & hacker: hackers) {
            if (hacker->numOfGifts==3) {
                if (fl - (hacker->totalStickerTime+hacker->totalHoodieTime) > 0.00001) {
                    spentLeastID = hacker->id;
                    fl = hacker->totalStickerTime+hacker->totalHoodieTime;
                } else if (abs(fl - (hacker->totalStickerTime+hacker->totalHoodieTime)) < 0.00001) {
                    if (spentLeastID > hacker->id) {
                        spentLeastID = hacker->id;
                        fl = hacker->totalStickerTime+hacker->totalHoodieTime;
                    }
                }
            }
        }
    }

    fprintf(outputF, "%.3f \n", ((float) totalGifts/hackers.size()));
    fprintf(outputF, "%.3f \n", ((float) totalWaitedSticker/totalGifts));
    fprintf(outputF, "%.3f \n", ((float) totalWaitedHoodie/totalGifts));
    fprintf(outputF, "%.3f \n", (avgCodeCommits));
    fprintf(outputF, "%.3f \n", (avgCommitLength));
    fprintf(outputF, "%.3f \n", ((float) totalTurnaroundTime/totalGifts));
    fprintf(outputF, "%d \n", totalInvalid);
    fprintf(outputF, "%d \n", invalidAttempts3Gifts);
    fprintf(outputF, "%d %.3f \n", spentMostID, fm);
    fprintf(outputF, "%d %.3f \n", spentLeastID, fl);
    fprintf(outputF, "%.3f \n", lastEvent);

    //Delete operations to prevent memory leak
    for (auto & hacker : hackers) {
        delete hacker;
    }
    for (auto & stickerDesk : stickerDesks) {
        delete stickerDesk;
    }
    for (auto & hoodieDesk : hoodieDesks) {
        delete hoodieDesk;
    }

    return 0;
}