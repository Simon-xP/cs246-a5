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
            x++;
            if (x == 3) {
                break;
            }
        }
    }
}

void tcontroller::accept(const Player* p){
    std::cout << p->Name << ", do you accept the trade? (type y for yes): ";
 }

void tcontroller::board(const Board& b){
    std::string resour[6] = {"Caffeine", "Lab", "Lecture", "Study", "Tutorial", "Netflix"};
    int c = 0;
    int e = 0;
    int t = 0;
    int t2 = 0;
    bool long_space = false; 
    for (int i = 0; i < BOARD_ROWS; ++i) {
        std::cout << "\n";
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            switch (layout.at(i).at(j))
            {
            case 'C':
                if (b.criterions.at(c)->owner) {
                    std::cout << "|" << b.players[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b.criterions.at(c)->owner;}))]->colors[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, c](const std::shared_ptr<PlayerData>& p) {return p.get() == b.criterions.at(c)->owner;}))] << b.criterions.at(c)->getgreed() << "|";
                    if (j + 1 < BOARD_COLUMNS && layout.at(i).at(j+1) != ' ') {
						std::cout << " --";
					}else {
                        std::cout << "         ";
                    }
                } else {
                    if (c >= 10) {
                    std::cout << "|" << c << "|";
                    }
                    else {
                        std::cout << "| " << c << "|";
                    }
					if (j + 1 < BOARD_COLUMNS && layout.at(i).at(j+1) != ' ') {
						std::cout << " --";
					}else {
                        if (c < 10) {
                        std::cout << "          ";
                        } else {
                            std::cout << "         ";
                        }
                    }
                }
                c++;
                break;
            case 'E':
                if (b.goals.at(e)->owner) {
						std::cout << " "<< b.players[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b.goals.at(e)->owner;}))]->colors[std::distance(b.data, std::find_if(b.data, b.data + 3, [b, e](const std::shared_ptr<PlayerData>& p) {return p.get() == b.goals.at(e)->owner;}))];
                if (j + 1 < BOARD_COLUMNS && layout.at(i).at(j+1) != ' ') {
                        std::cout << "-- ";
					} else {
                            std::cout << "               ";
                    }
                } else {
                    
					if (j + 1 < BOARD_COLUMNS && layout.at(i).at(j+1) != ' ') {
                        std::cout << e;
						std::cout << "-- ";
					} else {
                        if (e < 10){
                            std::cout <<" " << e << "               ";
                        } else {
                            std::cout << e << "               ";
                        }
                    }
                }
                e++;
                break;
            case 'T':
                if (t < 19) {
                    if (b.tiles.at(t)->dieVal == -1) {
                        std::cout << 7 << "       ";
                    }
                    else if (b.tiles.at(t)->dieVal < 10) {
                        std::cout << b.tiles.at(t)->dieVal << "        ";
                    } else {
                        std::cout << b.tiles.at(t)->dieVal << "       ";
                    }
                } else{
                    std::cout <<"frick";
                }
                t++;
                break;

            case '1':
                std::cout << "                                       ";
                break;

            case '2':
                std::cout << "                                     ";
                break;

            case '3':
                std::cout << "                       ";
                break;
            case '4':
                std::cout << "                    ";
                break;

            case '5':
                std::cout << "     ";
                break;

            case '6':
                std::cout << "   ";
                break;

            default:
                std::cout << "";
                break;
            }
        }

        bool in = (i < 4 || (i < 16 && (i % 4 == 1 || i % 4 == 0)));    
        if ((i % 4 == 0 || i % 4 == 2) && (i < 16 && i > 4)) {
            long_space = !long_space;
        }
        

        if (i == BOARD_ROWS - 1) {
            continue;
        }
        std::cout << std::endl;
        std::cout << "   ";
        for (int j = 0; j < BOARD_COLUMNS; ++j) {
            // Determine the row to use based on the condition
            const auto& current_row = (2 * i < BOARD_ROWS) ? layout.at(i) : layout.at(i + 1);
            std::string prod_output = "";

            // Determine if there is a product to output
            if ((j+2 < BOARD_COLUMNS && layout.at(i + 1).at(j+2) == 'T') || (j+3 < BOARD_COLUMNS && layout.at(i + 1).at(j+3) == 'T')) {
                if (t2 < 19){
                prod_output = resour[static_cast<int>(b.tiles.at(t2)->res.prod)]; //b.tiles.at(t2)->res.prod; // Get the product
                }
            }

            // Render based on layout
            switch (current_row.at(j)) {
            case 'C': {
                // Logic is flipped for layout.at(i + 1)
                if ((2 * i < BOARD_ROWS && i % 2 == 0) || (2 * i >= BOARD_ROWS && i % 2)) {
                    std::cout << (in ? "/" : "\\"); // Output slash

                    // Calculate the remaining space dynamically
      
                    int base_space = long_space ? 18 : 14;
                    int adjusted_space; // Ensure no negative spaces
                    if ((i > 0) && (i % 2 == 1) && (i < 19)){
                        adjusted_space = base_space - static_cast<int>(prod_output.size());
                        adjusted_space = std::max(0, adjusted_space); // Ensure no negative spaces
                        std::cout << std::string((adjusted_space)/2, ' ');
                        std::cout << prod_output;
                        if (prod_output != "") {
                            ++t2;
                        }
                        std::cout << std::string((adjusted_space+1)/2, ' ');
                        prod_output = "";

                        
                    } else {
                         adjusted_space = base_space;
                         std::cout << std::string(adjusted_space, ' ');
                    }


                    // Output product if exists

                    // Output remaining spaces
                    

                    in = !in;          // Toggle slash direction
                    long_space = !long_space; // Toggle space length
                }
                break;
            }

            case 'E': {
                // Logic is flipped for layout.at(i + 1)
                if ((i * 2< BOARD_ROWS && i % 2) || (2 * i >= BOARD_ROWS && i % 2 == 0)) {
                    std::cout << (in ? "/" : "\\"); // Output slash

                    // Calculate the remaining space dynamically
                    int base_space = long_space ? 18 : 14;
                    int adjusted_space; // Ensure no negative spaces
                    if (i > 0 && (i % 2 == 1) && i < 19){
                        adjusted_space = base_space - static_cast<int>(prod_output.size());
                        adjusted_space = std::max(0, adjusted_space); // Ensure no negative spaces
                        std::cout << std::string((adjusted_space)/2, ' ');
                        std::cout << prod_output;
                        std::cout << std::string((adjusted_space+1)/2, ' ');
                        if (prod_output != "") {
                            ++t2;
                        }
                        prod_output = "";
                        

                        
                    } else {
                         adjusted_space = base_space;
                         std::cout << std::string(adjusted_space, ' ');
                    }
                    // Output product if exists


                    in = !in;          // Toggle slash direction
                    long_space = !long_space; // Toggle space length
                }
                break;
            }

            case 'T':
                // Handle 'T' case if needed
                break;


            case '1':
                std::cout << "                                    ";
                break;

            case '2':
                std::cout << "                                  ";
                break;

            case '3':
                std::cout << "                   ";
                break;
            case '4':
                std::cout << "                 ";
                break;

            case '5':
                std::cout << "  ";
                break;

            case '6':
                if (i == 7 || i == 12) {
                std::cout << "  ";
                }
                std::cout << "";
                break;            

            default:
                std::cout << "";
                break;
            }
        }
    long_space = !long_space; 
    }
    std::cout << std::endl;
}

