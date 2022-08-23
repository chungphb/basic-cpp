#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>

#include "test_util.h"

// Notes:
// - A technique that considers searching every possible combination in order to solve a computational problem.
// - Typical problems:
//   + Decision problem: Search for a feasible solution.
//   + Optimization problem: Search for the best solution.
//   + Enumeration problem: Find all feasible solutions.
// - Pseudo code:
//   void solve(n, params) :
//       if (found a solution) :
//           ++numSolutions;
//           if (numSolutions >= NUM_SOLUTIONS_TARGET) :
//               return;
//       for (val = first -> last) :
//           if (isValid(val, n)) :
//               addValueToCurSolution(val, n);
//               solve(n + 1, params);
//               removeValueFromCurSolution(val, n);

BOOST_AUTO_TEST_SUITE(test_back_tracking)

// The Knight's tour problem
// Problem:
// - Given an N x N board.
// - A Knight is placed on the  first empty block of the board. 
// - Using Chess rules, the Knight must visit each block on the board exactly once.
// - Print the visited blocks in order.

BOOST_AUTO_TEST_SUITE(the_knights_tour_problem_suite)

#define BOARD_SIZE 8
#define NUM_VALID_DIRS 8

bool isValid(int r, int c, int sol[BOARD_SIZE][BOARD_SIZE]) {
	return (r >= 0 && r < BOARD_SIZE)
		&& (c >= 0 && c < BOARD_SIZE)
		&& (sol[r][c] == -1);
}

void print(int sol[BOARD_SIZE][BOARD_SIZE]) {
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			std::cout << std::setw(2) << sol[r][c] << " ";
		}
		std::cout << "\n";
	}
}

bool solve(int r, int c, int k, int sol[BOARD_SIZE][BOARD_SIZE], int rDir[NUM_VALID_DIRS], int cDir[NUM_VALID_DIRS]) {
	if (k == BOARD_SIZE * BOARD_SIZE) {
		return true;
	}

	for (int i = 0; i < NUM_VALID_DIRS; ++i) {
		int nextR = r + rDir[i];
		int nextC = c + cDir[i];
		if (isValid(nextR, nextC, sol)) {
			sol[nextR][nextC] = k;
			int isSolved = solve(nextR, nextC, k + 1, sol, rDir, cDir);
			if (isSolved) {
				return true;
			}
			sol[nextR][nextC] = -1;
		}
	}

	return false;
}

BOOST_AUTO_TEST_CASE(the_knights_tour_problem_test) {
	TEST_MARKER();

	int sol[BOARD_SIZE][BOARD_SIZE];
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			sol[r][c] = -1;
		}
	}

	int rDir[NUM_VALID_DIRS] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int cDir[NUM_VALID_DIRS] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	sol[0][0] = 0;
	bool isSolved = solve(0, 0, 1, sol, rDir, cDir);
	if (!isSolved) {
		std::cout << "Solution not exists.\n";
	} else {
		print(sol);
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()