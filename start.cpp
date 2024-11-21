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

            crow::response res;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

            res.write(crow::json::dump(getDict(avl, keyword)));
            return res;
            });

    CROW_ROUTE(app, "/bst").methods("GET"_method)
        ([&bst](const crow::request& req) {
            string keyword = req.url_params.get("keyword");

            crow::response res;
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

            res.write(crow::json::dump(getDict(bst, keyword)));
            return res;
            });

    CROW_ROUTE(app, "/binarysearch").methods("GET"_method)
        ([&array](const crow::request& req) {
        string keyword = req.url_params.get("keyword");

        crow::response res;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

        res.write(crow::json::dump(getDict(array, keyword)));
        return res;
        });

    CROW_ROUTE(app, "/map").methods("GET"_method)
        ([&mp](const crow::request& req) {
        string keyword = req.url_params.get("keyword");

        crow::response res;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

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
        res.write(crow::json::dump(data));
        return res;
        });


    app.port(18080).multithreaded().run();
}