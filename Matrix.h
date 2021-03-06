//
// Created by harelfeldman on 1/14/20.
//

#ifndef ADVANCEDPROG2_MATRIX_H
#define ADVANCEDPROG2_MATRIX_H

#include <vector>
#include "Searchable.h"
#include "Point.h"
/*
class Matrix : public Searchable<Point> {
private:
    State<Point> *initState;
    State<Point> *goalState;
    vector<vector<State<Point> *>> matrix;
public:
    Matrix(vector<vector<State<Point> *>> matrix,Point init, Point goal) {
        this->matrix = matrix;
        this->initState = matrix[init.getI()][init.getJ()];
        this->goalState = matrix[goal.getI()][goal.getJ()];

    };

    State<Point> *getInitialState() {
        return this->initState;
    };

    State<Point> *getGoalState() {
        return this->goalState;
    };

    list<State<Point> *> getAllPossibleStates(State<Point> &state) {
        int x = state.get_state().getI();
        int y = state.get_state().getJ();
        list<State<Point> *> possibleStates;
        // iterating 8 neighbors of the current state
        // for (int i = x - 1; i <= x + 1; i++) {
        //    for (int j = y - 1; j <= y + 1; y++) {
        //      if ((i != x || j != y) && (isValid(i, j)))
        //        possibleStates.push_back(this->matrix[i][j]);
        //   }
        //}
        //for 4 neighbors
        if(isValid(x-1,y-1))
            possibleStates.push_back(this->matrix[x-1][y-1]);
        if(isValid(x,y-1))
            possibleStates.push_back(this->matrix[x][y-1]);
        if(isValid(x-1,y))
            possibleStates.push_back(this->matrix[x-1][y]);
        if(isValid(x,y))
            possibleStates.push_back(this->matrix[x][y]);
        return possibleStates;
    };
    //checks if a neighbor is in the matrix and the state is not with infinite cost.
    bool isValid(int i, int j) {
        if ((i >= 0 && i < this->matrix.size()) && (j >= 0 && j < this->matrix[0].size())) {
            if (this->matrix[i][j]->getCost() != -1) {
                return true;
            }
        }
        return false;
    };

};
*/
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <string>


#define INF -1
#define FIRST_ROW 0

/*
 * This class represent a matrix,its heir from searchable.
 * for each matrix have a init and goal points,and number of row and col
 * each cell is State of Point
 */
using namespace std;
class Matrix: public Searchable<Point> {
    State<Point> *initState;
    State<Point> *goalState;
    vector<vector<State<Point> *>> matrix;
    unsigned long rows;
    unsigned long cols;

public:

    /*
     * the constructor of Matrix
     */
    Matrix(vector<vector<State<Point> *>> matrix, Point init, Point goal) {
        this->matrix = matrix;
        this->initState = getStateAtPoint(init);
        this->goalState = getStateAtPoint(goal);
        this->rows = matrix.size();
        this->cols = matrix[FIRST_ROW].size();
    }

    //copy constructor
    Matrix(const Matrix &matrix1) {
        this->matrix = matrix1.matrix;
        this->initState = getStateAtPoint(matrix1.initState->getCurState());
        this->goalState = getStateAtPoint(matrix1.goalState->getCurState());
        this->rows = matrix1.rows;
        this->cols = matrix1.cols;
    }

    /**
     * this function calculates the manhattan distance from a state to goal state.
     * @param a a state
     * @return the manhattan distance
     */
    double heuristic(State<Point> *a) override {
        double prm1 = pow(a->getCurState().getI() - this->goalState->getCurState().getI(), 2);
        double prm2 = pow(a->getCurState().getJ() - this->goalState->getCurState().getJ(), 2);
        return sqrt(prm1 + prm2);
    }

    /*
     * this method return the init state
     */
    State<Point> *getInitState() const override {
        return this->initState;
    }

    /*
     * this method return the goal state
     */
    State<Point> *getGoalState() const override {
        return this->goalState;
    }

    /*
     * this method return the cost of the point
     */
    double getCostOfPoint(Point p) {
        return matrix[p.getI()][p.getJ()]->getCost();
    }

    /*
     * this method get a point and return the state of the point
     */
    State<Point> *getStateAtPoint(Point p) {
        return matrix[p.getI()][p.getJ()];
    }

    /*
     * this method get a state of point and check for the adjacent of the point
     * if the cost of some adjacent is -1 we cant pass through this point
     * we also check if the adjacent are in the matrix range
     */
    vector<State<Point> *> getPossibleStates(State<Point> *state) override {
        int IPoint = state->getCurState().getI();
        int JPoint = state->getCurState().getJ();
        vector<State<Point> *> possibleStates;

        //if the point is in the range
        if (!(IPoint >= 0 && IPoint < rows && JPoint >= 0 && JPoint < cols)) {
            perror("Point is out of range");
            exit(1);
        }
        //if the point,at i index, is not in the first line we have upState
        if (IPoint != 0) {
            State<Point> *upState = getStateAtPoint(Point(IPoint - 1, JPoint));
            //if the cost is not -1
            if (upState->getCost() != INF) {
                possibleStates.push_back(upState);
            }
        }
        //if the point,at index j,is not the most left we have leftState
        if (JPoint != 0) {
            State<Point> *leftState = getStateAtPoint(Point(IPoint, JPoint - 1));
            if (leftState->getCost() != INF) {
                possibleStates.push_back(leftState);
            }
        }
        //if the point,at index j,is not the last column we have rightState
        if (JPoint != cols - 1) {
            State<Point> *rightState = getStateAtPoint(Point(IPoint, JPoint + 1));
            if (rightState->getCost() != INF) {
                possibleStates.push_back(rightState);
            }
        }
        //if the point,at i index, is not in the lowest line we have downState
        if (IPoint != this->rows - 1) {
            State<Point> *downState = getStateAtPoint(Point(IPoint + 1, JPoint));
            if (downState->getCost() != INF) {
                possibleStates.push_back(downState);
            }
        }
        return possibleStates;
    }


    /**
     * this function returns the columns of the matrix
     */
    unsigned long getCols() const {
        return cols;
    }
    /**
     * this function returns the matrix.
     */
    const vector<vector<State<Point> *>> &getMatrix() const {
        return matrix;
    }

    /**
     * this function returns the rows of the matrix
     */
    unsigned long getRows() const {
        return rows;
    }

    /*
     * this method convert a matrix to string .first we write the i,j of the init point,than we have separated |
     * and after that we write the i,j of the goal point.after the init and the goal state we put :
     * than we write all the values that are separated with comma.each line in the matrix are separated with |
     * after we finish to write the matrix we put $ in order to separate the problem=matrix ,from the solution.
     * after the $ we write the string that represent the path of the solution
     */
    operator string() const override {
        string str;
        str += to_string(initState->getCurState().getI()) + ',' + to_string(initState->getCurState().getJ());
        str += '|';
        str += to_string(goalState->getCurState().getI()) + ',' + to_string(goalState->getCurState().getJ());
        str += ':';

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                str += to_string(matrix[i][j]->getCost());
                if (j != cols - 1) {
                    str += ',';
                }
            }
            if (i != rows - 1) {
                str += '|';
            }
        }
        return str;
    }

};
#endif //ADVANCEDPROG2_MATRIX_H
