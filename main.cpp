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
		reverse_iterator<Cont<int>::iterator> iter;

		//Cont<int>::reverse_iterator itr;		// compile pas car pas dans Cont

		vector<int> *vect = new vector<int>(5);

		vect->operator[](2) = 3;
		const vector<int>::const_iterator ite = vect->begin();

		(void) ite;
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

	return 1;
}
