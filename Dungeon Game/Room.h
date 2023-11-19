#pragma once
#include <string>
#include "Monster.h"
using namespace std;


class Room
{
public:
    Room(const string& title, const string& description,
        Room* North, Room* South, Room* East, Room* West, Monster* roomMonster,
        int skillReq, const string& skillType): title(title), description(description),
        North(North), South(South),
        East(East), West(West), roomMonster(roomMonster), skillReq(skillReq),
        skillType(skillType) {};
    void RenderRoom() {
        cout << endl;
        cout << description << endl;
    }
    Room* North;
    Room* South;
    Room* East;
    Room* West;
    Monster* roomMonster;

private:
    string title;
    string description;  
    string skillType;
    int skillReq;
};
