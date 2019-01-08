#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "Terrain.h"
#include "Robot.h"
#include <string>

class Game
{
    public:
        Game();
        virtual ~Game();
        void LoadGame(int& window);
		void Affichage();
        void PlayGame();
        void moveRobot(int i,int i2);
        void moveRobotToTop();
        void moveRobotToBottom();
        void moveRobotToLeft();
        void moveRobotToRight();
		void AlgoPledge(int direction, vector<Cases>& t1);
		void AlgoMainGauche(vector<Cases>& t1);
		void AlgoMaindroite(vector<Cases>& t1);
		bool fin() const;
		Terrain terrain() const;
		string name() const;
		Robot robot() const;
		void SelectButton(int x, int y, bool & quittez);

    protected:

    private:
		void Emplacement();
		void browseFile();
        Robot d_robot;
        Terrain d_terrain;
		string d_name;
		vector<Cases> d_boutton;
};

#endif // GAME_H
