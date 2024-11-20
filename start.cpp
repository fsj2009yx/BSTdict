#include "crow.h"
#include "BSTTree.hpp"
#include "AVLTree.hpp"

int main()
{
    bst::BST bst;
    avl::AVLTree<string, string> avl;
    crow::SimpleApp app;

    avl.readCSV("EnWords.csv");
    bst.readCSV("EnWords.csv");

    CROW_ROUTE(app, "/avl").methods("GET"_method)
        ([&avl](const crow::request& req) {
            string keyword= req.url_params.get("keyword");
            vector<pair<string*, string*>> dict = avl.search(keyword);
            crow::json::wvalue data;
            if (!keyword.length()){
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
            });

    CROW_ROUTE(app, "/bst").methods("GET"_method)
        ([&bst](const crow::request& req) {
            string keyword = req.url_params.get("keyword");
            vector<pair<string*, string*>> dict = bst.search(keyword);
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
            });

    app.port(18080).multithreaded().run();
}