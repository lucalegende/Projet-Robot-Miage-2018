#include "Cases.h"

Cases::Cases()
{}

Cases::Cases(int left,int top,int right,int bottom,string type):
    d_left{left},
    d_top{top},
    d_right{right},
    d_bottom{bottom},
    d_type{type}
{}

Cases::~Cases()
{}

int Cases::left() const
{
    return d_left;
}

int Cases::right() const
{
    return d_right;
}

int Cases::top() const
{
    return d_top;
}

int Cases::bottom() const
{
    return d_bottom;
}

string Cases::type() const
{
    return d_type;
}

void Cases::setType(const string& type)
{
	d_type = type;
}

bool Cases::operator==(const Cases & rhs)
{
	return (d_left == rhs.left() && d_top == rhs.top() && d_right == rhs.right() && d_bottom == rhs.bottom() && d_type == rhs.type());
}

void Cases::move(double left, double top, double right,double bottom)
{
  d_left += left;
  d_top += top;
  d_right += right;
  d_bottom += bottom;
}
