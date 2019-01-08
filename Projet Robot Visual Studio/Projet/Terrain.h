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
        Terrain();
        Terrain(int longeur, int largeur);
        ~Terrain();

        void verificationTailleTerrain();
        void initialise();
        void afficherTerrain();
        int longeur() const;
        int largeur() const;
		void operator= (const Terrain& T);
		void Type(int i, string type);
		vector<Cases> cases() const;
		Cases casesPrecis(int i) const;
		bool operator== (vector<Cases>& T) const;
		void moveRobot(int init,int final);

    private:
        int d_longeur;
        int d_largeur;
        vector<Cases> d_terrain;
};

#endif // TERRAIN_H
