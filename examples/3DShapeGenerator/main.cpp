
#include "API.h"
#include "writefile.h"

using namespace std;

int main()
{
	string str;
	str = CreateRandomShapes({ 10, 0 });
	WriteFile("test.csv", str);
	return 0;
}
