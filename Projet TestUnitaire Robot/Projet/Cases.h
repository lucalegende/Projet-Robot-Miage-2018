#ifndef CASES_H
#define CASES_H

#include <string>

using std::string;

class Cases
{
    public:
        Cases();
        Cases(int left,int top,int right,int bottom,string type);
        ~Cases();

        int left() const;
        int right() const;
        int top() const;
        int bottom() const;
        string type() const;

		void setType(const string& type);
		bool operator==(const Cases& rhs);
		void move(double left, double top, double right,double bottom);

    private:
        int d_left;
        int d_top;
        int d_right;
        int d_bottom;
        string d_type;
};


#endif // CASES_H
