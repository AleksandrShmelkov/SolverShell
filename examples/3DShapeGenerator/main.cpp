
#include "API.h"

using namespace std;

int main()
{
	CreateShapes("torus.csv", { ShapeType::Cylinder, 10, 0 });
	return 0;
}
