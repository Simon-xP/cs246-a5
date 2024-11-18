#include "course.h"
#include <iostream>


tileobs::tileobs(Tile* subject): subject{subject}{
    subject->attach(this);
}
void tileobs::notify(){
    owner->gain(subject->getStateT());
}


void Criteria::attach(Observer* o){
    observers.emplace_back(o);
}
void Criteria::notifyObservers() {
    std::cout << "hoooo" << std::endl;
    for (auto i: observers){
        i->notify();
    }
}
void Criteria::gain(Producer r){
    last = r;
    notifyObservers();
}
Hand Criteria::getStateC() const{
    Hand temp;
    for (int i = 0; i < last.amount ; i++) {
        for (int j = 0; j < greed; j++) {
            hadd(&temp, last.prod);
        }
    }
    return temp;
}
bool Criteria::buy(PlayerData* p) {
    if ((!owner || owner == p) && (greed < 3)){
        if  ((std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* i){return std::find(ajacent.begin(), ajacent.end(), i) != ajacent.end();}))){
            if (std::all_of(neighbours.begin(), neighbours.end(), [](Criteria* i){return !(i->owner);})){
                if (std::all_of(p->hand->cards.begin(), p->hand->cards.end(), [p, this](Resource i){return herr(p->hand, i)<herr(&cost, i);})) {
                    for (auto i : cost.cards) {
                        hsub(p->hand, i);
                    }
                    if (!owner){
                        owner = p;
                        new courseobs(this, p);
                    }
                    greed++;
                    cost = COSTS[greed];
                    p->points++;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Criteria::buy_start(PlayerData* p) {
    if (!owner){
        if (std::all_of(neighbours.begin(), neighbours.end(), [](Criteria* i){return !(i->owner);})){
            owner = p;
            new courseobs(this, p);
            greed++;
            cost = COSTS[greed];
            p->points++;
            return true;
        }
    }
    return false;
}


courseobs::courseobs(Criteria* subject, PlayerData* p): subject{subject}, owner{p}{
    subject->attach(this);
    owner->eyes.emplace_back(this);
}

void courseobs::notify(){
    owner->gain(subject->getStateC());
}

bool Goal::buy(PlayerData* p){
    if (!owner) {
        if  ((std::any_of(p->corners.begin(), p->corners.end(), [this](Criteria* i){return std::find(ajacent2.begin(), ajacent2.end(), i) != ajacent2.end();})) || (std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* j){return std::find(ajacent1.begin(), ajacent1.end(), j) != ajacent1.end();}))){
            if (std::all_of(p->hand->cards.begin(), p->hand->cards.end(), [p, this](Resource i){return herr(p->hand, i)<herr(&cost, i);})) {
                for (auto i : cost.cards) {
                    hsub(p->hand, i);
                }
                p->edges.emplace_back(this);
                owner = p;
                return true;
            }
        }
    }
    return false;
}

bool Goal::buy_start(PlayerData* p){
    if (!owner) {
        p->edges.emplace_back(this);
        owner = p;
        return true;
    }
    return false;
}


Criteria::~Criteria(){
    for (auto i: eyes){
        delete i;
    }
    for (auto i: observers){
        detach(i);
    }
 }

tileobs::~tileobs() {
    if (subject) {
        subject->detach(this); // Detach the observer from the subject
    }
    // Nullify or reset pointers if necessary
    subject = nullptr;
    owner = nullptr;
}

courseobs::~courseobs() {
    if (subject) {
        subject->detach(this); // Detach the observer from the subject
    }
    // Nullify or reset pointers if necessary
    subject = nullptr;
    owner = nullptr;
}
