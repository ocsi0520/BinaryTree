#include "binarytree.hpp"
#ifndef __binarytree_cpp__
#define __binarytree_cpp__
#include <cmath>
#include <algorithm>
#include <bitset>


std::ostream& operator<<(std::ostream& writeout,BinaryTree& btree)
{
	btree.print(writeout);
	return writeout;
}

std::ostream& operator<<(std::ostream& writeout,BinaryTree&& btree)
{
	btree.print(writeout);
	return writeout;
}


std::string transform(char& c) //works
{
	std::string asd="";
	for (int i = 0; i < 8; ++i)
	{
		if(c&0x80) //if the first bit is 1
		asd+='1';
		else
		asd+='0';
		c<<=1;
	}
	//std::cout << "asd: " << asd << std::endl;
	return asd;
}

BinaryTree& BinaryTree::operator<<(char c)
	{
		std::string b=transform(c);
		this->add(b);
		return *this;
	}

void BinaryTree::copy(BinaryTree::Iterator& to, BinaryTree::Iterator& from)
{
	if(!(*from).is_empty_left()) //if it has a left branch
		{
			(*to).add('0');
			copy(++to,++from);
			--to;--from;
		}
	if(!(*from).is_empty_right()) //if it has a right branch
		{
			(*to).add('1');
			copy(to++,from++);
			to--;from--;
		}
	return;
}

unsigned int BinaryTree::Iterator::get_depth() const
{
	return depth;
}

void BinaryTree::count()
{
	Iterator save=itsIterator; //insertion point save
	itsIterator=root;
	average=0;max_depth=0,dispersion=0;
	std::vector<unsigned int> depth_vector;
	count(depth_vector);
	itsIterator=save; ////insertion point backup
	average/=depth_vector.size();
	for (std::vector<unsigned int>::iterator i = depth_vector.begin(); i != depth_vector.end(); ++i)
	{
	dispersion+=(*i-average)*(*i-average); //https://hu.wikipedia.org/wiki/Tapasztalati_sz%C3%B3r%C3%A1s	
	}
	if(depth_vector.size()>1)
	dispersion/=(depth_vector.size()-1);
	dispersion=sqrt(dispersion);
}

void BinaryTree::count(std::vector<unsigned int>& depth_vector)
{
	if( !(*itsIterator).is_empty_left() && !(*itsIterator).is_empty_right()) //we can go both way
	{
		itsIterator++;
		count(depth_vector);
		itsIterator--;
		++itsIterator;
		count(depth_vector);
		--itsIterator;
		return;
	}
	if(!(*itsIterator).is_empty_left()) //we can go just left
	{
		++itsIterator;
		count(depth_vector);
		--itsIterator;
		return;
	}
	if(!(*itsIterator).is_empty_right()) //just right
	{
		itsIterator++;
		count(depth_vector);
		itsIterator--;
		return;
	}
	//if we are here, it must be a leaf
	average+=itsIterator.get_depth();
	depth_vector.push_back(itsIterator.get_depth());
	if(max_depth<itsIterator.get_depth())
		max_depth=itsIterator.get_depth();
}

bool BinaryTree::Node::is_empty_left() const
{
	if(left)
		return false;
	return true;
}

bool BinaryTree::Node::is_empty_right() const
{
	if(right)
		return false;
	return true;
}

void BinaryTree::print(std::ostream& printer) const
{
	int current_depth=0;
	root->print(current_depth,printer);
	printer << std::endl << "depth: " <<  max_depth << " average: " << average << " dispersion: " << dispersion << std::endl;
}

std::ostream& BinaryTree::Node::print(int& current_depth,std::ostream& printer) const
{
	if(!is_empty_left()) //if it has a left branch
		{left->print(++current_depth,printer);--current_depth;}

	for (int i = 0; i < current_depth; ++i)
		printer << "---";
	printer << value << " (" << current_depth << ")" << std::endl;

	if(!is_empty_right()) //right branch
		{right->print(++current_depth,printer);--current_depth;}
	return printer;
}

void BinaryTree::add(std::string& input)
{
	/*std::bitset<200> bits{input};
	//std::cout << "bitek: " << bitek << std::endl << "input: " << input << std::endl << "//";
	for (int i = input.length()-1; i >= 0; --i)
	{
		//std::cout << bitek[i];
		if(!bits[i]) //if its 0
		{
			if((*itsIterator).is_empty_left())
			{
				(*itsIterator).add('0');
				itsIterator=root;
			}
			else
				++itsIterator;
		}
		else
		{
			if((*itsIterator).is_empty_right())
			{
				(*itsIterator).add('1');
				itsIterator=root;	
			}
			else
				itsIterator++;
		}
	}
	//std::cout << std::endl;*/
	for (int i = 0; i < input.length(); ++i)
	{
		if(input[i]=='0')
		{
			if((*itsIterator).is_empty_left())
			{
				(*itsIterator).add('0');
				itsIterator=root;
			}
			else
				++itsIterator;
		}
		else
		{
			if((*itsIterator).is_empty_right())
			{
				(*itsIterator).add('1');
				itsIterator=root;	
			}
			else
				itsIterator++;
		}
	}
}

void BinaryTree::Node::add(char input)
{
	if(input=='1')
		right=new Node('1',this);
	else
		left=new Node('0',this);
}
#endif