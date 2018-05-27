#ifndef _STATPANE_H_
#define _STATPANE_H_

#include "Pane.h"

class StatPane : public Pane{
    public:
        StatPane(int x, int y, int width, int height);
        ~StatPane();

        virtual void Draw();
        void turnPass();
    protected:
        int turn;
};

#endif