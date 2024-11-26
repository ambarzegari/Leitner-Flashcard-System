#include "Day.hpp"


Day::Day(int day)
{
    dayNumber = day;
    correctAnswer = 0;
    incorrectAnswer = 0;
}
int Day::getDayNumber() { return dayNumber; }
int Day::getCorrectAnswerNumber() { return correctAnswer; }
int Day::getIncorrectAnswerNumber() { return incorrectAnswer; }
void Day::increseCorrectAnswer()
{
    correctAnswer++;
}
void Day::increseIncorrectAnswer()
{
    incorrectAnswer++;
}