#pragma once

#include<vector>
#include<utility>
#include<fstream>
#include <sstream>
#include <iostream>
namespace avl {
	template<class K, class V>
	struct AVLTreeNode
	{
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;

		pair<K, V> _kv;
		int _bf; //平衡因子

		AVLTreeNode(const pair<const K, V>& kv)
			:_left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _kv(kv)
			, _bf(0)
		{}
	};

	template<class K, class V>
	class AVLTree
	{
		typedef AVLTreeNode<K, V> Node;
	public:
		bool insert(const pair<const K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				parent = cur;
				if (kv.first > cur->_kv.first)
					cur = cur->_right;
				else if (kv.first < cur->_kv.first)
					cur = cur->_left;
				else
					return false;
			}

			cur = new Node(kv);
			if (kv.first > parent->_kv.first)
			{
				parent->_right = cur;
				cur->_parent = parent;
			}
			else
			{
				parent->_left = cur;
				cur->_parent = parent;
			}

			while (cur != _root)
			{
				if (cur == parent->_left)
					parent->_bf--;
				else
					parent->_bf++;

				if (parent->_bf == 0)
					break;
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)//平衡异常
				{
					if (parent->_bf == 2)
					{
						if (cur->_bf == 1)
						{
							RotateLeft(parent);
						}
						else if (cur->_bf == -1)
						{
							RotateRL(parent);
						}
					}
					else
					{
						if (cur->_bf == 1)
						{
							RotateLR(parent);
						}
						else if (cur->_bf == -1)
						{
							RotateRight(parent);
						}
					}
					break;
				}
			}

			return true;
		}

		void RotateLeft(Node* parent) //新节点插入较高右子树的右侧：左单旋
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;

			Node* parentParent = parent->_parent;

			if (parent != _root)
			{
				subR->_parent = parentParent;
				if (parent == parentParent->_left)
					parentParent->_left = subR;
				else
					parentParent->_right = subR;
			}
			else
			{
				_root = subR;
				subR->_parent = nullptr;
			}

			subR->_left = parent;
			parent->_parent = subR;

			parent->_bf = subR->_bf = 0;
		}

		void RotateRight(Node* parent) //新节点插入较高左子树的左侧：右单旋
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
				subLR->_parent = parent;

			Node* parentParent = parent->_parent;

			if (parent != _root)
			{
				subL->_parent = parentParent;
				if (parent == parentParent->_left)
					parentParent->_left = subL;
				else
					parentParent->_right = subL;
			}
			else
			{
				_root = subL;
				subL->_parent = nullptr;
			}

			subL->_right = parent;
			parent->_parent = subL;

			parent->_bf = subL->_bf = 0;
		}

		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			int bf = subRL->_bf;

			RotateRight(subR);
			RotateLeft(parent);

			if (bf == 0)
			{
				parent->_bf = subR->_bf = subRL->_bf = 0;
			}
			else if (bf == 1)
			{
				parent->_bf = -1;
				subR->_bf = subRL->_bf = 0;
			}
			else if (bf == -1)
			{
				subR->_bf = 1;
				parent->_bf = subRL->_bf = 0;
			}
			else
			{
				return;
			}
		}

		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = subLR->_bf;

			RotateLeft(subL);
			RotateRight(parent);

			if (bf == 0)
			{
				parent->_bf = subL->_bf = subLR->_bf = 0;
			}
			else if (bf == 1)
			{
				subL->_bf = -1;
				parent->_bf = subLR->_bf = 0;
			}
			else if (bf == -1)
			{
				parent->_bf = 1;
				subL->_bf = subLR->_bf = 0;
			}
			else
			{
				return;
			}
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}

		bool IsBalance()
		{
			return _IsBalance(_root);
		}

		int Height()
		{
			return _Height(_root);
		}

		size_t Size()
		{
			return _Size(_root);
		}

		// 查找键值对（接口函数）
		vector<pair<K*, K*>> search(const K& key) {
			vector<Node*> nodes = Find(key);
			vector<pair<K*, K*>> values;
			for (Node* node : nodes) {
				values.push_back(make_pair(&node->_kv.first, &node->_kv.second));
			}
			return values;
		}

		//读取CSV文件
		void readCSV(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::in);
			if (!file.is_open()) {
				std::cerr << "Error opening file: " << filename << std::endl;
			}

			std::string line;
			std::getline(file, line);// 跳过第一行

			std::string value1, value2;
			// Read the file line by line
			while (std::getline(file, line)) {
				std::stringstream ss(line);

				if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {

					value1.erase(std::remove(value1.begin(), value1.end(), '"'), value1.end());
					value2.erase(std::remove(value2.begin(), value2.end(), '"'), value2.end());
					insert(make_pair(value1, value2));
				}
			}
			file.close();
		}
	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr)
				return;
			_InOrder(root->_left);
			cout << root->_kv.first << " "<<root->_kv.second << "\n";
			_InOrder(root->_right);
		}

		vector<Node*> Find(const K& key)
		{
			Node* cur = _root;
			vector<Node*> vec;
			while (cur)
			{
				
				size_t pos = cur->_kv.first.find(key);
				if (pos == 0)
				{
					vec.push_back(cur);
				}
				if (key > cur->_kv.first)
				{
					cur = cur->_right;
				}
				else {
					cur = cur->_left;
				}
			}
			return vec;
		}

		bool _IsBalance(Node* root)
		{
			if (root == nullptr)
				return true;
			int leftHeigit = _Height(root->_left);
			int rightHeight = _Height(root->_right);
			if (rightHeight - leftHeigit != root->_bf)
			{
				cout << root->_kv.first << "平衡因子异常" << endl;
				return false;
			}

			return abs(rightHeight - leftHeigit) <= 1
				&& _IsBalance(root->_left)
				&& _IsBalance(root->_right);
		}

		int _Height(Node* root)
		{
			if (root == nullptr)
				return 0;
			int higher = max(_Height(root->_left), _Height(root->_right));
			return higher + 1;
		}

		size_t _Size(Node* root)
		{
			if (root == nullptr)
				return 0;
			return _Size(root->_left) + _Size(root->_right) + 1;
		}
	private:
		Node* _root = nullptr;
	};
}