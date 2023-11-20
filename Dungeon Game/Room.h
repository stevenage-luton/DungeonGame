#pragma once
#include <string>
#include "Monster.h"
using namespace std;


class Room
{
public:
    Room(const string& title, 
        const string& description,
        Room* North,
        Room* South,
        Room* East,
        Room* West,
        Monster* roomMonster,
        int skillReq,
        const string& skillType,
        const string& successMessage,
        const string& failMessage,
        const string& rewardType,
        const string& skillPrompt): 
        title(title),
        description(description),
        North(North),
        South(South),
        East(East),
        West(West),
        roomMonster(roomMonster),
        skillReq(skillReq),
        skillType(skillType),
        successMessage(successMessage),
        failMessage(failMessage),
        rewardType(rewardType),
        skillPrompt(skillPrompt) {};
    void RenderRoom() {
        cout << endl;
        cout << description << endl;
    }
    string getTitle() {
        return title;
    }
    string getSuccessMessage() {
        return successMessage;
    };
    string getFailMessage() {
        return failMessage;
    };
    string getRewardType() {
        return rewardType;
    }
    string getPrompt() {
        return skillPrompt;
    }
    Room* North;
    Room* South;
    Room* East;
    Room* West;
    Monster* roomMonster;
    string skillType;
    int skillReq;
    bool attempted = false;

private:
    string title;
    string description;  
    string skillPrompt;
    string successMessage;
    string failMessage;
    string rewardType;
};