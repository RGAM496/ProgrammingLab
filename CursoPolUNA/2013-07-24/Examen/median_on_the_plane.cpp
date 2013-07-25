#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

class Point{
public:
	long long x;
	long long y;
	double c;
	int nro;
};

Point chosen;

bool comparatorXY(Point p1,Point p2){
	if(p1.x==p2.x){
		return p1.y<p2.y;
	}
	return p1.x<p2.x;
}

bool comparatorTG(Point p1,Point p2){
	if(p1.x-chosen.x==0)
		return false;
	if(p2.x-chosen.x==0)
		return true;
	return ((double)(p1.y-chosen.y)) / ((double)(p1.x-chosen.x)) < ((double)(p2.y-chosen.y))/((double)(p2.x-chosen.x));
}

int main(int argc, char **argv){
	int n;
	cin >> n;
	Point points[n];
	for(int i=0;i<n;i++){
		cin >> points[i].x;
		cin >> points[i].y;
		points[i].nro=i+1;
	}
	sort(points,points+n,comparatorXY);
	chosen=points[0];
	sort(points+1, points+n,comparatorTG);

	
	cout << points[0].nro << " " << points[n/2].nro << endl;
	
	return 0;
}