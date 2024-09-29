#include "tarot.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Card::Card(string csv_id, string value, string suit)
{
    id = csv_id;
    cValue = value;
    cSuit = suit;
}

string Card::GetCardString()
{
    string SUITS[] = {"Pentacles", "Wands", "Cups", "Swords"};

    for (int i = 0; i < size(SUITS); i++)
    {
        if (SUITS[i] == cSuit)
        {
            string s = cValue + " of " + cSuit;
            return s;
        }
    }

    // else Major Arcana
    return cSuit;
}

vector<Card> buildDeck()
{
    vector<Card> deck;

    // file details
    string filename{"deck.csv"};
    ifstream input{filename};

    //if open fails, exit early
    if (!input.is_open())
    {
        cerr << "Couldn't open file\n";
        return vector<Card>();
    }

    input.ignore(numeric_limits<streamsize>::max(), '\n');

    // read file data line by line
    for (string line; getline(input, line);)
    {
        istringstream ss(move(line));
        vector<string> row;
        row.reserve(line.size());

        // break up our line by commas
        for (string value; getline(ss, value, ',');)
        {
            // add the value between commas to the row
            row.push_back(string(move(value)));
        }

        // ensure our values only have printable characters
        for (int i = 0; i < row.size(); i++)
        {
            string original = row[i];

            string updated(original.size(), '\0');

            int k = 0;
            for (int j = 0; j < original.size(); j++)
            {
                if (isprint(original[j]))
                {
                    updated[k++] = original[j];
                }
            }
            // resize to actual printable characters
            updated.resize(k);

            row[i] = updated;
        }

        // create a temp card from our data
        // and add to our deck
        Card temp(row[0], row[1], row[2]);
        deck.push_back(temp);
    }

    // finished creating deck, close the file!
    input.close();

    // test loop to print all cards in the deck
    // for (int i = 0; i < deck.size(); i++)
    // {
    //     string temp = deck[i].GetCardString();

    //     cout << temp << endl;
    // }

    return deck;
}
