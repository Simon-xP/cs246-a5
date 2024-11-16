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
    Hand COSTS[3] = {Hand{}, Hand{}, Hand{}};
    protected:
        std::vector <Criteria*> neighbours;
        std::vector <Goal*> ajacent;
        std::vector <Tile*> tiles;
        int greed = 0;
        Producer last;
    public:
        void attach(Observer* o);
        void notifyObservers();
        void gain(Producer r);
        Hand getStateC() const override;
        void buy(PlayerData* p) override;
};

class courseobs: public Observer{
    Criteria* subject;
    PlayerData* owner;
    public:
        courseobs(Criteria* subject);
        ~courseobs();
        void notify() override;
};

class Goal: public Object{
    std::vector <Criteria*> ajacent;
    public:
        void buy(PlayerData* p) override;
};

