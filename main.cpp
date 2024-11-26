#include "Leitner.hpp"
#include "Day.hpp"
#include "Box.hpp"
#include "Flashcard.hpp"
#include <iostream>

const string ADD_FLASHCARD = "add_flashcard";
const string REVIEW_TODAY = "review_today";
const string NEXT_DAY = "next_day";
const string STREAK = "streak";
const string GET_REPORT = "get_report";
const string GET_PROGRESS_REPORT = "get_progress_report";

const string COMPLETE_REVIEW_MASSAGE = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!";
const string FLASHCARD_ADDED_MASSAGE = "flashcards added to the daily box";
const string REPORT_MASSAGE = "Keep up the great work! You're making steady progress toward mastering your flashcards.";

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