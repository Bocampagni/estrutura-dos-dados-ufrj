#include <iostream>
#include <cmath>
#include <any>

using namespace std;

template<typename E, typename D>
class X{
public:

    X(E e, D d): noPontoSemDiff(e), noPontoDiff(d){}

    auto e(double v) const {return noPontoSemDiff(v);}
    auto dx(double v) const {return noPontoDiff(v); }

private:
    E noPontoSemDiff;
    D noPontoDiff;
};

template<typename E, typename D>
auto transformada( X<E,D> equation){return equation;}

auto transformada(double num){
    X aux([num](double v) {return num; }, [num](double v) {return 0;});
    return aux;
}


template <typename TIPO, typename OUTROTIPO >
auto operator+(TIPO func, OUTROTIPO outraFunc){
    auto aux = transformada(func);
    auto outroAux = transformada(outraFunc);
    return X([aux,outroAux](double v ){return aux.e(v) + outroAux.e(v);}, [aux,outroAux](double v){return aux.dx(v) + outroAux.dx(v);});
}

template <typename TIPO, typename OUTROTIPO >
auto operator-(TIPO func, OUTROTIPO outraFunc){
    auto aux = transformada(func);
    auto outroAux = transformada(outraFunc);
    return X([aux,outroAux](double v ){return aux.e(v) - outroAux.e(v);}, [aux,outroAux](double v){return aux.dx(v) - outroAux.dx(v);});
}


template <typename TIPO, typename OUTROTIPO >
auto operator*(TIPO func, OUTROTIPO outraFunc){
    auto aux = transformada(func);
    auto outroAux = transformada(outraFunc);
    return X([aux,outroAux](double v ){return aux.e(v) * outroAux.e(v);}, [aux,outroAux](double v){return aux.dx(v)*outroAux.e(v) + aux.e(v)*outroAux.dx(v);});
}
template <typename T>
auto log(T x){
    auto aux = transformada(x);
    return X([aux](double v){return log(v);}, [aux](double v){return 1/v;});
}
template<typename T>
auto sin(T x){
    auto aux = transformada(x);
    return X([aux](double v){return sin(aux.e(v));},[aux](double v){return cos(aux.e(v) * aux.dx(v));});
}


template<typename T>
auto cos(T x){
    auto aux = transformada(x);
    return X([aux](double v){return cos(aux.e(v));},[aux](double v){return -(sin(aux.e(v))) * aux.dx(v);});
}

template <typename T>
auto exp(T x){
    auto aux = transformada(x);
    return X([aux](double v){return exp(v);}, [aux](double v){return exp(aux.e(v) * aux.dx(v));});
}


template <typename TIPO, typename OUTROTIPO >
auto operator ->*(TIPO func, OUTROTIPO outraFunc){
    auto aux = transformada(func);
    using T = decltype(outraFunc);

    static_assert(is_same<int,T>::value, "Operador de potenciação definido apenas para inteiros");

    return X([aux,outraFunc](double v){return pow(aux.e(v),outraFunc); }, [aux,outraFunc](double v ){return outraFunc * pow(aux.e(v), outraFunc - 1) * aux.dx(v); });
}




X x([](double v){return v;}, [](double v){return 1;});


int main(){
    double v = 3;
    auto f = 2 * x->*2;

    std::cout << "f(" << v << ")=" << f.e(v) << ", f'(" << v << ")=" << f.dx(v) << std::endl;
}