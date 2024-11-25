#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "../Game/abstracts.h"
#include "window.h"
#include "gui.h"

class Player;
struct Hand;
class Board;
enum class Resource;
class Dice;
class PlayerData;

enum Action {TRADE, ROLL, CRIT, GOAL, BOARD, SWITCH, END, SAVE, EXIT};

class controller {
    protected:
        enum Controltypes {TEXT, GRAPHIC};
        Controltypes controltype;
    public:
        enum Commands {MENU, RESET, MOVEG, TRADE1, TRADE2, STEAL, FIRSTGOAL, FIRSTCRIT, CHOOSECRIT, CHOOSEGOAL,
        INVALIDGOAL, INVALIDCRIT, INVALIDPLAYER, ROLL, SAVEBOARD, END, AFDGOAL, AFDCRIT, INVALIDNUM, NOPLAY, ALRROLL, TRADE3, INVTRADE,
        RES, MUST, PICK, SFILENAME};
        virtual void chooseplayer(const Player* p[3]) = 0;
        virtual void offer(const Player* p, Hand& h1, Hand& h2) = 0;
        virtual void accept(const Player* p) = 0;
        virtual void board(const Board& b) = 0;
        virtual void reso(const Resource r) = 0;
        virtual void turn(const Player& p, const int& i) = 0;
        virtual void winner(const Player& p, const int& i) = 0;
        virtual void showhand(const Hand& b, const Player& p) = 0;
        virtual controller& operator<<(const Resource resource) = 0;
        virtual controller& operator<<(const std::vector<Resource> resources) = 0;
        virtual  controller& operator<<(const std::string& c) = 0;
        virtual controller& operator<<(const Commands c) = 0;
        virtual controller& operator<<(const Hand& c) = 0;
        virtual controller& operator<<(const Dice& c) = 0;
        virtual controller& operator<<(const PlayerData& player) = 0;
        virtual controller& operator>>(Action& c) = 0;
        virtual controller& operator>>(int& c) = 0;
        virtual controller& operator>>(std::string& c) = 0;
        
};

class gcontroller: public controller{
    std::shared_ptr<Xwindow> win;
    std::shared_ptr<gui> graphs;
    public:
        void chooseplayer(const Player* p[3]) override;
        void accept(const Player* p) override;
        void offer(const Player* p, Hand& h1, Hand& h2) override;
        void reso(const Resource) override;
        void board(const Board& b)override;
        void turn(const Player& p, const int& i)override;
        void winner(const Player& p, const int& i)override;
        void showhand(const Hand& b, const Player& p)override;
        controller& operator<<(const Resource resource) override;
        controller& operator<<(const std::vector<Resource> resources) override;
        controller& operator<<(const std::string& c) override;
        controller& operator<<(const Commands c)override;
        controller& operator<<(const Hand& c)override;
        controller& operator<<(const Dice& c)override;
        controller& operator<<(const PlayerData& player) override;
        controller& operator>>(Action& c) override;
        controller& operator>>(int& c) override;
        controller& operator>>(std::string& c) override;
};

class tcontroller: public controller{
    public:
        void chooseplayer(const Player* p[3]) override;
        void accept(const Player* p) override;
        void reso(const Resource) override;
        void offer(const Player* p, Hand& h1, Hand& h2) override;
        void board(const Board& b)override;
        void turn(const Player& p, const int& i)override;
        void winner(const Player& p, const int& i)override;
        void showhand(const Hand& b, const Player& p)override;
        controller& operator<<(const Resource resource) override;
        controller& operator<<(const std::vector<Resource> resources) override;
        controller& operator<<(const std::string& c) override;
        controller& operator<<(const Commands c) override;
        controller& operator<<(const Hand& c)override;
        controller& operator<<(const Dice& c)override;
        controller& operator<<(const PlayerData& player) override;
        controller& operator>>(Action& c)override;
        controller& operator>>(int& c) override;
        controller& operator>>(std::string& c) override;
};

class ResourceCollection {
public:
    int resources[5];

    ResourceCollection() {
        // Initialize all resources to 0
        for (int i = 0; i < 5; ++i) {
            resources[i] = 0;
        }
    }

    void inputResources(controller* cont);

    // Function to get the name of the resource as a string
    std::string getResourceName(Resource r) const {
        switch (r) {
            case Resource::CAFF: return "Caffeine";
            case Resource::LAB: return "Lab";
            case Resource::LEC: return "Lecture";
            case Resource::STD: return "Study";
            case Resource::TUT: return "Tutorial";
            default: return "Unknown";
        }
    }

    Hand get_hand() {
        Hand temp;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < resources[i]; j++) {
                hadd(&temp, static_cast<Resource>(i));
            }
        }
        return temp;
    }
};


#endif
