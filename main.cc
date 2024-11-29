#include "Game/abstracts.h"
#include "course.h"
#include "constants.h"
#include "tile.h"
#include <iostream>
#include <algorithm>
#include "game.h"

// STILL TODO: COMMAND LINE ARGUMENTS
// --save, --load, --board

int main(int argc, char *argv[]) {
    bool hidden = false;
           collection col;
        if (argc > 0) {
            char c = *argv[0];
            switch (c)
            {
            case 't':
                col = collection('e');
                break;
            case 'f':
                col = collection('f');
                break;

            case 'g':
                col = collection('g');
                break;
            
            default:
                col = collection('e');
                break;
            }
        } else {
            col = collection('t');
        }
    if (argc > 1) {
        if (*argv[1] == 'H') {
            hidden = true;
        }
    }
    if (!hidden) {
        Action2 act;
        bool running = true;
        while (running) {
            *col.screen <<  controller::Commands::MENU2;
            *col.screen >> act;
            switch (act) {
                case Action2::LOAD: {
                    *col.screen  << controller::Commands::SFILENAME;
                    std::string filename;
                    *col.screen >> filename;
                    *col.screen  << controller::Commands::BOARDNAME;
                    std::string boardname;
                    *col.screen >> boardname;
                    *col.screen  << controller::Commands::SEED;
                    int seed;
                    *col.screen >> seed;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string a;
                    *col.screen >> a;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string b;
                    *col.screen >> b;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string c;
                    *col.screen >> c;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string d;
                    *col.screen >> d;


                    if ((a != b) && (a != c) && (a != d) && (b != c) && (b != d) && (c != d)) {
                        std::string ps[4]{a,b,c,d};
                        try {col.bringin(filename, boardname, seed, ps);}
                        catch(const std::exception& e){}
                    
                    } else {
                        *col.screen  << controller::Commands::INVALIDNUM; 
                    }
                     break; 
                }

                case Action2::MAKE: {
                    *col.screen  << controller::Commands::BOARDNAME;
                    std::string boardname;
                    *col.screen >> boardname;
                    *col.screen  << controller::Commands::SEED;
                    int seed;
                    *col.screen >> seed;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string a;
                    *col.screen >> a;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string b;
                    *col.screen >> b;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string c;
                    *col.screen >> c;
                    *col.screen  << controller::Commands::PLAYER;
                    std::string d;
                    *col.screen >> d;


                    if ((a != b) && (a != c) && (a != d) && (b != c) && (b != d) && (c != d)) {
                        std::string ps[4]{a,b,c,d};
                        try {col.generate(boardname, seed, ps);}
                        catch(const std::exception& e)
                        {
                        }
                        
                    } else {
                        *col.screen  << controller::Commands::INVALIDNUM; 
                    }
                    break;
                }
                case Action2::PLAY: {
                    *col.screen  << controller::Commands::BOARDNAME;
                    std::string boardname;
                    *col.screen >> boardname;
                    col.play(boardname);
                    break;
                }
                case Action2::ADDPLAY: {
                    *col.screen  << controller::Commands::PLAYER;
                    std::string a;
                    *col.screen >> a;
                    *col.screen  << controller::Commands::PASS;
                    std::string b;
                    *col.screen >> b;
                    col.addplayer(a, b);
                    break;
                }
                case Action2::PLAYERS: {
                    col.listplayers();
                    break;
                }
                case Action2::BOARDS: {
                    col.listboards();
                    break;
                }
                case Action2::EX: {
                    running = false;
                    break;
                }
                default:
                    break;
            }
        }
    } else {
        while(true) {
        *col.screen  << controller::Commands::BOARDNAME;
        std::string boardname;
        *col.screen >> boardname;
        *col.screen  << controller::Commands::PLAYER;
        std::string c;
        *col.screen >> c;
        col.gethand(c, boardname);
        }
    }
     return 0;
}
        
