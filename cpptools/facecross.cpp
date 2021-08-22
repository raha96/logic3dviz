#include <iostream>

using namespace std;

int main()
{
	int a, b, c, d;
	cout << "Index of the first vertex of face 1? ";
	cin >> a;
	cout << "Index of the last vertex of face 1? ";
	cin >> b;
	cout << "Index of the first vertex of face 2? ";
	cin >> c;
	d = b - a;
	for (int i = 0; i < d; i++)
	{
		cout << "f " << a + i << ' ' << c + i << ' ' << c + i + 1 << ' ' << a + i + 1 << endl;
	}
	cout << "f " << b << ' ' << c + d << ' ' << c << ' ' << a << endl;
	return 0;
}
