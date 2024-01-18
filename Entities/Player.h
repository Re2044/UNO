#ifndef DS_REPO_DZHEENTAEV_B_AUCA_2022_PLAYER_H
#define DS_REPO_DZHEENTAEV_B_AUCA_2022_PLAYER_H

#include "Card.h"
#include "deque"

class Player{
protected:
    std::deque<Card> Hand;
public:
    int id;
    Player(std::deque<Card> &hand, int id){
        Hand = hand;
        this->id = id;
    }
    int GetHandSize(){
        return Hand.size();
    }
    Card PlayCard(int cardId){
        auto card = Hand[cardId];
        Hand.erase(Hand.begin() + cardId);
        return card;
    }
    void TakeCard(Card& card){
        Hand.push_back(card);
    }
    Card& GetCard(int id){
        return Hand[id];
    }
    std::deque<Card>& GetCards(){
        return this->Hand;
    }
    static const int InitHandSize = 7;
};


#endif /* DS_REPO_DZHEENTAEV_B_AUCA_2022_PLAYER_H */