#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;
# define M_PI 3.14159265358979323846
# define M_E 2.71828182845904523536

struct point{
	double x, y;

	point(): x(0), y(0){}

	point(double x, double y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	
	point operator*(const double & k) const{return point(x * k, y * k);}

	point operator/(const double & k) const{return point(x / k, y / k);}

	point operator+=(const point & p){*this = *this + p; return *this;}

	point operator-=(const point & p){*this = *this - p; return *this;}

	point operator*=(const double & p){*this = *this * p; return *this;}

	point operator/=(const double & p){*this = *this / p; return *this;}

	point rotate(const double angle) const{
		return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
	}
	point rotate(const double angle, const point & p){
		return p + ((*this) - p).rotate(angle);
	}

	double dot(const point & p) const{
		return x * p.x + y * p.y;
	}
	double length() const{
		return hypot(x, y);
	}
	double cross(const point & p) const{
		return x * p.y - y * p.x;
	}

	point normalize() const{
		return (*this) / length();
	}

	point projection(const point & p) const{
		return (*this) * p.dot(*this) / dot(*this);
	}
	point normal(const point & p) const{
		return p - projection(p);
	}

	bool operator==(const point & p) const{
		return abs(x - p.x) < eps && abs(y - p.y) < eps;
	}
	bool operator!=(const point & p) const{
		return !(*this == p);
	}
	bool operator<(const point & p) const{
		if(abs(x - p.x) < eps){
			return y < p.y;
		}else{
			return x < p.x;
		}
	}
	bool operator>(const point & p) const{
		if(abs(x - p.x) < eps){
			return y > p.y;
		}else{
			return x > p.x;
		}
	}
};

istream &operator>>(istream &is, point & P){
	point p;
    is >> p.x >> p.y;
    P = p;
    return is;
}

ostream &operator<<(ostream &os, const point & p) { 
    return os << fixed << setprecision(8) << p.x << " " << p.y;
}

int sgn(double x){
	if(abs(x) < eps){
		return 0;
	}else if(x > 0){
		return 1;
	}else{
		return -1;
	}
}

bool pointInLine(point & a, point & b, point & p){
	//line ab, point p
	return abs((p - a).cross(b - a)) < eps;
}

bool pointInSegment(point a, point b, point & p){
	//segment ab, point p
	if(a > b) swap(a, b);
	return pointInLine(a, b, p) && !(p < a || p > b);
}

int intersectLinesInfo(point & a, point & b, point & c, point & d){
	//line ab, line cd
	point v1 = b - a, v2 = d - c;
	double det = v1.cross(v2);
	if(abs(det) < eps){
		if(abs((c - a).cross(v1)) < eps){
			return -1; //infinity points
		}else{
			return 0; //no points
		}
	}else{
		return 1; //single point
	}
}

point intersectLines(point & a, point & b, point & c, point & d){
	//assuming that they intersect
	point v1 = b - a, v2 = d - c;
	double det = v1.cross(v2);
	return a + v1 * ((c - a).cross(v2) / det);
}

int intersectLineSegmentInfo(point & a, point & b, point & c, point & d){
	//line ab, segment cd
	point v1 = b - a, v2 = d - c;
	double det = v1.cross(v2);
	if(abs(det) < eps){
		if(abs((c - a).cross(v1)) < eps){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v1.cross(c - a)) != sgn(v1.cross(d - a)); //1: single point, 0: no point
	}
}

int intersectSegmentsInfo(point & a, point & b, point & c, point & d){
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}

double distancePointLine(point & a, point & v, point & p){
	//line: a + tv, point p
	return abs(v.cross(p - a)) / v.length();
}

double perimeter(vector<point> & points){
	int n = points.size();
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += (points[i] - points[(i + 1) % n]).length();
	}
	return ans;
}

double area(vector<point> & points){
	int n = points.size();
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += points[i].cross(points[(i + 1) % n]);
	}
	return abs(ans / 2);
}

