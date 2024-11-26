#ifndef LEITNER_H
#define LEITNER_H "LEITNER_H"

#include "Day.hpp"
#include "Flashcard.hpp"
#include "Box.hpp"


#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Leitner
{
private:
    vector<Flashcard *> flashcard;
    vector<Flashcard *> today_flashcards;

    vector<Day> days;

    int streak;
    int mastered_flashcards;
    int total_days_participated;

    Box daily;
    Box once_in_three_days;
    Box weekly;
    Box monthly;

public:
    Leitner();
    ~Leitner();
    void addFlashcard();
    void reviewToday();
    void nextDay();
    void printStreak();
    void getReport();
    void getProgressReprt();
};

#endif