#include "Editeur.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <Windows.h>
#include <fstream>

using std::cout;
using std::endl;
using std::find;
using std::distance;

string nam = ""; //Nom du fichir
int windows; //fenetre actuelle

//Retourne le nom du fichier
string getFileName(const string& s) {

	char sep = '/';

	#ifdef _WIN32
	sep = '\\';
	#endif

	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		return(s.substr(i + 1, s.length() - i));
	}

	return("");
}

//Constructeur
Editeur::Editeur():
    d_terrain{},
	d_robot{0}
{
	BrowseName();
}

//Destructeur
Editeur::~Editeur()
{
}

//Méthode permettant l'affichage du de l'écran
void Editeur::Ecran(int& window)
{
	windows = window;
    Affichage();
	ModificationTerrain();
}

//Retourne le terrain
Terrain Editeur::terrain() const
{
	return d_terrain;
}

//Affichage du terrain et des bouton  
void Editeur::Affichage()
{
	d_terrain.afficherTerrain();

	Emplacement();

	for (auto boutton : d_boutton)
	{
		cout << boutton.left() << " " << boutton.top() << " " << boutton.right() << " " << boutton.bottom() << endl;
		rectangle(boutton.left(), boutton.top(), boutton.right(), boutton.bottom());
	}

    outtextxy(d_boutton[0].left() + 20, d_boutton[0].bottom() + 10, "Sauver");
    outtextxy(d_boutton[1].left() + 20, d_boutton[1].bottom() + 10, "Retour");

}

//Emplacement et création des boutonns
void Editeur::Emplacement()
{
	int  left = d_terrain.casesPrecis(d_terrain.longeur() - 1).left()+70 ,
		 top = d_terrain.casesPrecis(d_terrain.longeur() - 1).top()+20,
		 right = d_terrain.casesPrecis(d_terrain.longeur() - 1).right()+180,
		 bottom = d_terrain.casesPrecis(d_terrain.longeur() - 1).bottom();

	for (int i = 0; i < 2; ++i)
	{
		d_boutton.push_back(Cases{ left,top,right,bottom,"button" });
		top += 70; bottom += 70;
	}
}

//Permet l'ouverture du fichier
void Editeur::BrowseName()
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
		nam = filename;
		string line;
		std::ifstream myfile(filename);

		if (myfile.is_open())
		{
			int longeur, largeur;
			myfile >> longeur >> largeur;

			d_terrain = Terrain{longeur,largeur };

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
						if (d_robot == 0)
						{
							d_terrain.Type(i, "robot");
							d_robot = 1;
							i++;
						}
						else
						{
							d_terrain.Type(i, "vide");
							i++;
						}
                       
                    }
                    else if(l =='f')
                    {
                        d_terrain.Type(i,"fin");
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
			cout << "Impossible a ouvrir";
	}
}

//permet de sauvegarder le fichier
void Editeur::SaveFile()
{

	LPSTR s = const_cast<char *>(nam.c_str());

	char filename[MAX_PATH];

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Tous\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = s;
	ofn.nMaxFile = MAX_PATH;

	if (GetSaveFileName(&ofn))
	{
		string name2 = (string)s;

		std::ofstream myfile(name2);

		if (myfile.is_open())
		{
			myfile << d_terrain.longeur() << endl;
			myfile << d_terrain.largeur() << endl;

			for (int i = 0; i < d_terrain.largeur(); i++)
			{
				for (int j = 0; j < d_terrain.longeur(); j++)
				{
					if (d_terrain.casesPrecis(j + i * d_terrain.longeur()).type() == "mur")
					{
						myfile << "*";
					}
					else if (d_terrain.casesPrecis(j + i * d_terrain.longeur()).type() == "robot")
					{
					    myfile << "o";
					}
					else if (d_terrain.casesPrecis(j + i * d_terrain.longeur()).type() == "fin")
					{
					    myfile << "f";
					}
					else
                    {
						myfile << " ";
					}
				}
				myfile << endl;
			}
			myfile.close();
			cout << "Votre fichier a été sauvegarder" << endl;
		}
		else
			cout << "Impossible d'ouvrir le fichier" << endl;
	}

}

//Sauvegarde le fichier
void Editeur::save()
{

	SaveFile();
}

//Ouvre le fichier
void Editeur::open()
{
	BrowseName();
}

//Méthode permettant de selectionner un boutton
void Editeur::SelectButton(int x ,int y,bool &quittez)
{
	if (x >= d_boutton[0].left() && x <= d_boutton[0].right() && y >= d_boutton[0].bottom() && y <= d_boutton[0].top())
	{
		save();
	}
	else if (x >= d_boutton[1].left() && x <= d_boutton[1].right() && y >= d_boutton[1].bottom() && y <= d_boutton[1].top())
	{
		closegraph(windows);
		quittez = true;
	}
}

//Calcul de l'index du robot dans le terrain
int Editeur::distanceRobot(int& right, int& bottom, vector<Cases>& t1, string type) const
{
	return distance(t1.begin(), find(t1.begin(), t1.end(), Cases{ right + 20,bottom + 20,right,bottom,type }));
}

//Méthode de modification de Terrain
void Editeur::ModificationTerrain()
{
	bool quittez = false;
	int x, y, right, bottom ;

	while (!quittez)
	{
		while (!ismouseclick(WM_LBUTTONDOWN) )
		{
		
		}
		
		getmouseclick(WM_LBUTTONDOWN,x, y);

		SelectButton(x,y,quittez);

		right = (((x - 5) / 20) * 20) + 5;
		bottom = (((y - 5) / 20) * 20) + 5;

		auto t1 = d_terrain.cases();


		if (distanceRobot(right, bottom, t1, "vide") < d_terrain.largeur()*d_terrain.longeur())
		{
				setfillstyle(SOLID_FILL, WHITE);
                bar(right + 20, bottom + 20, right, bottom);

				d_terrain.Type(distanceRobot(right, bottom, t1, "vide"), "mur");

		}
		else if (distanceRobot(right, bottom, t1, "mur") < d_terrain.largeur()*d_terrain.longeur())
		{
				setfillstyle(SOLID_FILL, BLUE);
                bar(right + 20, bottom + 20, right, bottom);
				d_terrain.Type(distanceRobot(right, bottom, t1, "mur"), "fin");

		}
		else if (distanceRobot(right, bottom, t1, "fin") < d_terrain.largeur()*d_terrain.longeur())
		{

				setfillstyle(SOLID_FILL, BLACK);
                bar(right + 20, bottom + 20, right, bottom);

                setcolor(WHITE);
                rectangle(right + 20, bottom + 20, right, bottom);

                if (d_robot == 1)
                {
					d_terrain.Type(distanceRobot(right, bottom, t1, "fin"), "vide");
                }
                else
                {
                    setcolor(YELLOW);
                    circle(right+10, bottom+10,10);
					d_terrain.Type(distanceRobot(right, bottom, t1, "fin"), "robot");
                    d_robot = 1;
                }


		}
		else if (distanceRobot(right, bottom, t1, "robot") < d_terrain.largeur()*d_terrain.longeur())
		{
                setcolor(BLACK);
                bar(right + 20, bottom + 20, right, bottom);

                setcolor(WHITE);
                rectangle(right + 19.5, bottom + 19.5, right, bottom);
				d_terrain.Type(distanceRobot(right, bottom, t1, "robot"), "vide");
                d_robot = 0;
		}
	}
}
