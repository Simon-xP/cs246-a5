#include "abstracts.h"
#include "tile.h"
#include "constants.h"
#include "course.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <string>

int BOARD_ROWS = 21;
int BOARD_COLUMNS = 23;
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

// 4 labs, 4 caffeines, 3 study, 3 tutorial, 4 lecture, 1 netflix
std::vector<Resource> getTileOrder(std::mt19937 *gen) {
    std::vector<Resource> vec{
        Resource::LAB, Resource::LAB, Resource::LAB, Resource::LAB, 
        Resource::CAFF, Resource::CAFF, Resource::CAFF, Resource::CAFF, 
        Resource::LEC, Resource::LEC, Resource::LEC, Resource::LEC, 
        Resource::STD, Resource::STD, Resource::STD, Resource::TUT, 
        Resource::TUT, Resource::TUT, Resource::UM
    };
    std::shuffle(vec.begin(), vec.end(), *gen);
    return vec;
}

std::vector<int> getTileOrder2(std::mt19937 *gen) {
    std::vector<int> vec{3, 10, 5, 4, 10, 11, 3, 8, 2, 6, 8, 12, 5, 11, 4, 6, 9, 9};
    std::shuffle(vec.begin(), vec.end(), *gen);
    return vec;
}

std::shared_ptr<Board> generateBoard(std::string name, Player* players[4], std::mt19937 *gen) {
    std::shared_ptr<Dice> d = std::make_shared<Dice>();
    std::shared_ptr<Goose> g = std::make_shared<Goose>();
    auto tileorder = getTileOrder(gen);
    auto tileorder2 = getTileOrder2(gen);
    int t = 0;
    int t2 = 0;

    // goals are edges, criterion are corners, tiles are T

    std::vector<std::vector <std::shared_ptr<Tile>>> temp0;
    
    std::vector<std::vector <std::shared_ptr<Criteria>>> tempa;
    
    std::vector <std::vector <std::shared_ptr<Goal>>> tempb;
    std::vector <std::shared_ptr<Tile>> c;
    
   std::vector <std::shared_ptr<Criteria>> a;
    
   std::vector <std::shared_ptr<Goal>> b;
    for (int i = 0; i < BOARD_ROWS; ++i) {
        std::vector <std::shared_ptr<Tile>> temp1;
        std::vector <std::shared_ptr<Criteria>> temp3;
        std::vector <std::shared_ptr<Goal>> temp4;
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
            {
                std::shared_ptr<Criteria> w = std::make_shared<Criteria>();
                temp1.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                temp3.emplace_back(w);
                a.emplace_back(w);
                break;
            }
            case 'E':
            {
                std::shared_ptr<Goal> s = std::make_shared<Goal>();
                temp1.emplace_back(nullptr);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(s);
                b.emplace_back(s);
                break;
            }
            case 'T':
            {
                std::shared_ptr<Tile> q = std::make_shared<Tile>(d.get());
                temp1.emplace_back(q);
                c.emplace_back(q);
                temp3.emplace_back(nullptr);
                temp4.emplace_back(nullptr);
                break;
            }
            
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
                if (j + 3 < BOARD_COLUMNS){
                    if (layout.at(i).at(j+3) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i).at(j+3).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if (j - 3 >= 0){
                    if (layout.at(i).at(j-3) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i).at(j-3).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j + 1 < BOARD_COLUMNS) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j+1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i+2).at(j+1).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j + 1 < BOARD_COLUMNS) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j+1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i-2).at(j+1).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j - 1 >= 0) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j-1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i+2).at(j-1).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }
                if ((j - 1 >= 0) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j-1) == 'T') {
                        std::shared_ptr<tileobs> v = std::make_shared<tileobs>(temp0.at(i-2).at(j-1).get());
                        v->owner =  tempa.at(i).at(j).get();
                        tempa.at(i).at(j)->eyes.emplace_back(v);
                    }
                }

                if (j + 2 < BOARD_COLUMNS){
                    if (layout.at(i).at(j+2) == 'C') {
                        tempa.at(i).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }
                if (j - 2 >= 0){
                    if (layout.at(i).at(j-2) == 'C') {
                        tempa.at(i).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j+2) == 'C') {
                    tempa.at(i-2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }
                if ((j -2 >= 0) && (i - 2 >= 0)){
                    if (layout.at(i-2).at(j-2) == 'C') {
                        tempa.at(i-2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j+2) == 'C') {
                        tempa.at(i+2).at(j+2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }
                if ((j - 2 >= 0) && (i + 2 < BOARD_ROWS)){
                    if (layout.at(i+2).at(j-2) == 'C') {
                        tempa.at(i+2).at(j-2)->neighbours.emplace_back(tempa.at(i).at(j).get());
                    }
                }

                
                break;
            case 'E':
                for (int k = -1; k < 2; ++k) {
                    if ((j + 1 < BOARD_COLUMNS) && (i + k < BOARD_ROWS) && (i + k >= 0)){
                        if (layout.at(i+k).at(j+1) == 'C') {
                            tempa.at(i+k).at(j+1)->ajacent.emplace_back(tempb.at(i).at(j).get());
                            tempb.at(i).at(j)->ajacent2.emplace_back(tempa.at(i+k).at(j+1).get());
                        }
                    }
                    if ((j - 1 >= 0) && (i + k < BOARD_ROWS)&& (i + k >= 0)){
                        if (layout.at(i+k).at(j-1) == 'C') {
                            tempa.at(i+k).at(j-1)->ajacent.emplace_back(tempb.at(i).at(j).get());
                            tempb.at(i).at(j)->ajacent2.emplace_back(tempa.at(i+k).at(j-1).get());
                        }
                    }
                }

                if ((j + 2 < BOARD_COLUMNS) && (i + 1 < BOARD_ROWS)){
                    if (layout.at(i+1).at(j+2) == 'E') {
                        tempb.at(i+1).at(j+2)->ajacent1.emplace_back(tempb.at(i).at(j).get());
                    }
                }
                if ((j - 2 >= 0) && (i + 1 < BOARD_ROWS)){
                    if (layout.at(i+1).at(j-2) == 'E') {
                        tempb.at(i+1).at(j-2)->ajacent1.emplace_back(tempb.at(i).at(j).get());
                    }
                }
                if ((j + 2 < BOARD_COLUMNS) && (i - 1 >= 0)){
                    if (layout.at(i-1).at(j+2) == 'E') {
                        tempb.at(i-1).at(j+2)->ajacent1.emplace_back(tempb.at(i).at(j).get());
                    }
                }
                if ((j - 2 >= 0) && (i - 1 >= 0)){
                    if (layout.at(i-1).at(j-2) == 'E') {
                        tempb.at(i-1).at(j-2)->ajacent1.emplace_back(tempb.at(i).at(j).get());
                    }
                }

                break;
            case 'T':
                temp0.at(i).at(j)->res = {tileorder.at(t), 1};
                if (tileorder.at(t) != Resource::UM) {
                    temp0.at(i).at(j)->dieVal = tileorder2.at(t2);
                    t2++;
                }
                t++;
                break;
            
            default:
                break;
            }
        }
    }
    std::shared_ptr<PlayerData> p1 = std::make_shared<PlayerData>();
    std::shared_ptr<PlayerData> p2 = std::make_shared<PlayerData>();
    std::shared_ptr<PlayerData> p3 = std::make_shared<PlayerData>();
    std::shared_ptr<PlayerData> p4 = std::make_shared<PlayerData>();
    std::shared_ptr<Board> bor(new Board{name, 0, players[0],players[1],players[2],players[3],p1,p2,p3,p4 , b, a, c, d, gen, g});
    p1->b = bor.get();
    p2->b = bor.get();
    p3->b = bor.get();
    p4->b = bor.get();
    return bor;
}

