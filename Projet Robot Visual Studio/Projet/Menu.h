#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Cases.h"

using std::vector;

class Menu
{
    public:
        //Constrcuter
        Menu();
        //Desctructeur
        ~Menu();

    private:
        // Méthode privé
        void Emplacement();          // Emplacement des bouttons avec texte
        void SelectButton();         // Permet d'aller sois dans l'éditeur soir de jouer
        void Affichage();            // Affiche le Menu

		//Variable privée
        vector<Cases> d_bouttonMenu; // Vecteur de boutton

};

#endif // MENU_H
