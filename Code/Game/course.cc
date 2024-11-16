#include "course.h"


tileobs::tileobs(Tile* subject): subject{subject}{
    subject->attach(this);
}
tileobs::~tileobs(){
    subject->detach(this);
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
}
void Criteria::buy(PlayerData* p) override{
    if ((!owner || owner == p) && (greed < 3)){
        if  ((std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* i){return std::find(ajacent.begin(), ajacent.end(), i);})) || (std::any_of(p->corners.begin(), p->corners.end(), [](auto i){return std::find(ajacent.begin(), ajacent.end(), i);}))){
            if (std::all_of(neighbours.begin(), neighbours.end(), [](Criteria* i){return !(i->owner);})){
                if (std::all_of(p->hand->cards.begin(), p->hand->cards.end(), [p, this](Resource i){return herr(p->hand, i)<herr(&cost, i);})) {
                    for (auto i : cost.cards) {
                        hsub(p->hand, i);
                    }
                    owner = p;
                    greed++;
                    cost = COSTS[greed];
                }
            }
        }
    }
}



courseobs::courseobs(Criteria* subject): subject{subject}{
    subject->attach(this);
}
courseobs::~courseobs(){
    subject->detach(this);
}
void courseobs::notify(){
    owner->gain(&subject->getStateC());
}

void Goal::buy(PlayerData* p){
            if (!owner) {
                if  ((std::any_of(p->edges.begin(), p->edges.end(), [this](Goal* i){return std::find(ajacent.begin(), ajacent.end(), i);})) || (std::any_of(p->corners.begin(), p->corners.end(), [](auto i){return std::find(ajacent.begin(), ajacent.end(), i);}))){
                    if (std::all_of(p->hand->cards.begin(), p->hand->cards.end(), [p, this](Resource i){return herr(p->hand, i)<herr(&cost, i);})) {
                        for (auto i : cost.cards) {
                            hsub(p->hand, i);
                        }
                        p->edges.emplace_back(this);
                        owner = p;
                    }
                }
            }
        }