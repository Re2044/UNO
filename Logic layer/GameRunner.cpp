#include "GameRunner.h"
#include "iostream"

using namespace std;

void GameRunner::Run() {
    GameRunner();
    while(Game->CheckWin() == -1){
        auto playerId = Game->order.front();
        Game->order.pop();
        Game->order.push(playerId);
        if(playerId == Game->GetRealPlayerId()){
            DisplayUI();
            MakeRealPlayerMove();
        }
        else{
            Game->MakeFirstPossibleMove(playerId);
        }
    }
    GameView::DisplayWin(Game->CheckWin() == Game->GetRealPlayerId(), Game->CheckWin());
}

void GameRunner::DisplayUI() {
    GameView::SetUpOutput();
    GameView::DisplayAllPlayers(Game->GetPlayers(), Game->GetCondition(),  Game->GetRealPlayerId());
    GameView::DisplayTopCard(Game->GetTopCard(), !Game->GetCondition());
}

void GameRunner::MakeRealPlayerMove() {
    auto res = GameView::GetCommand(Game->GetRealPlayersCards().size());
    if(res.inputType == CallUno){
        if(Game->GetRealPlayersCards().size() != 1){
            Game->TakeCard(Game->GetRealPlayerId());
            Game->TakeCard(Game->GetRealPlayerId());
            DisplayUI();
            MakeRealPlayerMove();
        }
    }
    if(res.inputType == Draw){
        if(Game->GetRealPlayersCards().size() == 1){
            Game->TakeCard(Game->GetRealPlayerId());
            Game->TakeCard(Game->GetRealPlayerId());
        }
        DisplayUI();
        Game->TakeCard(Game->GetRealPlayerId());
        DisplayUI();
        MakeRealPlayerMove();
    }
    if(res.inputType == PlayCard){
        try {
            if(Game->GetRealPlayersCards().size() == 1){
                Game->TakeCard(Game->GetRealPlayerId());
                Game->TakeCard(Game->GetRealPlayerId());
            }
            DisplayUI();
            int cardId = res.cardId;
            if(Game->GetCondition() && Game->GetRealPlayersCards()[cardId].GetDark().GetType() == WildDrawColor){
                auto color = GameView::GetDarkColor();
                Game->GetRealPlayersCards()[cardId].GetDark().SetColor(color);
            }
            else if(!Game->GetCondition() && Game->GetRealPlayersCards()[cardId].GetLight().GetType() == Wild){
                auto color = GameView::GetLightColor();
                Game->GetRealPlayersCards()[cardId].GetLight().SetColor(color);
            }
            Game->PlayCard(Game->GetRealPlayerId(), res.cardId);
        }
        catch(std::invalid_argument& ex){
            GameView::DisplayError({Error, ex.what()});
            DisplayUI();
            MakeRealPlayerMove();
        }
    }
}
