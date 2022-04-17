#include <iostream>
#include "functions.h"

using namespace std;

struct Result{
    double result;
    bool error;
};

Result evaluate(string input)
{
    Result res;
    string in = '(' + input + ')';
    // 1- descomponer el input y validar
    Stack<double> numbers;
    Stack<char> symbols;
    res.error = decompose(numbers, symbols, in);
    // 2- convertir de Infijo a Postfijo
    
    // 3- resolver la expresion

    //* Si no cumple la validacion retornar Result.error = true;

    return res;
}
