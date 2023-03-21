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
#include <time.h>

//#include "common.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096


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


	map_int.insert(ft::make_pair(4, 5));

	std::cout << map_int[4] << std::endl;

	std::srand(seed);

	//std::vector<int> v(1000);
	//std::generate(v.begin(), v.end(), std::rand);

	std::vector<int> vect;
	rand_insert(vect, 10);
	printContainer(vect);


	std::cout << std::endl;
	return (0);
}
