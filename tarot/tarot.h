// tarot predef -- guards at top and end
#ifndef TAROT
#define TAROT

#include <string>
#include <vector>

class Card
{
    public:
        Card(std::string csv_id, std::string value, std::string suit);
        std::string GetCardString();

    private:
        std::string id;
        std::string cValue;
        std::string cSuit;
};

std::vector<Card> buildDeck();

#endif
