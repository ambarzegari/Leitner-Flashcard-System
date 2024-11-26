#include "Flashcard.hpp"


Flashcard::Flashcard(string _question, string _answer)
{
    question = _question;
    answer = _answer;
    number_of_incorrect_answer = 0;
    review = false;
}
string Flashcard::getQuestion() { return question; }
string Flashcard::getAnswer() { return answer; }
int Flashcard::getNumberOfIncorrectAnswer() { return number_of_incorrect_answer; }
void Flashcard::increaseNumberOfIncorrectAnswer()
{
    number_of_incorrect_answer += 1;
}
void Flashcard::resetToZeroNumberOfIncorrectAnswer()
{
    number_of_incorrect_answer = 0;
}
bool Flashcard::checkAnswer(string userAnswer)
{
    if (answer == userAnswer)
    {
        return true;
    }
    return false;
}
void Flashcard::reviweTrue()
{
    review = true;
}
void Flashcard::reviewFalse()
{
    review = false;
}
bool Flashcard::readStatus()
{
    return review;
}