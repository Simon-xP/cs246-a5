#include <vector>
enum Resource {CAFF, LAB, LEC, STD, TUT, UM};

struct Hand {
    std::vector <Resource> cards;
};

struct Producer {
    Resource prod = UM;
    int amount = 0;
};

int hsize(Hand* h){
    return int(h->cards.size());
}

void hclear(Hand* h){
    h->cards.clear();
}

void hadd(Hand* h, Resource r){
    h->cards.emplace_back(r);
}

void hsub(Hand* h, Resource r){
    for (int i = 0; i < hsize(h); i++) {
        if (h->cards.at(i) == r) {
            h->cards.erase(h->cards.begin() + i);
            break;
        }
    }
}

int herr(Hand* h, Resource r){
    int err = 0;
    for (auto i : h->cards) {
        if (i == r) {
            err++;
        }
    }
    return err;
}