#ifndef ROBOT_H
#define ROBOT_H

#include "Cases.h"

class Robot
{
    public:
        Robot();
        Robot(Cases emplacement,int direction=90);
        virtual ~Robot();
        void draw() const;
        void position() const;
        int direction() const;
        void turnLeft();
        void turnRight();
        void turnTop();
        void turnBottom();
        void move();
        void operator=(const Robot& R);
        Cases cases() const;

    private:
        Cases d_cases;
        int d_direction;
    };

#endif // ROBOT_H
