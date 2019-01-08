#include "doctest.h"
#include "Cases.h"
#include <string>
#include <iostream>
#include <sstream>

TEST_CASE("Les cases fonctionne correctement")
{
	int left = 25, right = 25, top = 5, bottom = 5;
	string type = "mur";
	

	SUBCASE("la création de la case fonctionne correctement")
	{
		Cases C{ left,right,top,bottom,type };

		SUBCASE("La valeur left est bien retourné")
		{
			REQUIRE_EQ(C.left(), 25);
			
		}

		SUBCASE("La valeur right est bien retourné")
		{
			REQUIRE_EQ(C.right(), 5);

		}

		SUBCASE("La valeur top est bien retourné")
		{
			REQUIRE_EQ(C.top(), 25);

		}

		SUBCASE("La valeur bottom est bien retourné")
		{
			REQUIRE_EQ(C.bottom(), 5);

		}

		SUBCASE("La valeur type est bien retourné")
		{
			REQUIRE_EQ(C.type(), "mur");

		}
		
	}
}
