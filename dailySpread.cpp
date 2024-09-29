#include <iostream>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>

// because of this, remember we need to compile using
// g++ response.cpp tarot.cpp -o response
#include "tarot.h"

using namespace std;

void printWelcome();
int requestDraw();
bool requestPlace();
int requestPlacement(int deckSize, vector<short int> selections);
void announceCards(int cards, string format);

int main()
{
    // VARIABLES
    short int draw{1};          // default to 1, "draw 1 card"
    bool place = true;          // default to true, for "draw from top of deck"
    string spacer = "   ";   // indentation for final reporting of cards

    // create a deck using the Tarot Header file
    vector<Card> deck = buildDeck();

    // exit early if we didn't actually get any cards back
    if (deck.empty())
    {
        cerr << "Unable to build deck";
        return 1;
    }

    // print an initial acknowledgement for player
    printWelcome();

    // shuffle cards using time as a seed
    unsigned seed = time(0);
    auto rng = default_random_engine(seed);
    shuffle(deck.begin(), deck.end(), rng);

    cout << "The deck has been shuffled...\n";

    // ask for total cards to draw until valid answer
    draw = requestDraw();

    // ask where they would like their cards from
    place = requestPlace();

    // use place bool to determine if more info is needed
    if (place)
    {
        // announce the cards
        announceCards(draw, spacer);

        // draw the top of deck as many cards as they requested with draw
        for (int i = 0; i < draw; i++)
        {
            cout << deck[i].GetCardString() << endl;
            if (i != draw -1)
            {
                cout << spacer;
            }
        }

        // end file
        return 0;
    }
    else
    {
        // ask for the placements they want for the number of cards they want from draw
        // store them as an array, which we can size to the size of draw for ease (and looping)
        vector<short int> placements;
        for (int i = 0; i < draw; i ++)
        {
            // request a placement
            short int temp{-1};
            while (temp == -1)
            {
                temp = requestPlacement(deck.size(), placements);
                // optionally we could just call deck.size() instead of having a variable just for this
                // but it seems like this will mean we have less function calls :thinkies:
            }

            placements.push_back(temp);
        }

        // announce the card(s)
        announceCards(draw, spacer);

        // then draw the placements requested
        for (int i = 0; i < draw; i++)
        {
            cout << deck[placements[i]].GetCardString() << endl;
            if (i != draw -1)
            {
                cout << spacer;
            }
        }

        // end file
        return 0;
    }
}

void printWelcome()
{
    cout << "                       Daily Spread" << endl;
    cout << "A deck has been drawn including the Minor and Major Aracana." << endl;
    cout << "Select how many cards you would like to draw, and whether you " << endl;
    cout << "would like to draw them from the top of the deck or elsewhere.\n" << endl;
}

int requestDraw()
{
    int choice{0};
    // ask for total cards to draw until valid answer
    while (choice < 1 || choice > 5)
    {
        cout << "\nHow many cards would you like to draw?" << endl;
        cout << "Input 1, 2, 3, 4, or 5." << endl;

        if(!(cin >> choice))
        {
            // clarify bad input and clear the stream to retry
            cout << "Please input only 1, 2, 3, 4, or 5." << endl;
            choice = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return choice;
}

bool requestPlace()
{
    int choice{0};
    while (choice < 1 || choice > 2)
    {
        cout << "\nWould you like to draw from the top of the deck, or pick specific places to draw from?" << endl;
        cout << "1 - Top of Deck Draw" << endl;
        cout << "2 - Specific Draw by Number" << endl;

        if(!(cin >> choice))
        {
            cout << "Please input only 1 or 2." << endl;
            choice = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // update place based on choice
    switch (choice)
    {
        case 1:
        return true;

        case 2:
        return false;

        default:
        cout << "Something odd happened to your selection. Drawing from top of the deck by default." << endl;
        return true;
    }
}

int requestPlacement(int deckSize, vector<short int> selections)
{
    short int choice{0};

    while (choice < 1 || choice > deckSize)
    {
        cout << "Input a number from 1 to " << deckSize << " to choose which card to draw." << endl;
        if(!(cin >> choice))
        {
            cout << "Please only input a number from 1 to " << deckSize << "." << endl;
            choice = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // account for 0-base in deck counting
    choice = choice - 1;

    // check that our selection isn't already selected
    for (int i = 0; i < selections.size(); i++)
    {
        if (choice == selections[i])
        {
            cout << "\nYou've already requested that card. Please request unique cards." << endl;
            return -1;
        }
    }

    return choice;
}

void announceCards(int cards, string format)
{
    cout << "\n\n";
    if (cards > 1)
    {
        cout << "Your cards are:" << endl;
        cout << format;
    }
    else
    {
        cout << "Your card is: ";
    }
}
