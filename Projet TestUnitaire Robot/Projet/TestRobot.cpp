#include "doctest.h"
#include "Robot.h"
#include "Cases.h"
#include <string>
#include "graphics.h"

TEST_CASE("Verifie si La classe Robot fonctionne rrectemeent")
{
	int left = 25, right = 25, top = 5, bottom = 5, direction = 270/*vers le bas*/;
	string type = "Robot";


	SUBCASE("la création du robot fonctionne correctement")
	{
		Cases C{ left,right,top,bottom,type };
		Robot R{ C,direction};
		initwindow(500, 500);

		SUBCASE("test la direction du robot")
		{
			REQUIRE_EQ(R.direction(), 270);
		}

		SUBCASE("Teste la position du robot")
		{
			REQUIRE(R.cases().operator==(C));
		}

		SUBCASE("Teste le déplacement de la direction vers la droite")
		{
			R.turnRight();
			REQUIRE_EQ(R.direction(), 180);
		}

		SUBCASE("Teste le déplacement de la direction vers la gauche")
		{
			R.turnLeft();
			REQUIRE_EQ(R.direction(), 0);
		}

		SUBCASE("Teste le déplacement de la direction vers le haut")
		{
			R.turnTop();
			REQUIRE_EQ(R.direction(), 90);
		}

		SUBCASE("Teste le déplacement de la direction vers le bas")
		{
			R.turnBottom();
			REQUIRE_EQ(R.direction(), 270);
		}
		closegraph();
	}
}