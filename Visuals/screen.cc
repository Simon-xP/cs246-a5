#include "screen.h"
#include "course.h"
#include <vector>
#include <algorithm>


void tcontroller::chooseplayer(const Player* p[3]){
    int x = 0;
    if (p[0]) {
        std::cout << "Choose Player" << std::endl;
        while (p[x]) {
            std::cout << x << ": " << p[x]->Name << std::endl;
        }
    }
}

void accept(const Player* p){
    std::cout << p->Name << ", do you accept the trade? (type y for yes): ";
 }

void tcontroller::board(const Board& b){
 int c = 0;
    int e = 0;
    int t = 0;
     for (int i = 0; i < BOARD_ROWS; ++i) {
        std::cout << "\n" << std::endl;
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                if (b.criterions.at(c)->owner) {
                    std::cout << b.players[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b.criterions.at(c)->owner;}))]->colors[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b.criterions.at(c)->owner;}))] << b.criterions.at(c)->getgreed();
                } else {
                    std::cout << "C" << c << " ";
                }
                c++;
                break;
            case 'E':
                if (b.goals.at(e)->owner) {
                    std::cout << b.players[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b.goals.at(e)->owner;}))]->colors[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b.goals.at(e)->owner;}))] <<" ";
                } else {
                    std::cout << "E" << e << " ";
                }
                e++;
                break;
            case 'T':
                if (t < 19) {
                    std::cout << b.tiles.at(t)->res.prod;
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

void tcontroller::turn(const Player& p, const int& i){
    std::cout << "\n--- TURN " << i << " ---" << std::endl;
    std::cout << "\n--- Player " << p.Name << "'s Turn ---" << std::endl;
}

void tcontroller::winner(const Player& p, const int& i){
    std::cout << "\n--- Winner " << p.Name << " ---" << std::endl;
}

void tcontroller::showhand(const Hand& b, const Player& p){
    std::cout << "\n--- " << p.Name << "'s Hand ---" << std::endl;
    *this << b;
}

controller& tcontroller::operator<<(const Resource resource){
    switch (resource) {
        case Resource::CAFF:
            std::cout << "Caffeine";
            break;
        case Resource::LEC:
            std::cout << "Lecture";
            break;
        case Resource::LAB:
            std::cout << "Lab";
            break;
        case Resource::STD:
            std::cout << "Study";
            break;
        case Resource::TUT:
            std::cout << "Tutorial";
            break;
        default:
            break;
    }
    return *this;
}

controller& tcontroller::operator<<(const std::vector<Resource> resources){
    for (auto i : resources) {
        *this << i;
    }
    return *this;
}

controller& tcontroller::operator<<(const Commands c) {
    switch (c) {
        case MENU:
            std::cout << "\nWhat would you like to do?" << std::endl;
            std::cout << "0. Trade" << std::endl;
            std::cout << "1. Roll the dice" << std::endl;
            std::cout << "2. Buy a Criteria" << std::endl;
            std::cout << "3. Buy a Goal" << std::endl;
            std::cout << "4. View game board" << std::endl;
            std::cout << "5. Switch Dice Type" << std::endl;
            std::cout << "6. End turn" << std::endl;
            std::cout << "7. Save" << std::endl;
            std::cout << "8. Leave Game" << std::endl;
            std::cout << "Enter your choice: \n";
            break;

        case RESET:
            std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            break;

        case MOVEG:
            std::cout << "Select a target tile (number between 0 and 18): ";
            break;

        case TRADE1:
            std::cout << "Select cards to give: ";
            break;

        case TRADE2:
            std::cout << "Select cards to Recieve: ";
            break;

        case TRADE3:
            std::cout << "Player Choose: ";
            break;

        case STEAL:
            std::cout << "Select a player to steal from: ";
            break;

        case FIRSTGOAL:
            std::cout << "Choose a Goal to buy (enter its index): ";
            break;

        case FIRSTCRIT:
            std::cout << "Choose a Criteria to buy (enter its index): ";
            break;

        case CHOOSECRIT:
            std::cout << "Choose a Criteria to buy (enter its index): ";
            break;

        case CHOOSEGOAL:
            std::cout << "Choose a Goal to buy (enter its index): ";
            break;

        case INVALIDGOAL:
            std::cout << "Invalid Goal index!" << std::endl;
            break;

        case INVALIDCRIT:
            std::cout << "Invalid Criteria index!" << std::endl;
            break;

        case INVALIDPLAYER:
            std::cout << "Invalid player selection!" << std::endl;
            break;

        case ROLL:
            std::cout << "Rolling the dice again..." << std::endl;
            break;

        case END:
            std::cout << "Ending your turn." << std::endl;
            break;

        case AFDGOAL:
            std::cout << "Not enough resources or invalid action to buy Goal!" << std::endl;
            break;

        case AFDCRIT:
            std::cout << "Not enough resources or invalid action to buy Criteria!" << std::endl;
            break;

        case INVALIDNUM:
            std::cout << "Invalid number entered. Please try again." << std::endl;
            break;

        case NOPLAY:
            std::cout << "No players available to steal from." << std::endl;
            break;
        case ALRROLL:
            std::cout << "Already Rolled This Turn" << std::endl;
            break;

        case INVTRADE:
            std::cout << "Invalid Trade" << std::endl;
            break;
        case RES:
            std::cout << "Enter the quantities of resources (Caffeine, Lab, Lecture, Study, Tutorial):\n";
            break;
        case MUST:
            std::cout << "YOU MUST ROLL FIRST\n";
            break;
        case PICK:
            std::cout << "PICK YOUR ROLL\n";
            break;

        default:
            std::cout << "Unknown command!" << std::endl;
            break;
    }
    return *this;
}

controller& tcontroller::operator<<(const Hand& c){
    Hand ca = c;
    std::sort(ca.cards.begin(), ca.cards.end());
    for (Resource r : ca.cards){
        *this << r << " "; // Cast to int for resource enum display
    }
    std::cout << std::endl;
    return *this;
}
controller& tcontroller::operator<<(const std::string& c){
    std::cout << c;
    return *this;
}

controller& tcontroller::operator<<(const Dice& c){
    std::cout << "ROLL IS: " << c.getStateD() << std::endl;
    return *this;
}

controller& tcontroller::operator>>(Action& c){
    int temp;
    while (true){
        if (std::cin >> temp) {
            if ((temp >= 0) && (temp <= 8)) {
                c = static_cast<Action>(temp);
                break;
            } else {
                *this << INVALIDNUM;
            }
            
        } else {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    return *this;
}

controller& tcontroller::operator>>(int& c){
    int temp;
    while (true){
        if (std::cin >> temp) {
            c = temp;
            break;
            
        } else {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    return *this;
}

controller& tcontroller::operator>>(std::string& c){
    int temp;
    while (true){
        if (std::cin >> temp) {
            c = temp;
            break;
            
        } else {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    return *this;
}

void tcontroller::offer(const Player* p, Hand& h1, Hand& h2){
std:: cout << p->Name << ": " << std::endl;
*this << h1;
std::cout << " for ";
*this << h2;
std::cout << std::endl;
}

void tcontroller::accept(const Player* p) {

    std::cout << p->Name << " DO YOU ACCEPT?  (enter y to accept)" << std::endl;
}

void tcontroller::reso(const Resource r){
    std::cout << "Enter quantity for ";
    *this << r;
    std::cout <<  ": ";
 }

void ResourceCollection::inputResources(controller* cont) {
    *cont << controller::Commands::RES;

    // Loop through each resource and prompt for input
    for (int i = 0; i < 5; ++i) {
        cont->reso(static_cast<Resource>(i));
        *cont >> resources[i];
    }
}