void Goose::move(Tile* target){
    if (tile) {
        tile->goosed = false;
    }
    if (target) {
        target->goosed = true;
    }
    tile = target;
}


void PlayerData::gain(Hand h){
    if (h.cards.at(0) != Resource::UM) {
        for (Resource i : h.cards) {
            hadd(hand.get(), i);
        }
    } else {
        can_steal = true;
    }
}

Tile* PlayerData::selectTargetTile() {
    int targetIndex = -1;

    // Input loop to ensure a valid number between 0 and 18 is selected
    while (true) {
        std::cout << "Select a target tile (number between 0 and 18): ";
        std::cin >> targetIndex;

        // Check if input is valid
        if (std::cin.fail() || targetIndex < 0 || targetIndex > 18) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number between 0 and 18." << std::endl;
        } else {
            break; // Valid input
        }
    }

    // Assuming `b->tiles` is a vector of tiles, and targetIndex corresponds to its index
    if (targetIndex >= 0 && targetIndex < int(b->tiles.size())) {
        return b->tiles.at(targetIndex).get(); // Return the selected tile
    }

    std::cout << "Invalid tile selection. Returning nullptr." << std::endl;
    return nullptr; // In case of an invalid index (edge case)
}

PlayerData* PlayerData::selectPlayerToStealFrom(const std::vector<PlayerData*>& options) {
    if (options.empty()) {
        std::cout << "No players available to steal from." << std::endl;
        return nullptr;
    }

    std::cout << "Select a player to steal from:" << std::endl;

    // Display the list of available options
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i << ": Player " <<  b->players[std::distance(b->data, 
        std::find_if(b->data, b->data + 3, [options, i](const std::shared_ptr<PlayerData>& p) {return p.get() == options[i];}))]->Name << std::endl; // Assuming PlayerData has a 'name' property
    }

    int selectedIndex = -1;

    // Input loop to ensure valid selection
    while (true) {
        std::cout << "Enter the number corresponding to the player: ";
        std::cin >> selectedIndex;

        if (std::cin.fail() || selectedIndex < 0 || selectedIndex >= static_cast<int>(options.size())) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number between 0 and " << options.size() - 1 << "." << std::endl;
        } else {
            break; // Valid input
        }
    }

    // Return the selected player
    return options[selectedIndex];
}

