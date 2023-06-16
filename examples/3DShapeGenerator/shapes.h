
#include <vector>
#include <random>
#include <fstream>

using namespace std;

//  ласс описани¤ точки
class Point {
	public:
		double x, y, z;
};

//  ласс, описывающий любую поверхность
class Figure: public Point {
	public:
		//vector <Point> p;
		//vector <vector <Point>> f;
		virtual string GetAsCSV(vector <vector <Point>> f);
		virtual string GetAsCSV(vector <Point> p);
		virtual string GetAsJSON(vector <vector <Point>> f);
		virtual vector <Point> GetAsPoints(double o);
		Point rotatePoint(Point p, double angle);
		size_t& NumberInCSV() { static size_t c = 0; return ++c; }
};

//  ласс, описывающий цилиндр
class Cylinder: public Figure {
	public:
		double r, h, k_x, k_y, k_z;
		Cylinder(double radius, double height, double offset_x, double offset_y, double offset_z);
		vector <Point> GetAsPoints(double o) override;
		vector <Point> CreateFooting(double r, double h);
		vector <Point> CreateWalls();
		vector <Point> CreateFooting(double r, double h, double o);
		vector <Point> CreateWalls(double o);
		string GetAsCSV(vector <vector <Point>> f) override;
		string GetAsCSV(vector <Point> p) override;
		string GetAsJSON(vector <vector <Point>> f) override;
};

//  ласс, описывающий поверхность
class Plane: public Figure {
	public:
		int Point_Count;
		double k_x, k_y, k_z;
		Plane(int Count, double offset_x, double offset_y, double offset_z);
		vector <Point> GetAsPoints(double o) override;
		string GetAsCSV(vector <vector <Point>> f) override;
		string GetAsCSV(vector <Point> p) override;
		string GetAsJSON(vector <vector <Point>> f) override;
};

//  ласс, описывающий сферу
class Sphere: public Figure {
	public:
		double r, k_x, k_y, k_z;
		Sphere(double radius, double offset_x, double offset_y, double offset_z);
		vector <Point> GetAsPoints(double o) override;
		vector <Point> CreateFooting();
		vector <Point> CreateUpHemisphere();
		vector <Point> CreateDownHemisphere();
		vector <Point> CreateFooting(double o);
		vector <Point> CreateUpHemisphere(double o);
		vector <Point> CreateDownHemisphere(double o);
		string GetAsCSV(vector <vector <Point>> f) override;
		string GetAsCSV(vector <Point> p) override;
		string GetAsJSON(vector <vector <Point>> f) override;
};


