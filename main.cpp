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
		ft::reverse_iterator<Cont<int>::iterator> iter;

		//Cont<int>::reverse_iterator itr;		// compile pas car pas dans Cont

		vector<int> *vect = new vector<int>(5);


		vect->operator[](0) = 2;
		vect->operator[](1) = 3;
		vect->operator[](4) = 5;

		vector<int>::reverse_iterator ite = vect->rbegin();
		vector<int>::reverse_iterator o = ite + 1;
		std::cout << "begin " << *o << std::endl;

		for (vector<int>::reverse_iterator i = vect->rbegin(); i != vect->rend(); i++ )
			std::cout << *i << std::endl;

		std::cout << "classic " << std::endl;
		for (vector<int>::const_iterator it = vect->begin(); it != vect->end(); it++ )
			std::cout << *it << std::endl;

		std::cout << "vec end : " << *vect->rend() << std::endl;


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
