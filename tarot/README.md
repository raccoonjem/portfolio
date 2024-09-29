# Digital Tarot
#### Video Demo: https://youtu.be/5LTR6l7KIJE

## Introduction
As I have experience with Unreal Engine, and have an interest in using it more in a coding capacity, I chose to make my final project in **C++** as a language. Naturally, then, step one in the plan was to put the final project on a brief hold while I brushed up on C++ syntax. I opted to do this by reading Michael Dawson's _Beginning C++ Through Game Programming_ -- a book I've owned for some time, but repeatedly felt too overwhelmed to get through. I managed to understand it much better this time, and used CS50's codespace to quickly try some of the exercises in the project for certainty.

After brushing up on some C++ and feeling somewhat confident I could make something unique from it, rather than solving a preexisting problem from the book, I laid out a couple things I wanted to be sure to use -- the first was to center the work around a Class, as classes are pretty central to C++, and using one would be a good way to ensure I was understanding them. The second goal was to use a header file, or otherwise link a file together, as we'd seen done in some problem sets. Games are complex, using multiple files together will be necessary, so having a basic understanding of this is, similarly, a pretty good test for myself.

To create my final, I ultimately created one header file, `tarot.h` (and, subsequently, `tarot.cpp`), which was used in three different versions of a c++ program to read some amount of Tarot card(s). In order of complexity, they are: `dailySingle.cpp`, `dailySpread.cpp`, and `response.cpp`

### Quick Tarot Rundown
For a more in-depth look at tarot, check out something like Tarot's wikipedia page -- https://en.wikipedia.org/wiki/Tarot -- or more specifically the page for the Rider-Waite tarot -- https://en.wikipedia.org/wiki/Rider%E2%80%93Waite_Tarot
Tarot decks are, in essence, an extended playing card deck. Tarot Reading is a practice amongst individuals to use randomized card-drawing from a deck of Tarot cards to influence their understanding around questions in their life. Some believe there to be predictive powers in Tarot card reading, while others treat them more as an exercise in self-reflection and allowing their sub-conscious mind to respond proactively.

