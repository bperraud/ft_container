#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <list>
#include <map>


#include "common.hpp"

#define T1 char
#define T2 foo<float>
typedef TESTED_NAMESPACE::map<T1, T2> _map;
typedef _map::const_iterator const_it;

static unsigned int i = 0;

void	ft_comp(const _map &mp, const const_it &it1, const const_it &it2)
{
	bool res[2];

	std::cout << "\t-- [" << ++i << "] --" << std::endl;
	res[0] = mp.key_comp()(it1->first, it2->first);
	res[1] = mp.value_comp()(*it1, *it2);
	std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

int		main(void)
{
	_map	mp;

	mp['a'] = 2.3;
	mp['b'] = 1.4;
	mp['c'] = 0.3;
	mp['d'] = 4.2;
	printSize(mp);

	for (const_it it1 = mp.begin(); it1 != mp.end(); ++it1)
		for (const_it it2 = mp.begin(); it2 != mp.end(); ++it2)
			ft_comp(mp, it1, it2);

	printSize(mp);
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
