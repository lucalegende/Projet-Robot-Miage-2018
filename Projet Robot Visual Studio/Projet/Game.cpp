#include "Game.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <random>


using namespace std;

int windo = 0;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> rando(0, 1);

//Constructeur
Game::Game():
    d_terrain{},
	d_name{""}
{
	browseFile();
}

//Destructeur
Game::~Game()
{
}

//Démarre le jeux
void Game::LoadGame(int& window)
{
	if (d_name != "")
	{
		windo = window;
		Affichage();
		PlayGame();
	}
}

//Affichage du terrain du robot et de la fin
void Game::Affichage()
{
	d_terrain.afficherTerrain();
	d_robot.draw();

	Emplacement();

	setcolor(WHITE);
	for (auto boutton : d_boutton)
	{
		rectangle(boutton.left(), boutton.top(), boutton.right(), boutton.bottom());
	}

	outtextxy(d_boutton[0].left() + 20, d_boutton[0].bottom() + 10, "Algo1");
	outtextxy(d_boutton[1].left() + 20, d_boutton[1].bottom() + 10, "Algo2");
	outtextxy(d_boutton[2].left() + 20, d_boutton[2].bottom() + 10, "Retour");
}

//Emplacement des bouton
void Game::Emplacement()
{
	int  left = d_terrain.casesPrecis(d_terrain.longeur() - 1).left() + 70,
		top = d_terrain.casesPrecis(d_terrain.longeur() - 1).top() + 20,
		right = d_terrain.casesPrecis(d_terrain.longeur() - 1).right() + 180,
		bottom = d_terrain.casesPrecis(d_terrain.longeur() - 1).bottom();

	for (int i = 0; i < 3; ++i)
	{
		d_boutton.push_back(Cases{ left,top,right,bottom,"button" });
		top += 70; bottom += 70;
	}
}

//Ouverture du  fichier terrain
void Game::browseFile()
{
    char filename[MAX_PATH];


	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Tous\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;


	if (GetOpenFileNameA(&ofn))
	{
		d_name = filename;

		string line;
		std::ifstream myfile(filename);

		if (myfile.is_open())
		{
			int longeur, largeur;
			myfile >> longeur >> largeur;

			d_terrain = Terrain{longeur,largeur};

			int i = 0;

			getline(myfile, line);

			while (getline(myfile, line) && i < d_terrain.cases().size())
			{
			    for(auto l : line)
                {
                    if(l == '*')
                    {
                        d_terrain.Type(i,"mur");
                        i++;
                    }
                    else if(l =='o')
                    {
                        d_terrain.Type(i,"robot");
                        d_robot = Robot{d_terrain.casesPrecis(i)};
                        i++;
                    }
					else if (l == 'f')
					{
						d_terrain.Type(i, "fin");
						i++;
					}
                    else
                    {
                        d_terrain.Type(i,"vide");
                        i++;
                    }
                }

			}
			myfile.close();
		}
		else
			cout << "Impossible a ouvrir" << endl;
	}
}

//Change le robot de cases
void Game::moveRobot(int init,int final){

	if(init < d_terrain.longeur()*d_terrain.largeur())
	{
		d_robot.move();
		d_terrain.moveRobot(init, final);
		d_robot.draw();
	}
}

//Le robot chagne de cases vers le haut
void Game::moveRobotToTop()
{
	auto t1 = d_terrain.cases();
	int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

    d_robot.turnTop();
	if (index - d_terrain.longeur() >= 0)
	{
		if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() != "mur")
		{
			moveRobot(index, (index - d_terrain.longeur()));
		}
	}
   
}

//Le robot chagne de cases vers le bas
void Game::moveRobotToBottom()
{
	auto t1 = d_terrain.cases();
	int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

    d_robot.turnBottom();
	if (index + d_terrain.longeur() < d_terrain.longeur()*d_terrain.largeur())
	{
		if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() != "mur")
		{
			moveRobot(index, (index + d_terrain.longeur()));
		}
	}
    
}

//Le robot chagne de cases vers la gauche
void Game::moveRobotToLeft()
{
	auto t1 = d_terrain.cases();
	int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

    d_robot.turnLeft();
	if (index % d_terrain.longeur() > 0)
	{
		if (d_terrain.casesPrecis(index - 1).type() != "mur")
		{
			moveRobot(index, (index - 1));
		}
	}
   
}

//Le robot chagne de cases vers la droite
void Game::moveRobotToRight()
{
	auto t1 = d_terrain.cases();
    int index = distance(t1.begin(), find(t1.begin(), t1.end(),d_robot.cases()));

    d_robot.turnRight();
	if ((index-(d_terrain.longeur()-1)) % d_terrain.longeur() != 0)
	{
		if (index + 1 < d_terrain.longeur()*d_terrain.largeur())
		{
			if (d_terrain.casesPrecis(index + 1).type() != "mur")
			{
				moveRobot(index, (index + 1));
			}
		}
		
	}
	
    
}

