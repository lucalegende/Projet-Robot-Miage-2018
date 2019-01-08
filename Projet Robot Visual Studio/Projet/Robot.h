#ifndef ROBOT_H
#define ROBOT_H

#include "Cases.h"

class Robot
{
    public:
		//Constructeur
        Robot();
        Robot(Cases emplacement,int direction=90);
		//Destructeur
        ~Robot();

		//M�thode de modification ou d'affichage
        void draw() const;
        void position() const;
		void turnLeft();
		void turnRight();
		void turnTop();
		void turnBottom();
		void move();
		void operator=(const Robot& R);

		//M�thode de recup�ration de valeur
        int direction() const;
        Cases cases() const;

    private:
		//Variable priv�e
        Cases d_cases;
        int d_direction;
    };

#endif // ROBOT_H
