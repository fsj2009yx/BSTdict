#include <iostream>
#include<fstream>
#include <sstream>  
#include <vector>
#include<string>
#include <utility>
using namespace std;

namespace bst {

    // �������ڵ�ṹ
    struct TreeNode {
        string key;
        string value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    // ������������
    class BST
    {
    private:
        TreeNode* root;

        // ���뺯��
        TreeNode* insert(TreeNode* node, const string& key, const string& value) {
            // �����Ϊ�գ�ֱ�ӷ����½ڵ���Ϊ���ڵ�
            if (node == nullptr) {
                return new TreeNode(key, value);
            }

            TreeNode* cur = node;
            while (cur != nullptr) {
                // �����С�ڵ�ǰ�ڵ�ļ���������������
                if (key < cur->key) {
                    // ������ӽڵ�Ϊ�գ������
                    if (cur->left == nullptr) {
                        cur->left = new TreeNode(key, value);
                        return node; // ���ظ��ڵ�
                    }
                    cur = cur->left; // ����������������ƶ�
                }
                // ��������ڵ�ǰ�ڵ�ļ���������������
                else if (key > cur->key) {
                    // ������ӽڵ�Ϊ�գ������
                    if (cur->right == nullptr) {
                        cur->right = new TreeNode(key, value);
                        return node; // ���ظ��ڵ�
                    }
                    cur = cur->right; // ����������������ƶ�
                }
                // �������ȣ����½ڵ��ֵ
                else {
                    cur->value = value;
                    return node; // ���ظ��ڵ�
                }
            }

            return node; // ���ظ��ڵ�
        }
        //���Һ���
        vector<TreeNode*> search(TreeNode* node, const string& key) {
            vector<TreeNode*> result;
            TreeNode* cur = node;

            while (cur != nullptr) {
                size_t pos = cur->key.find(key);  // �ڵ�ǰ�ڵ���� key �Ƿ���ǰ׺

                // ����ҵ�ƥ���ǰ׺�����뵽�����
                if (pos == 0) {
                    result.push_back(cur);  // ���ƥ��Ľڵ�
                }

                // ���ݶ��������������ʣ������Ƿ����������������
                if (key < cur->key) {
                    cur = cur->left;  // ������������
                }
                else {
                    cur = cur->right; // ������������
                }
            }
            return result;
        }

        // ɾ���ڵ㺯��
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
                // ��ǰ�ڵ���Ҫɾ���Ľڵ�
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

                // ��ǰ�ڵ��������ӽڵ㣬�ҵ�����������С�ڵ������ǰ�ڵ�
                TreeNode* temp = minNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
            return node;
        }

        // ��ȡ��С�ڵ�
        TreeNode* minNode(TreeNode* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        // ������������
        void inorder(TreeNode* node) {
            if (node != nullptr) {
                inorder(node->left);
                cout << "(" << node->key << ", " << node->value << ") ";
                inorder(node->right);
            }
        }
        //BST�����Ż�
        void insertBalanced(const vector<pair<string, string>>& key_value,int left,int right) {
            if (left > right) return;
            int mid = left + (right - left) / 2;
            insert(key_value[mid].first, key_value[mid].second);
            insertBalanced(key_value, left, mid - 1);
            insertBalanced(key_value, mid + 1, right);
        }

    public:
        BST() : root(nullptr) {}

        // �����ֵ��
        void insert(const string& key, const string& value) {
            root = insert(root, key, value);
        }

        // ���Ҽ�ֵ��
        vector<pair<string*, string*>> search(const string& key) {
            vector<TreeNode*> nodes = search(root, key);
            vector<pair<string*, string*>> values;
            for (TreeNode* node : nodes) {
                values.push_back(make_pair(&node->key, &node->value));
            }
            return values;
        }

        // ɾ����
        void remove(const string& key) {
            root = remove(root, key);
        }

        // �������
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
            std::getline(file, line);// ������һ��

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
