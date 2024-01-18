#include "Game.h"
#include <random>
#include <stdexcept>
#include <algorithm>

Game::Game(int playersCount) {
    if(playersCount * Player::InitHandSize> Game::DeckSize || playersCount < 2){
        throw std::invalid_argument("Invalid number of players");
    }

    auto draw = InitAndShuffleCards();

    InitPlayersCardsAndDraw(draw, playersCount);
}

Card& Game::GetTopCard() {
    return DiscardPile.top();
}



std::vector<Card> Game::InitAndShuffleCards() {
    std::vector<Card> draw;

    for(int i = 1; i <= 4;i++){
        for(int j = 2; j <= 7; j++){
            auto lightSide = LightCardSide{LightColor(i), LightCardType(j)};
            auto darkSide = DarkCardSide{DarkColor(5 - i), DarkCardType(9 - j)};

            draw.push_back(Card(lightSide, darkSide));
            if(LightCardType(j) != WildDrawTwo && LightCardType(j) != Wild)
                draw.push_back(Card(lightSide, darkSide));
        }
        for(int j = 1; j <= 9; j++){
            auto lightSide = LightCardSide{LightColor(i), Number(j)};
            auto darkSide = DarkCardSide{DarkColor(5 - i), Number(10 - j)};

            draw.push_back(Card(lightSide, darkSide));
            draw.push_back(Card(lightSide, darkSide));
        }
    }
    std::shuffle(draw.begin(), draw.end(), std::mt19937(std::random_device()()));

    return draw;
}

void Game::InitPlayersCardsAndDraw(std::vector<Card>& draw, int playersCount) {
    std::stack<Card> deck;
    int pos = 0;
    Players = std::vector<Player>();
    std::vector<int>ids;
    for(int i = 0; i < playersCount; i++){
        std::deque<Card> temp;
        for(int j = 0; j < Player::InitHandSize; j ++){
            temp.push_back(draw[pos]);
            pos++;
        }
        if(i != 0)
            ids.push_back(i);
        Players.push_back(Player(temp, i));
    }

    this->order.push(0);
    std::shuffle(ids.begin(), ids.end(), std::mt19937(std::random_device()()));
    for(int i = 0; i < playersCount - 1; i++){
        this->order.push(ids[i]);
    }
    DiscardPile = std::stack<Card>();
    DiscardPile.push(draw[pos]);
    pos++;
    for(;pos < draw.size(); pos++){
        deck.push(draw[pos]);
    }

    this->DrawPile = deck;
}



int Game::CheckWin(){
    for(auto &item : this->Players){
        if(item.GetHandSize() == 0){
            return item.id;
        }
    }
    return - 1;
}

void Game::ReverseOrder(int playerId) {
    std::stack<int> stack;
    while (!order.empty()) {
        stack.push(order.front());
        order.pop();
    }
    order.push(playerId);
    while (!stack.empty()) {
        order.push(stack.top());
        stack.pop();
    }
}

void Game::PlayCard(int playerId, int cardId){
    auto card = Players[playerId].GetCard(cardId);
    if(CheckIfPlayable(card, Players[playerId])){
        Players[playerId].PlayCard(cardId);
        DiscardPile.push(card);
        if(isFlipped){
            switch(card.GetDark().GetType()){
                case DrawFive:
                    for(int i = 1; i <= 5;i ++)
                        TakeCard(order.front());
                    SkipNextPlayer();
                    break;
                case DarkFlip:
                    FlipDiscard();
                    break;
                case DarkReverse:
                    ReverseOrder(playerId);
                    break;
                case SkipEveryone:
                    SkipIteration(playerId);
                    break;
                case WildDrawColor:
                    DrawTillHasColor();
                    break;
                default:
                    break;
            }
        }
        else{
            switch(card.GetLight().GetType()) {
                case WildDrawTwo:
                    for (int i = 1; i <= 2; i++)
                        TakeCard(order.front());
                    SkipNextPlayer();
                    break;
                case Flip:
                    FlipDiscard();
                    break;
                case Skip:
                    SkipNextPlayer();
                    break;
                case Reverse:
                    ReverseOrder(playerId);
                    break;
                case DrawOne:
                    TakeCard(order.front());
                    SkipNextPlayer();
                    break;
                default:
                    break;
            }
        }
    }
    else{
        throw std::invalid_argument("Can't play this card");
    }
}

void Game::SkipIteration(int playerId) {
    auto currId = order.front();
    while(currId != playerId){
        order.pop();
        order.push(currId);
        currId = order.front();
    }
}

Card Game::MakeFirstPossibleMove(int playerId){
    auto cards = Players[playerId].GetCards();
    for(int id = 0; id < cards.size(); id++){
        auto item = cards[id];
        if(CheckIfPlayable(item, Players[playerId])){
            PlayCard(playerId, id);
            return item;
        }
    }
    TakeCard(playerId);
    MakeFirstPossibleMove(playerId);
}

void Game::DrawTillHasColor() {
    auto playerId = order.front();
    order.pop();
    order.push(playerId);
    auto card = TakeCard(playerId);
    if (isFlipped){
        while(card.GetDark().GetColor() != GetTopCard().GetDark().GetColor()){
            TakeCard(playerId);
        }
    }
    else{
        while(card.GetLight().GetColor() != GetTopCard().GetLight().GetColor()){
            TakeCard(playerId);
        }
    }
}

void Game::ReshuffleDraw() {
    std::vector<Card>temp;
    while(!DiscardPile.empty()){
        temp.push_back(DiscardPile.top());
        DiscardPile.pop();
    }
    std::shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));
    for(auto &item : temp){
        DrawPile.push(item);
    }
}

bool Game::CanPlayAnyNotWild(int playerId) {
    auto cards = Players[playerId].GetCards();
    for(auto &item : cards){
        if(isFlipped && item.GetDark().GetType() != WildDrawColor){
            if(CheckIfPlayable(item, Players[playerId])) return true;
        }
        else if(!isFlipped && item.GetLight().GetType() != Wild){
            if(CheckIfPlayable(item, Players[playerId])) return true;
        }
    }
    return false;
}

bool Game::CheckIfPlayable(Card& card, Player& player) {
    auto topCard = this->GetTopCard();
    if(isFlipped && card.GetDark().GetType() == WildDrawColor){
        return !CanPlayAnyNotWild(player.id);
    }
    if(!isFlipped && card.GetLight().GetType() == Wild) {
        return !CanPlayAnyNotWild(player.id);
    }
    if(isFlipped && Card::IsCompatibleDark(topCard.GetDark(), card.GetDark())){
        return true;
    }

    if(!isFlipped && Card::IsCompatibleLight(topCard.GetLight(), card.GetLight())){
        return true;
    }

    return false;
}

Card Game::TakeCard(int playerId) {
    if(!this->DrawPile.empty() || !(this->DrawPile.size() == 1 && this->DiscardPile.empty())){
        auto card = this->DrawPile.top();
        Players[playerId].TakeCard(card);
        this->DrawPile.pop();
        return card;
    }
    else if(this->DrawPile.empty()){
        ReshuffleDraw();
        return TakeCard(playerId);
    }
}
