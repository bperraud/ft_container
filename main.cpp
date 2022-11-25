#include <iostream>
#include <string>
#include <deque>


#include "BST.hpp"
#include "Vect.hpp"
#include "Cont.hpp"
#include "Vector.hpp"

#include "Iterator.hpp"

int main() {
		/*
		ft::vector<int>::iterator it;
		ft::vector<int>::reverse_iterator itr;
		ft::reverse_iterator<ft::vector<int>::iterator> iter;
		*/

		//ft::reverse_iterator<Cont<int>::iterator> iter;

		//Cont<int>::reverse_iterator itr;		// compile pas car pas dans Cont

		vector<int> *vect = new vector<int>(5);

		vect->operator[](0) = 2;
		vect->operator[](1) = 3;

		std::cout << "capacity " << vect->capacity() << std::endl;
		std::cout << "size " << vect->size() << std::endl;

		vect->push_back(8);
		vect->insert(vect->begin(), -1);
		vect->insert(vect->begin(), -2);
		//vect->insert(vect->begin(), -10, -10);

		vect->insert(vect->begin(), 1, -10);
		vect->push_back(-9);

		for (vector<int>::reverse_iterator i = vect->rbegin(); i != vect->rend(); i++ )
			std::cout << *i << std::endl;

		std::cout << "size :" << vect->size() << std::endl;
		std::cout << "vec rbegin : " << *vect->rbegin() << std::endl;
		std::cout << "vec rend : " << *vect->rend() << std::endl;
		std::cout << "max size : " << vect->max_size() << std::endl;

		vect->reserve(20);
		vect->resize(10);
		vect->pop_back();

		std::cout << "classic " << std::endl;
		for (vector<int>::const_iterator it = vect->begin(); it != vect->end(); it++ )
			std::cout << *it << std::endl;

		std::cout << "vec size : " << vect->size() << std::endl;

		vect->resize(5);

		std::cout << "classic " << std::endl;
		for (vector<int>::const_iterator it = vect->begin(); it != vect->end(); it++ )
			std::cout << *it << std::endl;

		std::cout << "vec size : " << vect->size() << std::endl;
		std::cout << "vec back : " << vect->back() << std::endl;


		//vect->clear();

		//vect->erase(vect->begin());

		vect->erase(vect->begin());

		//vect->erase(vect->begin() + 1, vect->end() - 1);

		for (vector<int>::const_iterator y = vect->begin(); y != vect->end(); y++ )
			std::cout << *y << std::endl;

		delete vect;
		//vector<int>::iterator ite = vect->begin();


		/*
		Info<int> info;
		std::cout << vect->at(0) << std::endl;
		container->insert(4);
		std::cout << "container[0] : " << container->at(0) << std::endl;
		std::cout << "container[0] : " << container[0] << std::endl;

		BST<int> tree;
		tree.insert(4);
		tree.insert(0);
		tree.insert(-4);
		tree.insert(-3);
		tree.insert(2);
		tree.insert(89);
		std::vector<int> vec(90);

		std::cout << vec.max_size() << std::endl;
		std::cout << vec.capacity() << std::endl;
		std::cout << vec.size() << std::endl;

		std::cout << tree.exists(-4) << std::endl;
		std::cout << tree.exists(89) << std::endl;
		std::cout << tree << std::endl;

		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		*/

	return 0;
}
