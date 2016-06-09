// Copyright (C) 2016, Faragó Tamás, ocsi0520@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthetõ illetve módosítható a
// Free Software Foundation által kiadott GNU General Public License
// dokumentumában leírtak; akár a licenc 3-as, akár (tetszõleges) késõbbi
// változata szerint.
//
// Ez a program abban a reményben kerül közreadásra, hogy hasznos lesz,
// de minden egyéb GARANCIA NÉLKÜL, az ELADHATÓSÁGRA vagy VALAMELY CÉLRA
// VALÓ ALKALMAZHATÓSÁGRA való származtatott garanciát is beleértve.
// További részleteket a GNU General Public License tartalmaz.
//
// A felhasználónak a programmal együtt meg kell kapnia a GNU General
// Public License egy példányát; ha mégsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.


#include "binarytree.cpp"

void useless(BinaryTree asd)
{
	return;
}

int main(int argc,char** argv)
{
	char c;
	bool read=true;
	std::string bits="";
	if(argc <2 || argc>3)
	{
		std::cout << "usage:\t./main input_filename [output_filename]" << std::endl;
		exit(-1);
	}
	std::ifstream inputfile(argv[1]);
	if(!inputfile.is_open())
	{
		std::cout << "couldn't open the input file" << std::endl;
		exit(-2);
	}

	std::ofstream outputfile;
	if(argc==3)
	{
		outputfile.open(argv[2]);
		if(!outputfile.is_open())
		{
			std::cout << "couldn't write the output file" << std::endl;
			exit(-3);
		}
	}

	BinaryTree my_tree;
	BinaryTree::Iterator eniteratorom(my_tree);
	//int i=0;
	while(inputfile.get(c)) //&& i<10*1024*1024)
	{
		//i++;
		if(c=='\n')
		{
			read=true;
			continue;
		}
		if(!read)
			continue;
		if(c=='>')
			{
				read=false;
				continue;
			}
		if(c=='N')
			continue;
		//bits=transform(c);
		//my_tree.add(bits);
		my_tree << c;
	}
	my_tree.count();
	//BinaryTree asdasd = std::move(my_tree);
	/*my_tree.count();
	BinaryTree asd{"000000000011111111111111111111111111111111111"};
	std::vector<BinaryTree> few_trees;
	few_trees.push_back(my_tree);
	few_trees.push_back(asd);
	few_trees.push_back(BinaryTree{"0111"});
	
	std::sort(few_trees.begin(),few_trees.end(),[&] (const BinaryTree asd1,const BinaryTree asd2)
	{
		return asd1.get_dispersion() > asd2.get_dispersion();
	}
		);
	for (std::vector<BinaryTree>::iterator i = few_trees.begin(); i != few_trees.end(); ++i)
	{
		outputfile << (*i) << std::endl;
	}*/
		outputfile.close();



		BinaryTree bla=std::move(BinaryTree{"000000000000000111111111111111"});
		bla.count();
		std::cout << bla << std::endl;
	return 0;
}