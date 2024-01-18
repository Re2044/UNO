#include "../Entities/Game.h"
#include "../Presentation Layer/GameView.h"
class GameRunner {
private:
    Game *Game;
    static GameView *GameView;
public:
    GameRunner(int playersCount = 3){
        this->Game = new class Game(playersCount);
    }
    void Run();
    void MakeRealPlayerMove();
    void DisplayUI();
};
