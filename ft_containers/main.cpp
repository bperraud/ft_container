#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <list>
#include <map>


#include "common.hpp"
#include <list>

#define T1 char
#define T2 int
typedef _pair<const T1, T2> T3;

template <class T>
void	is_empty(T const &mp)
{
	std::cout << "is_empty: " << mp.empty() << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, lst_size - i));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end()), mp2;
	TESTED_NAMESPACE::map<T1, T2>::iterator it;

	lst.clear();
	is_empty(mp);
	printSize(mp);

	is_empty(mp2);
	mp2 = mp;
	is_empty(mp2);

	it = mp.begin();
	for (unsigned long int i = 3; i < mp.size(); ++i)
		it++->second = i * 7;

	printSize(mp);
	printSize(mp2);

	mp2.clear();
	is_empty(mp2);
	printSize(mp2);
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
