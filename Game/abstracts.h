#include <vector>
#include <string>
#include <random>
#include "constants.h"

class Goal;
class Criteria;
class Dice;
class PlayerData;
class Player;
class Board;
class Tile;

class Player{
    enum colors{BLUE, RED, GREEN, YELLOW} ;
    std::string Name;
    std::string password;
    public:
        Player(std::string name, std::string pass): Name{name}, password{pass}{}
};

struct Board {
    std::string name;
    int turn = 0;
    Player* players[4];
    PlayerData* data[4];
    std::vector <Goal*> goals;
    std::vector <Criteria*> criterions;
    std::vector <Tile*> tiles;
    Dice* dice;
    std::mt19937 *gen;
    Goose* goose;
};

void run_turn (Board* b);

class Observer {
 public:
  virtual void notify() = 0;
  virtual ~Observer() = default;
};

class PlayerData{
    public:
        Hand* hand = new Hand{};
        int points = 0;
        std::vector <Criteria* > corners;
        std::vector <Goal* > edges;
        Board* b;
        std::vector <Observer* > eyes;
        bool can_steal = false;
        void gain(Hand* h);
        void goosefy();
        void roll(Dice* d);
        void turn();
        void writedata();
        void Discard();
        void Trade();
};

class Object {
    public:
        Hand cost;
        PlayerData* owner;
        virtual ~Object();
        virtual void buy(PlayerData* p) = 0;
};

class Goose { 
    public:
        Tile* tile;
        void move(Tile* target){
            tile->goosed = false;
            target->goosed = true;
            tile = target;
        }
};

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers();
  virtual Producer getStateT() const = 0;
  virtual Hand getStateC() const = 0;
  virtual int getStateD() const = 0;
  virtual ~Subject() = default;
};
std::vector<Resource> *getTileOrder(std::mt19937 *gen);
Board* generateBoard(std::string name, Player* players[4], std::mt19937 *gen);