//
// Created by harelfeldman on 1/14/20.
//

#ifndef ADVANCEDPROG2_SOLVERMATRIX_H
#define ADVANCEDPROG2_SOLVERMATRIX_H


#include <vector>
#include "State.h"
#include "Point.h"
#include <string>
#include "ISearcher.h"
#include "Solver.h"
/*
using namespace std;

class SolverMatrix : public Solver<Searchable<Point>*, string>{
    Searcher<Point>* searcher;

public:
    SolverMatrix(Searcher<Point>* searcher);
    string solve(Searchable<Point> *problem) override;
    string PathStr(vector<State<Point>*> States);

private:
    string getDirection(Point cur, Point next);
};

*/

using namespace std;
/**
 * this class solve a matrix problem
 */
class SolverMatrix : public Solver<Searchable<Point>*, string>{
    ISearcher<Point>* searcher;

public:
    SolverMatrix(ISearcher<Point>* searcher);
    string solve(Searchable<Point> *problem) override;
    string getPath(vector<State<Point>*> States);

private:
    string getDirection(Point cur, Point next);
};

#endif //ADVANCEDPROG2_SOLVERMATRIX_H
