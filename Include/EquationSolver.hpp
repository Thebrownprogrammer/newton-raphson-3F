#include <iostream>
#include <symengine/parser.h>
#include <symengine/expression.h>
#include <symengine/solve.h>

using namespace std;
using SymEngine::Expression;
using SymEngine::symbol;
using SymEngine::solve;
using SymEngine::rcp_dynamic_cast; 

class EquationSolver {
public:
    EquationSolver(string equation, int iterations, double errorPercent)
        : equation_(std::move(equation)),
          iterations_(iterations),
          errorPercent_(errorPercent) {}

    double solve() {
        Expression expr = SymEngine::parse(equation_);
        double solution = newtonRaphson(expr, 0.0);
        
        if (!isnan(solution)) {
            cout << "La solución aproximada es: " << solution << endl;
        }
        
        return solution;
    }

private:
    string equation_;
    int iterations_;
    double errorPercent_;

    double evaluate(Expression expr, double x) {
        auto evaluated = expr.subs({{symbol("x"), Expression(x)}});
        //auto evaluated_double = rcp_dynamic_cast<SymEngine::Number>(evaluated);
        return 0.0;// evaluated_double->as_double();
    }

    Expression derivative(Expression expr) {
        auto x = symbol("x");
        return expr.diff(x);
    }

    double newtonRaphson(Expression expr, double initialGuess) {
        double x = initialGuess;
        double errorThreshold = errorPercent_ / 100.0;
        
        for (int i = 0; i < iterations_; i++) {
            double y = evaluate(expr, x);
            double dy = evaluate(derivative(expr), x);
            double step = y / dy;
            
            if (abs(step) < errorThreshold) {
                cout << "Converged within the specified error threshold." << endl;
                return x;
            }
            
            x -= step;
        }
        
        cout << "Failed to converge within the specified number of iterations." << endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
};