#include "constants.h"

int BOARD_ROWS = 21;
int BOARD_COLUMNS = 23;

std::vector<std::vector<char>> layout = 
{{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '2', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', '3', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', '4', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' '},
{' ', '5', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{' ', '5', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{' ', '5', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
{'6', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
{' ', '5', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
{' ', ' ', ' ', ' ', '4', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', '3', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '2', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};



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


