/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:49:40 by rzafari           #+#    #+#             */
/*   Updated: 2021/11/14 19:11:33 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <iostream>

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "timer.hpp"

#include <string>
#include <algorithm>
#include <stdlib.h>
#include <limits>

#define BUFFER_SIZE 4096
#define MAXRAM (std::numeric_limits<int>::max())
#define MAXSIZE ((std::size_t)(std::numeric_limits<int>::max()) / sizeof(int))

#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"

// ------------------ TIMER ------------------
#define PRINT_TIME(t)                                                                              \
    {                                                                                              \
        std::cout << GREEN << t.get_time() << "ms" <<  RESET << std::endl;                                            \
    }                                                                               \

#define PRINT_SUM()                                                                                \
    {                                                                                              \
        std::cout << GREEN << sum << "ms" << RESET << std::endl;                                                     \
    }

#define SETUP                                                                                      \
    srand(64);                                                                                     \
    volatile int x = 0;                                                                            \
    (void)x;                                                                                       \
    long sum = 0;                                                                                  \
    (void)sum;

#define _RESET(t)                                                                                      \
	t.reset();                                                                                     \
    x = 0;                                                                            \
    sum = 0;                                                                                  \

timer::timer()
{
    reset();
}

long timer::get_time()
{
    struct timeval now;
    struct timeval diff;

    gettimeofday(&now, NULL);
    timersub(&now, &stamp, &diff);

    return diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void timer::reset()
{
    gettimeofday(&stamp, NULL);
}

// ------------------ END TIMER ------------------

template <typename T>
void printContainer(T &cont) {
	typename T::iterator it;
	it = cont.begin();
	while (it != cont.end())
	{
		std::cout << *it ;
		it++;
	}
}

#include <sstream>


class Test {
	public :
		Test(int i, char v) : _i(i), _v(v) {
		};
		int _i;
		char _v;
	};


int main(int argc, char **argv) {


	ft::vector<Test*> v;


	Test *a = new Test(1, 'a');
	Test *b = new Test(2, 'b');
	Test *c = new Test(3, 'c');
	Test *d = new Test(4, 'd');


    v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);

	const Test* ptr = v[0];
	//Test **ptr_to_ptr = &v[0];

	std::cout << ptr->_i << std::endl;
	std::cout << ptr << std::endl;
	std::cout << &v[0] << std::endl;

	v.reserve(50000000);
	//v.reserve(500000);

	std::cout << ptr->_i << std::endl;
	std::cout << ptr << std::endl;
	std::cout << &v[0] << std::endl;

    //v.assign(v.begin(), v.begin() + 12);

	return 1;

	NS::vector<std::string> vector_str;
	NS::vector<int> vect;
	NS::stack<int> stack_int;

	int seed;

	if (argc == 2)
		seed = atoi(argv[1]);
	else
		seed = 19;

	std::srand(seed);


	// ------------------- VECTOR -------------------

	std::cout << "--------------------" << std::endl;

	std::cout  << "VECTOR"  << std::endl;

	std::cout << "--------------------" << std::endl;

	// ------------------ push_back ------------------

	std::cout << YELLOW << "push_back" << RESET << std::endl;
	timer t;

	SETUP;

	_RESET(t);

    for (std::size_t i = 0; i < MAXSIZE / 100; ++i) {
        vect.push_back(rand());
    }

	PRINT_TIME(t);

	// ------------------ insert ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "insert" <<  RESET << std::endl;


	t.reset();

	for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
            v.insert(v.begin(), rand());
        }
    }
	PRINT_TIME(t);

	t.reset();

    for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < 5000; ++i) {
            v.insert(v.end(), rand());
        }
        for (std::size_t i = 0; i < 200000; ++i) {
			std::size_t index = rand() % (v.size() + 1); // generate random index
			v.insert(v.begin() + index, rand());
		}
    }

	PRINT_TIME(t);

    // ------------------ erase ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW <<  "erase" <<  RESET << std::endl;

	_RESET(t);

	for (int i = 0; i < 1; ++i) {
		NS::vector<int> v;
		for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
			v.push_back(rand());
		}
		t.reset();
		for (std::size_t i = 0; i < 5000; ++i) {
			v.erase(v.begin() + (rand() % v.size()));
		}
		sum += t.get_time();
	}

	PRINT_SUM();

// ------------------ assign ------------------
	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "assign" << RESET << std::endl;
	t.reset();
	for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
		NS::vector<int> v;
		v.assign(1000, rand());
	}
	PRINT_TIME(t);

// ------------------ resize ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "resize" << RESET << std::endl;
	t.reset();
	for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
		NS::vector<int> v(1000);
		v.resize(2000);
		v.resize(0);
	}
	PRINT_TIME(t);

	// ------------------- MAP -------------------

	std::cout << "--------------------" << std::endl;

	std::cout  << "MAP" << std::endl;

	std::cout << "--------------------" << std::endl;

	// ------------------ insert ------------------

	std::cout << YELLOW << "insert" <<  RESET << std::endl;

	t.reset();

	for (int i = 0; i < 2; ++i) {
		NS::map<int, int> map;

		for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
	}

	for (int i = 0; i < 2; ++i) {
		NS::map<int, int> map;

		for (std::size_t i = 0; i < 20000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
	}

	for (int i = 0; i < 2; ++i) {
		NS::map<int, int> map;

		for (std::size_t i = 0; i < 5000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
		for (std::size_t i = 0; i < 20000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
	}

	PRINT_TIME(t);

	// ------------------ erase ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW <<  "erase" <<  RESET << std::endl;

	_RESET(t);

	for (int i = 0; i < 1; ++i) {
		NS::map<int, int> map;
		for (std::size_t i = 0; i < MAXSIZE / 500; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
		t.reset();
		while (!map.empty()) {
			map.erase(map.begin());
		}
		sum += t.get_time();
    }

    PRINT_SUM();


	// ------------------ clear ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "clear" << RESET << std::endl;

	_RESET(t);

	for (std::size_t i = 0; i < 3; ++i) {
		NS::map<int, int> map;
		for (std::size_t i = 0; i < MAXSIZE / 500; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
		t.reset();
		map.clear();
		sum += t.get_time();
	}

	PRINT_SUM();

	// ------------------ find ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "find" << RESET << std::endl;

	_RESET(t);

	for (int i = 0; i < 3; ++i) {
		NS::map<int, int> map;
		for (std::size_t i = 0; i < MAXSIZE / 10000000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
		t.reset();
		for (std::size_t i = 0; i < 10000000; ++i) {
			map.find(rand() % map.size());
		}
		sum += t.get_time();
	}

	PRINT_SUM();

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "equal_range" << RESET << std::endl;


	for (int i = 0; i < 1; ++i) {
		NS::map<int, int> map;
		for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
			map.insert(NS::make_pair(rand(), rand()));
		}
		t.reset();
		for (std::size_t i = 0; i < 1000; ++i) {
			map.equal_range(rand() % map.size());
		}
	}

	PRINT_TIME(t);
	return 0;
}
