//
// Created by Murilo on 25/04/2024.
//

#ifndef CG2_COLOR_H
#define CG2_COLOR_H

#include <vector>
using namespace std;

class Color{

    friend Color operator+(double const &v, Color const &c){ return c + v;}

    friend Color operator-(double const &v, Color const &c){ return (c - v);}

    friend Color operator*(double const &v, Color const &c){ return c * v;}

public:
    double r, g, b, a;

    //Construtores padrões
    Color();
    Color(Color const &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
    Color(double _r, double _g, double _b, double _a) : r(_r), g(_g), b(_b), a(_a) {}
    Color(double const *c ) : r(c[0]), g(c[1]), b(c[2]), a(c[3]) {}
    Color(vector<double>& c) : r(c[0]), g(c[1]), b(c[2]), a(c[3]){} // cuidado nessa função!

    //Funções para setar rgba
    void set(double _r, double _g, double _b, double _a) {r = _r; g = _g;b = _b; a = _a;}
    void set(double const *v){r = v[0]; g = v[1]; b = v[2]; a = v[3];}
    void set(vector<double>& v){r = v[0]; g = v[1]; b = v[2]; a = v[3];}

    //Funções para pegar rgba
    void getValue(double *v) const {v[0] = r; v[1] = g; v[2] = b; v[3] = a;}
    void getValue(vector<double>& v) const {v[0] = r; v[1] = g; v[2] = b; v[3] = a;}
    vector<double> getValue() const { return {r, g, b, a};}

    //Operadores Binários
    Color  operator + ( Color const &c ) const { return Color(r+c.r, g+c.g, b+c.b, a+c.a); }
    Color  operator - ( Color const &c ) const { return Color(r-c.r, g-c.g, b-c.b, a-c.a); }
    Color  operator * ( Color const &c ) const { return Color(r*c.r, g*c.g, b*c.b, a*c.a); }
    Color  operator / ( Color const &c ) const { return Color(r/c.r, g/c.g, b/c.b, a/c.a); }
    Color  operator + ( double  const &n ) const { return Color(r+n, g+n, b+n, a+n); }
    Color  operator - ( double  const &n ) const { return Color(r-n, g-n, b-n, a-n); }
    Color  operator * ( double  const &n ) const { return Color(r*n, g*n, b*n, a*n); }
    Color  operator / ( double  const &n ) const { return Color(r/n, g/n, b/n, a/n); }

    //Operadores de assignment
    Color& operator += ( Color const &c ) { r+=c.r; g+=c.g; b+=c.b; return *this; }
    Color& operator -= ( Color const &c ) { r-=c.r; g-=c.g; b-=c.b; return *this; }
    Color& operator *= ( Color const &c ) { r*=c.r; g*=c.g; b*=c.b; return *this; }
    Color& operator /= ( Color const &c ) { r/=c.r; g/=c.g; b/=c.b; return *this; }
    Color& operator += ( double const &n ) { r+=n; g+=n; b+=n; return *this; }
    Color& operator -= ( double const &n ) { r-=n; g-=n; b-=n; return *this; }
    Color& operator *= ( double const &n ) { r*=n; g*=n; b*=n; return *this; }
    Color& operator /= ( double const &n ) { r/=n; g/=n; b/=n; return *this; }

    //Operador de Igualdade
    bool operator == ( Color const &c ) const { return ( (c.r==r) && (c.g==g) && (c.b==b) && (c.a==a) ); }
    bool operator != ( Color const &c ) const { return ( (c.r!=r) || (c.g!=g) || (c.b!=b) || (c.a!=a) ); }

    // Talvez fazer funções de escala cinza depois
};

#endif //CG2_COLOR_H
