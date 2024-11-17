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

Board* generateBoard(std::string name, Player* players[4], PlayerData* data[4], std::mt19937 *gen) {
    Dice* d = new Dice();
    Goose* g = new Goose();
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
    std::vector<Tile*> c;
    
    std::vector<Criteria*> a;
    
    std::vector<Goal*> b;

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
                a.emplace_back(new Criteria());
                break;
            case 'E':
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(new Goal());
                b.emplace_back(new Goal());
                break;
            case 'T':
                temp1.emplace_back(new Tile());
                c.emplace_back(new Tile());
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
                 if (layout.at(i).at(j+3) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i).at(j+3)));
                }
                if (layout.at(i).at(j-3) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i).at(j-3)));
                }
                if (layout.at(i+2).at(j+1) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i+2).at(j+1)));
                }
                if (layout.at(i-2).at(j+1) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i-2).at(j+1)));
                }
                 if (layout.at(i+2).at(j-1) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i+2).at(j-1)));
                }
                 if (layout.at(i-2).at(j-1) == 'T') {
                    tempa.at(i).at(j)->eyes.emplace_back(new tileobs(temp0.at(i-2).at(j-1)));
                }


                if (layout.at(i).at(j+2) == 'C') {
                    tempa.at(i).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                }
                if (layout.at(i).at(j-2) == 'C') {
                    tempa.at(i).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                }
                if (layout.at(i-2).at(j+2) == 'C') {
                   tempa.at(i-2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                }
                if (layout.at(i-2).at(j-2) == 'C') {
                     tempa.at(i-2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                }
                 if (layout.at(i+2).at(j+2) == 'C') {
                    tempa.at(i+2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j));
                }
                 if (layout.at(i+2).at(j-2) == 'C') {
                    tempa.at(i+2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j));
                }

                
                break;
            case 'E':
                for (int k = -1; k < 2; ++k) {
                    if (layout.at(i+k).at(j+1) == 'C') {
                        tempa.at(i+k).at(j+1)->ajacent.emplace_back(tempb.at(i).at(j));
                        tempb.at(i).at(j)->ajacent.emplace_back(tempa.at(i+k).at(j+1));
                    }
                    if (layout.at(i+k).at(j-1) == 'C') {
                        tempa.at(i+k).at(j-1)->ajacent.emplace_back(tempb.at(i).at(j));
                        tempb.at(i).at(j)->ajacent.emplace_back(tempa.at(i+k).at(j-1));
                    }
                }


                if (layout.at(i+1).at(j+2) == 'E') {
                    tempb.at(i+1).at(j+2)->ajacent.emplace_back(tempb.at(i).at(j));
                }
                if (layout.at(i+1).at(j-2) == 'E') {
                    tempb.at(i+1).at(j-2)->ajacent.emplace_back(tempb.at(i).at(j));
                }
                if (layout.at(i-1).at(j+2) == 'E') {
                    tempb.at(i-1).at(j+2)->ajacent.emplace_back(tempb.at(i).at(j));
                }
                if (layout.at(i-1).at(j-2) == 'E') {
                    tempb.at(i-1).at(j-1)->ajacent.emplace_back(tempb.at(i).at(j));
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
    return new Board{name, 0, players[0],players[1],players[2],players[3], data[0],data[1],data[2],data[3], b, a, c, d, gen, g};
}

void PlayerData::gain(Hand* h){
    if (h->cards.at(0) != Resource::UM) {
        for (Resource i : h->cards) {
            hadd(hand, i);
        }
    } else {
        can_steal = true;
    }
}

void PlayerData::goosefy(){
    for (PlayerData* p : b->data) {
        p->Discard();
    }
    Tile* target;
    b->goose->move(target);
    std::vector <PlayerData*> options;
    for (PlayerData* i : b->data) {
        if ((i->can_steal) && (i != this)){
            options.emplace_back(i);
        }
    }
    PlayerData* selected;
    if (selected->hand->cards.size()){
        std::shuffle(selected->hand->cards.begin(), selected->hand->cards.end(), b->gen);
        hadd(hand, selected->hand->cards.front());
        hsub(selected->hand, selected->hand->cards.front());
    }

}

void PlayerData::Discard(){
    if (int(hand->cards.size()) >= 10) {
        std::shuffle(hand->cards.begin(), hand->cards.end(), b->gen);
        for (int i = int(hand->cards.size())/2; i > 0; i--) {
            hsub(hand, hand->cards.front());
        }
    }

};

void PlayerData::roll(Dice* d){
    int num = 1;
    for (PlayerData* i : b->data) {
        i->can_steal = false;
    } 
    d->setValue(num, this);
}


void PlayerData::turn() {
    bool turnActive = true;
    int choice;

    // Start the player's turn by rolling the dice
    roll(b->dice);

    std::cout << "\n--- Player " << id << "'s Turn ---" << std::endl;

    while (turnActive) {
        // Display current hand and points
        std::cout << "\nYour current hand:" << std::endl;
        for (Resource r : hand->cards) {
            std::cout << static_cast<int>(r) << " "; // Cast to int for resource enum display
        }
        std::cout << "\nYour current points: " << points << std::endl;

        // Display available actions
        std::cout << "\nWhat would you like to do?" << std::endl;
        std::cout << "1. Roll the dice (again, if applicable)" << std::endl;
        std::cout << "2. Buy a Criteria" << std::endl;
        std::cout << "3. Buy a Goal" << std::endl;
        std::cout << "4. View game board" << std::endl;
        std::cout << "5. End turn" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Rolling the dice again..." << std::endl;
                roll(b->dice);
                break;
            }
            case 2: {
                std::cout << "Choose a Criteria to buy (enter its index): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < b->criterions.size()) {
                    if (b->criterions[index]->buy(this)) {
                        std::cout << "Criteria bought successfully!" << std::endl;
                    } else {
                        std::cout << "Not enough resources or invalid action!" << std::endl;
                    }
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
                    if (b->goals[index]->buy(this)) {
                        std::cout << "Goal bought successfully!" << std::endl;
                    } else {
                        std::cout << "Not enough resources or invalid action!" << std::endl;
                    }
                } else {
                    std::cout << "Invalid Goal index!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\nDisplaying the game board:\n" << std::endl;
                b->display(); // Assume `Board` has a display function
                break;
            }
            case 5: {
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