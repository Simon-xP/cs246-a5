#include "course.h"
#include <iostream>
#include <memory>


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
        if  ((std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* i){return std::find_if(ajacent.begin(), ajacent.end(), [i](Goal* x){return i == x;}) != ajacent.end();}))){
            if (std::all_of(neighbours.begin(), neighbours.end(), [](Criteria* i){return !(i->owner);})){
                if (std::all_of(cost.cards.begin(), cost.cards.end(), [p, this](Resource i){return herr(p->hand.get(), i)>=herr(&cost, i);})) {
                    for (auto i : cost.cards) {
                        hsub(p->hand.get(), i);
                    }
                    if (!owner){
                        owner = p;
                        p->eyes.emplace_back(std::make_shared<courseobs>(this,p));
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
            p->eyes.emplace_back(std::make_shared<courseobs>(this,p));
            greed++;
            cost = COSTS[greed];
            p->points++;
            return true;
        }
    }
    return false;
}

bool Criteria::force_buy(PlayerData* p) {
    if (!owner){
        owner = p;
        p->eyes.emplace_back(std::make_shared<courseobs>(this,p));
        greed++;
        cost = COSTS[greed];
        p->points++;
        return true;
    }
    return false;
}


courseobs::courseobs(Criteria* subject, PlayerData* p): subject{subject}, owner{p}{
    subject->attach(this);
}

void courseobs::notify(){
    auto x = owner;
    auto y = subject;
    x->gain(y->getStateC());
}

bool Goal::buy(PlayerData* p){
    if (!owner) {
        if  (std::any_of(p->corners.begin(), p->corners.end(), [this, p](Criteria* i){return std::find_if(ajacent2.begin(), ajacent2.end(), [i](Criteria* x){return i == x;}) != ajacent2.end();}) || 
        std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* j){return std::find_if(ajacent1.begin(), ajacent1.end(), [j](Goal* x){return j == x;}) != ajacent1.end();})){
            if (std::all_of(cost.cards.begin(), cost.cards.end(), [p, this](Resource i){return herr(p->hand.get(), i)>=herr(&cost, i);})) {
                for (auto i : cost.cards) {
                    hsub(p->hand.get(), i);
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

void Criteria::detach(courseobs* o){
    // if (observers.size()) {
    // for (auto it = observers.begin(); it != observers.end(); ++it) {
    //     if ((*it) == o) {
    //         observers.erase(it);
    //          break;
    //     }
    // }
    // }
}
void Criteria::detach(tileobs* o){
    if (eyes.size()) {
    for (auto it = eyes.begin(); it != eyes.end(); ++it) {
        if ((*it).get() == o) {
            eyes.erase(it);
             break;
        }
    }
    }
}

Goal::~Goal(){
    // ajacent1.clear();
    // ajacent2.clear();
    //     if (owner){
    // owner->detach(this);
    // }
    // owner = nullptr;
}

Criteria::~Criteria(){
    // observers.clear();
    // ajacent.clear();
    // neighbours.clear();
    // tiles.clear();
    // if (owner){
    // owner->detach(this);
    // }
    // owner = nullptr;
}
courseobs::~courseobs(){
    // if (subject){
    // subject->detach(this);
    // }
    // if (owner){
    // owner->detach(this);
    // }
    // subject = nullptr;
    // owner = nullptr;
}
tileobs::~tileobs(){
    // if (subject){
    // subject->detach(this);
    // }
    // if (owner){
    // owner->detach(this);
    // }
    // subject = nullptr;
    // owner = nullptr;
}