vector<point> convexHull(vector<point> points){
	sort(points.begin(), points.end());
	vector<point> L, U;
	for(int i = 0; i < points.size(); i++){
		while(L.size() >= 2 && (L[L.size() - 2] - points[i]).cross(L[L.size() - 1] - points[i]) <= 0){
			L.pop_back();
		}
		L.push_back(points[i]);
	}
	for(int i = points.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && (U[U.size() - 2] - points[i]).cross(U[U.size() - 1] - points[i]) <= 0){
			U.pop_back();
		}
		U.push_back(points[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

bool pointInPerimeter(vector<point> & points, point & p){
	int n = points.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(points[i], points[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

int pointInPolygon(vector<point> & points, point & p){
	if(pointInPerimeter(points, p)){
		return -1; //point in the perimeter
	}
	point bottomLeft = (*min_element(points.begin(), points.end())) - point(M_E, M_PI);
	int n = points.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += (intersectSegmentsInfo(p, bottomLeft, points[i], points[(i + 1) % n]) == 1 ? 1 : 0);
	}
	return rays & 1; //0: point outside, 1: point inside
}

bool comp1(const point & a, const point & b){
	return a.y < b.y;
}
pair<point, point> closestPairOfPoints(vector<point> points){
	sort(points.begin(), points.end(), comp1);
	set<point> S;
	double ans = 1e9;
	point p, q;
	int pos = 0;
	for(int i = 0; i < points.size(); ++i){
		while(pos < i && abs(points[i].y - points[pos].y) >= ans){
			S.erase(points[pos++]);
		}
		auto lower = S.lower_bound({points[i].x - ans - eps, -1e9});
		auto upper = S.upper_bound({points[i].x + ans + eps, -1e9});
		for(auto it = lower; it != upper; ++it){
			double d = (points[i] - *it).length();
			if(d < ans){
				ans = d;
				p = points[i];
				q = *it;
			}
		}
		S.insert(points[i]);
	}
	return {p, q};
}

point centroid(vector<point> & points){
	point P;
	double div = 0;
	int n = points.size();
	for(int i = 0; i < n; ++i){
		double cross = points[i].cross(points[(i + 1) % n]);
		P += (points[i] + points[(i + 1) % n]) * cross;
		div += cross;
	}
	return P / (3.0 * div);
}

struct vantage_point_tree{
	struct node
	{
		point p;
		double th;
		node *l, *r;
	}*root;

	vector<pair<double, point>> aux;

	vantage_point_tree(vector<point> &ps){
		for(int i = 0; i < ps.size(); ++i)
			aux.push_back({ 0, ps[i] });
		root = build(0, ps.size());
	}

	node *build(int l, int r){
		if(l == r)
			return 0;
		swap(aux[l], aux[l + rand() % (r - l)]);
		point p = aux[l++].second;
		if(l == r)
			return new node({ p });
		for(int i = l; i < r; ++i)
			aux[i].first = (p - aux[i].second).length() * (p - aux[i].second).length();
		int m = (l + r) / 2;
		nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
		return new node({ p, sqrt(aux[m].first), build(l, m), build(m, r) });
	}

	priority_queue<pair<double, node*>> que;

	void k_nn(node *t, point p, int k){
		if(!t)
			return;
		double d = (p - t->p).length();
		if(que.size() < k)
			que.push({ d, t });
		else if(que.top().first > d){
			que.pop();
			que.push({ d, t });
		}
		if(!t->l && !t->r)
			return;
		if(d < t->th){
			k_nn(t->l, p, k);
			if(t->th - d <= que.top().first)
				k_nn(t->r, p, k);
		}else{
			k_nn(t->r, p, k);
			if(d - t->th <= que.top().first)
				k_nn(t->l, p, k);
		}
	}

	vector<point> k_nn(point p, int k){
		k_nn(root, p, k);
		vector<point> ans;
		for(; !que.empty(); que.pop())
			ans.push_back(que.top().second->p);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main(){
	int n;
	cin >> n;
	vector<point> poly(n);
	for(int i = 0; i < n; ++i){
		cin >> poly[i];
	}
	cout << centroid(poly) << "\n";
}