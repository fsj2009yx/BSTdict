#include <iostream>
#include<fstream>
#include <sstream>  
#include <vector>
#include<string>
#include <utility>
using namespace std;

namespace bst {

    // 定义树节点结构
    struct TreeNode {
        string key;
        string value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    // 二叉搜索树类
    class BST
    {
    private:
        TreeNode* root;

        // 插入函数
        TreeNode* insert(TreeNode* node, const string& key, const string& value) {
            // 如果树为空，直接返回新节点作为根节点
            if (node == nullptr) {
                return new TreeNode(key, value);
            }

            TreeNode* cur = node;
            while (cur != nullptr) {
                // 如果键小于当前节点的键，向左子树插入
                if (key < cur->key) {
                    // 如果左子节点为空，则插入
                    if (cur->left == nullptr) {
                        cur->left = new TreeNode(key, value);
                        return node; // 返回根节点
                    }
                    cur = cur->left; // 否则继续向左子树移动
                }
                // 如果键大于当前节点的键，向右子树插入
                else if (key > cur->key) {
                    // 如果右子节点为空，则插入
                    if (cur->right == nullptr) {
                        cur->right = new TreeNode(key, value);
                        return node; // 返回根节点
                    }
                    cur = cur->right; // 否则继续向右子树移动
                }
                // 如果键相等，更新节点的值
                else {
                    cur->value = value;
                    return node; // 返回根节点
                }
            }

            return node; // 返回根节点
        }
        //查找函数
        vector<TreeNode*> search(TreeNode* node, const string& key) {
            vector<TreeNode*> result;
            TreeNode* cur = node;

            while (cur != nullptr) {
                size_t pos = cur->key.find(key);  // 在当前节点查找 key 是否是前缀

                // 如果找到匹配的前缀，加入到结果中
                if (pos == 0) {
                    result.push_back(cur);  // 添加匹配的节点
                }

                // 根据二叉搜索树的性质，决定是否向左或右子树查找
                if (key < cur->key) {
                    cur = cur->left;  // 向左子树查找
                }
                else {
                    cur = cur->right; // 向右子树查找
                }
            }
            return result;
        }

        // 删除节点函数
        TreeNode* remove(TreeNode* node, const string& key) {
            if (node == nullptr) {
                return nullptr;
            }
            if (key < node->key) {
                node->left = remove(node->left, key);
            }
            else if (key > node->key) {
                node->right = remove(node->right, key);
            }
            else {
                // 当前节点是要删除的节点
                if (node->left == nullptr) {
                    TreeNode* temp = node->right;
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr) {
                    TreeNode* temp = node->left;
                    delete node;
                    return temp;
                }

                // 当前节点有两个子节点，找到右子树的最小节点替代当前节点
                TreeNode* temp = minNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
            return node;
        }

        // 获取最小节点
        TreeNode* minNode(TreeNode* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        // 中序遍历输出树
        void inorder(TreeNode* node) {
            if (node != nullptr) {
                inorder(node->left);
                cout << "(" << node->key << ", " << node->value << ") ";
                inorder(node->right);
            }
        }
        //BST插入优化
        void insertBalanced(const vector<pair<string, string>>& key_value,int left,int right) {
            if (left > right) return;
            int mid = left + (right - left) / 2;
            insert(key_value[mid].first, key_value[mid].second);
            insertBalanced(key_value, left, mid - 1);
            insertBalanced(key_value, mid + 1, right);
        }

    public:
        BST() : root(nullptr) {}

        // 插入键值对
        void insert(const string& key, const string& value) {
            root = insert(root, key, value);
        }

        // 查找键值对
        vector<pair<string*, string*>> search(const string& key) {
            vector<TreeNode*> nodes = search(root, key);
            vector<pair<string*, string*>> values;
            for (TreeNode* node : nodes) {
                values.push_back(make_pair(&node->key, &node->value));
            }
            return values;
        }

        // 删除键
        void remove(const string& key) {
            root = remove(root, key);
        }

        // 中序遍历
        void inorder() {
            inorder(root);
            cout << endl;
        }

        void readCSV( const std::string& filename)
        {
            std::ifstream file(filename, std::ios::in);
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << filename << std::endl;
            }

            std::string line;
            std::getline(file, line);// 跳过第一行

            vector<pair<string,string>> data;
            std::string value1, value2;
            // Read the file line by line
            while (std::getline(file, line)) {
                std::stringstream ss(line);

                if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {

                    value1.erase(std::remove(value1.begin(), value1.end(), '"'), value1.end());
                    value2.erase(std::remove(value2.begin(), value2.end(), '"'), value2.end());
                    data.push_back(make_pair(value1, value2));
                }
            }
            insertBalanced(data,0,data.size()-1);
            file.close();
        }
    };
}
