#ifndef EDITEUR_H
#define EDITEUR_H

#include "Terrain.h"
#include "Cases.h"

class Editeur
{
    public:
        Editeur();
        ~Editeur();

        //Méthode public
        void Ecran(int& window);         // Efface l'ecran
		Terrain terrain() const;

    private:
        //Methode privé
        void Affichage();
		void Emplacement();
		void BrowseName();
		void SaveFile();
		void save();                 // Permet de sauvegarder un terrain
        void open();                 // Permet d'ouvrir un terrain
		void SelectButton(int x, int y, bool & quittez);
		int distanceRobot(int & right, int & bottom, vector<Cases>& t1, string  type) const;
		void ModificationTerrain();

		//Variable privé
		vector<Cases> d_boutton;
		int d_robot;
		Terrain d_terrain;
};

#endif // EDITEUR_H
