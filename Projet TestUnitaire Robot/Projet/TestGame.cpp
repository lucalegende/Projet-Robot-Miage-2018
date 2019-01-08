#include "doctest.h"
#include "Game.h"
#include <string>
#include <iterator>
#include <windows.h>
#include <algorithm>
#include "graphics.h"

TEST_CASE("Le jeux fonctionne correctement")
{
	
	Game G{};
	initwindow(500, 500);

	vector<Cases> t1 = G.terrain().cases();

	

	SUBCASE("Teste Si le jeux est bien initialiser")
	{
		REQUIRE_NE(G.name(), "");	
	}

	SUBCASE("Teste si le robot est bien descendu d'une case")
	{
		int index = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));
		G.moveRobotToBottom();

		t1 = G.terrain().cases();
		int index2 = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));

		REQUIRE_EQ(index2, index+G.terrain().longeur());
	}

	SUBCASE("Teste si le robot est bien monter d'une case")
	{
		int index = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));
		G.moveRobotToTop();

		t1 = G.terrain().cases();
		int index2 = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));

		REQUIRE_EQ(index2, index - G.terrain().longeur());
	}

	SUBCASE("Teste si le robot a bien tourné a gauche d'une case")
	{
		int index = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));
		G.moveRobotToLeft();

		t1 = G.terrain().cases();
		int index2 = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));

		REQUIRE_EQ(index2, index - 1);
	}

	SUBCASE("Teste si le robot  a bien tourné a droite d'une case")
	{
		int index = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));
		G.moveRobotToRight();

		t1 = G.terrain().cases();
		int index2 = distance(t1.begin(), find(t1.begin(), t1.end(), G.robot().cases()));

		REQUIRE_EQ(index2, index + 1);
	}
	closegraph();
	
}