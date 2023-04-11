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

// ------------------ TIMER ------------------
#define PRINT_TIME(t)                                                                              \
    {                                                                                              \
        std::cout << t.get_time() << "ms" << std::endl;                                            \
    }

#define SETUP                                                                                      \
    srand(64);                                                                                     \
    volatile int x = 0;                                                                            \
    (void)x;                                                                                       \
    long sum = 0;                                                                                  \

#define PRINT_SUM()                                                                                \
    {                                                                                              \
        std::cout << sum << "ms" << std::endl;                                                     \
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

	std::cout << "push_back" << std::endl;
	SETUP;
	timer t;

	t.reset();

    for (std::size_t i = 0; i < MAXSIZE / 10000; ++i) {
        vect.push_back(rand());
		sum += t.get_time();
    }

	PRINT_SUM();

	// ------------------ insert ------------------
	std::cout << "insert" << std::endl;

	t.reset();

    //rand_insert(vect,  MAXSIZE / 50000);

	for (int i = 0; i < 2; ++i) {
        NS::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE / 100; ++i) {
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

	//------------------ erase ------------------


    for (int i = 0; i < 5; ++i) {
        NS::vector<int> v = vect;

        while (!v.empty()) {
            v.pop_back();
        }
    }

	return (0);
}
#else
#define TESTED_TYPE int
#include "common.hpp"

#define TESTED_NAMESPACE ft

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printSize(vct3);

	return (0);
}
#endif
