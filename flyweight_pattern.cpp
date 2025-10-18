#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Use Case: Flyweight Pattern is used to save memory by sharing common data among many objects, e.g., managing cricket players across multiple matches.
// Flyweight class - stores intrinsic (shared) attributes of a player
class PlayerFlyweight{
    string name;        // intrinsic attribute: player name
    string bowlingtype; // intrinsic attribute: bowling style
    string battingtype; // intrinsic attribute: batting style

public:
    // Constructor sets intrinsic attributes
    PlayerFlyweight(string name,string bowlingtype,string battingtype){
        this->name=name;
        this->bowlingtype=bowlingtype;
        this->battingtype=battingtype;
    }

    // Display method uses extrinsic attributes (unique per match)
    void display(int runs,int wickets){
        // runs and wickets change for every match → extrinsic attributes
        cout << name << " scored " << runs << " and took " << wickets << endl;
    }
};

// Factory class to manage and reuse PlayerFlyweight objects
class PlayerFactory{
    vector<PlayerFlyweight*> p;                      // optional list to keep track of players
    unordered_map<string,PlayerFlyweight*> mp;       // map for intrinsic attribute combination

public:
    PlayerFlyweight* getPlayer(string name,string bowlingtype,string battingtype){
        // Create a unique key based on intrinsic attributes
        string hash = name + '-' + bowlingtype + '-' + battingtype;

        // If player object for this combination doesn't exist, create it
        if(mp.find(hash) == mp.end()){
            PlayerFlyweight* player = new PlayerFlyweight(name, bowlingtype, battingtype);
            cout << "New object created" << endl;
            mp[hash] = player; // store in map for reuse
        }

        // Return existing object if already created
        return mp[hash];
    }
};

int main()
{
    PlayerFactory* pf = new PlayerFactory();

    // Creating two different players
    PlayerFlyweight* first = pf->getPlayer("Virat Kohli","Right arm medium","Right hand");
    PlayerFlyweight* second = pf->getPlayer("Umesh Yadav","Right arm fast","Right hand");

    // Extrinsic attributes (runs, wickets) passed externally
    first->display(40,0);
    second->display(0,4);

    // Reusing existing player object for Virat Kohli
    PlayerFlyweight* third = pf->getPlayer("Virat Kohli","Right arm medium","Right hand");

    return 0;
}

/*
Output:
New object created
New object created
Virat Kohli scored 40 and took 0
Umesh Yadav scored 0 and took 4

Impact of Flyweight:

Without Flyweight:
- Every time we need to reference a player, a new object would be created.
- Memory usage would grow with number of matches and repeated players.
- Example: 11 players x 1000 matches = 11,000 objects.

With Flyweight:
- Only unique player objects are created based on intrinsic attributes.
- Extrinsic attributes are passed separately per match.
- Memory usage is reduced significantly.
- Example: Only 11 unique player objects for 11 players, reused across matches.

*/
