#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>

using namespace std;

typedef long long int ull;

ull gcd(ull a, ull b){
    ull r;
    while(b!=0) r = a%b, a = b, b = r;
    return a;
}

ull mod(ull a, ull b){
    ull ans = a % b;
    if(ans < 0) ans += b;
    return ans;
}

struct enteroModular{
    ull a, n;
    enteroModular(ull x, ull y){
    	if(y == 0) a = x;
        else a = mod(x, y);
        n = y;
    }
    enteroModular(ull x){
        a = x, n = 0;
    }
    enteroModular(){
        a = 0, n = 0;
    }
    enteroModular operator+(const enteroModular & e) const{
        return enteroModular(a + e.a, max(n, e.n));
    }
    enteroModular operator-() const{
        return enteroModular(-a, n);
    }
    enteroModular operator-(const enteroModular & e) const{
        return *this + (-e);
    }
    enteroModular operator*(const enteroModular & e) const{
        return enteroModular(a * e.a, max(n, e.n));
    }
    enteroModular inverso() const{
        ull r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
        while(r1 != 0){
            ri = r0 % r1;
            si = s0 - s1 * (r0 / r1);
            r0 = r1, r1 = ri;
            s0 = s1, s1 = si;
        }
        return enteroModular(s0, n);
    }
    enteroModular operator/(const enteroModular & e) const{
    	enteroModular tmp(e.a, max(n, e.n));
        return enteroModular(a * tmp.inverso().a, max(n, e.n));
    }
    enteroModular operator+=(const enteroModular & e){
        *this = *this + e;
        return *this;
    }
    enteroModular operator-=(const enteroModular & e){
        *this = *this - e;
        return *this;
    }
    enteroModular operator*=(const enteroModular & e){
        *this = *this * e;
        return *this;
    }
    enteroModular operator/=(const enteroModular & e){
        *this = *this / e;
        return *this;
    }
    enteroModular operator++(int xd){
        *this = *this + enteroModular(1, n);
        return * this;
    }
    enteroModular operator--(int xd){
        *this = *this - enteroModular(1, n);
        return * this;
    }
    bool operator==(const enteroModular & e) const{
    	if(max(n, e.n) == 0)
    		return a == e.a;
        return mod(a, max(n, e.n)) == mod(e.a, max(n, e.n));
    }
    bool operator!=(const enteroModular & e) const{
    	if(max(n, e.n) == 0)
    		return a != e.a;
        return mod(a, max(n, e.n)) != mod(e.a, max(n, e.n));
    }
    string str() const{
    	stringstream ss;
    	ss << a << "," << n;
    	return ss.str();
    }
};

struct fraccion{
    ull num, den;
    fraccion(){
        num = 0, den = 1;
    }
    fraccion(ull x, ull y){
        if(y < 0){
            x *= -1, y *=-1;
        }
        ull d = gcd(abs(x), abs(y));
        num = x/d, den = y/d;
    }
    fraccion(ull v){
        num = v;
        den = 1;
    }
    fraccion operator+(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return fraccion(num*(f.den/d) + f.num*(den/d), den*(f.den/d));
    }
    fraccion operator-() const{
        return fraccion(-num, den);
    }
    fraccion operator-(const fraccion& f) const{
        return *this + (-f);
    }
    fraccion operator*(const fraccion& f) const{
        return fraccion(num*f.num, den*f.den);
    }
    fraccion operator/(const fraccion& f) const{
        return fraccion(num*f.den, den*f.num);
    }
    fraccion operator+=(const fraccion& f){
        *this = *this + f;
        return *this;
    }
    fraccion operator-=(const fraccion& f){
        *this = *this - f;
        return *this;
    }
    fraccion operator++(int xd){
        *this = *this + 1;
        return *this;
    }
    fraccion operator--(int xd){
        *this = *this - 1;
        return *this;
    }
    fraccion operator*=(const fraccion& f){
        *this = *this * f;
        return *this;
    }
    fraccion operator/=(const fraccion& f){
        *this = *this / f;
        return *this;
    }
    bool operator==(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) == (den/d)*f.num);
    }
    bool operator!=(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) != (den/d)*f.num);
    }
    bool operator >(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) > (den/d)*f.num);
    }
    bool operator <(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) < (den/d)*f.num);
    }
    bool operator >=(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) >= (den/d)*f.num);
    }
    bool operator <=(const fraccion& f) const{
        ull d = gcd(den, f.den);
        return (num*(f.den/d) <= (den/d)*f.num);
    }
    fraccion inverso() const{
        return fraccion(den, num);
    }
    fraccion fabs() const{
        fraccion nueva;
        nueva.num = abs(num);
        nueva.den = den;
        return nueva;
    }
    double value() const{
    	return (double)num / (double)den;
    }
    string str() const{
        stringstream ss;
        ss << num;
        if(den != 1) ss << "/" << den;
        return ss.str();
    }
};

