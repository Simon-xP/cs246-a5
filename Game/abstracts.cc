#include "abstracts.h"
#include "tile.h"
#include "constants.h"
#include "course.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

int BOARD_ROWS = 21;
int BOARD_COLUMNS = 23;

// 4 labs, 4 caffeines, 3 study, 3 tutorial, 4 lecture, 1 netflix
std::vector<Resource> *getTileOrder(std::mt19937 *gen) {
    std::vector<Resource> vec{
        Resource::LAB, Resource::LAB, Resource::LAB, Resource::LAB, 
        Resource::CAFF, Resource::CAFF, Resource::CAFF, Resource::CAFF, 
        Resource::LEC, Resource::LEC, Resource::LEC, Resource::LEC, 
        Resource::STD, Resource::STD, Resource::STD, Resource::TUT, 
        Resource::TUT, Resource::TUT, Resource::UM
    };
    std::shuffle(vec.begin(), vec.end(), *gen);
    return &vec;
}

Board* generateBoard(std::string name, Player* players, PlayerData* data, std::mt19937 *gen) {
    Dice* d = new Dice();
    auto tileorder = getTileOrder(gen);
    int t = 0;
    std::vector<std::vector<char>> layout = 
    {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C'},
    {' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' '},
    {' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', 'C', 'E', 'C', ' ', ' ', 'T', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'E', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
    // goals are edges, criterion are corners, tiles are T

    std::vector<std::vector<Tile*>> temp0;
    
    std::vector<std::vector<Criteria*>> tempa;
    
    std::vector<std::vector<Goal*>> tempb;

    for (int i = 0; i < BOARD_ROWS; ++i) {
        std::vector<Tile*> temp1;
        std::vector<Criteria*> temp3;
        std::vector<Goal*> temp4;
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                temp1.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                temp3.emplace_back(new Criteria());
                break;
            case 'E':
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(new Goal());
                break;
            case 'T':
                temp1.emplace_back(new Tile());
                temp3.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                break;
            
            default:
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                break;
            }
        }
        temp0.emplace_back(temp1);
        tempa.emplace_back(temp3);
        tempb.emplace_back(temp4);
    }

    for (int i = 0; i < BOARD_ROWS; ++i) {
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                
                break;
            case 'E':
                for (int k = -1; k < 2; ++k) {
                    if () {

                    }
                    if () {

                    }
                }


                break;
            case 'T':
                temp0.at(i).at(j)->res = {tileorder->at(t), 1};
                temp0.at(i).at(j)->subject = d;
                t++;
                break;
            
            default:
                break;
            }
        }
    }
}

void PlayerData::gain(Hand* h){
    for (Resource i : h->cards) {
        hadd(hand, i);
    }
}

void PlayerData::goosefy(){

}

void PlayerData::roll(Dice* d){
    int num = 1;
    d->setValue(num, this);
}

void PlayerData::turn() {
    bool turnActive = true;
    int choice;
    roll(b->dice);

    std::cout << "It's your turn, Player!" << std::endl;

    while (turnActive) {
        std::cout << "\nYour current hand:" << std::endl;
        for (Resource r : hand->cards) {
            std::cout << r << " ";
        }
        std::cout << "\nYour current points: " << points << std::endl;

        // Display available actions
        std::cout << "\nWhat would you like to do?" << std::endl;
        std::cout << "1. Roll the dice\n2. Buy a Criteria\n3. Buy a Goal\n4. End turn" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Rolling the dice..." << std::endl;
                roll(b->dice); // Rolls the dice and triggers any associated events
                break;
            }
            case 2: {
                std::cout << "Choose a Criteria to buy (enter its index): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < b->criterions.size()) {
                    b->criterions[index]->buy(this); // Attempt to buy the selected Criteria
                } else {
                    std::cout << "Invalid Criteria index!" << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Choose a Goal to buy (enter its index): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < b->goals.size()) {
                    b->goals[index]->buy(this); // Attempt to buy the selected Goal
                } else {
                    std::cout << "Invalid Goal index!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "Ending your turn." << std::endl;
                turnActive = false;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}


void PlayerData::writedata(){

}


void run_turn (Board* b) {
    b->turn++;
    b->data[b->turn%4]->turn();
}