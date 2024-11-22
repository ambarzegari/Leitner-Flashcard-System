#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
const string REVIEW_TODAY = "review_today";
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
    Flashcard* getFlashcard(int i){
        return flashcard[i];
    }
    void deleteFlashcardFromBox(Flashcard *flashcard_ptr)
    {
        flashcard.erase(find(flashcard.begin(), flashcard.end(), flashcard_ptr));
    }
};

class Leitner
{
private:
    vector<Flashcard *> flashcard;
    Box daily;
    Box once_in_three_days;
    Box weekly;
    Box monthly;

public:
    Leitner()
    {
        flashcard = {};
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
    void reviewToday(){
        Flashcard* fc;

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
            }
            else
            {
                cout << "Your answer was incorrect. Don't worry! The correct answer is: " << fc->getAnswer() << ". Keep practicing!" << endl;
            }
            
            
        }
        
        
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
        
        
    }
}