#include "abstracts.h"
#include "constants.h"
#include "tile.h"
#include <algorithm>


class tileobs: public Observer{
        Tile* subject;
        Criteria* owner;
    public:
        tileobs(Tile* subject);
        ~tileobs();
        void notify() override;
};

class Criteria: public Object, public Subject{
    std::vector <Observer*> observers;
    Hand COSTS[3] = {Hand{std::vector <Resource> {Resource::CAFF, Resource::TUT, Resource::LEC, Resource::LAB}}, 
    Hand{std::vector <Resource> {Resource::STD, Resource::LEC, Resource::LEC,Resource::STD,Resource::STD}},
    Hand{std::vector <Resource> {Resource::CAFF,Resource::CAFF,Resource::CAFF,Resource::LAB, Resource::LAB,Resource::LEC,Resource::LEC, Resource::TUT, Resource::STD, Resource::STD}}};
    protected:
        int greed = 0;
        Producer last;
    public:
        std::vector <Observer*> eyes;
        std::vector <Criteria*> neighbours;
        std::vector <Goal*> ajacent;
        std::vector <Tile*> tiles;
        void attach(Observer* o);
        void notifyObservers();
        void gain(Producer r);
        Hand getStateC() const override;
        int getStateD() const override { return 0; };
        Producer getStateT() const override { return Producer{}; };
        void buy(PlayerData* p) override;
};

class courseobs: public Observer{
    Criteria* subject;
    PlayerData* owner;
    public:
        courseobs(Criteria* subject, PlayerData* p);
        ~courseobs();
        void notify() override;
};

class Goal: public Object{
    public:
        Hand cost = {std::vector <Resource> {Resource::STD, Resource::TUT}};
        std::vector <Object*> ajacent;
        void buy(PlayerData* p) override;
};

