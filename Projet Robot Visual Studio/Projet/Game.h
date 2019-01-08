#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "Terrain.h"
#include "Robot.h"
#include <string>

class Game
{
    public:
		//Constructeur
        Game();
		//Destructeur
        ~Game();

		//Méthode de modification
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
		void SelectButton(int x, int y, bool & quittez);

		//Méthode de récupération de donnée
		bool fin() const;
		Terrain terrain() const;
		string name() const;
		Robot robot() const;
		
    private:
		//Méthode privée
		void Emplacement();
		void browseFile();

		//Variable privée
        Robot d_robot;
        Terrain d_terrain;
		string d_name;
		vector<Cases> d_boutton;
};

#endif // GAME_H
