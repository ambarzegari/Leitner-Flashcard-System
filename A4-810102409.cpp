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
    bool checkAnswer(string userAnswer)
    {
        if (answer == userAnswer)
        {
            return true;
        }
        return false;
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
    int numberOfFlashcardInBox()
    {
        return flashcard.size();
    }
    /*void reviewFlashcardFromBox(int numOfFc)
    {
        Flashcard *fc;
        string user_answer;

        for (int i = 0; i < numOfFc && i < flashcard.size(); i++)
        {
            fc = flashcard[i];
            cout << "Flashcard: " << fc->getQuestion() << endl;
            cout << "Your answer: ";
            cin >> user_answer;

            if (fc->getAnswer() == user_answer)
            {
                cout << "Your answer was correct! Well done, keep it up!" << endl;
                weekly.addFlashcardToBox(fc);
                daily.deleteFlashcardFromBox(fc);
                i -= 1;
                numOfFc -= 1;
            }
            else
            {
                cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
            }
        }
    }*/
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
    void increseCorrectAnswer()
    {
        correctAnswer += 1;
    }
    void increseIncorrectAnswer()
    {
        incorrectAnswer += 1;
    }
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

        Day today = days[days.size() - 1];

        string user_answer;

        int number_of_flashcards;
        cin >> number_of_flashcards;
        int num_fc = number_of_flashcards;

        if (today.getDayNumber() % 30 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < monthly.numberOfFlashcardInBox(); i++)
            {
                fc = monthly.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    monthly.deleteFlashcardFromBox(fc);
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        weekly.addFlashcardToBox(fc);
                        monthly.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= monthly.numberOfFlashcardInBox();
        }

        if (today.getDayNumber() % 7 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < weekly.numberOfFlashcardInBox(); i++)
            {
                fc = weekly.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    monthly.addFlashcardToBox(fc);
                    weekly.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        once_in_three_days.addFlashcardToBox(fc);
                        weekly.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= weekly.numberOfFlashcardInBox();
        }

        if (today.getDayNumber() % 3 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < once_in_three_days.numberOfFlashcardInBox(); i++)
            {
                fc = once_in_three_days.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    weekly.addFlashcardToBox(fc);
                    once_in_three_days.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                    fc->increaseNumberOfIncorrectAnswer();
                    if (fc->getNumberOfIncorrectAnswer() == 2)
                    {
                        daily.addFlashcardToBox(fc);
                        once_in_three_days.deleteFlashcardFromBox(fc);
                        fc->resetToZeroNumberOfIncorrectAnswer();
                    }
                }
            }
            num_fc -= once_in_three_days.numberOfFlashcardInBox();
        }

        if (today.getDayNumber() % 1 == 0 && num_fc > 0)
        {
            for (int i = 0; i < num_fc && i < daily.numberOfFlashcardInBox(); i++)
            {
                fc = daily.getFlashcard(i);

                cout << "Flashcard: " << fc->getQuestion() << endl;
                cout << "Your answer: ";
                cin >> user_answer;

                if (fc->getAnswer() == user_answer)
                {
                    cout << "Your answer was correct! Well done, keep it up!" << endl;
                    once_in_three_days.addFlashcardToBox(fc);
                    daily.deleteFlashcardFromBox(fc);
                    fc->resetToZeroNumberOfIncorrectAnswer();
                    days[days.size() - 1].increseCorrectAnswer();
                    i -= 1;
                    num_fc -= 1;
                }
                else
                {
                    cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                    days[days.size() - 1].increseIncorrectAnswer();
                }
            }
        }

        cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
    }
    void nextDay()
    {

        Day oldDay = days[days.size() - 1];
        Day newDay = Day(days.size() + 1);
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