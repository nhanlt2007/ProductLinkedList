// shared.h - khai báo chung cho cả nhóm (đề 12: quản lý sản phẩm theo danh mục)
// Không tự ý sửa file này, cần sửa thì báo cả nhóm.
#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Sản phẩm, lưu bằng danh sách liên kết đơn
struct Product {
    string id;
    string name;
    double price;
    Product* next;   // sản phẩm kế tiếp trong cùng danh mục

    Product(string _id, string _name, double _price)
        : id(_id), name(_name), price(_price), next(nullptr) {}
};

// Danh mục, lưu dạng cây nhiều nhánh.
// Mỗi node chỉ giữ con đầu tiên (childHead), các con còn lại nối nhau bằng nextSibling.
struct Category {
    string id;
    string name;
    Category* parent;       // danh mục cha, gốc thì là nullptr
    Category* childHead;    // danh mục con đầu tiên
    Category* nextSibling;  // danh mục anh/em kế tiếp
    Product* productHead;   // đầu danh sách sản phẩm của danh mục

    Category(string _id, string _name, Category* _parent = nullptr)
        : id(_id), name(_name), parent(_parent),
          childHead(nullptr), nextSibling(nullptr), productHead(nullptr) {}
};

// ----- hàm kiểm tra dữ liệu nhập, cả nhóm cùng dùng -----

// bỏ khoảng trắng ở đầu và cuối chuỗi
inline string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// ID hợp lệ: 1 đến 20 ký tự, chỉ có chữ, số, '_' hoặc '-'
inline bool isValidId(const string& s) {
    if (s.empty() || s.size() > 20) return false;
    for (char c : s)
        if (!isalnum((unsigned char)c) && c != '_' && c != '-') return false;
    return true;
}

// tên hợp lệ: không rỗng, tối đa 60 ký tự
inline bool isValidName(const string& s) { return !s.empty() && s.size() <= 60; }

// ----- TV1: category.cpp -----
Category* createRoot(const string& id, const string& name);
Category* addCategory(Category* parent, const string& id, const string& name);
bool editCategoryName(Category* root, const string& id, const string& newName);
bool deleteCategory(Category*& root, const string& id);
void freeTree(Category*& root);

// ----- TV2: navigate.cpp -----
Category* findCategoryById(Category* root, const string& id);
Category* findRoot(Category* cat);
void printPath(Category* cat);
void printSubCategories(Category* cat);
void printTree(Category* root, int depth = 0);
void printCategoryInfo(Category* cat);

// ----- TV3: product.cpp -----
bool addProduct(Category* cat, const string& id, const string& name, double price);
bool deleteProduct(Category* cat, const string& id);
void printProducts(Category* cat);
bool productIdExists(Category* root, const string& id);
void freeProducts(Product*& head);

// ----- TV4: report.cpp, main.cpp -----
void printAllProducts(Category* cat);
void loadSampleData(Category* root);
void showMenu();