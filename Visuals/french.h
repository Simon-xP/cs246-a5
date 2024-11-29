#ifndef __FRENCH_H__
#define __FRENCH_H__
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "../Game/abstracts.h"
#include "window.h"
#include "gui.h"
#include "../Game/game.h"
#include "screen.h"
struct pairing;

class frenchTController: public controller{
    public:
        void chooseplayer(const Player* p[3]) override;
        void accept(const Player* p) override;
        void reso(const Resource) override;
        void offer(const Player* p, Hand& h1, Hand& h2) override;
        void board(const Board& b)override;
        void turn(const Player& p, const int& i)override;
        void winner(const Player& p, const int& i)override;
        void showhand(const Hand& b, const Player& p)override;
        void printstatus(const PlayerData& data) override;
        void printcompletions(const PlayerData& data) override;
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
        controller& operator>>(Action2& c) override;
        void boards(std::vector<pairing> boards) override;
        void players(std::vector<std::shared_ptr<Player>> players) override;
        void recipes() override;
        void showshow(std::string lin) override;
        void winner(std::string name) override;
};

#endif