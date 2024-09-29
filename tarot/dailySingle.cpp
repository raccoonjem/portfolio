#include <iostream>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>

// because of this, remember we need to compile using
// g++ dailySingle.cpp tarot.cpp -o dailySingle
#include "tarot.h"

using namespace std;

void printWelcome(string format);

int main()
{
    // create a deck using the Tarot Header file
    vector<Card> deck = buildDeck();

    // exit early if we didn't actually get any cards back
    if (deck.empty())
    {
        cerr << "Unable to build deck";
        return 1;
    }

    // VARIABLES
    string spacer = "   ";   // indentation for final reporting of cards

    // print an initial acknowledgement for player
    printWelcome(spacer);

    // shuffle cards using time as a seed
    unsigned seed = time(0);
    auto rng = default_random_engine(seed);
    shuffle(deck.begin(), deck.end(), rng);


    // announce the card
    cout << "\n";
    cout << spacer << spacer << spacer << spacer << "Your card is: ";

    cout << deck[0].GetCardString() << endl;

    return 0;
}

void printWelcome(string format)
{
    cout << format << format << format << format << "  Welcome to Daily Draw!" << endl;
    cout << format << " Shuffle a Tarot deck, and pull the top card." << endl;
    cout << "A deck has been drawn with the Minor and Major Arcana.\n" << endl;
}
