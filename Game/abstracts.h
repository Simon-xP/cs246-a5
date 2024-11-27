#ifndef _ABSTRACT_H_
#define _ABSTRACT_H_
#include <vector>
#include <string>
#include <random>
#include "constants.h"
#include "obs.h"
#include <memory>
#include "../Visuals/screen.h"


class Goal;
class Criteria;
class Dice;
class PlayerData;
class Player;
class Board;
class Tile;
class controller;

class Goose { 
    public:
        Tile* tile;
        void move(Tile* target);
        ~Goose();
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
    std::shared_ptr<Player> players[4];
    std::shared_ptr<PlayerData> data[4];
    std::vector <std::shared_ptr<Goal>> goals;
    std::vector <std::shared_ptr<Criteria>> criterions;
    std::vector <std::shared_ptr<Tile>> tiles;
    std::shared_ptr<Dice> dice;
    std::mt19937* gen;
    std::shared_ptr<Goose> goose;
    void saveBoard(std::string filename, controller* cont);
    ~Board();
 
};
void display(Board* b);
void run_turn (Board* b, controller* cont);
std::shared_ptr<Board> generateBoard(std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen);
std::shared_ptr<Board> loadBoard(std::string info, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen);
std::shared_ptr<Board> openFile(std::string filename, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen);
std::shared_ptr<Board> loadGameState(std::string info, std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen);

class PlayerData{
    public:
        std::unique_ptr<Hand> hand = std::make_unique<Hand>();
        int points = 0;
        std::vector <Criteria*> corners;
        std::vector <Goal*> edges;
        Board* b;
        std::vector <std::shared_ptr<Observer>> eyes;
        bool can_steal = false;
        bool loaded_dice = false;
        void gain(Hand h);
        void goosefy(controller* cont);
        void roll(Dice* d, controller* cont);
        void turn(controller* cont);
        void writedata();
        void Discard();
        void Trade(controller* cont);
        ~PlayerData();
        Tile* selectTargetTile(controller* cont);
        PlayerData* selectPlayerToStealFrom(const std::vector<PlayerData*>& options, controller* cont);
        void executeTrade(PlayerData* selectedPlayer, Hand* hand1, Hand* hand2);
        bool hasResourcesForTrade(const Hand* selectedHand);
        int getAmountResource(Resource r) const;
        void detach(Goal *o);
        void detach(Criteria *o);
        void detach(Observer *o);
        friend std::ostream& operator<<(std::ostream& os, const PlayerData& player);
};

class Object {
    public:
        Hand cost;
        PlayerData* owner;
        virtual bool buy(PlayerData* p) = 0;
};



std::vector<Resource> getTileOrder(std::mt19937 *gen);
std::shared_ptr<Board> generateBoard(std::string name, std::shared_ptr<Player> players[4], std::mt19937* gen);
void firstTurn(Board* board, controller* cont);

#endif
