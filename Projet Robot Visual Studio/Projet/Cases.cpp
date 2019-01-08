#include "Cases.h"

//Constructeur
Cases::Cases()
{}

//Constructeur
Cases::Cases(int left,int top,int right,int bottom,string type):
    d_left{left},
    d_top{top},
    d_right{right},
    d_bottom{bottom},
    d_type{type}
{}

//Destructeur
Cases::~Cases()
{}

//Méthode retournant la cases gauche
int Cases::left() const
{
    return d_left;
}

//Méthode retournant la cases droite
int Cases::right() const
{
    return d_right;
}

//Méthode retournant la cases haut
int Cases::top() const
{
    return d_top;
}

//Méthode retournant la cases bas
int Cases::bottom() const
{
    return d_bottom;
}

//Méthode retournant le type
string Cases::type() const
{
    return d_type;
}

//Méthode de modification du type
void Cases::setType(const string& type)
{
	d_type = type;
}

//Méthode retournant si une cases est égale à une autre cases
bool Cases::operator==(const Cases & rhs)
{
	return (d_left == rhs.left() && d_top == rhs.top() && d_right == rhs.right() && d_bottom == rhs.bottom() && d_type == rhs.type());
}

//Méthode modifiant la cases
void Cases::move(double left, double top, double right,double bottom)
{
  d_left += left;
  d_top += top;
  d_right += right;
  d_bottom += bottom;
}
