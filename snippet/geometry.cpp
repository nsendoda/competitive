#include <vector>
#include <cmath>
#include <cstring>

const double EPS = 1e-10;
#define equals(a,b) (fabs((a) - (b)) < EPS)
struct Point{
	double x,y;
	Point(double x = 0.0,double y =0.0):x(x),y(y){}
	Point operator + (const Point& p){ return Point(x+p.x,y+p.y);	}
	Point operator - (const Point& p){ return Point(x-p.x,y-p.y); }
	Point operator * (double k){ return Point(x*k,y*k);	}
	Point operator / (double k){ return Point(x/k,y/k); }

	double norm(){return x*x+y*y;}
	double abs(){return sqrt(norm());}

	bool operator < (const Point& p) const {
		return x != p.x ? x < p.x : y < p.y;
	}
	bool operator == (const Point &p) const{
		return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS;
	}
};
typedef Point Vector;

double norm(Vector a){return a.x*a.x+a.y*a.y;}
double abs(Vector a){return sqrt(norm(a));}

//内積
double dot(Vector a, Vector b){
	return a.x * b.x + a.y * b.y;
}

//外積
double cross(Vector a, Vector b){
	return a.x*b.y - a.y*b.x;
}


struct Segment{
	Point p1,p2;
	Segment(Point p1,Point p2):p1(p1),p2(p2){}
	Segment(double a,double b,double c,double d):p1(Point(a,b)),p2(Point(c,d)){}
};

typedef Segment Line;
class Circle{
public:
	Point c;
	double r;
	Circle(Point c = Point(), double r = 0.0): c(c),r(r){}
};
typedef vector<Point> Polygon;

bool isOrthgonal(Vector a, Vector b){
	return equals(dot(a,b),0.0);
}

bool isOrthgonal(Point a1, Point a2, Point b1, Point b2){
	return isOrthgonal(a1-a2,b1-b2);
}

bool isOrthgonal(Segment s1, Segment s2){
	return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1),0.0);
}

bool isParallel(Vector a,Vector b){
	return equals(cross(a,b),0.0);
}

bool isParallel(Point a1, Point a2, Point b1, Point b2){
	return isParallel(a1-a2,b1-b2);
}

bool isParallel(Segment s1, Segment s2){
	return equals(cross(s1.p2 - s1.p1,s2.p2-s2.p1),0.0);
}

Point project(Segment s,Point p){
	Vector base = s.p2 - s.p1;
	double r = dot(p-s.p1,base)/base.norm();
	return s.p1 + base * r;
}

Point reflect(Segment s, Point p){
	return p + (project(s,p) - p) * 2.0;
}



//時計周りチェック
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Vector a, Vector b){
	if(cross(a,b) > EPS)return COUNTER_CLOCKWISE;
	if(cross(a,b) < -EPS)return CLOCKWISE;
	if(dot(a,b) < -EPS)return ONLINE_BACK;
	if(a.norm() < b.norm())return ONLINE_FRONT;
	return ON_SEGMENT;
}

int ccw(Point p1,Point p2,Point p3){
	Vector a = p2 - p1;
	Vector b = p3 - p1;
	if(cross(a,b) > EPS)return COUNTER_CLOCKWISE;
	if(cross(a,b) < -EPS)return CLOCKWISE;
	if(dot(a,b) < -EPS)return ONLINE_BACK;
	if(a.norm() < b.norm())return ONLINE_FRONT;
	return ON_SEGMENT;
}


//線分交差判定
bool intersect(Point p1, Point p2, Point p3,Point p4){
	return ccw(p1,p2,p3)*ccw(p1,p2,p4) <= 0 && ccw(p3,p4,p1)*ccw(p3,p4,p2) <= 0;
}

bool intersect(Segment s1,Segment s2){
	return intersect(s1.p1,s1.p2, s2.p1,s2.p2);
}

//交点
Point getCrossPoint(Segment s1, Segment s2){
	Vector base = s2.p2 - s2.p1;
	double d1 = abs(cross(base,s1.p1 - s2.p1));//約分で消去
	double d2 = abs(cross(base,s1.p2 - s2.p1));
	double t = d1 / (d1+d2);
	return s1.p1 + (s1.p2 - s1.p1)*t;
}

//{点,直線,線分}^2の距離
double getDistance(Point a,Point b){
	return abs(a-b);
}

double getDistanceLP(Line l, Point p){
	return abs(cross(l.p2 - l.p1, p-l.p1) / abs(l.p2 - l.p1));
}

double getDistanceSP(Segment s,Point p){
	if(dot(s.p2 - s.p1, p-s.p1) < 0.0) return abs(p-s.p1);
	if(dot(s.p1 - s.p2, p-s.p2) < 0.0) return abs(p-s.p2);
	return getDistanceLP(s,p);
}

double getDistance(Segment s1, Segment s2){
	if(intersect(s1,s2)) return 0.0;
	return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
						 min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
