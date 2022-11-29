#include <iostream>
#include <string>
#include <deque>


#include "BST.hpp"
#include "Vect.hpp"
#include "Cont.hpp"
#include "Vector.hpp"

#include "Iterator.hpp"



#define TESTED_NAMESPACE ft
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

/*
#define TESTED_TYPE std::string

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(8);
	std::cout << "ici" << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();


	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);
	printSize(vct, true);

	std::cout << "push_back():\n" << std::endl;

	vct.push_back("One long string");
	vct2.push_back("Another long string");

	printSize(vct);
	printSize(vct2);

	vct.pop_back();
	vct2.pop_back();

	printSize(vct);
	printSize(vct2);

	return (0);
}

*/

int main() {

		//ft::reverse_iterator<Cont<int>::iterator> iter;

		//Cont<int>::reverse_iterator itr;		// compile pas car pas dans Cont

		//ft::vector<std::string> vct(8);

		ft::vector<int> *vect = new ft::vector<int>(5);

		vect->assign(2, 42);

		vect->operator[](0) = 2;
		vect->operator[](1) = 3;

		std::cout << "main capacity " << vect->capacity() << std::endl;
		std::cout << "main size " << vect->size() << std::endl;
		std::cout << "main empty " << vect->empty() << std::endl;

		//vect->reserve(20);

		vect->push_back(8);
		vect->push_back(-9);
		vect->pop_back();

		vect->insert(vect->begin(), -1);		// sysmalloc ici !
		vect->insert(vect->begin(), -2);
		vect->insert(vect->begin(), vect->begin() , vect->begin() + 3);

		for (ft::vector<int>::reverse_iterator i = vect->rbegin(); i != vect->rend(); i++ )
			std::cout << *i << std::endl;

		vect->reserve(20);
		vect->resize(10);

		std::cout << "classic " << std::endl;
		for (ft::vector<int>::iterator it = vect->begin(); it != vect->end(); it++ )
			std::cout << *it << std::endl;

		std::cout << "vec size : " << vect->size() << std::endl;

		//vect->resize(5);

		//vect->assign(5, 5);

		vect->assign(vect->begin(), vect->end());

		std::cout << "classic " << std::endl;
		for (ft::vector<int>::const_iterator it = vect->begin(); it != vect->end(); it++ )
			std::cout << *it << std::endl;

		std::cout << "vec size : " << vect->size() << std::endl;
		std::cout << "vec back : " << vect->back() << std::endl;

		//vect->clear();
		//vect->erase(vect->begin());
		vect->erase(vect->begin());
		vect->erase(vect->begin() + 1, vect->end() - 1);

		ft::vector<int> *vec = new ft::vector<int>();

		//vec->push_back(6);

		vect->swap(*vec);

		for (ft::vector<int>::const_iterator y = vect->begin(); y != vect->end(); y++ )
			std::cout << *y << std::endl;

		std::cout << "deuxieme" << std::endl;

		for (ft::vector<int>::const_iterator iter = vec->begin(); iter != vec->end(); iter++ )
			std::cout << *iter << std::endl;

		delete vec;
		delete vect;
		//vector<int>::iterator ite = vect->begin();


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


