#define BOOST_TEST_MODULE cpp17 test
#include <boost/test/included/unit_test.hpp>
#include <array>
#include <vector>
#include <algorithm>

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

// "The Knight's tour" problem
// Problem:
// - Given an N x N board.
// - A Knight is placed on the  first empty block of the board. 
// - Using Chess rules, the Knight must visit each block on the board exactly once.
// - Print the visited blocks in order.
// Input: 8
// Output:
//   {  0, 59, 38, 33, 30, 17,  8, 63 }
//   { 37, 34, 31, 60,  9, 62, 29, 16 }
//   { 58,  1, 36, 39, 32, 27, 18,  7 }
//   { 35, 48, 41, 26, 61, 10, 15, 28 }
//   { 42, 57,  2, 49, 40, 23,  6, 19 }
//   { 47, 50, 45, 54, 25, 20, 11, 14 }
//   { 56, 43, 52,  3, 22, 13, 24,  5 }
//   { 51, 46, 55, 44, 53,  4, 21, 12 }

BOOST_AUTO_TEST_SUITE(the_knights_tour_suite)

constexpr int BOARD_SIZE = 8;
constexpr int NUM_VALID_DIRS = 8;

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

BOOST_AUTO_TEST_CASE(the_knights_tour_test) {
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

// "Rat in a Maze" problem
// Problem:
// - Given an N x N maze.
// - A rat starts from the source (maze[0][0]) and has to reach the destination (maze[N - 1][N - 1]). 
// - The rat can only move in two directions: Forward and Down.
// Input: (1 = valid, 0 = invalid)
//   { 1, 0, 0, 0 }
//   { 1, 1, 0, 1}
//   { 0, 1, 0, 0}
//   { 1, 1, 1, 1 }
// Output:
//   { 1, 0, 0, 0 }
//   { 1, 1, 0, 0 }
//   { 0, 1, 0, 0 }
//   { 0, 1, 1, 1 }

BOOST_AUTO_TEST_SUITE(rat_in_a_maze_suite)

constexpr int MAZE_SIZE = 4;
constexpr int NUM_VALID_DIRS = 2;

void print(int out[MAZE_SIZE][MAZE_SIZE]) {
	for (int r = 0; r < MAZE_SIZE; ++r) {
		for (int c = 0; c < MAZE_SIZE; ++c) {
			std::cout << out[r][c] << " ";
		}
		std::cout << "\n";
	}
}

bool isValid(int r, int c, int in[MAZE_SIZE][MAZE_SIZE]) {
	return (r >= 0 && r < MAZE_SIZE)
		&& (c >= 0 && c < MAZE_SIZE)
		&& in[r][c] == 1;
}

bool solve(int r, int c, int in[MAZE_SIZE][MAZE_SIZE], int out[MAZE_SIZE][MAZE_SIZE], int rDir[NUM_VALID_DIRS], int cDir[NUM_VALID_DIRS]) {
	if (r == MAZE_SIZE - 1 && c == MAZE_SIZE - 1) {
		return true;
	}

	for (int i = 0; i < NUM_VALID_DIRS; ++i) {
		int nextR = r + rDir[i];
		int nextC = c + cDir[i];
		if (isValid(nextR, nextC, in)) {
			out[nextR][nextC] = 1;
			bool isSolved = solve(nextR, nextC, in, out, rDir, cDir);
			if (isSolved) {
				return true;
			}
			out[nextR][nextC] = 0;
		}
	}

	return false;
}

BOOST_AUTO_TEST_CASE(rat_in_a_maze_test) {
	TEST_MARKER();

	int in[MAZE_SIZE][MAZE_SIZE] = { 
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 1 }
	};

	int out[MAZE_SIZE][MAZE_SIZE];
	for (int r = 0; r < MAZE_SIZE; ++r) {
		for (int c = 0; c < MAZE_SIZE; ++c) {
			out[r][c] = 0;
		}
	}
	out[0][0] = 1;
	out[MAZE_SIZE - 1][MAZE_SIZE - 1] = 1;

	int rDir[NUM_VALID_DIRS] = { 1, 0 };
	int cDir[NUM_VALID_DIRS] = { 0, 1 };

	bool isSolved = solve(0, 0, in, out, rDir, cDir);
	if (!isSolved) {
		std::cout << "Solution not exists\n";
	} else {
		print(out);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "N Queen" problem
// Problem:
// - Given an N x N board.
// - Place N queens on the board so that no two queens attack each other.
// Input: 4
// Output:
//   { 0, 1, 0, 0 }
//   { 0, 0, 0, 1 }
//   { 1, 0, 0, 0 }
//   { 0, 0, 1, 0 }

BOOST_AUTO_TEST_SUITE(n_queen_suite)

constexpr int BOARD_SIZE = 4;
constexpr int NUM_VALID_POSITIONS = BOARD_SIZE;

void print(int sol[BOARD_SIZE][BOARD_SIZE]) {
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			std::cout << sol[r][c] << " ";
		}
		std::cout << "\n";
	}
}

