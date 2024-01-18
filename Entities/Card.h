#ifndef DS_REPO_DZHEENTAEV_B_AUCA_2022_CARD_H
#define DS_REPO_DZHEENTAEV_B_AUCA_2022_CARD_H

#include "DarkCardSide.h"
#include "LightCardSide.h"

class Card {
protected:
    LightCardSide Light;
    DarkCardSide Dark;
public:
    Card(LightCardSide light, DarkCardSide dark) : Light(light), Dark(dark){
    }
    LightCardSide& GetLight(){
        return Light;
    }
    DarkCardSide& GetDark(){
        return Dark;
    }
    static bool IsCompatibleDark(const DarkCardSide& first, const DarkCardSide& other){
        if(first.GetType() == DarkCommon && other.GetType() == DarkCommon){
            if(first.GetColor() == other.GetColor())
                return true;
            if(first.GetNumber() == other.GetNumber())
                return true;
            return false;
        }
        if(first.GetType() == other.GetType()){
            return true;
        }
        if(first.GetColor() == other.GetColor())
            return true;

        if(first.GetType() == DarkWild)
            return true;

        return false;
    }

    static bool IsCompatibleLight(const LightCardSide& first, const LightCardSide& other){
        if(first.GetType() == Common && other.GetType() == Common){
            if(first.GetColor() == other.GetColor())
                return true;
            if(first.GetNumber() == other.GetNumber())
                return true;
            return false;
        }
        if(first.GetType() == other.GetType()){
            return true;
        }
        if(first.GetColor() == other.GetColor())
            return true;

        if(first.GetType() == Wild)
            return true;
        return false;
    }
};

#endif /* DS_REPO_DZHEENTAEV_B_AUCA_2022_CARD_H */