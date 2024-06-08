#include<iostream>
using namespace std;


class Sphere
{
private:
	double r;
	const float pi = 3.14;
public:
	Sphere() {
	}
	Sphere(double radius) {
		r = radius;
	}

	void setradius(float r1) {
		r = r1;
	}
	float getradius() {

		return r;
	}
	float getdiameter() {
		double d1;
		d1 = 2 * r;
		return d1;
	}
	float getarea() {
		float area;
		area = 4 * pi * r;
		return area;
	}
	float getcircum() {
		double circum;
		circum = 2 * pi * r;
		return circum;
	}
	float getvolume() {
		double vol;
		vol = (4 / 3) * (pi * r * r * r);
		return vol;
	}
};

int main() {

	Sphere myshpere(3.5443);

	cout << "Diamter :" << myshpere.getdiameter() << endl;
	cout << "Area :" << myshpere.getarea() << endl;
	cout << "Circumference :" << myshpere.getcircum() << endl;
	cout << "Get vol :" << myshpere.getvolume() << endl;






}