void PlayerData::goosefy(){
    for (std::shared_ptr<PlayerData> p : b->data) {
        p->Discard();
    }
    Tile* target = selectTargetTile();
    if (target) {
        b->goose->move(target);
        std::vector <PlayerData*> options;
        for (std::shared_ptr<PlayerData> i : b->data) {
            if ((i->can_steal) && (i.get() != this)){
                options.emplace_back(i.get());
            }
        }
        PlayerData* selected = selectPlayerToStealFrom(options);
        if (selected){
            if (selected->hand->cards.size()){
                std::shuffle(selected->hand->cards.begin(), selected->hand->cards.end(), *b->gen);
                hadd(hand.get(), selected->hand->cards.front());
                hsub(selected->hand.get(), selected->hand->cards.front());
            }
        }
    }

}

void PlayerData::Discard(){
    if (int(hand->cards.size()) >= 10) {
        std::shuffle(hand->cards.begin(), hand->cards.end(), *b->gen);
        for (int i = int(hand->cards.size())/2; i > 0; i--) {
            hsub(hand.get(), hand->cards.front());
        }
    }

};

void PlayerData::roll(Dice* d){
    std::uniform_int_distribution<> dist(1, 6);
    int num = dist(*b->gen);
    int num2 = dist(*b->gen);
    for (std::shared_ptr<PlayerData> i : b->data) {
        i->can_steal = false;
    } 
    d->setValue(num+num2, this);
}


