#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#define PI 3.14159265

using namespace std;

struct point {double x, y, z;};
typedef vector<point> points;

inline void shift (point& p, double xshift = 0.0, double yshift = 0.0, double zshift = 0.0)
{
	p.x += xshift;
	p.y += yshift;
	p.z += zshift;
}

void shift (points& set, double xshift = 0.0, double yshift = 0.0, double zshift = 0.0)
{
	for (int i = 0; i < set.size(); i++)
	{
		shift (set[i], xshift, yshift, zshift);
	}
}

void scale (points& set, double xscale = 1.0, double yscale = 1.0, double zscale = 1.0)
{
	for (int i = 0; i < set.size(); i++)
	{
		set[i].x *= xscale;
		set[i].y *= yscale;
		set[i].z *= zscale;
	}
}

inline void swap (double& a, double& b)
{
	double tmp = a;
	a = b;
	b = tmp;
}

string format (double num)
{
	string out;
	constexpr int digits = 6;
	if (num < 0)
		out = "-";
	else
		out = " ";
	num = abs(num);
	
	string part1 = "";
	int intpart = int(num);
	do {
		part1 = char(intpart % 10 + '0') + part1;
		intpart /= 10;
	} while (intpart > 0);

	string part2 = "";
	num -= floor(num);
	for (int i = 0; i < digits; i++)
	{
		num *= 10.0;
		part2 += char(int(num) + '0');
		num -= floor(num);
	}

	out = out + part1 + "." + part2;
	return out;
}

points createCircle (double angleBegin, double angleEnd, int segmentNum, double scale = 0.5, double xshift = 0.0, double yshift = 0.0, double xscale = 1.0, double yscale = 1.0)
{
	points output;
	if (angleBegin > angleEnd)
		swap(angleBegin, angleEnd);
	double segment = abs(angleEnd - angleBegin) / double(segmentNum);
	double x, y, z = 0;
	for (double angle = angleBegin; angle <= angleEnd; angle += segment)
	{
		x = xscale * (cos(angle) * scale + xshift);
		y = yscale * (sin(angle) * scale + yshift);
		point cp;
		cp.x = x;
		cp.y = y;
		cp.z = z;
		output.push_back(cp);
	}
	return output;
}

void printCircle (double angleBegin, double angleEnd, int segmentNum, double scale = 0.5, double xshift = 0.0, double yshift = 0.0, double xscale = 1.0)
{
	if (angleBegin > angleEnd)
		swap(angleBegin, angleEnd);
	double segment = abs(angleEnd - angleBegin) / double(segmentNum);
	double x, y, z = 0;
	for (double angle = angleBegin; angle <= angleEnd; angle += segment)
	{
		x = cos(angle) * scale + xshift;
		y = sin(angle) * scale + yshift;
		cout << "v " << format(xscale * x) << ' ' << format(y) << ' ' << format(z) << endl;
	}
}

void printPoints (points& ps)
{
	for (int i = 0; i < ps.size(); i++)
		cout << "v " << format(ps[i].x) << ' ' << format(ps[i].y) << ' ' << format(ps[i].z) << endl;
}

void printPoint (point p)
{
	cout << "v " << format(p.x) << ' ' << format(p.y) << ' ' << format(p.z) << endl;
}

point midPoint (point p1, point p2)
{
	point p;
	p.x = (p1.x + p2.x) * 0.5;
	p.y = (p1.y + p2.y) * 0.5;
	p.z = (p1.z + p2.z) * 0.5;
	return p;
}

int main()
{
	points arc1, arc2, arc3;
	point middle;

	arc1 = createCircle (-0.375*PI, -0.074*PI, 6);
	scale (arc1, 2, 2, 2);
	shift (arc1, 0.0, 0.1);
	scale(arc1, 2, 1);
	shift(arc1, -1.5);

	arc2 = createCircle (0.375*PI, 0.075*PI, 6);
	scale (arc2, 2, 2, 2);
	shift (arc2, 0.0, -0.19);
	scale(arc2, 2, 1);
	shift(arc2, -1.5);

	arc3 = createCircle (-0.125*PI, 0.125*PI, 6);
	scale (arc3, 3, 3, 2);
	shift (arc3, -2);

	middle = midPoint(arc1[6], arc2[0]);
	shift (middle, 0.02);

	printPoints(arc1);
	cout << endl;
	printPoint(middle);
	cout << endl;
	printPoints(arc2);
	cout << endl;
	printPoints(arc3);
	return 0;
}
