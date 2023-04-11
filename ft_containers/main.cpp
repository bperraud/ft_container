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

// ------------------ TIMER ------------------
#define PRINT_TIME(t)                                                                              \
    {                                                                                              \
        std::cout << CYAN << t.get_time() << "ms" <<  RESET << std::endl;                                            \
    }

#define SETUP                                                                                      \
    srand(64);                                                                                     \
    volatile int x = 0;                                                                            \
    (void)x;                                                                                       \
    long sum = 0;                                                                                  \

#define PRINT_SUM()                                                                                \
    {                                                                                              \
        std::cout << CYAN << sum << "ms" << RESET << std::endl;                                                     \
    }

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
void rand_erase(T &container, unsigned int n) {
	unsigned int pos;
	unsigned int second_pos;
	for (std::size_t i = 0; i < n; i++)
	{
		pos = rand() % (container.size() == 0 ? 1 : container.size());
		if (rand() % 2 == 0)
			container.erase(container.begin() + pos);
		else
		{
			second_pos = rand() % (container.size() - pos <= 0 ? 1 : container.size() - pos);
			container.erase(container.begin() + pos, container.begin() + pos + second_pos);
		}
	}
}

template <typename T>
void rand_insert(T &container, unsigned int n) {
	unsigned int pos;
	unsigned int second_pos;
	for (std::size_t i = 0; i < n; i++)
	{
		pos = rand() % container.size();
        second_pos = rand() % (container.size() - pos);

		if (rand() % 2 == 0)
			container.insert(container.begin() + pos, rand());
		else
		{
			//container.insert(container.begin() + pos, container.begin() + second_pos, container.begin() + second_pos);
			container.insert(container.begin() + pos, 3);
		}
	}
}

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

#if 1
int main(int argc, char **argv) {

	NS::vector<std::string> vector_str;
	NS::vector<int> vector_int;
	NS::stack<int> stack_int;

	NS::map<int, int> map_int;

	int seed;

	if (argc == 2)
		seed = atoi(argv[1]);
	else
		seed = 19;

	std::srand(seed);

	//std::vector<int> v(1000);
	//std::generate(v.begin(), v.end(), std::rand);

	NS::vector<int> vect;
	//rand_insert(vect, 10);
	//printContainer(vect);

	// ------------------ push_back ------------------

	std::cout << YELLOW << "push_back" << RESET << std::endl;
	SETUP;
	timer t;

	t.reset();

    for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
        vect.push_back(rand());
		sum += t.get_time();
    }

	PRINT_SUM();

	// ------------------ insert ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "insert" <<  RESET << std::endl;

	t.reset();

	for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
            v.insert(v.end(), rand());
        }
    }

    for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < 20000; ++i) {
            v.insert(v.begin(), rand());
        }
    }

    for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < 5000; ++i) {
            v.insert(v.end(), rand());
        }
        for (std::size_t i = 0; i < 20000; ++i) {
            v.insert(v.begin() + 450, rand());
        }
    }

	PRINT_TIME(t);

    // ------------------ erase ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW <<  "erase" <<  RESET << std::endl;

	t.reset();

	for (int i = 0; i < 2; ++i) {
		NS::vector<int> v;


		for (std::size_t i = 0; i < MAXSIZE / 1000; ++i) {
			v.push_back(rand());
		}

		for (std::size_t i = 0; i < 5000; ++i) {
			v.erase(v.begin() + (rand() % v.size()));
		}
	}

	PRINT_TIME(t);

// ------------------ assign ------------------
	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "assign" << RESET << std::endl;

	t.reset();

	for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
	NS::vector<int> v;
	v.assign(1000, rand());
	}

	PRINT_TIME(t);

// ------------------ resize ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "resize" << RESET << std::endl;

	t.reset();

	for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
	NS::vector<int> v(1000);
	v.resize(2000);
	}

	PRINT_TIME(t);

// ------------------ clear ------------------

	std::cout << "--------------------" << std::endl;
	std::cout << YELLOW << "clear" << RESET << std::endl;

	t.reset();

	for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
		NS::vector<int> v(1000);
		v.clear();
	}

	PRINT_TIME(t);

	return (0);
}
#else

#include "common.hpp"

#define TESTED_NAMESPACE ft

#define TESTED_TYPE std::string

void	checkErase(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct,
					TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}

#endif