The Rider-Waite tarot deck is a commonly referenced tarot deck set up that consists of two parts, resulting in 78 total cards. First, the Minor Arcana function roughly like a standard deck of cards, consisting of 4 suits with an even amount of cards. Within each suit, the cards are numbered as Ace, 2 to 10, Page, Knight, Queen, and King. The suits in the original Rider-Waite are Wands, Cups, Swords, and Pentacles. <sub>In playing cards, these would be Clubs, Hearts, Spades, and Diamonds, in order.</sub> In variations on this deck, the suits may be renamed, and certain cards may even take on different names (for instance, in Tille Walden's [Cosmic Slumber Tarot](https://www.amazon.com/Cosmic-Slumber-Tarot-Tillie-Walden/dp/1454943092), Page and Knight are instead Princess and Prince).

> For all intents and purposes, this program functions as a "game", wherein players can request a number of cards and are presented with a randomized card as a result. No output of this program is meant to supply any predictive insight or advice to the user.

## Description
> Note that to compile any of the associated pieces, users will need to use `g++ file.cpp tarot.cpp -o file` where `file.cpp` is either `dailySingle.cpp`, `dailySpread.cpp`, or `response.cpp`!

### tarot.cpp and tarot.h
Prior to fully starting the coding, I figured that I could use a class to create each individual card, and that I could create a vector of classes to store a group of them together. Each card would need a number and a suit, with the note that the Major Aracana could each have their title (Fool, Judgment, Wheel of Fortune, etc) as their "suit" and their number in the deck (from 1 to 22) as their "number". I first created a cpp file, "tarot.cpp". This would eventually become the header, but I wanted to verify that I could make the deck work. After proving out that it worked, I made adjustments to create cards from a csv file, rather than creating them explicitly in the code (which I did initally for 3 as a test). Even just 3 quickly spiraled the lines of code out of control.

To avoid creating 78 cards in code, I created a **simple, three-column chart in Google Sheets** with the information for an ID value (a simple, 0-based count), a Value (number) column, and a Suit column. I then imported this as deck.csv to my codespace.

> This would also allow me to, in the future, include multiple renditions of a Tarot deck with different numbers of cards, names, or organization, with only the need to swap the name in the file reading function and include the new csv. At least once during coding, this allowed me to correct some data without needing to sort through lines of code to fix an issue.

tarot.h became the home to all of the prototypes for tarot.cpp. This piece defines a prototype for the Card class, including the 3 private variables we import from our csv file, a public constructor (`Card::Card`) which allows us to feed in 3 variables to initialize our private variables on creation, and a public function `getCardString` which gets the string of a selected card. Additionally, I include the prototype for buildDeck, a function that returns a vector of Cards.

From the top of tarot.cpp, we declare a number of needed libraries for our deck creation. We don't need to create the Card class here, so we instead jump into our constructor for the Card class, which simply takes the 3 string inputs and assigns them to the appropriate Card private variables.

The next function is then defined, `getCardString`. These needs to output another string, but branches -- as mentioned, we have our minor and major arcana, and their suits funciton differently. So from the card we're given, we loop through a simple array of strings that are our minor arcana suits. If the suit is part of the minor arcana, we return a string _"Value of Suit"_ -- ex, the 1 of Cups or 5 of Pentacles. However, if we loop through and do not find our suit, it's safe to say we have a Major Aracana card, in which case we only return the _"Suit"_ -- ex, Death, Temperance, or The Wheel of Fortune.

Finally, we get our most conplex function: create the deck of cards. We start by defining an empty vector of cards, **deck**. If opening the file fails, we return an empty vector -- this _does_ puts the onus on the cpp files that call this funciton to return our of the program if the vector is empty, which does kinda suck in my opinion.
Assuming, though, that we open successfully, we read the file **line by line**, and within the line, we use **commas to break input up** whenever we see one. We push each value between commas to a **row** array.
>We then need to ensure we only have printable characters -- this is because when using getCardString, we need to ensure we're comparing to the exact Strings that we present in our array of suits. If we have invisible, unprintable characters, our comparisons will fail. So, to check for printable characters, which we loop through each element in the **row** array and iterate through _that_ element character by character to check if the character is printable. If they are, we copy them into a temp value, and if they aren't, we ignore them. Finally, we reassign the array value to the temp value once we've reached the end.
Once we know we have a **row** of valid inputs, we create a `Card` using that data, and push that `Card` into the **deck**.

That then **repeats for all lines in the csv**, creating all the cards in the deck. After closing our input csv file, we return the **deck** to whoever called the function.

### dailySingle.cpp
> `dailySingle.cpp` is a simplified program that returns a random card from the top of the deck after shuffling it.

After including the necessary libraries and the `tarot.h` library, we declare a single function prototype for this file -- `printWelcome`. In main, we start by creating a **deck** calling **buildDeck()** from `tarot.h`. We then verify that the deck is not empty -- _remember that if it is, we've likely returned from failing to open the csv file_ -- and return out of the program with an error if it is empty. Following this, we define a single variable for formatting text later, **spacer**, which is a simple string of a set number of spaces.

Once we have our deck, we use `printWelcome()` to print our entry message. We pass in our **spacer** variable, to keep some standardized formatting. This lets us make the text look vaguely centered (compared to the text written, not fully in the window, though).

Once that is printed, we immediately create a seed using the user's current time, and create an **rng** value from `default_random_engine()` of that seed. Using `shuffle()`,  we shuffle the deck with that **rng** value.

dailySingle.cpp then simply formats a string announcing the card, and gives the `GetCardString()` value for the top card in the deck -- `deck[0]`.

### dailySpread.cpp
> `dailySpread.cpp` takes the shuffled deck and announced card of `dailySingle.cpp` and adds player input that allows users to change how many cards are reported -- from 1 up to 5 -- and change where the cards are reported from, instead of just reporting the card in array place 0.

In the prototypes for functions of `dailySpread.cpp`, we declare 4 new functions. `requestDraw()` returns an int for how many cards the user would like drawn from the deck. `requestPlace()` returns a bool for whether the user would like to draw cards from the top of the deck, or draw from specific places. `requestPlacement` returns an int -- specifically for one place within the deck. To accomodate the potential for differently sized decks, we give it an input of int **deckSize**, which can be gotten easily using the `deck.size()` function once we've built a deck.

Our main function starts with the same set up as `dailySingle.cpp`,with the caveat taht we declare two additional variables to our formatting string -- and int for **draw** and a bool for **place**. We then continue with our normal set up: creating a **deck** from `buildDeck()` in our tarot header, complete with a check for returning a program failure (1) if a deck isn't built.

Similarly, We follow this with `printWelcome()`, which prints out the relevant text welcoming the user to the program. Then, we create a **seed** using the user's current time, create an **rng** value using `default_random_engine()` on that seed, and `shuffle()` the deck using our **rng** value.

After this, we branch by setting a **draw** value to the output of `requestDraw()`. In the associated function, we create a temporary int, **choice**, and ask the player for an input while that choice option doesn't match the inputs we need -- in this case, a number from 1 to 5, inclusive. This cin for **choice** is within a _while_ loop that looks for the number range we want, but also contains a catch for non-numeric inputs that can clear and ignore the previous input, prompting the user again to input "only 1, 2, 3, 4, or 5" as a reminder. Once a valid value has been given, we return **choice** to main, and store it as **draw**.

Back in main, we follow this up with a similar looking line, this time taking our **place** bool and assigning it to the output of `requestPlace()`. We use the same temporary int **choice** method for `requestPlace()` then ask the user to input a 1 or a 2 to specify whether they want to draw from the top of the deck, or specify numbers to draw. We, again, set this cin for **choice** into a _while_ loop, with a catch for non-numeric inputs. Once we have a valid number for **choice**, we use a switch to return a value to **place** back in main. In the switch, where _case 1_ returns true, _case 2_ returns false, and we include a _default_ where we report, "something odd happened... Drawing from top of the deck," and once more return true, same as we did in case 1.

Back in main, we move into a branching path, based on whether **place** is true or false. Remember, _true_ means "draw from the top of the deck", and _false_ means "let me pick card number(s) for my drawing."

> Both of these pathes will use `announceCards()`, a function which takes the input of an int for the number of cards to draw, and a string for formatting. The function then prints a small break of 2 empty lines with cout, then checks if the user is drawing multiple cards. If the user wants more then one card, it prints a string using pluralized grammer and a follow-up line with a format -- our spacer value from main. Otherwise, the user only wants a single card drawn, so we print a line with singular grammar, and don't end that line so that when the card is printed, it appears on the same line.

Starting with **_if place is true_**, we call our function to `announceCards()`, feeding in our **draw** value and **spacer** string. Then, we loop through the **deck** using a simple **int i = 0** to iterate and our **draw** value as the max. Because we want to draw from the top, we simply print `deck[i].GetCardString()`, which will get the string from the card in position 0, 1, 2, etc -- as many as we'd like to draw. Once we are finished printing, we end the file with return 0.

In the case where **_place is false_**, we need to do a bit more. Instead of juping straight into pulling cards, we define **placements** as a vector of short ints. We then loop through as many times as we want to draw, defining a **temp** short int that looks for a value from `requestPlacement()`, feeding in the `deck.size()`, and the **placements** vector. While the value of **temp*** is -1, we loop, and once we have an accepted value, we push_back **temp** into **placements**.

`requestPlacement()` uses a **choice** int, similar to our other functions. Here, while choice is less than 1 or higher than the size of the deck, we ask to input a valid number between 1 and the size of the deck. We once again catch for any non-numeric inputs. Once we have a valid number, we update it to **1 less than what was input** -- to account for the deck counting being **0-base**. We then loop through the "selections" local variable -- which is generally passed the placements vector when the function is called. Our loop checks if the number that's being offered is already in our list of numbers. If it is, we print a message and return -1 -- which, back in main, prompts temp == -1, and loops us back to `requestPlacement()`. If our number isn't present by the end of the loop, we return the **choice** value, and main continues down its path.

Once main has all of the values we need in **placements**, we use `announceCards()`, same as in our previous path, to format our messaging correctly for the upcoming cards. Then, we loop through printing each card one by one. This time, instead of just using the `deck[i]` that we used when printing from the top of the deck, we use `deck[placements[i]].GetCardString()`, which fills in the exact inputs, in order, from the placements vector that was just filled by the user's inputs. When printing finishes, we return 0 again to make it clear to the program that we've done what we needed to.

#### response.cpp
> `response.cpp` adjusts the set up of `dailySpread.cpp` to allow players to input a string prompt that helps calculate the seed used to shuffle their deck. After this, it follows the same process as `dailySpread.cpp` of asking players how many cards they'd like drawn, and where they'd like them drawn from in the deck.

`response.cpp` adds a single prototype compared to `dailySpread.cpp`. This is `getQuestion()`, a function that returns an unsigned int. `response.cpp` then otherwise begins like the previous iterations: defining the needed variables, creating a **deck** with `buildDeck()`, checking that the **deck** is not empty, and printing an initial message with `printWelcome()`.

After this, we introduce a **seed** that is declared as the output of `getQuestion()`. In the associated function, we create a string **question**, which we initialize as empty. Plays are then able to input any text they wish -- this cin does _not_ have any verification that it is correct, as players can enter as much or little as they like for this input.

> As this is meant to facilitate people having "full control" of their seed, though not visibly, it doesn't seem valuable to try and force them to format their question a specific way, or include a certain amount of characters in their response at a minimum or maximum. With how cin works, players must put in at least one character, and if their plan is to put in just one character, that is their perogative, as far as the scope of this program is concerned.

We then calculate an unsigned **value** starting at 0. We iterate through each character in the **question** one by one, getting the ascii value of that character using `int(question[c])` and adding it to our **value**. Once we've looped through all the characters, we return the value to main.

From here, the function works much the same as `dailySpread.cpp` -- the seed is fed into `default_random_engin()` to create an **rng** value, which is used in `shuffle()` to shuffle the deck. The player is then prompted for the number of cards to draw with `requestDraw()`, and where they would like to draw cards from with `requestPlace()`.

If the player draws from the top of the deck, they are then given their cards and the program ends. If the player wants to draw from specific places in teh deck, we follow our process of creatings a **placements** vector, using `requestPlacement()` to get values, and pushing those values into placements until it's full. Once it is, we similarly announce and print the card(s) using `deck[placements[i]].GetCardString()`, then end the program.