bool isValid(int r, int c, int sol[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < r; ++i) {
		if (sol[i][c] == 1) {
			return false;
		}
	}

	for (int j = 0; j < c; ++j) {
		if (sol[r][j] == 1) {
			return false;
		}
	}

	int k = 1;
	while (r - k >= 0 && c - k >= 0) {
		if (sol[r - k][c - k] == 1) {
			return false;
		}
		++k;
	}

	k = 1;
	while (r - k >= 0 && c + k < BOARD_SIZE) {
		if (sol[r - k][c + k] == 1) {
			return false;
		}
		++k;
	}

	return true;
}

bool solve(int r, int c, int sol[BOARD_SIZE][BOARD_SIZE]) {
	if (r + 1 == BOARD_SIZE) {
		return true;
	}
	int nextR = r + 1;
	for (int nextC = 0; nextC < BOARD_SIZE; ++nextC) {
		if (isValid(nextR, nextC, sol)) {
			sol[nextR][nextC] = 1;
			bool isSolved = solve(nextR, nextC, sol);
			if (isSolved) {
				return true;
			}
			sol[nextR][nextC] = 0;
		}
	}

	return false;
}

BOOST_AUTO_TEST_CASE(n_queen_test) {
	TEST_MARKER();

	int sol[BOARD_SIZE][BOARD_SIZE];
	for (int r = 0; r < BOARD_SIZE; ++r) {
		for (int c = 0; c < BOARD_SIZE; ++c) {
			sol[r][c] = 0;
		}
	}

	bool isSolved = solve(-1, -1, sol);
	if (!isSolved) {
		std::cout << "Solution not exists\n";
	} else {
		print(sol);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// "Subset Sum" problem
// Problem:
// - Find all subsets of elements selected from a given set whose sum adds up to a given number K.
// Input: { 15, 22, 14, 26, 32, 9, 16, 8 }, K = 53
// Output: { 8, 9, 14, 22 }, { 8, 14, 15, 16 }, { 15, 16, 22 }

BOOST_AUTO_TEST_SUITE(subset_sum_suite)

constexpr int MAX_NUM_ITEMS = 8;

void print(std::vector<int> subarr) {
	for (int item : subarr) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}

bool isValid(int id, std::array<int, MAX_NUM_ITEMS> arr, int targetSum, int currentSum) {
	return id < arr.size() && arr[id] + currentSum <= targetSum;

}

void solve(int id, std::array<int, MAX_NUM_ITEMS> arr, int targetSum, std::vector<int> subarr) {
	int currentSum = std::accumulate(subarr.begin(), subarr.end(), 0);
	
	for (int nextId = id + 1; nextId < arr.size(); ++nextId) {
		if (isValid(nextId, arr, targetSum, currentSum)) {
			subarr.push_back(arr[nextId]);
			if (currentSum + arr[nextId] == targetSum) {
				print(subarr);
			}
			solve(nextId, arr, targetSum, subarr);
			subarr.pop_back();
		}
	}
}

BOOST_AUTO_TEST_CASE(subset_sum_test) {
	TEST_MARKER();

	std::array<int, MAX_NUM_ITEMS> arr = { 15, 22, 14, 26, 32, 9, 16, 8 };
	int targetSum = 53;
	std::vector<int> subarr;

	std::sort(arr.begin(), arr.end());

	solve(-1, arr, targetSum, subarr);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()