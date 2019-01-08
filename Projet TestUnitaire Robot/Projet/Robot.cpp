#include <iostream>
#include "Robot.h"
#include "graphics.h"

Robot::Robot()
{
}

Robot::Robot(Cases emplacement,int direction):
    d_cases{emplacement},
    d_direction{direction}
{}

Robot::~Robot()
{}

void Robot::position() const{
    std::cout<<d_cases.left()*d_cases.top()<<","<<d_cases.right()*d_cases.bottom();
}

int Robot::direction() const{
    return d_direction;
}

void Robot::draw() const{

	setfillstyle(SOLID_LINE, BLACK);
	bar(d_cases.left(), d_cases.top(), d_cases.right(), d_cases.bottom());

	setcolor(YELLOW);
	circle(d_cases.left() - 10, d_cases.top() - 10, 10);

    if(d_direction==0)
        line(d_cases.left()-10, d_cases.top()-10, d_cases.right(), d_cases.bottom()+10);
    if(d_direction==90)
        line(d_cases.left()-10, d_cases.top()-10, d_cases.right()+10, d_cases.bottom());
    if(d_direction==180)
        line(d_cases.left()-10, d_cases.top()-10, d_cases.right()+20, d_cases.bottom()+10);
    if(d_direction==270)
        line(d_cases.left()-10, d_cases.top()-10, d_cases.right()+10, d_cases.bottom()+20);
}

void Robot::turnLeft(){
    d_direction=0;
    draw();
}
void Robot::turnRight(){
    d_direction=180;
    draw();
}
void Robot::turnTop(){
    d_direction=90;
    draw();
}
void Robot::turnBottom(){
    d_direction=270;
    draw();
}
void Robot::move(){

    if(d_direction==90){
        d_cases.move(0,-20,0,-20);
    }
    if(d_direction==180){
        d_cases.move(20,0,20,0);
    }
    if(d_direction==270){
        d_cases.move(0,20,0,20);
    }
    if(d_direction==0){
        d_cases.move(-20,0,-20,0);
    }
}

void Robot::operator=(const Robot& R)
{
	d_cases = R.d_cases;
	d_direction = R.d_direction;
}

Cases Robot::cases() const
{
    return d_cases;
}
