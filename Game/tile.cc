#include "tile.h"
#include "abstracts.h"
#include <iostream>

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

Tile::Tile(Dice* subject): subject{subject}{
    subject->attach(this);
}

void Tile::notifyObservers() {
    std::cout << "pop" << std::endl;
    for (auto i: observers){
        i->notify();
    }
}

void Tile::attach(Observer* o){
    observers.emplace_back(o);
}

void Tile::notify(){
    if (subject->getStateD() == dieVal) {
        notifyObservers();
    }
}

Tile::~Tile(){
    for (auto i: observers){
        detach(i);
    }
 }