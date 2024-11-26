#ifndef DAY_H
#define DAY_H "DAY_H"

using namespace std;


class Day
{
private:
    int dayNumber;
    int correctAnswer;
    int incorrectAnswer;

public:
    Day(int day);
    int getDayNumber();
    int getCorrectAnswerNumber();
    int getIncorrectAnswerNumber();
    void increseCorrectAnswer();
    void increseIncorrectAnswer();
};


#endif