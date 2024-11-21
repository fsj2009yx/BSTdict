#include "crow.h"
#include "BSTTree.hpp"
#include "AVLTree.hpp"
#include "binarySearch.hpp"
#include "MyMap.hpp"

template <typename T>
crow::json::wvalue getDict(T &object,const string& keyword) {
    vector<pair<string*, string*>> dict = object.search(keyword);
    crow::json::wvalue data;
    if (!keyword.length()) {
        data["error"] = "keyword Missing";
    }
    else {
        if (!dict.size()) {
            data["error"] = "not Found";
        }
        else {
            for (auto& i : dict) {
                data[*i.first] = *i.second;
            }
        }
    }
    return data;
}

int main()
{
    bst::BST bst;
    avl::AVLTree<string, string> avl;
    binarySearch array;
    MyMap mp;

    crow::SimpleApp app;

    avl.readCSV("EnWords.csv");
    bst.readCSV("EnWords.csv");
    array.readCSV("EnWords.csv");
    mp.readCSV("EnWords.csv");

    CROW_ROUTE(app, "/avl").methods("GET"_method)
        ([&avl](const crow::request& req) {
            string keyword= req.url_params.get("keyword");
            return getDict(avl, keyword);
            });

    CROW_ROUTE(app, "/bst").methods("GET"_method)
        ([&bst](const crow::request& req) {
            string keyword = req.url_params.get("keyword");
            return getDict(bst, keyword);
            });

    CROW_ROUTE(app, "/binarysearch").methods("GET"_method)
        ([&array](const crow::request& req) {
        string keyword = req.url_params.get("keyword");
        return getDict(array, keyword);
        });

    CROW_ROUTE(app, "/map").methods("GET"_method)
        ([&mp](const crow::request& req) {
        string keyword = req.url_params.get("keyword");
        vector<pair<string, string>> dict =mp.search(keyword);
        crow::json::wvalue data;
        if (!keyword.length()) {
            data["error"] = "keyword Missing";
        }
        else {
            if (!dict.size()) {
                data["error"] = "not Found";
            }
            else {
                for (auto& i : dict) {
                    data[i.first] = i.second;
                }
            }
        }
        return data;
        });


    app.port(18080).multithreaded().run();
}