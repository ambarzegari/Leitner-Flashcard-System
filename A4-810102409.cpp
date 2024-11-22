#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ADD_FLASHCARD = "add_flashcard";
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
};

int main()
{
    Leitner leitner_boxes;

    string command;
    while (cin >> command)
    {
        if (command == "add_flashcard")
        {
            leitner_boxes.addFlashcard();
        }
    }
}