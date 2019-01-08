#include "Menu.h"
#include "graphics.h"
#include "Editeur.h"
#include "Game.h"

#include <iostream>

using std::cout;
using std::endl;

int windows1;

//Constructeur
Menu::Menu()
{
    Emplacement();
    Affichage();
	SelectButton();
}

//Destructeur
Menu::~Menu()
{}

//Aficchage du menu
void Menu::Affichage()
{
    outtextxy(140, 70, "Projet Robot 2018/2019");

    for (auto boutton : d_bouttonMenu)
    {
        cout << boutton.left() <<" "<< boutton.top() <<" "<< boutton.right() <<" "<< boutton.bottom() << endl;
        rectangle(boutton.left(),boutton.top(),boutton.right(),boutton.bottom());
    }

    outtextxy(210, 220, "Éditeur");
    outtextxy(210, 290, "Jouer");
    outtextxy(210, 360, "Quitter");

}

//Emplacement des bouttons
void Menu::Emplacement()
{
    int top =260, bottom = 205;

    for(int i = 0; i < 3; ++i)
    {
        d_bouttonMenu.push_back(Cases{350,top,125,bottom,"button"});
        top+=70; bottom+=70;
    }
}

//Selection le boutton en fonction de l'emplacement du clique
void Menu::SelectButton()
{
    int x , y;
    bool quittez = false;

    do
    {

		while (!ismouseclick(WM_LBUTTONDOWN))
		{
		}

		getmouseclick(WM_LBUTTONDOWN, x, y);

		if ( x >= 125 && x <=350 && y >= 205 && y <= 260)
		{

			Editeur E{};
			
			int windows = initwindow(E.terrain().longeur() * 20 + 220, E.terrain().largeur() * 20 + 20, "Editeur", 0, 0, false, false);
			setcurrentwindow(windows);

			E.Ecran(windows);

			setcurrentwindow(0);
			
		}
		else if(x >= 125 && x <=350 && y >= 275 && y <= 330)
		{
			Game G{};
			if (G.name() != "")
			{
				int windows2 = initwindow(G.terrain().longeur() * 20 + 220, G.terrain().largeur() * 20 + 20, "Game", 0, 0, false, false);
				setcurrentwindow(windows2);

				G.LoadGame(windows2);

				setcurrentwindow(0);
			}
		}
		else if(x >= 125 && x <=350 && y >= 345 && y <= 400)
        {
            closegraph();
            quittez = true;
        }
    } while(!quittez);
}
