    #include "Leitner.hpp"

    
    Leitner::Leitner()
    {
        flashcard = {};
        days = {Day(1)};
        streak = 0;
        mastered_flashcards = 0;
        total_days_participated = 0;
    }
    Leitner::~Leitner()
    {
        for (size_t i = 0; i < flashcard.size(); i++)
        {
            delete flashcard[i];
        }
    }
    void Leitner::addFlashcard()
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

        cout << "flashcards added to the daily box" << endl;
    }
    void Leitner::reviewToday()
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

        cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
    }

    void Leitner::nextDay()
    {

        Day oldDay = days[days.size() - 1];
        Day newDay = Day(days.size() + 1);
        days.push_back(newDay);

        for (size_t i = 0; i < today_flashcards.size(); i++)
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
    void Leitner::printStreak()
    {
        cout << "Your current streak is: " << streak << endl;
        cout << "Keep going!" << endl;
    }
    void Leitner::getReport()
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
    void Leitner::getProgressReprt()
    {
        cout << "Challenge Progress Report:" << endl
             << endl;
        cout << "Day of the Challenge: " << days.size() << endl;
        cout << "Streak: " << streak << endl;
        cout << "Total Days Participated: " << total_days_participated << endl;
        cout << "Mastered Flashcards: " << mastered_flashcards << endl
             << endl;
        cout << "Keep up the great work! You're making steady progress toward mastering your flashcards." << endl;
    }