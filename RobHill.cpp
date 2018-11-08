/*
Cambia - Healthsparq Programming Test
Robert Hill 11/8/2018

Program reads in a .csv file of city names then
organizes them in descending alphabetical order.
The result is written to another .csv file.

I used a binary tree for inserting names. The left
branches have higher alphabetic ranking than right branches.

Printing the sorted name is a recursive depth first traversal
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

struct CityNode
{
	std::string name;
	struct CityNode* left;
	struct CityNode* right;
	CityNode(const std::string& data)
	{
		this->name = data;
		left = right = NULL;
	}
};

class CityTree
{
public:
	CityTree() 
	{
		root = NULL;
	}

	~CityTree()
	{
		destroyTree();
	}

	void insertNode(const std::string& name)
	{
		// insert first entry as root
		if (root == NULL)
		{
			root = new CityNode(name);
		}
		else
		{
			insert(root, name);
		}
	}

	void outputTree(std::ofstream& outFile)
	{
		printToFile(root, outFile);
	}

	void destroyTree()
	{
		if (root != NULL)
		{
			killTree(root);
			root = NULL;
		}
	}
private:
	void insert(CityNode * node, const std::string& name)
	{
		if (node->name.compare(name) < 0)
		{
			if (node->left != NULL)
			{
				// go to left node
				insert(node->left, name);
			}
			else
			{
				// insert into left node
				node->left = new CityNode(name);
			}
		}
		else if (node->name.compare(name) > 0)
		{
			if (node->right != NULL)
			{
				// go to right node
				insert(node->right, name);
			}
			else
			{
				// insert to right node
				node->right = new CityNode(name);
			}
		}
	}

	void printToFile(CityNode* node, std::ofstream& outFile)
	{
		if (node == NULL)
			return;
		printToFile(node->left, outFile);
		outFile << node->name << ",";
		printToFile(node->right, outFile);
	}

	void killTree(CityNode* node)
	{
		if (node == NULL)
			return;
		// go to left node
		killTree(node->left);
		// go to right node
		killTree(node->right);
		// delete the node
		delete node;
	}
	CityNode * root;
};

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "\nerror: missing command line args\nArg1 is input file name\nArg2 is output file name\n";
		return -1;
	}

	std::ifstream inFile;
	inFile.open(argv[1], std::ifstream::in);
	if (!inFile.is_open())
	{
		std::cout << "\nerror: cannot open file " << argv[1] << "\n";
	}

	std::ofstream outFile;
	outFile.open(argv[2], std::ifstream::out);

	CityTree* tree = new CityTree();

	std::string cityName;
	while (inFile.good())
	{
		std::getline(inFile, cityName, ',');
		tree->insertNode(cityName);
	}

	tree->outputTree(outFile);
	delete tree;
	inFile.close();
	outFile.close();
	return 0;
}
