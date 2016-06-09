#ifndef __binarytree_hpp__
#define __binarytree_hpp__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#define __help__
class BinaryTree
{
	friend std::ostream& operator<<(std::ostream&, BinaryTree&);
	friend std::ostream& operator<<(std::ostream&,BinaryTree&&);
	class Node;
public:
	double get_dispersion() const
	{
		return dispersion;
	}
	class Iterator;
	BinaryTree() : root{new Node()},max_depth{0},average{0},dispersion{0},itsIterator{*this}
	{
		#ifdef __help__
		std::cout<< "constructor" <<std::endl;
		#endif
	}
	BinaryTree(std::string input): BinaryTree()
	{
		#ifdef __help__
		std::cout << "constructor with text" << std::endl;
		#endif
		(*this).add(input);
		(*this).count();
	}
	BinaryTree(const BinaryTree& tree):itsIterator{*this}
	{
		#ifdef __help__
		std::cout << "copy constructor" << std::endl;
		#endif
		root=nullptr;
		*this=tree;
	}
	BinaryTree& operator=(const BinaryTree& tree)
	{
		#ifdef __help__
		std::cout << "copy assignment" << std::endl;
		#endif
		if (this==&tree) //if it's the same (it has absolutely no sense but we handle it)
		{
			//std::cout << "---\nit's the same -.-'\n--" << std::endl;
			return *this;
		}
		delete root;
		max_depth=tree.max_depth;
		average=tree.average;
		dispersion=tree.dispersion;
		root=new Node{};
		itsIterator=root;
		Iterator save{tree};
		copy(itsIterator,save); //we are copying it
		//we made a new iterator in order not to change the point where we insert the new Nodes
		//if we want to continue to build the tree
		itsIterator=tree.itsIterator; //it'll be the same insertion point
		return *this;
	}
	BinaryTree(BinaryTree && tree): itsIterator{*this}
	{
		#ifdef __help__
		std::cout << "moving constructor" << std::endl;
		#endif
		root=nullptr;
		*this=std::move(tree);
	}

	BinaryTree& operator=(BinaryTree && tree)
	{
		#ifdef __help__
		std::cout << "moving assignment" << std::endl;
		#endif
		max_depth=tree.max_depth;
		average=tree.average;
		itsIterator=tree.itsIterator;
		dispersion=tree.dispersion;
		Node* help=root;
		root=tree.root;
		tree.root=help;
		return *this;
	}

	BinaryTree& operator<<(char c);

	~BinaryTree()
	{
		#ifdef __help__
		std::cout << "destructor" << std::endl;
		#endif
		delete root;
	}
	void add(std::string& input);
	void print(std::ostream& printer = std::cout) const;
	void count(std::vector<unsigned int>& depth_vector);
	void count();
	class Iterator
	{
	public:
		Iterator(const BinaryTree& tree){depth=0;pointer=tree.root;}
		unsigned int get_depth() const;
		Iterator& operator++() //prefix, azaz nullás rész
		{
			pointer=pointer->left;
			depth++;
			return *this;
		}

		Iterator& operator++(int) //postfix, azaz egyes rész
		{
			pointer=pointer->right;
			depth++;
			return *this;
		}

		Iterator& operator--()
		{
			pointer=pointer->prev;
			depth--;
			return *this;
		}

		Iterator& operator--(int)
		{
			return --*this; //it'll call the prefix one
		}

		Node& operator*()
		{
			return *pointer;
		}

		Node* operator&()
		{
			return pointer;
		}

		Iterator& operator=(Node*mutato)
		{
			pointer=mutato;
			depth=0;
			return *this;
		}
	private:
		Node* pointer;
		unsigned int depth;
	};
private:
	void copy(Iterator& to, Iterator& from);
	Node* root;
	class Node
	{
		friend class Iterator;
	public:
		Node(): left{nullptr},right{nullptr},prev{nullptr}{value='\\';} //root
		Node(char input,Node* parent): Node(){value=input;prev=parent;} //the rest
		~Node(){delete left;delete right;}
		std::ostream& print(int& current_depth,std::ostream& printer) const;
		void add(char input);
		bool is_empty_left() const;
		bool is_empty_right() const;
		char value;
	private:
		Node* left;
		Node* right;
		Node* prev;
	};
	unsigned int max_depth;
	double average;
	double dispersion;
	Iterator itsIterator;
};
#endif