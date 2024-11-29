#include "abstracts.h"
#include <vector>
#include <random>

struct pairing {
    std::shared_ptr<Board> board;
    std::mt19937 gen;
};

class collection {
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<pairing>> boards;
    std::shared_ptr<controller> screen;
    public:
        void bringin(std::string file, std::string name, int seed, std::string p[4]);
        void generate(std::string name, int seed, std::string p[4]);
        void play(std::string board);
        void readhand(std::string player, std::string board);
        void addplayer(std::string name, std::string password);
        collection(char f);
        std::string gethand(std::string player, std::string board);
        void listplayers();
        void listboards();
};
