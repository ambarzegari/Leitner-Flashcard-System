#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
const string REVIEW_TODAY = "review_today";
const string NEXT_DAY = "next_day";
const string STREAK = "streak";

class Flashcard
{
private:
    string question;
    string answer;
    int number_of_incorrect_answer;

public:
    Flashcard(string _question, string _answer)
    {
        question = _question;
        answer = _answer;
        number_of_incorrect_answer = 0;
    }
    string getQuestion() { return question; }
    string getAnswer() { return answer; }
    int getNumberOfIncorrectAnswer() { return number_of_incorrect_answer; }
    void increaseNumberOfIncorrectAnswer()
    {
        number_of_incorrect_answer += 1;
    }
    void resetToZeroNumberOfIncorrectAnswer()
    {
        number_of_incorrect_answer = 0;
    }
};

class Box
{
private:
    vector<Flashcard *> flashcard;

public:
    Box()
    {
        flashcard = {};
    }
    void addFlashcardToBox(Flashcard *flashcard_ptr)
    {
        flashcard.push_back(flashcard_ptr);
    }
    Flashcard *getFlashcard(int i)
    {
        return flashcard[i];
    }
    void deleteFlashcardFromBox(Flashcard *flashcard_ptr)
    {
        flashcard.erase(find(flashcard.begin(), flashcard.end(), flashcard_ptr));
    }
};

class Day
{
private:
    int dayNumber;
    int correctAnswer;
    int incorrectAnswer;

public:
    Day(int day)
    {
        dayNumber = day;
        correctAnswer = 0;
        incorrectAnswer = 0;
    }
    int getDayNumber() { return dayNumber; }
    int getCorrectAnswerNumber() { return correctAnswer; }
    int getIncorrectAnswerNumber() { return incorrectAnswer; }
};

class Leitner
{
private:
    vector<Flashcard *> flashcard;

    vector<Day> days;

    int streak;

    Box daily;
    Box once_in_three_days;
    Box weekly;
    Box monthly;

public:
    Leitner()
    {
        flashcard = {};
        days = {Day(1)};
        streak = 0;
    };
    void addFlashcard()
    {
        string question;
        string answer;

        Flashcard *fc;

        int number_of_question;
        cin >> number_of_question;

        for (int i = 0; i < number_of_question; i++)
        {
            cin >> question;
            cin >> answer;
            fc = new Flashcard(question, answer);
            flashcard.push_back(fc);
            daily.addFlashcardToBox(fc);
        }
    }
    void reviewToday()
    {
        Flashcard *fc;

        string user_answer;

        int number_of_flashcards;
        cin >> number_of_flashcards;

        for (int i = 0; i < number_of_flashcards; i++)
        {
            fc = daily.getFlashcard(i);

            cout << "Flashcard: " << fc->getQuestion() << endl;
            cout << "Your answer: ";
            cin >> user_answer;

            if (fc->getAnswer() == user_answer)
            {   
                cout << "Your answer was correct! Well done, keep it up!" << endl;
                weekly.addFlashcardToBox(fc);
                daily.deleteFlashcardFromBox(fc);
                i -= 1;
                number_of_flashcards -= 1;
            }
            else
            {
                cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
            }
        }

        cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
    }
    void nextDay(){

        Day oldDay = days[days.size()-1];
        Day newDay = Day(days.size()+1);
        days.push_back(newDay);

        if (oldDay.getCorrectAnswerNumber() == 0 && oldDay.getIncorrectAnswerNumber() == 0)
        {
            streak = 0;
        }
        else
        {
            streak += 1;
        }
        cout << "Good morning! Today is day " << newDay.getDayNumber() << " of our journey." << endl;
        cout << "Your current streak is: " << streak << endl;
        cout << "Start reviewing to keep your streak!" << endl;
    }
};

int main()
{
    Leitner leitner_boxes;

    string command;
    while (cin >> command)
    {
        if (command == ADD_FLASHCARD)
        {
            leitner_boxes.addFlashcard();
        }
        else if (command == REVIEW_TODAY)
        {
            leitner_boxes.reviewToday();
        }
        else if (command == NEXT_DAY)
        {
            leitner_boxes.nextDay();
        }
    }
}