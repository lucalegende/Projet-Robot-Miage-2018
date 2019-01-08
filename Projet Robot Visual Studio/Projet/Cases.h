#ifndef CASES_H
#define CASES_H

#include <string>

using std::string;

class Cases
{
    public:
		//Constructeur
        Cases();
        Cases(int left,int top,int right,int bottom,string type);
		//Destructeur
        ~Cases();

		//Méthode de récupération de données
        int left() const;
        int right() const;
        int top() const;
        int bottom() const;
        string type() const;
		bool operator==(const Cases& rhs);

		//Méthode de modification de données
		void setType(const string& type);
		void move(double left, double top, double right,double bottom);

    private:
		//Variable privée
        int d_left;
        int d_top;
        int d_right;
        int d_bottom;
        string d_type;
};


#endif // CASES_H
