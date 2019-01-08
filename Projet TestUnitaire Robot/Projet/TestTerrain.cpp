#include "doctest.h"
#include "Terrain.h"
#include <string>

TEST_CASE("Le Terrain fonctionne correctement")
{
	int longeur = 21, largeur = 20;
	vector<Cases> TestTerrain{};

	SUBCASE("la création de la case fonctionne correctement")
	{
		Terrain T{ longeur,largeur };

		SUBCASE("La longeur est bien retourné")
		{
			REQUIRE_EQ(T.longeur(), 21);

		}

		SUBCASE("La largeur est bien retourné")
		{
			REQUIRE_EQ(T.largeur(), 20);

		}

		SUBCASE("Le terrain a été créer")
		{
			int left = 25, top = 25, right = 5, bottom = 5;

			for (int i = 0; i < largeur; i++)
			{
				left = 25;
				right = 5;
				for (int j = 0; j < longeur; j++)
				{
					TestTerrain.push_back(Cases{ left, top, right, bottom,"vide" });
					left += 20;
					right += 20;
				}
				top += 20;
				bottom += 20;
			}

			REQUIRE(T.operator==(TestTerrain));
		}

	}
}