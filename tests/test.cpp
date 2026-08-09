//
//  test.cpp
//  project
//
//  Created by Aqsa Agro on 2026-08-08.
//

#include "Card.hpp"
#include <iostream>
#include <string>

using namespace std;

//helper function will print out whether a test passes or fails. Condtions will be true when code works as expected.
void checkTest(bool condition, const string& testName)
{
    if (condition)
    {
        cout << "PASS: " << testName << endl;
    }
    else
    {
        cout << "FAIL: " << testName << endl;
    }
}

int main()
{
    cout << "TESTING CARD CLASS" << endl;
  


  //TEST 1: checks that a regular number card stores the colour, type, and value that were passed into the construtor.
    Card blueEight("blue", "number", 8);

    checkTest(blueEight.getColour() == "blue",
              "Number card stores the correct colour");

    checkTest(blueEight.getType() == "number",
              "Number card stores the correct type");

    checkTest(blueEight.getValue() == 8,
              "Number card stores the correct value");


  //TEST 2: checks ot see whether action card's value gets changed to -1. While also checking that action card stores action and colour passed in.
    Card redSkip("red", "skip", 5);

    checkTest(redSkip.getColour() == "red",
              "Action card stores the correct colour");

    checkTest(redSkip.getType() == "skip",
              "Action card stores the correct type");

    checkTest(redSkip.getValue() == -1,
              "Action card value is changed to -1");


   //TEST 3: checks to see whether cards that have different numbers but same colour can be played.
    Card blueTwo("blue", "number", 2);

    checkTest(blueTwo.canPlayOn(blueEight),
              "Card can be played when colours match");


  //TEST 4: checks to see whether cards that have different colours but same number can be played.
    Card yellowEight("yellow", "number", 8);

    checkTest(yellowEight.canPlayOn(blueEight),
              "Number card can be played when values match");


  //TEST 5: checks to see whether cards that have different colours but the same action can be played.
    Card greenSkip("green", "skip", 0);

    checkTest(greenSkip.canPlayOn(redSkip),
              "Action card can be played when action types match");


//TEST 6: checks if the card matches the top card by colour or number
    Card greenThree("green", "number", 3);

    checkTest(!greenThree.canPlayOn(blueEight),
              "Different colour and different number are rejected");


//TEST 7: checks whether action cards with different colours and different actions are playable
    Card yellowReverse("yellow", "reverse", 0);

    checkTest(!yellowReverse.canPlayOn(redSkip),
              "Different action types and colours are rejected");


// TEST 8: checks to see whether the lowest and highest possible values are stored correctly.
    Card redZero("red", "number", 0);
    Card greenNine("green", "number", 9);

    checkTest(redZero.getValue() == 0,
              "Lowest number card value (0) is stored correctly");

    checkTest(greenNine.getValue() == 9,
              "Highest number card value (9) is stored correctly");


// TEST 9: checks that boundary values work correctly inside the fucntion canPlayOn(), not only inside getter function
    Card yellowZero("yellow", "number", 0);
    Card redNine("red", "number", 9);

    checkTest(yellowZero.canPlayOn(redZero),
              "Cards with the lowest value (0) can match");

    checkTest(redNine.canPlayOn(greenNine),
              "Cards with the highest value (9) can match");


   //TEST 10: testing to see if printCard() prints as expected
    cout << endl;
    cout << "Testing printCard():" << endl;

    cout << "Expected: 8 blue" << endl;
    cout << "Actual:   ";
    blueEight.printCard();
    cout << endl;

    cout << "Expected: red skip" << endl;
    cout << "Actual:   ";
    redSkip.printCard();
    cout << endl;


    return 0;
}