//Algorithme de la main gauche
void Game::AlgoMainGauche(vector<Cases>& t1)
{
	int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

	Sleep(50);
	//direction du haut
	if (d_robot.direction() == 90)
	{
		if (d_terrain.casesPrecis(index - 1).type() == "fin")
		{
				moveRobotToLeft();
		}
		else if (d_terrain.casesPrecis(index - 1).type() == "vide")
		{
			if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "vide" || d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
			{
				moveRobotToLeft();
			}

		}
		else if (d_terrain.casesPrecis(index - 1).type() == "mur")
		{
			moveRobotToTop();
			if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
			{
				d_robot.turnRight();
			}
		}
		else
		{
			d_robot.turnLeft();
		}


	}
	//direction de la droit
	else if (d_robot.direction() == 180)
	{
		if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "fin")
		{
				moveRobotToTop();
		}
		else if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "vide")
		{
			if (d_terrain.casesPrecis(index + 1).type() == "vide" || d_terrain.casesPrecis(index + 1).type() == "mur")
			{
				moveRobotToTop();
			}

		}
		else if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
		{
			moveRobotToRight();
			if (d_terrain.casesPrecis(index + 1).type() == "mur")
			{
				d_robot.turnBottom();
			}
		}
		else
		{
			d_robot.turnTop();
		}
	}
	//direction du bas
	else if (d_robot.direction() == 270)
	{
		if (d_terrain.casesPrecis(index + 1).type() == "fin")
		{
			moveRobotToRight();
		}
		else if (d_terrain.casesPrecis(index + 1).type() == "vide")
		{
			if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "vide" || d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
			{
				moveRobotToRight();
			}

		}
		else if (d_terrain.casesPrecis(index + 1).type() == "mur")
		{
			moveRobotToBottom();
			if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
			{
				d_robot.turnLeft();
			}
		}
		else
		{
			d_robot.turnRight();
		}
	}
	//direction de la gauche
	else if (d_robot.direction() == 0)
	{
		if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "fin")
		{
				moveRobotToBottom();
		}
		else if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "vide")
		{
			if (d_terrain.casesPrecis(index - 1).type() == "vide" || d_terrain.casesPrecis(index - 1).type() == "mur")
			{
				moveRobotToBottom();
			}

		}
		else if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
		{
			moveRobotToLeft();
			if (d_terrain.casesPrecis(index - 1).type() == "mur")
			{
				d_robot.turnTop();
			}
		}
		else
		{
			d_robot.turnBottom();
		}
	}
}

//Algorithme de pledge
void Game::AlgoPledge(int direction ,vector<Cases>& t1)
{
	switch (direction)
	{
	case 0:
		AlgoMaindroite(t1);
		break;
	case 1:
		AlgoMainGauche(t1);
		break;
	default:
		break;
	}
}

//Algorithme de la main gauche
void Game::AlgoMaindroite(vector<Cases>& t1)
{

	int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

	Sleep(50);
	//direction du haut
	if (d_robot.direction() == 90)
	{
		if (d_terrain.casesPrecis(index + 1).type() == "fin")
		{
				moveRobotToRight();
		}
		else if (d_terrain.casesPrecis(index + 1).type() == "vide")
		{
			if (index - d_terrain.longeur() > 0)
			{
				if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "vide" || d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
				{
					moveRobotToRight();
				}
			}
			

		}
		else if (d_terrain.casesPrecis(index + 1).type() == "mur")
		{
			moveRobotToTop();
			if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
			{
				d_robot.turnLeft();
			}
		}
		else
		{
			d_robot.turnRight();
		}


	}
	//direction de la droit
	else if (d_robot.direction() == 180)
	{
		if (index + d_terrain.longeur() > 0 && index - d_terrain.longeur() < d_terrain.longeur()*d_terrain.largeur() - 1)
		{
			if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "fin")
			{
				moveRobotToBottom();
			}
			else if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "vide")
			{

				if (d_terrain.casesPrecis(index + 1).type() == "vide" || d_terrain.casesPrecis(index + 1).type() == "mur")
				{
					moveRobotToBottom();
				}

			}
			else if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
			{
				moveRobotToRight();
				if (d_terrain.casesPrecis(index + 1).type() == "mur")
				{
					d_robot.turnTop();
				}
			}
			else
			{
				d_robot.turnBottom();
			}
		}
	}
	//direction du bas
	else if (d_robot.direction() == 270)
	{

		if (d_terrain.casesPrecis(index -1).type() == "fin")
		{
			moveRobotToLeft();
		}
		else if (d_terrain.casesPrecis(index - 1).type() == "vide")
		{
			if (index - d_terrain.longeur() > 0 && index - d_terrain.longeur() < d_terrain.longeur()*d_terrain.largeur() - 1)
			{
				if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "vide" || d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
				{
					moveRobotToLeft();
				}
			}

		}
		else if (d_terrain.casesPrecis(index - 1).type() == "mur")
		{
			moveRobotToBottom();
			if (d_terrain.casesPrecis(index + d_terrain.longeur()).type() == "mur")
			{
				d_robot.turnRight();
			}
		}
		else
		{
			d_robot.turnLeft();
		}
	}
	//direction de la gauche
	else if (d_robot.direction() == 0)
	{
		if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "fin")
		{
			moveRobotToTop();
		}
		else if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "vide")
		{
			if (index - d_terrain.longeur() > 0 && index - d_terrain.longeur() < d_terrain.longeur()*d_terrain.largeur() - 1)
			{
				if (d_terrain.casesPrecis(index - 1).type() == "vide" || d_terrain.casesPrecis(index - 1).type() == "mur")
				{
					moveRobotToTop();
				}
			}

		}
		else if (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "mur")
		{
			moveRobotToLeft();
			if (d_terrain.casesPrecis(index - 1).type() == "mur")
			{
				d_robot.turnBottom();
			}
		}
		else
		{
			d_robot.turnTop();
		}

	}
}

