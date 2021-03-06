#include "Terrain.h"
#include "wtypes.h"
#include <iostream>

//Constructeur
Terrain::Terrain():
    d_longeur{20},
    d_largeur{20}
{
    initialise();
}

//Constructeur
Terrain::Terrain(int longeur, int largeur):
    d_longeur{longeur},
    d_largeur{largeur},
    d_terrain{}
{
    verificationTailleTerrain();
    initialise();
}

//Destructeur
Terrain::~Terrain()
{}

//Taille de l'�cran
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

//V�rfie la taille de l'�cran
void Terrain::verificationTailleTerrain()
{
    int horizontal = 0;
    int vertical = 0;

    GetDesktopResolution(horizontal, vertical);

    if(d_largeur >(horizontal/20)-37 &&  d_longeur >(vertical/13))
    {
        d_largeur = (horizontal/20)-37;
        d_longeur = (vertical/13);
    }
}

//Initialise le terrain
void Terrain::initialise()
{

    int left=25, top=25, right=5,bottom=5;

    for(int i = 0; i < d_largeur; i++)
    {
        left=25;
        right=5;
        for(int j = 0; j < d_longeur; j++)
        {
            d_terrain.push_back(Cases{left, top, right, bottom,"vide"});
            left+=20;
            right+=20;
        }
        top+=20;
        bottom+=20;
    }
}

//Affiche le terrain
void Terrain::afficherTerrain()
{

	for (auto t : d_terrain)
	{
		if (t.type() == "mur")
		{
			bar(t.left(), t.top(), t.right(), t.bottom());
		}
		else if (t.type() == "fin")
		{
			setfillstyle(SOLID_FILL, BLUE);
			bar(t.left(), t.top(), t.right(), t.bottom());
			setfillstyle(SOLID_FILL, WHITE);
		}
		else if (t.type() == "robot")
        {
            setcolor(YELLOW);
            circle(t.left()-10,t.top()-10,10);
			setcolor(WHITE);
        }
		else
		{
            setcolor(WHITE);
			rectangle(t.left(), t.top(), t.right(), t.bottom());
		}
	}

}

//M�thode qui retourne la longeur du terrain
int Terrain::longeur() const
{
    return d_longeur;
}


//M�thode qui retourne la largeur du terrain
int Terrain::largeur() const
{
    return d_largeur;
}

//M�thode d'affectation
void Terrain::operator=(const Terrain & T)
{
	d_largeur = T.d_largeur;
	d_longeur = T.d_longeur;
	d_terrain = T.d_terrain;
}

//M�thode qui change le type de la cases dans un terrain
void Terrain::Type(int i,string type)
{
	d_terrain[i].setType(type);
}

//Retourne un vecteur de cases
vector<Cases> Terrain::cases() const
{
	return d_terrain;
}

//Retourne une cases 
Cases Terrain::casesPrecis(int i) const
{
	return d_terrain[i];
}

//Retourne si un terrain est egale a un autre terrain
bool Terrain::operator==(vector<Cases> & T) const
{
	bool ok = true;
	for (int i = 0; i < T.size(); i++)
	{
		if(T[i].operator==(d_terrain[i]))
		{}
		else
		{
			ok = false;
		}
	}
	return ok;
}

//Change la couleur
void changeColor(Cases& cases)
{
	setcolor(BLACK);
	bar(cases.left(), cases.top(), cases.right(), cases.bottom());
	setcolor(WHITE);
	rectangle(cases.left(), cases.top(), cases.right(), cases.bottom());
}

//Bouge le robot du terrain et change le type de la cases
void Terrain::moveRobot(int init,int final)
{
	d_terrain[init].setType("vide");
	changeColor(d_terrain[init]);
	if (d_terrain[final].type() != "fin")
	{
		d_terrain[final].setType("robot");
	}

}

