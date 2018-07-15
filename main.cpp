#include <cstring>
#include <iostream>

#include "src/Calculator.hpp"
#include "src/ConcreteLexer.hpp"
#include "src/Exception.hpp"

using namespace std;
using namespace Calculation;

int main(int argc, char* argv[])
{
    Calculation::Calculator calculator;
    string line;

    if(argc == 2 && !strcmp(argv[1], "--help"))
    {
        cout << "Usage:" << endl;
        cout << "1. To run interactively:" << endl;
        cout << "   ./calculation" << endl;
        cout << "   If running interactively, type the expression to be calculated and then press Enter." << endl;
        cout << "   In order to exit, press 'Q' and Enter" << endl;
        cout << "2. To run from file:" << endl;
        cout << "   ./calculation < <file>" << endl << endl;
        return 0;
    }

    while(getline(cin, line))
    {
        if(line == "Q" || line == "q")
            break;

        BigInteger result;
        try
        {
            ConcreteLexer lexer(line);
            result = calculator.calculate(lexer);
            cout << result;
        }
        catch(CalculationException& ex)
        {
            cout << ex.what();
        }
        cout << endl;
    }
    return 0;
}

/*
 * int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Usage: calculator <file_path>";
        return 1;
    }

    FileReader reader;
    vector<string> expressions = reader.readLines(argv[1]);

    Calculator calculator;
    for(int i = 0; i < expressions.size(); i++)
    {
        cout << (i + 1) << ". ";

        BigInteger result;
        try
        {
            ConcreteLexer lexer(expressions[i]);
            result = calculator.calculate(lexer);
            cout << result;
        }
        catch(CalculatorException& ex)
        {
            cout << ex.what();
        }
        cout << endl;
    }
    return 0;
}

*/
