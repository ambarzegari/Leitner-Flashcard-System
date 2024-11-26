#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
const string REVIEW_TODAY = "review_today";
const string NEXT_DAY = "next_day";
const string STREAK = "streak";
const string GET_REPORT = "get_report";
const string GET_PROGRESS_REPORT = "get_progress_report";

const string COMPLETE_REVIEW_MASSAGE = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!";
const string FLASHCARD_ADDED_MASSAGE = "flashcards added to the daily box";
const string REPORT_MASSAGE = "Keep up the great work! You're making steady progress toward mastering your flashcards.";

class Flashcard
{
private:
    string question;
    string answer;
    int number_of_incorrect_answer;
    bool review;

public:
    Flashcard(string _question, string _answer)
    {
        question = _question;
        answer = _answer;
        number_of_incorrect_answer = 0;
        review = false;
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
    void reviweTrue()
    {
        review = true;
    }
    void reviewFalse()
    {
        review = false;
    }
    bool readStatus()
    {
        return review;
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
        auto fc = flashcard.end();
        if (fc == find(flashcard.begin(), flashcard.end(), flashcard_ptr))
        {
        flashcard.push_back(flashcard_ptr);
        }
    }
    Flashcard *getFlashcard(int i)
    {
        return flashcard[i];
    }
    void deleteFlashcardFromBox(Flashcard *flashcard_ptr)
    {
        auto it = find(flashcard.begin(), flashcard.end(), flashcard_ptr);
        if (it != flashcard.end())
        {
            flashcard.erase(it);
        }
    }
    int numberOfFlashcardInBox()
    {
        return flashcard.size();
    }
    vector<Flashcard *> getFlashcardsInBox() { return flashcard; }
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
        correctAnswer++;
    }
    void increseIncorrectAnswer()
    {
        incorrectAnswer++;
    }
};

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
    Leitner()
    {
        flashcard = {};
        days = {Day(1)};
        streak = 0;
        mastered_flashcards = 0;
        total_days_participated = 0;
    };
    ~Leitner()
    {
        for (int i = 0; i < flashcard.size(); i++)
        {
            delete flashcard[i];
        }
    }
    void addFlashcard()
    {
        string question;
        string answer;

        Flashcard *fc;

        string s;
        getline(cin, s);
        int number_of_question = stoi(s);

        for (int i = 0; i < number_of_question; i++)
        {
            getline(cin, question);
            getline(cin, answer);
            fc = new Flashcard(question, answer);
            flashcard.push_back(fc);
            daily.addFlashcardToBox(fc);
        }

        cout << FLASHCARD_ADDED_MASSAGE << endl;
    }
    void reviewToday()
    {
        Flashcard *fc;

        string user_answer;

        int number_of_flashcards;
        cin >> number_of_flashcards;

        if (days[days.size() - 1].getCorrectAnswerNumber() == 0 && days[days.size() - 1].getIncorrectAnswerNumber() == 0)
        {
            streak++;
            total_days_participated++;

            if (days[days.size() - 1].getDayNumber() % 30 == 0)
            {
                for (int i = 0; i < monthly.numberOfFlashcardInBox(); i++)
                {
                    today_flashcards.push_back(monthly.getFlashcard(i));
                }
            }
            if (days[days.size() - 1].getDayNumber() % 7 == 0)
            {
                for (int i = 0; i < weekly.numberOfFlashcardInBox(); i++)
                {
                    today_flashcards.push_back(weekly.getFlashcard(i));
                }
            }
            if (days[days.size() - 1].getDayNumber() % 3 == 0)
            {
                for (int i = 0; i < once_in_three_days.numberOfFlashcardInBox(); i++)
                {
                    today_flashcards.push_back(once_in_three_days.getFlashcard(i));
                }
            }
            if (days[days.size() - 1].getDayNumber() % 1 == 0)
            {
                for (int i = 0; i < daily.numberOfFlashcardInBox(); i++)
                {
                    today_flashcards.push_back(daily.getFlashcard(i));
                }
            }
        }

        for (int i = 0; i < number_of_flashcards; i++)
        {
            fc = today_flashcards[i];
            while (fc->readStatus())
            {
                i++;
                fc = today_flashcards[i];
            }

            fc->reviweTrue();
            cout << "Flashcard: " << fc->getQuestion() << endl;
            cout << "Your answer: ";
            cin >> user_answer;
            cout << endl;
            if (fc->checkAnswer(user_answer))
            {
                if (find(daily.getFlashcardsInBox().begin(), daily.getFlashcardsInBox().end(), fc) != daily.getFlashcardsInBox().end())
                {
                    daily.deleteFlashcardFromBox(fc);
                    once_in_three_days.addFlashcardToBox(fc);
                }
                else if (find(once_in_three_days.getFlashcardsInBox().begin(), once_in_three_days.getFlashcardsInBox().end(), fc) != once_in_three_days.getFlashcardsInBox().end())
                {
                    once_in_three_days.deleteFlashcardFromBox(fc);
                    weekly.addFlashcardToBox(fc);
                }
                else if (find(weekly.getFlashcardsInBox().begin(), weekly.getFlashcardsInBox().end(), fc) != weekly.getFlashcardsInBox().end())
                {
                    weekly.deleteFlashcardFromBox(fc);
                    monthly.addFlashcardToBox(fc);
                }
                else if (find(monthly.getFlashcardsInBox().begin(), monthly.getFlashcardsInBox().end(), fc) != monthly.getFlashcardsInBox().end())
                {
                    mastered_flashcards++;
                    monthly.deleteFlashcardFromBox(fc);
                }
                cout << "Your answer was correct! Well done, keep it up!" << endl;
                days[days.size() - 1].increseCorrectAnswer();
            }
            else
            {
                fc->increaseNumberOfIncorrectAnswer();
                if (fc->getNumberOfIncorrectAnswer() == 2)
                {
                    if (find(once_in_three_days.getFlashcardsInBox().begin(), once_in_three_days.getFlashcardsInBox().end(), fc) != once_in_three_days.getFlashcardsInBox().end())
                    {
                        once_in_three_days.deleteFlashcardFromBox(fc);
                        daily.addFlashcardToBox(fc);
                    }
                    else if (find(weekly.getFlashcardsInBox().begin(), weekly.getFlashcardsInBox().end(), fc) != weekly.getFlashcardsInBox().end())
                    {
                        weekly.deleteFlashcardFromBox(fc);
                        once_in_three_days.addFlashcardToBox(fc);
                    }
                    else if (find(monthly.getFlashcardsInBox().begin(), monthly.getFlashcardsInBox().end(), fc) != monthly.getFlashcardsInBox().end())
                    {
                        monthly.deleteFlashcardFromBox(fc);
                        weekly.addFlashcardToBox(fc);
                    }
                }
                cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
                days[days.size() - 1].increseIncorrectAnswer();
            }
        }

        cout << COMPLETE_REVIEW_MASSAGE << endl;
    }

    void nextDay()
    {

        Day oldDay = days[days.size() - 1];
        Day newDay = Day(days.size() + 1);
        days.push_back(newDay);

        for (int i = 0; i < today_flashcards.size(); i++)
        {
            Flashcard *fc = today_flashcards[i];
            if (!fc->readStatus())
            {
                if (find(once_in_three_days.getFlashcardsInBox().begin(), once_in_three_days.getFlashcardsInBox().end(), fc) != once_in_three_days.getFlashcardsInBox().end())
                {
                    once_in_three_days.deleteFlashcardFromBox(fc);
                    daily.addFlashcardToBox(fc);
                }
                else if (find(weekly.getFlashcardsInBox().begin(), weekly.getFlashcardsInBox().end(), fc) != weekly.getFlashcardsInBox().end())
                {
                    weekly.deleteFlashcardFromBox(fc);
                    once_in_three_days.addFlashcardToBox(fc);
                }
                else if (find(monthly.getFlashcardsInBox().begin(), monthly.getFlashcardsInBox().end(), fc) != monthly.getFlashcardsInBox().end())
                {
                    monthly.deleteFlashcardFromBox(fc);
                    weekly.addFlashcardToBox(fc);
                }
            }

            fc->reviewFalse();
        }

        today_flashcards.clear();

        if (oldDay.getCorrectAnswerNumber() == 0 && oldDay.getIncorrectAnswerNumber() == 0)
        {
            streak = 0;
        }
        cout << "Good morning! Today is day " << newDay.getDayNumber() << " of our journey." << endl;
        cout << "Your current streak is: " << streak << endl;
        cout << "Start reviewing to keep your streak!" << endl;
    }
    void printStreak()
    {
        cout << "Your current streak is: " << streak << endl;
        cout << "Keep going!" << endl;
    }
    void getReport()
    {
        int start;
        int end;

        int correct = 0;
        int incorrect = 0;

        cin >> start;
        cin >> end;

        if (start != end)
        {
            for (int i = 0; i <= end - start; i++)
            {
                correct += days[start - 1 + i].getCorrectAnswerNumber();
                incorrect += days[start - 1 + i].getIncorrectAnswerNumber();
            }
            cout << "Day: " << start << " to " << end << endl;
            cout << "Correct Answers: " << correct << endl;
            cout << "Incorrect Answers: " << incorrect << endl;
            cout << "Total: " << incorrect + correct << endl;
        }
        else
        {
            cout << "Day: " << start << endl;
            cout << "Correct Answers: " << days[start - 1].getCorrectAnswerNumber() << endl;
            cout << "Incorrect Answers: " << days[start - 1].getIncorrectAnswerNumber() << endl;
            cout << "Total: " << days[start - 1].getCorrectAnswerNumber() + days[start - 1].getIncorrectAnswerNumber() << endl;
        }
    }
    void getProgressReprt()
    {
        cout << "Challenge Progress Report:" << endl
             << endl;
        cout << "Day of the Challenge: " << days.size() << endl;
        cout << "Streak: " << streak << endl;
        cout << "Total Days Participated: " << total_days_participated << endl;
        cout << "Mastered Flashcards: " << mastered_flashcards << endl
             << endl;
        cout << REPORT_MASSAGE << endl;
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
        else if (command == STREAK)
        {
            leitner_boxes.printStreak();
        }
        else if (command == GET_REPORT)
        {
            leitner_boxes.getReport();
        }
        else if (command == GET_PROGRESS_REPORT)
        {
            leitner_boxes.getProgressReprt();
        }
    }
    return 0;
}