ostream &operator<<(ostream &os, const enteroModular & e) { 
    return os << e.a;
}

ostream &operator<<(ostream &os, const fraccion & f) { 
    return os << f.str();
}

istream &operator>>(istream &is, fraccion & f){
    ull num = 0, den = 1;
    string str;
    is >> str;
    size_t pos = str.find("/");
    if(pos == string::npos){
        istringstream(str) >> num;
    }else{
        istringstream(str.substr(0, pos)) >> num;
        istringstream(str.substr(pos + 1)) >> den;
    }
    fraccion nueva(num, den);
    f = nueva;
    return is;
}

template <typename entrada>
struct matrix{
    vector< vector<entrada> > A;
    int m, n;

    matrix(int _m, int _n){
        m = _m, n = _n;
        A.resize(m, vector<entrada>(n, 0));
    }

    vector<entrada> & operator[] (int i){
        return A[i];
    }

    void multiplicarFilaPorEscalar(int k, entrada c){
        for(int j = 0; j < n; j++) A[k][j] *= c;
    }

    void intercambiarFilas(int k, int l){
        swap(A[k], A[l]);
    }

    void sumaMultiploFilaAOtra(int k, int l, entrada c){
        for(int j = 0; j < n; j++) A[k][j] += c * A[l][j];
    }

    int gauss_jordan(bool full = true, bool makeOnes = true, function<void(int, int, int, entrada)>callback = NULL){
        int i = 0, j = 0;
        while(i < m && j < n){
            if(A[i][j] == 0){
                for(int f = i + 1; f < m; f++){
                    if(A[f][j] != 0){
                        intercambiarFilas(i, f);
                        if(callback) callback(2, i, f, 0);
                        break;
                    }
                }
            }
            if(A[i][j] != 0){
            	entrada inv_mult = A[i][j].inverso();
                if(makeOnes && A[i][j] != 1){
                    multiplicarFilaPorEscalar(i, inv_mult);
                    if(callback) callback(1, i, 0, inv_mult);
                }
                for(int f = (full ? 0 : (i + 1)); f < m; f++){
                    if(f != i && A[f][j] != 0){
                        entrada inv_adit = -A[f][j];
                        if(!makeOnes) inv_adit *= inv_mult;
                        sumaMultiploFilaAOtra(f, i, inv_adit);
                        if(callback) callback(3, f, i, inv_adit);
                    }
                }
                i++;
            }
            j++;
        }
        return i;
    }

    void eliminacion_gaussiana(){
        gauss_jordan(false);
    }

    static entrada delta(int i, int j){
        if(i == j) return 1;
        else return 0;
    }

    static matrix identidad(int n){
        matrix<entrada> id(n, n);
        for(int i = 0; i < n; i++){
            id[i][i] = 1;
        }
        return id;
    }

