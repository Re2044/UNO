#ifndef DS_REPO_DZHEENTAEV_B_AUCA_2022_LIGHTCARDSIDE_H
#define DS_REPO_DZHEENTAEV_B_AUCA_2022_LIGHTCARDSIDE_H

#include "../Common//Enums/LightCardType.h"
#include "../Common//Enums/LightColor.h"


class LightCardSide{
    protected:
        LightColor Color;
        Number NumValue;
        LightCardType CardType;
    public:
        LightCardSide(LightColor color, Number number){
            this->Color = color;
            this->NumValue = number;
            this->CardType = Common;
        }
        LightCardSide(LightColor color, LightCardType cardType){
            this->Color = color;
            this->CardType = cardType;
        }
        void SetColor(LightColor& color){
            if(CardType == Wild)
                this->Color = color;
            else{
                throw std::invalid_argument("It is not permitted to change this cards color");
            }
        }
        LightColor GetColor() const{
            return this->Color;
        }
        Number GetNumber() const{
            return this->NumValue;
        }
        LightCardType GetType() const{
            return this->CardType;
        }
        LightCardSide& operator=(const LightCardSide& other){
            this->CardType = other.CardType;
            this->Color = other.Color;
            this->NumValue = other.NumValue;
            return *this;
        }
};

#endif /* DS_REPO_DZHEENTAEV_B_AUCA_2022_LIGHTCARDSIDE_H */