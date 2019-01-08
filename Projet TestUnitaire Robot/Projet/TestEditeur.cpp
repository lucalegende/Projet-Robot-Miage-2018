#include "doctest.h"
#include "Editeur.h"
#include <string>

TEST_CASE("Les cases fonctionne correctement")
{
	vector<Cases> TestEditeur{};
	Editeur E{};

	SUBCASE("la création d'un terrain pour l'éditeur fonction correctement fonctionne correctement")
	{
		Editeur E2{};
		
		REQUIRE(E.terrain().operator==(E2.terrain().cases()));
	}
}