    static matrix elemental_1(int n, int k, entrada c){
        matrix<entrada> E(n, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == k) E[i][j] = c * delta(k, j);
                else E[i][j] = delta(i, j);
            }
        }
        return E;
    }

    static matrix elemental_2(int n, int k, int l){
        matrix<entrada> E(n, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == k) E[i][j] = delta(l, j);
                else if(i == l) E[i][j] = delta(k, j);
                else E[i][j] = delta(i, j);
            }
        }
        return E;
    }

    static matrix elemental_3(int n, int k, int l, entrada c){
        matrix<entrada> E(n, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == k) E[i][j] = delta(k, j) + c * delta(l, j);
                else E[i][j] = delta(i, j);
            }
        }
        return E;
    }

    matrix operator+(const matrix & B) const{
        if(m == B.m && n == B.n){
            matrix<entrada> C(m, n);
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    C[i][j] = A[i][j] + B.A[i][j];
                }
            }
            return C;
        }else{
            return *this;
        }
    }

    matrix operator+=(const matrix & M){
        *this = *this + M;
        return *this;
    }

    matrix operator-() const{
        matrix<entrada> C(m, n);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                C[i][j] = -A[i][j];
            }
        }
        return C;
    }

    matrix operator-(const matrix & B) const{
        return *this + (-B);
    }

    matrix operator-=(const matrix & M){
        *this = *this + (-M);
        return *this;
    }

    matrix operator*(const matrix & B) const{
        if(n == B.m){
            matrix<entrada> C(m, B.n);
            for(int i = 0; i < m; i++){
                for(int j = 0; j < B.n; j++){
                    for(int k = 0; k < n; k++){
                        C[i][j] += A[i][k] * B.A[k][j];
                    }
                }
            }
            return C;
        }else{
            return *this;
        }
    }

    matrix operator*(const entrada & c) const{
        matrix<entrada> C(m, n);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                C[i][j] = A[i][j] * c;
            }
        }
        return C;
    }

    matrix operator*=(const matrix & M){
        *this = *this * M;
        return *this;
    }

    matrix operator*=(const entrada & c){
        *this = *this * c;
        return *this;
    }

    matrix operator^(ull b) const{
    	matrix<entrada> ans = matrix<entrada>::identidad(n);
    	matrix<entrada> A = *this;
    	while(b){
    		if(b & 1) ans *= A;
    		b >>= 1;
    		if(b) A *= A;
    	}
    	return ans;
    }

    matrix operator^=(ull n){
    	*this = *this ^ n;
    	return *this;
    }

    bool operator==(const matrix & B) const{
        if(m == B.m && n == B.n){
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    if(A[i][j] != B.A[i][j]) return false;
                }
            }
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const matrix & B) const{
        return !(*this == B);
    }

    matrix<entrada> escalonada_reducida_por_filas(){
        matrix<entrada> asoc = *this;
        asoc.gauss_jordan();
        return asoc;
    }

    matrix<entrada> escalonada_por_filas(){
        matrix<entrada> asoc = *this;
        asoc.eliminacion_gaussiana();
        return asoc;
    }

    bool invertible(){
        if(m == n){
        	matrix<entrada> tmp = *this;
            return tmp.gauss_jordan(false) == n;
        }else{
            return false;
        }
    }

    matrix<entrada> transpuesta(){
        matrix<entrada> T(n, m);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                T[j][i] = A[i][j];
            }
        }
        return T;
    }

    matrix<entrada> inversa(){
        if(m == n){
            matrix<entrada> tmp = *this;
            matrix<entrada> inv = matrix<entrada>::identidad(n);
            auto callback = [&](int op, int a, int b, entrada e){
            	if(op == 1){
            		inv.multiplicarFilaPorEscalar(a, e);
            	}else if(op == 2){
            		inv.intercambiarFilas(a, b);
            	}else if(op == 3){
            		inv.sumaMultiploFilaAOtra(a, b, e);
            	}
            };
            if(tmp.gauss_jordan(true, true, callback) == n){
                return inv;
            }else{
                return *this;
            }
        }else{
            return *this;
        }
    }

    entrada traza(){
    	entrada sum = 0;
    	for(int i = 0; i < min(m, n); i++){
    		sum += A[i][i];
    	}
    	return sum;
    }

    entrada determinante(){
        if(m == n){
            matrix<entrada> tmp = *this;
            entrada det = 1;
            auto callback = [&](int op, int a, int b, entrada e){
            	if(op == 1){
            		det /= e;
            	}else if(op == 2){
            		det *= -1;
            	}
            };
            if(tmp.gauss_jordan(false, true, callback) != n) det = 0;
            return det;
        }else{
            return 0;
        }
    }

    bool nextP(vector<int> & sigma, int & sign){
        int i = sigma.size() - 1;
        while(i > 0 & sigma[i - 1] >= sigma[i]) i--;
        if(i == 0) return false;
        int j = sigma.size() - 1;
        while(sigma[i - 1] >= sigma[j]) j--;
        swap(sigma[i - 1], sigma[j]);
        sign *= -1;
        j = sigma.size() - 1;
        if(((j - i + 1) >> 1) & 1) sign *= -1;
        while(i < j) swap(sigma[i++], sigma[j--]);
        return true;
    }

    entrada slowDeterminante(){
        if(m == n){
            entrada det = 0;
            vector<int> sigma(n);
            for(int i = 0; i < n; i++) sigma[i] = i;
            int sign = 1;
            do{
                entrada prod = 1;
                for(int i = 0; i < n; i++) prod *= A[i][sigma[i]];
                if(sign == 1) det += prod;
                else det -= prod;
            }while(nextP(sigma, sign));
            return det;
        }else{
            return 0;
        }
    }

    matrix<entrada> menor(int x, int y){
        matrix<entrada> M(0, 0);
        for(int i = 0; i < m; i++){
            if(i != x){
                M.A.push_back(vector<entrada>());
                for(int j = 0; j < n; j++){
                    if(j != y){
                        M.A.back().push_back(A[i][j]);
                    }
                }
            }
        }
        M.m = m - 1;
        M.n = n - 1;
        return M;
    }

    entrada cofactor(int x, int y){
        entrada ans = menor(x, y).determinante();
        if((x + y) % 2 == 1) ans *= -1;
        return ans;
    }

    matrix<entrada> cofactores(){
        matrix<entrada> C(m, n);
        for(int i = 0; i < m; i++){
        	for(int j = 0; j < n; j++){
        		C[i][j] = cofactor(i, j);
        	}
        }
        return C;
    }

    matrix<entrada> adjunta(){
        return cofactores().transpuesta();
    }

    vector< matrix<entrada> > PA_LU(){
    	matrix<entrada> U = *this;
    	matrix<entrada> L = matrix<entrada>::identidad(n);
    	matrix<entrada> P = matrix<entrada>::identidad(n);
    	auto callback = [&](int op, int a, int b, entrada e){
    		if(op == 2){
    			L.intercambiarFilas(a, b);
    			P.intercambiarFilas(a, b);
    			L.A[a][a] = L.A[b][b] = 1;
    			L.A[a][a + 1] = L.A[b][b - 1] = 0;
    		}else if(op == 3){
    			L.A[a][b] = -e;
    		}
    	};
    	U.gauss_jordan(false, false, callback);
    	return {P, L, U};
    }

    vector<entrada> polinomio(){
    	matrix<entrada> M(n, n);
    	vector<entrada> coef(n + 1);
    	matrix<entrada> I = matrix<entrada>::identidad(n);
    	coef[n] = 1;
    	for(int i = 1; i <= n; i++){
    		M = (*this) * M + I * coef[n - i + 1];
    		coef[n - i] = -((*this) * M).traza() / i;
    	}
    	return coef;
    }

    matrix<entrada> gram_schmidt(){ //los vectores son las filas de la matriz
    	matrix<entrada> B = (*this) * (*this).transpuesta();
    	matrix<entrada> ans = *this;
    	auto callback = [&](int op, int a, int b, entrada e){
    		if(op == 1){
    			ans.multiplicarFilaPorEscalar(a, e);
    		}else if(op == 2){
    			ans.intercambiarFilas(a, b);
    		}else if(op == 3){
    			ans.sumaMultiploFilaAOtra(a, b, e);
    		}
    	};
    	B.gauss_jordan(false, false, callback);
    	return ans;
    }

    string str() const{
        stringstream ss;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++) ss << A[i][j] << " ";
            ss << "\n";
        }
        ss << "\n";
        return ss.str();
    }

};

