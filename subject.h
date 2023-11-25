#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"


using namespace std;

// Abstract Subject Class

class Subject {
    vector <class Observer *> observers;

    public:
        Subject();
        void attach(Observer *o);
        void detach(Observer *o);
        virtual void notifyObservers() ;
        virtual ~Subject() = 0;
};

#endif
