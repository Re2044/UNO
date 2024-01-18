#include "../Entities//Player.h"
#include "iostream"
#include "vector"
#include "queue"
#include "Structures/InputObject.h"
#include "Structures/OutputResponse.h"
#include "../Common/Helpers/ColorCodes.h"

class GameView {
public:
    static void DisplayPlayerCards(Player& player, bool isFlipped);
    static void DisplayAllCardsOfPlayer(Player& player);
    static void DisplayAllPlayers(std::vector<Player>& players, bool isFlipped, int playerId);
    static void DisplayTopCard(Card& card, bool isFlipped);
    static void DisplayCurrentSide(Card& card, bool isFlipped);
    static struct InputObject GetCommand(int handSize);
    static void DisplayError(OutputResponse out);
    static DarkColor GetDarkColor();
    static LightColor GetLightColor();
    static void SetUpOutput();
    static void DisplayWin(bool isRealPlayer, int playerId = 1);
};


