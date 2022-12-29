#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <list>
#include <map>

#include "vector.hpp"
#include "stack.hpp"

#include "map.hpp"
#include "common.hpp"

#define T1 int
#define T2 std::string
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator iterator;

static int iter = 0;

template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	_pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

int		main(void)
{
	TESTED_NAMESPACE::map<T1, T2> mp, mp2;

	ft_insert(mp, T3(42, "lol"));
	ft_insert(mp, T3(42, "mdr"));

	ft_insert(mp, T3(50, "mdr"));
	ft_insert(mp, T3(35, "funny"));

	ft_insert(mp, T3(45, "bunny"));
	ft_insert(mp, T3(21, "fizz"));
	ft_insert(mp, T3(38, "buzz"));

	ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	ft_insert(mp2, mp2.end(), T3(1500, "World"));

	return (0);
}


/*
int main() {


		std::map<int, int> map;
		map.insert(std::pair<int, int>(1, 40));
		map.insert(std::pair<int, int>(3, 12));
		map.insert(std::pair<int, int>(2, 3));

		std::map<int, int>::iterator itr;

		itr = map.begin();
		itr++;
		itr++;
		std::cout << itr->second << std::endl;

		for (itr = map.begin(); itr != map.end(); ++itr) {
			std::cout << '\t' << itr->first << '\t' << itr->second << '\n';
		}

		ft::map<int, int> map1;

		BST<int, int> bst;

		map1.insert(ft::pair<int, int>(1, 40));
		map1.insert(ft::pair<int, int>(3, 12));
		map1.insert(ft::pair<int, int>(2, 3));
		map1.insert(ft::pair<int, int>(5, -9));

		ft::pair<ft::map<int,int>::iterator ,bool> ret;
		ret = map1.insert(ft::pair<int, int>(5, 7));

		if (ret.second==false) {
			std::cout << "element '5' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		//map1.find(3);

		ft::map<int, int>::reverse_iterator reverse_custom_itr;
		//reverse_custom_itr = map1.rend();

		ft::map<int, int>::iterator begin_itr;
		ft::map<int, int>::iterator end_itr;

		ft::map<int, int>::iterator find_elem;

		begin_itr = map1.begin();
		end_itr = map1.end();
		begin_itr++;
		end_itr--;

		//return 0;
		find_elem = map1.find(9);

		std::cout << find_elem->second << std::endl;
		std::cout << end_itr->second << std::endl;
		std::cout << begin_itr->second << std::endl;

		return 0;

		// insert elements in random order
		//gquiz1.insert(std::pair<int, int>(1, 40));

		//Info<int> info;
		//std::cout << vect->at(0) << std::endl;
		//container->insert(4);
		//std::cout << "container[0] : " << container->at(0) << std::endl;
		//std::cout << "container[0] : " << container[0] << std::endl;

		//BST<int> tree;
		//tree.insert(4);
		//tree.insert(0);
		//tree.insert(-4);
		//tree.insert(-3);
		//tree.insert(2);
		//tree.insert(89);
		//std::vector<int> vec(90);

		//std::cout << vec.max_size() << std::endl;
		//std::cout << vec.capacity() << std::endl;
		//std::cout << vec.size() << std::endl;

		//std::cout << tree.exists(-4) << std::endl;
		//std::cout << tree.exists(89) << std::endl;
		//std::cout << tree << std::endl;

		//std::cerr << "Usage: ./test seed" << std::endl;
		//std::cerr << "Provide a seed please" << std::endl;
		//std::cerr << "Count value:" << COUNT << std::endl;


	return 0;
}

*/
