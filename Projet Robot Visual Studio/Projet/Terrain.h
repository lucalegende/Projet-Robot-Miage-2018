#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "Cases.h"
#include "Robot.h"
#include "graphics.h"

using std::vector;

class Terrain
{
    public:
		//Constructeur
        Terrain();
        Terrain(int longeur, int largeur);
        //Destructeur
		~Terrain();

		//Méthode Public de modificaiton
        void verificationTailleTerrain();
        void initialise();
        void afficherTerrain();
		void operator= (const Terrain& T);
		void Type(int i, string type);
		void moveRobot(int init, int final);

		//Méthode public de récuperation de valeur
        int longeur() const;
        int largeur() const;
		vector<Cases> cases() const;
		Cases casesPrecis(int i) const;
		bool operator== (vector<Cases>& T) const;
		
    private:
		//Variable privé
        int d_longeur;
        int d_largeur;
        vector<Cases> d_terrain;
};

#endif // TERRAIN_H
