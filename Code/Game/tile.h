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
        void notifyObservers();
        void setValue(int num, PlayerData* p);
};

class Tile: public Observer, public Subject{
    Dice* subject;
    std::vector <Observer*> observers;
    protected:
        Producer res;
        int dieVal;
        int pos;
        bool goosed;
    public:
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
                return Producer{};
            }
        }
};
