#include "BSTTree.hpp"
#include "AVLTree.hpp"
int main()
{
	avl::AVLTree<string,string> avl;
	avl.readCSV("EnWords.csv");
	vector<pair<string*, string*>> data = avl.search("appl");
    	for (auto& i : data)
            	{
                	cout << *i.first << " " << *i.second << endl;
            	}
        	return 0;
}