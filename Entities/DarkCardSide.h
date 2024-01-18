#ifndef DS_REPO_DZHEENTAEV_B_AUCA_2022_DARKCARDSIDE_H
#define DS_REPO_DZHEENTAEV_B_AUCA_2022_DARKCARDSIDE_H

#include <stdexcept>
#include "../Common//Enums/DarkCardType.h"
#include "../Common//Enums/DarkColor.h"
#include "../Common//Enums/Number.h"

class DarkCardSide{
protected:
    DarkColor Color;
    Number NumValue;
    DarkCardType CardType;
public:
    DarkCardSide(DarkColor color, Number number){
        this->Color = color;
        this->NumValue = number;
        this->CardType = DarkCommon;
    }
    DarkCardSide(DarkColor color, DarkCardType cardType){
        this->Color = color;
        this->CardType = cardType;
    }

    DarkColor GetColor() const{
        return this->Color;
    }
    Number GetNumber() const{
        return this->NumValue;
    }
    DarkCardType GetType() const{
        return this->CardType;
    }
    void SetColor(DarkColor& color){
        if(CardType == WildDrawColor)
            this->Color = color;
        else{
            throw std::invalid_argument("It is not permitted to change this cards color");
        }
    }
    DarkCardSide& operator=(const DarkCardSide& other){
        this->CardType = other.CardType;
        this->Color = other.Color;
        this->NumValue = other.NumValue;
        return *this;
    }
};

#endif /* DS_REPO_DZHEENTAEV_B_AUCA_2022_DARKCARDSIDE_H */