void PlayerData::turn() {
    bool turnActive = true;
    int choice;

    // Start the player's turn by rolling the dice
    roll(b->dice.get());
    Player *play = b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [this](const std::shared_ptr<PlayerData>& p) {return p.get() == this;}))];

    std::cout << "\n--- Player " << play->Name << "'s Turn ---" << std::endl;
    std::cout << "ROLL:" << b->dice->val << std::endl;

    while (turnActive) {
        // Display current hand and points
        std::cout << "\nYour current hand:" << std::endl;
        std::sort(hand->cards.begin(), hand->cards.end());
        for (Resource r : hand->cards){
            std::cout << r << " "; // Cast to int for resource enum display
        }
        std::cout << "\nYour current points: " << points << std::endl;

        // Display available actions
        std::cout << "\nWhat would you like to do?" << std::endl;
        std::cout << "0. Trade" << std::endl;
        std::cout << "1. Roll the dice (again, if applicable)" << std::endl;
        std::cout << "2. Buy a Criteria" << std::endl;
        std::cout << "3. Buy a Goal" << std::endl;
        std::cout << "4. View game board" << std::endl;
        std::cout << "5. End turn" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0: {
                Trade();
            }
            case 1: {
                std::cout << "Rolling the dice again..." << std::endl;
                roll(b->dice.get());
                std::cout << "ROLL:" << b->dice->val << std::endl;
                break;
            }
            case 2: {
                std::cout << "Choose a Criteria to buy (enter its index): ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < int(b->criterions.size())) {
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
                if (index >= 0 && index < int(b->goals.size())) {
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
                display(b); // Assume `Board` has a display function
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

void firstTurn(Board* b) {
    for (int i = 0; i < 4; ++i) {
        PlayerData* player = b->data[i].get();
        Player* play = b->players[i];
        
        std::cout << "\n--- Player " << play->Name << "'s Setup Turn ---" << std::endl;

        // Player selects a criteria
        Criteria* chosenCriteria = nullptr;
        while (!chosenCriteria) {
            std::cout << "Available Criteria:\n";
            for (size_t j = 0; j < b->criterions.size(); ++j) {
                if ((!b->criterions[j]->owner) && std::all_of(b->criterions[j]->neighbours.begin(), b->criterions[j]->neighbours.end(), [](Criteria* i){return !(i->owner);})){
                    std::cout << j << ": Criteria at position " << j << std::endl;
                }
            }

            std::cout << "Select a Criteria by entering its index: ";
            int criteriaIndex;
            std::cin >> criteriaIndex;

            if (criteriaIndex >= 0 && criteriaIndex < int(b->criterions.size()) && !b->criterions[criteriaIndex]->owner && std::all_of(b->criterions[criteriaIndex]->neighbours.begin(), b->criterions[criteriaIndex]->neighbours.end(), [](Criteria* i){return !(i->owner);})) {
                chosenCriteria = b->criterions[criteriaIndex].get();
            } else {
                std::cout << "Invalid Criteria selection. Please try again.\n";
            }
        }

        // Display adjacent goals for the selected criteria
        std::cout << "Adjacent Goals:\n";
        std::vector<Goal*> adjacentGoals;
        for (auto* goal : chosenCriteria->ajacent) {
            if (!goal->owner) {
                adjacentGoals.push_back(goal);
            }
        }

        if (adjacentGoals.empty()) {
            std::cout << "No adjacent goals available for this Criteria. Please choose a different Criteria.\n";
            --i; // Retry this player's turn
            continue;
        }

        // Player selects a goal
        Goal* chosenGoal = nullptr;
        while (!chosenGoal) {
            for (size_t j = 0; j < adjacentGoals.size(); ++j) {
                std::cout << j << ": Goal at position " << adjacentGoals[j] << std::endl;
            }

            std::cout << "Select a Goal by entering its index: ";
            int goalIndex;
            std::cin >> goalIndex;

            if (goalIndex >= 0 && goalIndex < int(adjacentGoals.size())) {
                chosenGoal = adjacentGoals[goalIndex];
            } else {
                std::cout << "Invalid Goal selection. Please try again.\n";
            }
        }

        // Mark the criteria and goal as bought and assign them to the player
        if (chosenCriteria && chosenGoal) {
            chosenCriteria->buy_start(player);
            chosenGoal->buy_start(player);
            std::cout << "Setup complete! Player " << play->Name << " selected Criteria " 
                      << chosenCriteria << " and Goal " << chosenGoal << ".\n";
        }
    }
}

void display(Board *b){
    int c = 0;
    int e = 0;
    int t = 0;
     for (int i = 0; i < BOARD_ROWS; ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                if (b->criterions.at(c)->owner) {
                    std::cout << b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b->criterions.at(c)->owner;}))]->colors[std::distance(b->data, std::find_if(b->data, b->data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b->criterions.at(c)->owner;}))] << b->criterions.at(c)->getgreed();
                } else {
                    std::cout << "C" << c << " ";
                }
                c++;
                break;
            case 'E':
                if (b->goals.at(e)->owner) {
                    std::cout << b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b->goals.at(e)->owner;}))]->colors[std::distance(b->data, std::find_if(b->data, b->data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b->goals.at(e)->owner;}))] <<" ";
                } else {
                    std::cout << "E" << e << " ";
                }
                e++;
                break;
            case 'T':
                if (t < 19) {
                    std::cout << b->tiles.at(t)->res.prod;
                } else{
                    std::cout <<"frick";
                }
                t++;
                break;
            
            default:
                std::cout << "   ";
                break;
            }
        }

    }
}

void PlayerData::writedata(){

}

