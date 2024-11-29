#include "game.h"
#include "../Visuals/french.h"
#include <algorithm>


collection::collection(char f){
    switch (f)
    {
    case 'e':
        screen = std::make_shared<tcontroller>();
        break;
    case 'f':
        screen = std::make_shared<frenchTController>();
        break;
    case 'g':
        //screen = std::make_shared<gcontroller>();
        screen = std::make_shared<tcontroller>(); //temp just text
        break;

    default:
        break;
    }

}

void collection::bringin(std::string file, std::string name, int seed, std::string p[4]){
    std::shared_ptr<Player> ps[4]{nullptr, nullptr, nullptr, nullptr};
    for (int i = 0; i < 4; i++) {
        for (auto j : players) {
            if (j->Name == p[i]) {
                ps[i] = j;
                break;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (ps[i] == nullptr){
            throw std::runtime_error("Missing Player: " + p[i]);
        }
    }
    pairing temp;
    temp.gen = std::mt19937(seed);
    temp.board = openFile(file, name, ps, &temp.gen);
    boards.emplace_back(temp);

}

void collection::generate(std::string name, int seed, std::string p[4]){
    std::shared_ptr<Player> ps[4]{nullptr, nullptr, nullptr, nullptr};
    for (int i = 0; i < 4; i++) {
        for (auto j : players) {
            if (j->Name == p[i]) {
                ps[i] = j;
                break;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (ps[i] == nullptr){
            throw std::runtime_error("Missing Player: " + p[i]);
        }
    }
    pairing temp;
    temp.gen = std::mt19937(seed);
    temp.board = generateBoard(name, ps, &temp.gen);
    boards.emplace_back(temp);
}

void collection::play(std::string board){
    Board* b = nullptr;
    for (auto i : boards) {
        if (i.board->name == board) {
            b = i.board.get();
            break;
        }
    }
    if (!b) {
        *screen << controller::Commands::NOBOARD;
        return;
    }
    bool running = true;
    if (b->turn == 0) {
        firstTurn(b, screen.get());
    }
    while (std::all_of(b->data, b->data+3, [](std::shared_ptr<PlayerData> x){return x->points < 10;}) && running) {
        try
        {
            run_turn(b, screen.get());
            for (auto i : b->data) {  
                if (i->points >= 10) {
                    screen->winner(b->players[std::distance(b->data, std::find(b->data, b->data + 3, i))]->Name);
                }
            }
        }
        catch(const std::exception& e)
        {
            running = false;
        }     
    }

}

void collection::readhand(std::string player, std::string board){

    std::string filename = board + "_" + player;
    std::string password;
    bool passed = false;
    std::ifstream fileCheck(filename);

    if (fileCheck.good()) {
        *screen << controller::Commands::OPENHAND;

        fileCheck.close();
        std::ifstream fileStream(filename);
    if (!passed){
        *screen << controller::Commands::READHAND1;
        std::string pass;
        *screen >> pass;
        if (pass == password) {
            passed = true; 
        } else {
            *screen << controller::Commands::READHANDF;
            return;
        }
    }
        fileStream.close();
    } else {
        *screen << controller::Commands::NOHAND;
    }
    std::string in;
    while (in != "q") {
        screen->showshow(gethand(player, board));
        screen->recipes();
        *screen << controller::Commands::READHAND2;
        *screen >> in;
    }
    
}

std::string collection::gethand(std::string player, std::string board) {

    std::string filename = board + "_" + player;
    std::ifstream fileCheck(filename);
    if (fileCheck.good()) {
        std::string lin;
        fileCheck.close();
        std::ifstream fileStream(filename);
        fileStream >> lin >> lin;
        fileStream.close();
        return lin;
    } else {
        return "0 0 0 0 0";
    }
    return "0 0 0 0 0";
}

void collection::addplayer(std::string name, std::string password){
    std::shared_ptr<Player> temp = std::make_shared<Player>(name, password);
    players.emplace_back(temp);
}

void collection::listplayers(){
    screen->players(players);
}

void collection::listboards(){
    screen->boards(boards);
}