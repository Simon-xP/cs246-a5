#ifndef _TILE_H_
#define _TILE_H_
#include "constants.h"
#include "obs.h"
#include "../Visuals/screen.h"
#include <memory>

class PlayerData;

class Dice: public Subject{
    std::vector <Observer*> observers;
    public:
        int val;
        void attach(Observer* o);
        int getStateD() const override {
            return val;
        }
        Hand getStateC() const override { return Hand{}; };
        Producer getStateT() const override { return Producer{}; };
        void notifyObservers();
        void setValue(int num, PlayerData* p, controller* cont);
        ~Dice() override;
};

class Tile: public Observer, public Subject{
    std::vector <Observer*> observers;
    enum tiles{NETFLIX, STUDY, LECTURE, TUTORIAL, LAB, CAFFEINE};
    public:
        int pos;
        int dieVal = -1;
        bool goosed = false;
        Producer res;
        Dice* subject;
        void notifyObservers();
        void notify() override;
        void attach(Observer*);
        Producer getStateT() const override{
            if (!goosed) {
            return res;
            } else {
                return Producer{Resource::UM, 1};
            }
        }
        void stealify();
        int getStateD() const override { return 0; };
        Hand getStateC() const override { return Hand{}; };
        ~Tile() override;
        Tile(Dice* subject);
};

#endif
