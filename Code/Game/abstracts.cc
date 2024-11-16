#include "abstracts.h"
#include "tile.h"
#include <iostream>
#include <fstream>

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