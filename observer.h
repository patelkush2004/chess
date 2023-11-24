#ifndef _OBSERBER_H_
#define _OBSERBER_H_

using namespace std;

// Abstract Observer Class
// No need for .cc file since all methods are virtual

class Observer {
    public:
        virtual void notify() = 0;
        virtual ~Observer() = default;
};

#endif
