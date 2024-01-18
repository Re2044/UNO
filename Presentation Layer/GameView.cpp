#include "GameView.h"
#include "../Common/Helpers/EnumToStringHelpers.h"

void GameView::DisplayPlayerCards(Player& player, bool isFlipped) {
    std::cout<<"Player #"<<player.id + 1<<" : \n";
    for(auto card : player.GetCards()){
        DisplayCurrentSide(card, isFlipped);
    }
    std::cout<<std::endl;
}

DarkColor GameView::GetDarkColor() {
    int x = -1;
    do {
        std::cout << "Please choose color to set: 1 - Orange, 2 - Blue, 3 - Pink, 4 - Violet\n";
        std::cin >> x;
        if(x >=1 && x<=4)
            return DarkColor(x);
    }while(x<1 || x>4);
}

LightColor GameView::GetLightColor() {
    int x = -1;
    do {
        std::cout << "Please choose color to set: 1 - Red, 2 - Yellow, 3 - Blue, 4 - Green\n";
        std::cin >> x;
        return LightColor(x);
    }while(x<1 || x>4);
}

void GameView::DisplayAllCardsOfPlayer(Player &player) {
    std::cout<<"Light Side: ";
    for(auto card : player.GetCards()) {
        DisplayCurrentSide(card, true);
    }
    std::cout<<std::endl;

    std::cout<<"Dark Side: ";
    for(auto card : player.GetCards()) {
        DisplayCurrentSide(card, false);
    }
    std::cout<<std::endl;
}

void GameView::DisplayAllPlayers(std::vector<Player> &players, bool isFlipped, int playerId) {
    for(int i = 0; i< players.size(); i++){
        if(players[i].id != playerId){
            DisplayPlayerCards(players[i], isFlipped);
        }
    }
    std::cout<<"Your Hand: "<<std::endl;
    DisplayAllCardsOfPlayer(players[playerId]);
}

void GameView::DisplayWin(bool isRealPlayer, int playerId) {
    if(isRealPlayer){
        std::cout<<"Congratulations - you had won!\n";
    }
    else{
        std::cout<<"Player#"<<playerId + 1<<" has won!\n";
    }
    std::cout<<"Give any symbol to exit\n";
    std::string s;
    std::cin>>s;
}

void GameView::DisplayTopCard(Card &card, bool isFlipped) {
    std::cout<<"Top Card: \n";
    DisplayCurrentSide(card, isFlipped);
    std::cout<<std::endl;
}

void GameView::SetUpOutput() {
    system("CLS");
}

void GameView::DisplayCurrentSide(Card &card, bool isFlipped) {
    if(isFlipped){
        auto side = card.GetLight();
        if(side.GetType() == Common){
            std::cout<<LightColors[side.GetColor() - 1]<<" "<<NumberToString[side.GetNumber() - 1]<<" ";
        }
        else
            std::cout<<LightColors[side.GetColor() - 1]<<" "<<LightCardToString[side.GetType() - 1]<<" ";
    }
    else{
        auto side = card.GetDark();
        if(side.GetType() == DarkCommon){
            std::cout<<DarkColors[side.GetColor() - 1]<<" "<<NumberToString[side.GetNumber() - 1]<<" ";
        }
        else
            std::cout<<DarkColors[side.GetColor() - 1]<<" "<<DarkCardToString[side.GetType() - 1]<<" ";
    }
}

struct InputObject GameView::GetCommand(int handSize) {
    int x = 1e9+7;
    do{
        std::cout<<"Please choose action to do: Call Uno - -1, Draw a card - 0, Choose card to play - ID from 1 to "<<handSize<<std::endl;
        std::cin>>x;
    }
    while(x<-1 || x>handSize);
    switch(x){
        case -1:
            return {CallUno, x};
        case 0:
            return {Draw, x};
        default:
            return {PlayCard, x - 1};
    }
}


void GameView::DisplayError(OutputResponse out){
    if(out.outputType == Error){
        std::cout<<"Error: "<<out.message<<std::endl;
    }
}