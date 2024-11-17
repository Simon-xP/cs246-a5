#include "constants.h"

class PlayerData;
class Observer;

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
        void setValue(int num, PlayerData* p);
};

class Tile: public Observer, public Subject{
    std::vector <Observer*> observers;
    enum tiles{NETFLIX, STUDY, LECTURE, TUTORIAL, LAB, CAFFEINE} ;
    protected:
        int dieVal;
        int pos;
    public:
        bool goosed;
        Producer res;
        Dice* subject;
        void notifyObservers();
        void notify() override{
            if (subject->getStateD() == dieVal) {
                notifyObservers();
            }
        }
        void attach(Observer* o);
        Producer getStateT() const override{
            if (!goosed) {
            return res;
            } else {
                return Producer{Resource::UM, 1};
            }
        }
        int getStateD() const override { return 0; };
        Hand getStateC() const override { return Hand{}; };
};