void tcontroller::turn(const Player& p, const int& i){
    std::cout << "\n--- TURN " << i << " ---" << std::endl;
    std::cout << "\n--- Player " << p.Name << "'s Turn ---" << std::endl;
}

controller& tcontroller::operator<<(const PlayerData& player) {
    std::cout << player.getAmountResource(Resource::CAFF)
       << player.getAmountResource(Resource::LAB)
       << player.getAmountResource(Resource::LEC)
       << player.getAmountResource(Resource::STD)
       << player.getAmountResource(Resource::TUT);
    std::cout << "g";
    for (const auto& edge : player.edges) {
        if (edge) {
            std::cout << edge->index;
        }
    }
    std::cout << "c";
    for (const auto& corner : player.corners) {
        if (corner) {
            std::cout << corner->index << corner->getgreed();
        }
    }
    std::cout << std::endl;
    return *this;
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
            std::cout << "6. Print Player Status" << std::endl;
            std::cout << "7. Print Player Completions" << std::endl;
            std::cout << "8. End turn" << std::endl;
            std::cout << "9. Save" << std::endl;
            std::cout << "10. Leave Game" << std::endl;
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
        
        case SAVEBOARD:
            std::cout << "Saving to file..." << std::endl;
            break;

        case SFILENAME:
            std::cout << "Enter the filename: " << std::endl;
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
        case VIEWCOMP: 
            std::cout << "Which player index do you want to view the completions of?\n";
            break;
        case VIEWSTATUS: 
            std::cout << "Which player index do you want to view the status of?\n";
            break;
        default:
            std::cout << "Unknown command!" << std::endl;
            break;
    }
    return *this;
}

void tcontroller::printstatus(const PlayerData& data) {
    // 'B', 'R', 'O', 'Y'
    std::string color;
    if (data.b->data[0].get() == &data) {
        color = "Blue";
    } else if (data.b->data[1].get() == &data) {
        color = "Red";
    } else if (data.b->data[2].get() == &data) {
        color = "Orange";
    } else if (data.b->data[3].get() == &data) {
        color = "Yellow";
    } else {
        std::cout << "uh oh" << std::endl;
        color = "wrongcolor";
    }
    
    std::cout << color << " has " << data.points << " victory points, " << data.hand.get() << std::endl;
}

void tcontroller::printcompletions(const PlayerData& data) {
    // 'B', 'R', 'O', 'Y'
    std::string color;
    if (data.b->data[0].get() == &data) {
        color = "Blue";
    } else if (data.b->data[1].get() == &data) {
        color = "Red";
    } else if (data.b->data[2].get() == &data) {
        color = "Orange";
    } else if (data.b->data[3].get() == &data) {
        color = "Yellow";
    } else {
        std::cout << "uh oh" << std::endl;
    }

    std::cout << color << " has completed:" << std::endl;
    int idx;
    for (Criteria* c : data.corners) {
        for (int i = 0; i <= 53; ++i) { // 53 is max criterion index
            if (data.b->criterions[i].get() == c) {
                idx = i;
            }
        }
        std::cout << idx << " " << data.b->criterions[idx].get()->getgreed() << std::endl;
    }
}

controller& tcontroller::operator<<(const Hand& c) {
    int numCaffeines = std::count(c.cards.begin(), c.cards.end(), Resource::CAFF);
    int numLabs = std::count(c.cards.begin(), c.cards.end(), Resource::LAB);
    int numLectures = std::count(c.cards.begin(), c.cards.end(), Resource::LEC);
    int numTutorials = std::count(c.cards.begin(), c.cards.end(), Resource::TUT);
    int numStudies = std::count(c.cards.begin(), c.cards.end(), Resource::STD);

    std::cout << numCaffeines << " caffeines, "
              << numLabs << " labs, "
              << numLectures << " lectures, "
              << numTutorials << " tutorials, and "
              << numStudies << " studies." << std::endl;

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
    std::string temp;
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

