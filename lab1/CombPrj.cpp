#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "UINT32.h"
#include "Combinatorics.h"
#include "ArihmeticError.h"

using namespace std;

const char ARGUMENT_DELIMITER = ',';

const string INFO_MESSAGE = "Поддерживается вычисление следующих комбинаторных чисел\n"
  "\tЧисло размещений U(n,m)\n"
  "\tЧисло размещений без повторений A(n,m)\n"
  "\tЧисло перестановок P(n)\n"
  "\tЧисло сочетаний C(n,m)\n"
  "\tЧисло Стирлинга второго рода S(n,m)\n"
  "\tЧисло Белла B(n)\n"
  "Для выхода введи Q";

const unordered_map< char, function<UINT32(byte)> > functionsWithOneArgument = {
  {'P', Permutations},
  {'B', Bell},
};

const unordered_map< char, function<UINT32(byte, byte)> > functionsWithTwoArguments = {
  {'C', Binomial},
  {'U', Placements},
  {'A', PlacementsWithoutRepetition},
  {'S', Stirling},
};

std::vector<byte> parseArguments(std::string str)
{
  if (str.size() < 3 || str.front() != '(' || str.back() != ')') {
    throw std::invalid_argument("Введённая строка не соответсвует условиям ввода. Смотри в help");
  }

  // Remove parentheses for simpicity
  str.pop_back();
  str.erase(str.begin());

  vector<byte> arguments;
  string token;
  istringstream tokenStream(str);

  while (std::getline(tokenStream, token, ARGUMENT_DELIMITER)) {
    int argument = stoi(token);
    if (argument > numeric_limits<byte>::max() || argument < 0) {
      throw std::invalid_argument("Аргументы функции принимают только положительные числа, которые вмещаются в один байт!");
    }
    arguments.push_back(static_cast<byte>(argument));
  }
  return arguments;
}


int main(int argc, char *argv[])
{
  cout << "Для дополнительной информации введите H" << endl;
  
  string str;
  while (getline(cin, str)) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    if (str[0] == 'H') {
      cout << INFO_MESSAGE << endl;
      continue;
    } else if (str[0] == 'Q') {
      break;
    }

    vector<byte> arguments;
    try {
      arguments = parseArguments(str.substr(1));
    } catch (std::exception &ex) {
      cout << ex.what() << endl;
      continue;
    }
    try {
      if (functionsWithOneArgument.count(str[0])) {
        if (arguments.size() != 1) {
          cout << "Число аргументов для функции " << str[0] << " должно быть 1" << endl;
          continue;
        }
        cout << str << " = " << functionsWithOneArgument.at(str[0])(arguments[0]) << endl;
      } else if (functionsWithTwoArguments.count(str[0])) {
        if (arguments.size() != 2) {
          cout << "Число аргументов для функции " << str[0] << " должно быть 2" << endl;
          continue;
        }
        cout << str << " = " << functionsWithTwoArguments.at(str[0])(arguments[0], arguments[1]) << endl;
      } else {
        cout << str[0] + " не соответсвует ни одной функции из списка. Смотри в help" << endl;
      }
    } catch (ArihmeticError &er) {
      cout << "Во время вычисления " << str << " произошло переполение" << endl;
      cout << er.what() << endl;
    }
  }

  
  return 0;
}

