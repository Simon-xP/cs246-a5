#ifndef _ABSTRACT_H_
#define _ABSTRACT_H_
#include <vector>
#include <string>
#include <random>
#include "constants.h"
#include "obs.h"
#include <memory>


class Goal;
class Criteria;
class Dice;
class PlayerData;
class Player;
class Board;
class Tile;

class Goose { 
    public:
        Tile* tile = nullptr;
        void move(Tile* target);
};

class Player{
    std::string password;
    public:
        char colors[4] = {'B', 'R', 'G', 'Y'} ;
        std::string Name;
        Player(std::string name, std::string pass): password{pass},  Name{name}{}
};

struct Board {
    std::string name;
    int turn = 0;
    Player* players[4];
    std::shared_ptr<PlayerData> data[4];
    std::vector <std::shared_ptr<Goal>> goals;
    std::vector <std::shared_ptr<Criteria>> criterions;
    std::vector <std::shared_ptr<Tile>> tiles;
    std::shared_ptr<Dice> dice;
    std::mt19937 *gen;
    std::shared_ptr<Goose> goose;
    ~Board();
 
};
void display(Board* b);
void run_turn (Board* b);



class PlayerData{
    public:
        std::unique_ptr<Hand> hand = std::make_unique<Hand>();
        int points = 0;
        std::vector <Criteria* > corners;
        std::vector <Goal* > edges;
        Board* b;
        std::vector <std::shared_ptr<Observer>> eyes;
        bool can_steal = false;
        void gain(Hand h);
        void goosefy();
        void roll(Dice* d);
        void turn();
        void writedata();
        void Discard();
        void Trade();
        ~PlayerData();
        Tile* selectTargetTile();
        PlayerData* selectPlayerToStealFrom(const std::vector<PlayerData*>& options);
        void executeTrade(PlayerData* selectedPlayer, Hand* hand1, Hand* hand2);
        bool hasResourcesForTrade(const Hand* selectedHand);
};

class Object {
    public:
        Hand cost;
        PlayerData* owner;
        virtual bool buy(PlayerData* p) = 0;
};



std::vector<Resource> getTileOrder(std::mt19937 *gen);
std::shared_ptr<Board> generateBoard(std::string name, Player* players[4], std::mt19937 *gen);
void firstTurn(Board* board);

#endif