void PlayerData::Trade() {

    // Prompt the player to create an offer by selecting cards to give and receive
    std::cout << "Select cards to give:" << std::endl;
    for (auto& card : hand->cards) {
        std::cout << card << " ";  // Assuming there's a way to print card information
    }
    std::cout << std::endl;
    // Implement card selection logic (select cards to give)
    ResourceCollection temp1;
    temp1.inputResources();
    std::unique_ptr<Hand> selectedHand1 = std::make_unique<Hand>(temp1.get_hand());
    std::cout << "Select cards to receive:" << std::endl;
    ResourceCollection temp2;
    temp2.inputResources();
    std::unique_ptr<Hand> selectedHand2 = std::make_unique<Hand>(temp2.get_hand());
    for (auto& card : selectedHand2->cards) {
        std::cout << card << " ";  // Display options for what they want to receive
    }
    std::cout << std::endl;
    // Implement card selection logic (select cards to receive)

    // Check if the player has enough resources for the trade
    Hand* sh1 =selectedHand1.get();
    if (std::all_of(selectedHand1->cards.begin(), selectedHand1->cards.end(), [this, sh1](Resource i) {
            return herr(hand.get(), i) >= herr(sh1, i);
        })) {

        int selectedPlayeri = 0;

        while (true) {
        std::cout << "Enter the number corresponding to the player: ";
        std::cin >> selectedPlayeri;

        if (std::cin.fail() || selectedPlayeri < 0 || selectedPlayeri >= 4) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number between 0 and " << 3 << "." << std::endl;
        } else {
            break; // Valid input
        }
    }
    PlayerData* selectedPlayer = b->data[selectedPlayeri].get();
    Hand* sh2 =selectedHand2.get();
        while (selectedPlayer) {
            if (std::all_of(selectedPlayer->hand->cards.begin(), selectedPlayer->hand->cards.end(), [selectedPlayer, sh2](Resource i) {
                    return herr(selectedPlayer->hand.get(), i) >= herr(sh2, i);
                })) {

                // Ask all other players to accept or decline the trade
                std::cout << "Trade offer from " << b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [this](const std::shared_ptr<PlayerData>& p) {return p.get() == this;}))]->Name << ": " << selectedHand1->cards << " for " << selectedHand2->cards << std::endl;
                for (std::shared_ptr<PlayerData> p : b->data) {
                    if (p.get() != this) {
                        std::string response;
                        std::cout << b->players[std::distance(b->data, std::find(b->data, b->data + 3, p))]->Name << ", do you accept the trade? (y/n): ";
                        std::cin >> response;

                        if (response == "y" && hasResourcesForTrade(selectedHand2.get())) {
                            // Execute the trade if the player accepts
                            executeTrade(selectedPlayer, selectedHand1.get(), selectedHand2.get());
                            std::cout << "Trade successful!" << std::endl;
                            return;  // End trade once successful
                        }
                    }
                }
            } else {
                std::cout << b->players[std::distance(b->data, std::find_if(b->data, b->data + 3, [selectedPlayer](std::shared_ptr<PlayerData> p){return p.get() == selectedPlayer;}))]->Name << " does not have enough resources to complete the trade." << std::endl;
                selectedPlayer = nullptr;  // No valid player for the trade
            }
        }
    }
}

// Helper function to check if the player has enough resources for the trade
bool PlayerData::hasResourcesForTrade(const Hand* selectedHand) {
    for (auto& card : selectedHand->cards) {
        if (herr(hand.get(), card) < 1) {  // Not enough of the selected card
            return false;
        }
    }
    return true;
}

// Helper function to execute the trade (exchange cards between players)
void PlayerData::executeTrade(PlayerData* selectedPlayer, Hand* hand1, Hand* hand2) {
    // Transfer cards from current player to the selected player
    for (auto& card : hand1->cards) {
        hadd(selectedPlayer->hand.get(), card);  // Add card to the selected player
        hsub(hand.get(), card);  // Remove card from the current player's hand
    }
    // Transfer cards from selected player to current player
    for (auto& card : hand2->cards) {
        hsub(selectedPlayer->hand.get(), card);  // Remove card from the selected player
        hadd(hand.get(), card);  // Add card to the current player's hand
    }
}
void run_turn (Board* b) {
    b->turn++;
    b->data[b->turn%4]->turn();
}

PlayerData::~PlayerData(){
}

Board::~Board(){
        delete gen;
}