template <typename entrada>
ostream &operator<<(ostream &os, const matrix<entrada> & M) { 
    return os << M.str();
}

void pedirValores(matrix<fraccion> & S){
    for(int i = 0; i < S.m; i++){
        cout << "Introduce la fila " << (i + 1) << ": ";
        for(int j = 0; j < S.n; j++){
            cin >> S.A[i][j];
        }
    }
}

void pedirValores(matrix<enteroModular> & S, ull p){
    ull valor;
    for(int i = 0; i < S.m; i++){
        cout << "Introduce la fila " << (i + 1) << ": ";
        for(int j = 0; j < S.n; j++){
            cin >> valor;
            S.A[i][j] = enteroModular(valor, p);
        }
    }
}

int main()
{
	int m, n;
    ull p;
    string campo;
    cout << "Introduce el n\243mero de filas: ";
    cin >> m;
    cout << "Introduce el n\243mero de columnas: ";
    cin >> n;
    cout << "Introduce Q para trabajar en los racionales, o un numero primo p para trabajar en F_p: ";
    cin >> campo;
    if(campo == "Q"){
        matrix<fraccion> M(m, n);
        pedirValores(M);
        cout << "\nDeterminante: " << M.determinante() << "\n\n";
        cout << "Inversa:\n" << M.inversa() << "\n";
        vector< matrix<fraccion> > LU = M.PA_LU();
        cout << "P:\n" << LU[0] << "L:\n" << LU[1] << "U:\n" << LU[2];
        cout << "Polinomio caracteristico: ";
        vector<fraccion> polinomio = M.polinomio();
        for(int i = 0; i < polinomio.size(); i++){
        	cout << polinomio[i] << "x^" << i << ", ";
        }
        cout << "\nGram-Schmidt:\n" << M.gram_schmidt();
    }else{
        istringstream(campo) >> p;
        matrix<enteroModular> M(m, n);
        pedirValores(M, p);
        cout << "\nDeterminante: " << M.determinante() << "\n\n";
        cout << "Inversa:\n" << M.inversa() << "\n";
        vector< matrix<enteroModular> > LU = M.PA_LU();
        cout << "P:\n" << LU[0] << "L:\n" << LU[1] << "U:\n" << LU[2];
        cout << "Polinomio caracteristico: ";
        vector<enteroModular> polinomio = M.polinomio();
        for(int i = 0; i < polinomio.size(); i++){
        	cout << polinomio[i] << "x^" << i << ", ";
        }
    }
    return 0;
}