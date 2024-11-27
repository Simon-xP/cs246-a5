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

void Dice::setValue(int num, PlayerData* p, controller* cont){
    val = num;
    *cont << *this;
    if (num == 7) {
        p->goosefy(cont);
    } else {
        notifyObservers();
    }
}

Tile::Tile(Dice* subject): subject{subject}{
    subject->attach(this);
}

void Tile::notifyObservers() {
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
    // observers.clear();
    // if (subject) {
    // subject->detach(this);
    // }
    // subject = nullptr;
 }

 Dice::~Dice(){
    // observers.clear();
 }