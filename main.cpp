#include <iostream>
#include <cmath>
#include <any>

using namespace std;

template<typename Expression, typename Derivative>
class X{
public:

    X(Expression e, Derivative d): equacao(e), derivada(d){}

    auto e(double v) const {return equacao(v);}
    auto dx(double v) const {return derivada(v); }

private:
    Expression equacao;
    Derivative derivada;
};

template<typename E, typename D>
auto transfEmExp( X<E,D> eq){return eq;}

auto transfEmExp(double n){
    X delta([n](double v) {return n; }, [n](double v) {return 0;});
    return delta;
}

//Arrow function
template <typename T, typename H>
auto operator ->*(T f, H g){
    auto w = transfEmExp(f);
    using k = decltype(g);

    static_assert(is_same<int,k>::value, "Operador de potenciação definido apenas para inteiros");

    return X([w,g](double v){return pow(w.e(v),g); }, [w,g](double v ){return g * pow(w.e(v), g - 1) * w.dx(v); });
}

//Soma
template <typename T, typename H>
auto operator+(T f, H g){
    auto w = transfEmExp(f);
    auto z = transfEmExp(g);
    return X([w,z](double v ){return w.e(v) + z.e(v);}, [w,z](double v){return w.dx(v) + z.dx(v);});
}

template <typename T, typename H>
auto operator-(T f, H g){
    auto w = transfEmExp(f);
    auto z = transfEmExp(g);
    return X([w,z](double v ){return w.e(v) - z.e(v);}, [w,z](double v){return w.dx(v) - z.dx(v);});
}


template <typename T, typename H>
auto operator*(T f, H g){
    auto w = transfEmExp(f);
    auto z = transfEmExp(g);
    return X([w,z](double v ){return w.e(v) * z.e(v);}, [w,z](double v){return w.dx(v)*z.e(v) + w.e(v)*z.dx(v);});
}

//template <typename T, typename H>
//auto operator/(T f, H g){
//    auto w = transfEmExp(f);
//    auto z = transfEmExp(g);
//    return X([w,z](double v ){return w.e(v) / z.e(v);}, [w,z](double v){return w.dx(v)*z.e(v) + w.e(v)*z.dx(v);});
//}
//cos
template<typename T>
auto cos(T x){
    auto w = transfEmExp(x);
    return X([w](double v){return cos(w.e(v));},[w](double v){return -(sin(w.e(v))) * w.dx(v);});
}
//sin
template<typename T>
auto sin(T x){
    auto w = transfEmExp(x);
    return X([w](double v){return sin(w.e(v));},[w](double v){return cos(w.e(v) * w.dx(v));});
}
//exp
template <typename T>
auto exp(T x){
    auto w = transfEmExp(x);
    return X([w](double v){return exp(v);}, [w](double v){return exp(w.e(v) * w.dx(v));});
}
//Log
template <typename T>
auto log(T x){
    auto w = transfEmExp(x);
    return X([w](double v){return log(v);}, [w](double v){return 1/v;});
}

X x([](double v){return v;}, [](double v){return 1;});


int main(){
    double v = 3;
    auto f = 2 * x->*2;

    std::cout << "f(" << v << ")=" << f.e(v) << ", f'(" << v << ")=" << f.dx(v) << std::endl;
}