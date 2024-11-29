#include "screen.h"
#include "course.h"
#include "french.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include "game.h"


void frenchTController::chooseplayer(const Player* p[3]){
    int x = 0;
    if (p[0]) {
        std::cout << "Choisir un joueur" << std::endl;
        while (p[x]) {
            std::cout << x << ": " << p[x]->Name << std::endl;
            x++;
            if (x == 3) {
                break;
            }
        }
    }
}

void frenchTController::accept(const Player* p){
    std::cout << p->Name << ", acceptez-vous l'échange ? (tapez y pour oui) : ";
 }

void frenchTController::board(const Board& b){
    std::string resour[6] = {"Caféine", "Labo", "Cours", "Étude", "Tutoriel", "Netflix"};
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
                    std::cout <<"frique";
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

void frenchTController::turn(const Player& p, const int& i){
    std::cout << "\n--- TOUR " << i << " ---" << std::endl;
    std::cout << "\n--- Tour de joueur " << p.Name << " ---" << std::endl;
}

controller& frenchTController::operator<<(const PlayerData& player) {
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

void frenchTController::winner(const Player& p, const int& i){
    std::cout << "\n--- Gagnant " << p.Name << " ---" << std::endl;
}

void frenchTController::showhand(const Hand& b, const Player& p){
    std::cout << "\n--- Main de " << p.Name << " ---" << std::endl;
    *this << b;
}

controller& frenchTController::operator<<(const Resource resource){
    switch (resource) {
        case Resource::CAFF:
            std::cout << "Caféine";
            break;
        case Resource::LEC:
            std::cout << "Cours";
            break;
        case Resource::LAB:
            std::cout << "Labo";
            break;
        case Resource::STD:
            std::cout << "Étude";
            break;
        case Resource::TUT:
            std::cout << "Tutoriel";
            break;
        default:
            break;
    }
    return *this;
}

controller& frenchTController::operator<<(const std::vector<Resource> resources){
    for (auto i : resources) {
        *this << i;
    }
    return *this;
}

controller& frenchTController::operator<<(const Commands c) {
    switch (c) {
        case MENU:
            std::cout << "\nQu'aimeriez-vous faire ?" << std::endl;
            std::cout << "0. Échange" << std::endl;
            std::cout << "1. Lancer les dés" << std::endl;
            std::cout << "2. Acheter un Critère" << std::endl;
            std::cout << "3. Acheter un Objectif" << std::endl;
            std::cout << "4. Voir le tableau de jeu" << std::endl;
            std::cout << "5. Changer le type de dés" << std::endl;
            std::cout << "6. Terminer le tour" << std::endl;
            std::cout << "7. Sauvegarder" << std::endl;
            std::cout << "8. Quitter le jeu" << std::endl;
            std::cout << "Indiquez votre choix: \n";
            break;
        case MENU2:
            std::cout << "\nQue voulez-vous faire ?" << std::endl;
            std::cout << "0. Charger un tableau" << std::endl;
            std::cout << "1. Créer un nouveau tableau" << std::endl;
            std::cout << "2. Ajouter un joueur" << std::endl;
            std::cout << "3. Jouer" << std::endl;
            std::cout << "4. Liste des joueurs" << std::endl;
            std::cout << "5. Liste des tableaux" << std::endl;
            std::cout << "6. Quitter" << std::endl;
            std::cout << "Indiquez votre choix : \n";
            break;
        case VIEWCOMP:
            std::cout << "Quel index de joueur souhaitez-vous consulter pour les réalisations ?\n";
            break;
        case RESET:
            std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            break;
        case VIEWSTATUS:
            std::cout << "Quel index de joueur souhaitez-vous consulter pour le statut ?\n";
            break;
        case OPENHAND:
            std::cout << "Fichier ouvert avec succès\n";
            break;
        case NOBOARD:
            std::cout << "Le tableau n'existe pas\n";
            break;
        case BOARDNAME:
            std::cout << "Entrez un nom pour le tableau\n";
            break;
        case PLAYER:
            std::cout << "Entrez un nom pour le joueur\n";
            break;
        case SEED:
            std::cout << "Entrez un nombre pour la graine\n";
            break;
        case PASS:
            std::cout << "Entrez un nouveau mot de passe\n";
            break;
        case MOVEG:
            std::cout << "Sélectionnez une tuile (numéro entre 0 et 18) : ";
            break;

        case TRADE1:
            std::cout << "Sélectionnez les cartes à offrir : ";
            break;

        case TRADE2:
            std::cout << "Sélectionnez les cartes à recevoir : ";
            break;

        case TRADE3:
            std::cout << "Choisir un joueur : ";
            break;

        case STEAL:
            std::cout << "Sélectionnez un joueur à voler : ";
            break;

        case FIRSTGOAL:
            std::cout << "Choisissez un Objectif à acheter (entrez son indice) : ";
            break;

        case FIRSTCRIT:
            std::cout << "Choisissez un Critère à acheter (entrez son indice) : ";
            break;

        case CHOOSECRIT:
            std::cout << "Choisissez un Critère à acheter (entrez son indice) : ";
            break;

        case CHOOSEGOAL:
            std::cout << "Choisissez un Objectif à acheter (entrez son indice) : ";
            break;

        case INVALIDGOAL:
            std::cout << "Index de l'Objectif invalide !" << std::endl;
            break;

        case INVALIDCRIT:
            std::cout << "Index de Critère invalide !" << std::endl;
            break;

        case INVALIDPLAYER:
            std::cout << "Sélection de joueur invalide !" << std::endl;
            break;

        case ROLL:
            std::cout << "Les dés sont jetés..." << std::endl;
            break;
        
        case SAVEBOARD:
            std::cout << "Enregistrement dans un fichier..." << std::endl;
            break;

        case SFILENAME:
            std::cout << "Saisir le nom du fichier : " << std::endl;
            break;

        case END:
            std::cout << "Fin de votre tour." << std::endl;
            break;

        case AFDGOAL:
            std::cout << "Pas assez de ressources ou d'actions non valides pour acheter un Objectif !" << std::endl;
            break;

        case AFDCRIT:
            std::cout << "Pas assez de ressources ou d'actions non valides pour acheter un Critère !" << std::endl;
            break;

        case INVALIDNUM:
            std::cout << "Le numéro saisi n'est pas valide. Veuillez réessayer." << std::endl;
            break;

        case NOPLAY:
            std::cout << "Il n'y a pas de joueurs disponibles à voler." << std::endl;
            break;
        case ALRROLL:
            std::cout << "Déjà lancé les dés ce tour-ci" << std::endl;
            break;

        case INVTRADE:
            std::cout << "Échange non valide" << std::endl;
            break;
        case RES:
            std::cout << "Saisissez les quantités de ressources (caféine, labo, cours, étude, tutoriel) :\n";
            break;
        case MUST:
            std::cout << "VOUS DEVEZ D'ABORD LANCER LE DÉ\n";
            break;
        case PICK:
            std::cout << "CHOISISSEZ VOTRE JET DE DÉ\n";
            break;

        default:
            std::cout << "Commande inconnue !" << std::endl;
            break;
    }
    return *this;
}

controller& frenchTController::operator<<(const std::string& c){
    std::cout << c;
    return *this;
}

controller& frenchTController::operator<<(const Dice& c){
    std::cout << "LE JET DE DÉS EST : " << c.getStateD() << std::endl;
    return *this;
}

controller& frenchTController::operator>>(Action& c){
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

controller& frenchTController::operator>>(int& c){
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

controller& frenchTController::operator>>(std::string& c){
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

void frenchTController::offer(const Player* p, Hand& h1, Hand& h2){
std:: cout << p->Name << ": " << std::endl;
*this << h1;
std::cout << " pour ";
*this << h2;
std::cout << std::endl;
}

void frenchTController::reso(const Resource r){
    std::cout << "Saisir la quantité pour ";
    *this << r;
    std::cout <<  ": ";
 }

controller& frenchTController::operator<<(const Hand& c) {
    int numCaffeines = std::count(c.cards.begin(), c.cards.end(), Resource::CAFF);
    int numLabs = std::count(c.cards.begin(), c.cards.end(), Resource::LAB);
    int numLectures = std::count(c.cards.begin(), c.cards.end(), Resource::LEC);
    int numTutorials = std::count(c.cards.begin(), c.cards.end(), Resource::TUT);
    int numStudies = std::count(c.cards.begin(), c.cards.end(), Resource::STD);

    std::cout << numCaffeines << " caféines, "
              << numLabs << " labos, "
              << numLectures << " cours, "
              << numTutorials << " tutoriels, et "
              << numStudies << " études." << std::endl;

    return *this;
}

void frenchTController::printstatus(const PlayerData& data) {
    // 'B', 'R', 'O', 'Y'
    std::string color;
    if (data.b->data[0].get() == &data) {
        color = "Bleu";
    } else if (data.b->data[1].get() == &data) {
        color = "Rouge";
    } else if (data.b->data[2].get() == &data) {
        color = "Orange";
    } else if (data.b->data[3].get() == &data) {
        color = "Jaune";
    } else {
        std::cout << "uh oh" << std::endl;
        color = "wrongcolor";
    }
    
    std::cout << color << " a " << data.points << " points, " << data.hand.get() << std::endl;
}

void frenchTController::printcompletions(const PlayerData& data) {
    // 'B', 'R', 'O', 'Y'
    std::string color;
    if (data.b->data[0].get() == &data) {
        color = "Bleu";
    } else if (data.b->data[1].get() == &data) {
        color = "Rouge";
    } else if (data.b->data[2].get() == &data) {
        color = "Orange";
    } else if (data.b->data[3].get() == &data) {
        color = "Jaune";
    } else {
        std::cout << "uh oh" << std::endl;
    }

    std::cout << color << " a completé :" << std::endl;
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


controller& frenchTController::operator>>(Action2& c){
    int temp;
    while (true){
        if (std::cin >> temp) {
            if ((temp >= 0) && (temp <= 5)) {
                c = static_cast<Action2>(temp);
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


void frenchTController::boards(std::vector<pairing> boards) {
    std::cout << "Noms des tables : \n";
    for (auto i : boards){
        std::cout << i.board->name << std::endl;
    }
}

void frenchTController::players(std::vector<std::shared_ptr<Player>> players) {
    std::cout << "Noms des joueurs: \n";
    for (auto i : players){
        std::cout << i->Name << std::endl;
    }
}

void frenchTController::recipes(){
    std::cout << "Recettes : \n"
              << "Objectif : Étude + Tutoriel \n"
              << "Devoir : Caféine + Labo + Cours + Tutoriel \n"
              << "Examen : 2 Cours + 3 Étude \n"
              << "Final : 3 Caféine + 2 Labo + 2 Cours + Tutoriel + 2 Étude" 
              << std::endl;
}

void frenchTController::showshow(std::string lin){
    int a, b, c, d, e;
    std::stringstream ss{lin};
    ss >> a >> b >> c >> d >> e;
    std::cout << "\n\n\nCaféine: " << a << " Labo: " << b << " Lecture: " << c << " Tutoriel: " << d << " Cours: " << e << "\n" << std::endl;
}

void frenchTController::winner(std::string name){
    std::cout << "GAGNANT: " << name << std::endl;
}