//Vérifie si le robot arrive a la sortie
bool Game::fin() const
{
	auto t1 = d_terrain.cases();

	int index = distance(t1.begin(), find(t1.begin(), t1.end(), Cases{ d_robot.cases().left(),d_robot.cases().top(),d_robot.cases().right(),d_robot.cases().bottom(),"fin" }));

	if (index <  d_terrain.largeur()*d_terrain.longeur())
	{
		return d_terrain.casesPrecis(index).type() == "fin";
	}
	else
	{
		return false;
	}

}

//Retorune le terrain
Terrain Game::terrain() const
{
	return d_terrain;
}

//retourne le nom du fichier
string Game::name() const
{
	return d_name;
}

//retourne si il y a un robot
Robot Game::robot() const
{
	return d_robot;
}

//Selection du boutton 
void Game::SelectButton(int x, int y, bool &quittez)
{
	int direction = rando(gen);
	auto t1 = d_terrain.cases();

	if (x >= d_boutton[0].left() && x <= d_boutton[0].right() && y >= d_boutton[0].bottom() && y <= d_boutton[0].top())
	{
		while (!fin() && !kbhit())
		{
			t1 = d_terrain.cases();
			AlgoMaindroite(t1);
		}
	}
	else if (x >= d_boutton[1].left() && x <= d_boutton[1].right() && y >= d_boutton[1].bottom() && y <= d_boutton[1].top())
	{
		int index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

		if (index - d_terrain.longeur() > 0)
		{
			while (d_terrain.casesPrecis(index - d_terrain.longeur()).type() == "vide" && !kbhit())
			{

				Sleep(50);
				moveRobotToTop();
				t1 = d_terrain.cases();
				index = distance(t1.begin(), find(t1.begin(), t1.end(), d_robot.cases()));

				if (index - d_terrain.longeur() < 0)
				{
					break;
				}
			}
		}
		
		

		while (!fin() && !kbhit() && index-d_terrain.longeur() >=0)
		{
			t1 = d_terrain.cases();

			AlgoPledge(direction, t1);
		}
	}
	else if (x >= d_boutton[2].left() && x <= d_boutton[2].right() && y >= d_boutton[2].bottom() && y <= d_boutton[2].top())
	{
		closegraph(windo);
		quittez = true;
	}
}

//Méthode permettant de jouer au jeux
void Game::PlayGame()
{
    int x, y, command =0;
	bool end = false;
	cout << "Bonjour Voici notre projet Robot avez appyez sur les 4 fleche pour faire avancer le robot" << endl;

    while (!fin() && command != 27 && !end) {    // until ESC key (#27) is pressed
      
      cout << " COMMAND > ";
	  
	  while (!ismouseclick(WM_LBUTTONDOWN) && !kbhit())
	  {
	  }

	  getmouseclick(WM_LBUTTONDOWN, x, y);

	  if (x >= 0 && y >= 0)
	  {
		  SelectButton(x, y, end);
	  }
	  else
	  {
		  command = getch();  // *WIN32* unbuffered input, non-windows machines may have to change thi

		  switch (command) {
		  case 77: // Right Arrow Key (turn right)
			  cout << "Turn Right\n";

			  moveRobotToRight();
			  break;
		  case 75: // Left Arrow Key (turn left)
			  cout << "Turn Left\n";
			  moveRobotToLeft();
			  break;
		  case 72:  // Up Arrow Key (move forward)
			  cout << "Move Forward\n";
			  moveRobotToTop();
			  break;
		  case 80:  // Down Arrow Key (move backward)
			  cout << "Move Backward\n";
			  moveRobotToBottom();
			  break;
		  }
	  }  
   }

	if (fin())
	{
		cleardevice();
		outtextxy(0, 0, "Vous êtes sortie du labyrinthe");
		outtextxy(0, 20, "Félicitation");
		Sleep(5000);
		closegraph(windo);
	}
}

