#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "forward.h"
#include "stack.h"
#include "node.h"
using namespace std;


// Mientras mayor el valor de retorno, mayor la precedencia
int precedence(string s) {
  if(s == "(" || s == ")")
    return 4;
  else if(s == "^")
    return 3;
  else if(s == "*" || s == "/")
    return 2;
  else if(s == "+" || s == "-")
    return 1;
  return -1;
}


// Resuelve la expresión
double resolve(string s, double op1, double op2) {
  if(s == "^")
    return pow(op1, op2);
  else if(s == "/")
    return op1 / op2;
  else if(s == "*")
    return op1 * op2;
  else if(s == "+")
    return op1 + op2;
  else if(s == "-")
    return op1 - op2;
  return -1;
}


struct Result{
  double result;
  bool error = false;
};


Result evaluate(string input) {
  Result result;
  ForwardList<string>* postfix = new ForwardList<string>();
  ForwardList<string>* expression = new ForwardList<string>();
  StackList<string>* stack = new StackList<string>();

  string tmp = "", opetr = "";
  bool op_valid = true;
  int parentheses_count = 0;

  // 1- descomponer el input y validar
  // Pasar la expresión a una lista enlazada para guardar la expresión
  try {
    for(int i=0; i<input.length(); i++) {
      // Validamos que los parentesis estén cerrados
      if(input[i] == '(')
        parentheses_count++;
      else if(input[i] == ')')
        parentheses_count--;

      // Paso mi char a un string para saber si es un operador o no
      opetr.push_back(input[i]);

      // Me ayuda a saber si será un operando de 1 o más cifras
      if(input[i] != ' ') {
        if(precedence(opetr) == -1) { // Si no es un espacio en blanco ni un operador
          tmp += opetr;
        } else if(tmp != "") { // Si el tmp no está vacío
          expression->push_back(tmp);
          tmp = "";
        }

         // Si es un operador lo pushea automaticamente
        if(precedence(opetr) != -1) {
          expression->push_back(opetr);
        }
      }

      // Valida si un perantesis no cerrado al finalizar con la última iteración
      if(i == input.length() - 1) {
        if(parentheses_count != 0) {
          result.error = true;
          throw "Los parentesis no están bien cerrados";
        } else if(input[i] != ' ' && tmp != "") {
          expression->push_back(tmp);
        } else if(input[i] == ' ' && precedence(tmp) == -1 && tmp != "") {
          expression->push_back(tmp);
        }
      }

      opetr.clear();
    }

    // Quita los espacios en blanco para hacer las validaciones de operadores
    tmp = ""; // reutilizamos

    for(int i=0; i<input.length(); i++)
      if(input[i] != ' ')
        tmp += input[i];
    input = tmp;


    // Valida que entre los operadores haya operandos
    for(int i=0; i<input.length(); i++) {
      string exp, exp_aft, exp_bef;
      exp.push_back(input[i]);

      // Valida si entre un data hay operandos o parentesis
      if(precedence(exp) != -1 && precedence(exp) != 4) { // Es un operador aritmético?
        // Valida si hay un operador al final o al inicio de la expresión
        if( i == 0 || i == input.length() - 1) {
          result.error = true;
          throw "No hay suficientes operandos";
        } else { // Valida si hay operandos entre los operadores
          exp_bef.push_back(input[i-1]);
          exp_aft.push_back(input[i+1]);

          if((precedence(exp_bef) != -1 && precedence(exp_bef) != 4) ||
          (precedence(exp_aft) != -1 && precedence(exp_aft) != 4))  
            op_valid = false;

          if(!op_valid) {
            result.error = true;
            throw "No hay suficientes operandos";
          }
        }
      }
    }


    // Agregando parentesis a la lista para saber en donde empieza y termina cada expresión
    expression->push_front("(");
    expression->push_back(")");
    

    // 2- convertir de Infijo a Postfijo
    for(Node<string>* tmp = expression->head; tmp != nullptr; tmp = tmp->next) {
      string c = string(tmp->data);

      if(precedence(c) != -1) { // es un operador
        if(stack->is_empty()) { // si el stack esta vacio
          stack->push(c);
        } else { // si el stack no esta vacio
          if(c == ")") { // si es un ) de cierre
            while(stack->back() != "(") { // Mientras no encuentre un "(" hará push en el postfix
              postfix->push_back(stack->pop());
            }
            stack->pop();
          } else if(precedence(stack->back()) >= precedence(c) && stack->back() != "(") { // Si la prec es mayor o dif de "("
            while(precedence(stack->back()) >= precedence(c) && stack->back() != "(") {
              postfix->push_back(stack->pop());
            }
            stack->push(c);
          } else {
            stack->push(c);
          }
        }
      } else { // es un operando
        postfix->push_back(c);
      }
    }


    // 3- resolver la expresion
    for(Node<string>* tmp = postfix->head; tmp != nullptr; tmp = tmp->next) {
      // Si es un operando pushea al stack
      if(precedence(tmp->data) == -1) {
        stack->push(tmp->data);
      } else {
        string op2 = stack->pop(); // operador 1
        string op1 = stack->pop(); // operador 2

        double res = resolve(tmp->data, stod(op1), stod(op2));
        int res_int = int(res);

        // Le da un formato al resultado, si no tiene deciaml, retorna solo el número, sinno con un solo decimal 
        if(res - res_int == 0) {
          stack->push(to_string(res_int));
        } else {
          string res_str = to_string(res);
          stringstream res_s;
          
          res_s.str(res_str);
          res_s.precision(2);
          
          stack->push(res_s.str());
        }
      }
    }

    result.result = stod(stack->front());
    return result;

  } catch(const char* msg) {
    cerr << msg << endl;
  }

  result.result = -1;
  return result;
}
