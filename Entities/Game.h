#include <stack>
#include "Player.h"
#include "queue"
#include "vector"


class Game {
private:
    std::stack<Card> DiscardPile;
    std::stack<Card> DrawPile;
    std::vector<Player> Players;
    std::queue<int>order;
    bool isFlipped = false;
    const int realPlayerId = 0;
public:
    Game(int playersCount);
    void FlipDiscard(){
        isFlipped = true;
    }
    void SkipNextPlayer(){
        auto player = order.front();
        order.pop();
        order.push(player);
    }
    std::queue<int>& GetOrder(){
        return order;
    }
    int GetRealPlayerId(){
        return realPlayerId;
    }
    Player& GetPlayer(int id){
        return Players[id];
    }
    void DrawTillHasColor();
    void SkipIteration(int playerId);
    void ReverseOrder(int playerId);
    Card MakeFirstPossibleMove(int playerId);
    static std::vector<Card> InitAndShuffleCards();
    void InitPlayersCardsAndDraw(std::vector<Card>& draw, int playersCount);
    Card& GetTopCard();
    void PlayCard(int playerId, int cardId);
    bool CheckIfPlayable(Card& card, Player& player);
    void ReshuffleDraw();
    bool CanPlayAnyNotWild(int playerId);
    std::vector<Player>& GetPlayers(){
        return Players;
    }
    bool GetCondition(){
        return isFlipped;
    }
    Card TakeCard(int playerId);
    int CheckWin();
    std::deque<Card> GetRealPlayersCards(){
        return Players[realPlayerId].GetCards();
    }
    static const int DeckSize = 108;
    friend class GameRunner;
};


