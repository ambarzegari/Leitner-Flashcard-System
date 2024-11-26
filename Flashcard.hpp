#ifndef FLASHCARD_H
#define FLASHCARD_H "FLASHCARD_H"

#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>



using namespace std;

class Flashcard
{
private:
    string question;
    string answer;
    int number_of_incorrect_answer;
    bool review;

public:
    Flashcard(string _question, string _answer);
    string getQuestion();
    string getAnswer();
    int getNumberOfIncorrectAnswer();
    void increaseNumberOfIncorrectAnswer();
    void resetToZeroNumberOfIncorrectAnswer();
    bool checkAnswer(string userAnswer);
    void reviweTrue();
    void reviewFalse();
    bool readStatus();
};

#endif