#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <vector>
#include <string>
#include <iostream>

class controller;

enum class Resource {CAFF, LAB, LEC, STD, TUT, UM};
extern int BOARD_ROWS;
extern int BOARD_COLUMNS;

extern std::vector<std::vector<char>> layout;


struct Hand {
    std::vector <Resource> cards;
};

struct Producer {
    Resource prod = Resource::UM;
    int amount = 0;
};

int hsize(Hand* h);

void hclear(Hand* h);

void hadd(Hand* h, Resource r);

void hsub(Hand* h, Resource r);

int herr(Hand* h, Resource r);

std::ostream& operator<<(std::ostream& os, const Resource resource);
std::ostream& operator<<(std::ostream& os, const std::vector<Resource> resources);

#endif
