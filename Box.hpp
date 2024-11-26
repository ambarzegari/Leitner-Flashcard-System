#ifndef BOX_H
#define BOX_H "BOX_H"

using namespace std;
#include "Flashcard.hpp"


class Box
{
private:
    vector<Flashcard *> flashcard;

public:
    Box();
    void addFlashcardToBox(Flashcard *flashcard_ptr);
    Flashcard *getFlashcard(int i);
    void deleteFlashcardFromBox(Flashcard *flashcard_ptr);
    int numberOfFlashcardInBox();
    vector<Flashcard *> getFlashcardsInBox();
};


#endif