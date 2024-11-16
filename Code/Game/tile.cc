#include "tile.h"
#include "abstracts.h"

void Dice::attach(Observer* o){
    observers.emplace_back(o);
}

void Dice::notifyObservers() {
    for (auto i: observers){
        i->notify();
    }
}

void Dice::setValue(int num, PlayerData* p){
    val = num;
    if (num == 7) {
        p->goosefy();
    } else {
        notifyObservers();
    }
}

void Tile::notifyObservers() {
    for (auto i: observers){
        i->notify();
    }
}

void Tile::attach(Observer* o){
    observers.emplace_back(o);
}