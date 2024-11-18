#include "constants.h"


int hsize(Hand* h){
    return int(h->cards.size());
}

void hclear(Hand* h){
    h->cards.clear();
}

void hadd(Hand* h, Resource r){
    h->cards.emplace_back(r);
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

void hsub(Hand* h, Resource r){
    for (int i = 0; i < hsize(h); i++) {
        if (h->cards.at(i) == r) {
            h->cards.erase(h->cards.begin() + i);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Resource resource) {
    switch (resource) {
        case Resource::CAFF:
            os << "Caffeine";
            break;
        case Resource::LEC:
            os << "Lecture";
            break;
        case Resource::LAB:
            os << "Lab";
            break;
        case Resource::STD:
            os << "Study";
            break;
        case Resource::TUT:
            os << "Tutorial";
            break;
        default:
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Resource> resources) {
    for (auto i : resources) {
        os << i;
    }
    return os;
}

