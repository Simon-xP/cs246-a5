#ifndef _COURSE_H_
#define _COURSE_H_
#include "abstracts.h"
#include "constants.h"
#include "tile.h"
#include <algorithm>
#include "obs.h"
#include <memory>

class tileobs: public Observer{
        Tile* subject;  
    public:
        Criteria* owner;
        tileobs(Tile* subject);
        ~tileobs();
        void notify() override;
};

class Criteria: public Object, public Subject{
    std::vector <std::shared_ptr<Observer>> observers;
    Hand COSTS[3] = {Hand{std::vector <Resource> {Resource::CAFF, Resource::TUT, Resource::LEC, Resource::LAB}}, 
    Hand{std::vector <Resource> {Resource::STD, Resource::LEC, Resource::LEC,Resource::STD,Resource::STD}},
    Hand{std::vector <Resource> {Resource::CAFF,Resource::CAFF,Resource::CAFF,Resource::LAB, Resource::LAB,Resource::LEC,Resource::LEC, Resource::TUT, Resource::STD, Resource::STD}}};
    protected:
        int greed = 0;
        Producer last;
    public:
        std::vector <std::shared_ptr<Observer>> eyes;
        std::vector <Criteria*> neighbours;
        std::vector <Goal*> ajacent;
        std::vector <Tile*> tiles;
        void attach(Observer* o);
        void notifyObservers();
        void gain(Producer r);
        Hand getStateC() const override;
        int getStateD() const override { return 0; };
        Producer getStateT() const override { return Producer{}; };
        bool buy(PlayerData* p) override;
        bool buy_start(PlayerData* p);
        ~Criteria() override;
        int getgreed(){return greed;}
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
        std::vector <Goal*> ajacent1;
        std::vector <Criteria*> ajacent2;
        bool buy(PlayerData* p) override;
        bool buy_start(PlayerData* p);
};

#endif
