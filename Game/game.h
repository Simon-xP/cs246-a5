#ifndef __GAME_H__
#define __GAME_H__
#include "abstracts.h"
#include <vector>
#include <random>

struct pairing {
    std::shared_ptr<Board> board;
    std::mt19937 gen;
};

class collection {
    std::vector<pairing> boards;
   
    public:
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<controller> screen = nullptr;
        void bringin(std::string file, std::string name, int seed, std::string p[4]);
        void generate(std::string name, int seed, std::string p[4]);
        void play(std::string board);
        void readhand(std::string player, std::string board);
        void addplayer(std::string name, std::string password);
        collection(char f);
        collection(){}
        std::string gethand(std::string player, std::string board);
        void listplayers();
        void listboards();
        int len(){return players.size();}
};

#endif
