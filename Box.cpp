    #include "Box.hpp"
    #include "Flashcard.hpp"
    #include <bits/stdc++.h>
    #include <vector>
    
    
    
    Box::Box()
    {
        flashcard = {};
    }
    void Box::addFlashcardToBox(Flashcard *flashcard_ptr)
    {
        auto fc = flashcard.end();
        if (fc == find(flashcard.begin(), flashcard.end(), flashcard_ptr))
        {
        flashcard.push_back(flashcard_ptr);
        }
    }
    Flashcard *Box::getFlashcard(int i)
    {
        return flashcard[i];
    }
    void Box::deleteFlashcardFromBox(Flashcard *flashcard_ptr)
    {
        auto it = find(flashcard.begin(), flashcard.end(), flashcard_ptr);
        if (it != flashcard.end())
        {
            flashcard.erase(it);
        }
    }
    int Box::numberOfFlashcardInBox()
    {
        return flashcard.size();
    }
    vector<Flashcard *> Box::getFlashcardsInBox() { return flashcard; }