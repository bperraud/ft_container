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
		pos = rand() % (container.size() == 0 ? 1 : container.size());
		if (rand() % 2 == 0)
			container.insert(container.begin() + pos, rand());
		else
		{
			second_pos = rand() % (container.size() - pos <= 0 ? 1 : container.size() - pos);
			container.insert(container.begin() + pos, container.begin() + pos, container.begin() + pos + second_pos);
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

int main(int argc, char **argv) {

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;

	ft::map<int, int> map_int;

	int seed;

	if (argc == 2)
		seed = atoi(argv[1]);
	else
		seed = 19;

	std::srand(seed);

	//std::vector<int> v(1000);
	//std::generate(v.begin(), v.end(), std::rand);

	std::vector<int> vect;
	rand_insert(vect, 10);
	printContainer(vect);


	SETUP;
	timer t;
	t.reset();
	sum += t.get_time();
	PRINT_SUM();

    ft::vector<int> data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(rand());
    }

    for (int i = 0; i < 5; ++i) {
        ft::vector<int> v = data;

        while (!v.empty()) {
            v.pop_back();
        }
    }

	return (0);
}
