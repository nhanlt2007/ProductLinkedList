#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// ===================== MÔ HÌNH DỮ LIỆU =====================
struct Product {                 // node của DSLK đơn nằm trong 1 danh mục
    string id;
    string name;
    double price;
    Product* next;
    Product(string _id, string _name, double _price)
        : id(_id), name(_name), price(_price), next(nullptr) {}
};

struct Category {                // node của cây (first-child / next-sibling)
    string id;
    string name;
    Category* parent;            // danh mục cha (root = nullptr)
    Category* childHead;         // DSLK danh mục con (con đầu tiên)
    Category* nextSibling;       // anh/em kế tiếp trong DSLK con của cùng 1 cha
    Product*  productHead;       // DSLK sản phẩm của danh mục
    Category(string _id, string _name, Category* _parent = nullptr)
        : id(_id), name(_name), parent(_parent),
          childHead(nullptr), nextSibling(nullptr), productHead(nullptr) {}
};

// ===================== TIỆN ÍCH KIỂM TRA DỮ LIỆU (dùng chung) =====================
inline string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}
// ID hợp lệ: 1-20 ký tự, chỉ gồm chữ, số, '_' hoặc '-' (không khoảng trắng)
inline bool isValidId(const string& s) {
    if (s.empty() || s.size() > 20) return false;
    for (char c : s)
        if (!isalnum((unsigned char)c) && c != '_' && c != '-') return false;
    return true;
}
// Tên hợp lệ: không rỗng, tối đa 60 ký tự
inline bool isValidName(const string& s) { return !s.empty() && s.size() <= 60; }

// ===================== TV1: category.cpp =====================
Category* createRoot(const string& id, const string& name);                      // tạo danh mục gốc
Category* addCategory(Category* parent, const string& id, const string& name);   // nullptr nếu lỗi
bool editCategoryName(Category* root, const string& id, const string& newName);
bool deleteCategory(Category*& root, const string& id);   // chỉ xóa khi không có con và không có sản phẩm
void freeTree(Category*& root);

// ===================== TV2: navigate.cpp =====================
Category* findCategoryById(Category* root, const string& id);
Category* findRoot(Category* cat);              // đi ngược theo parent lên gốc
void printPath(Category* cat);                  // VD: Sieu Thi > Dien tu > Laptop
void printSubCategories(Category* cat);         // chỉ con trực tiếp
void printTree(Category* root, int depth = 0);  // xem cả cây thụt lề
void printCategoryInfo(Category* cat);          // xem thông tin 1 danh mục (đề: "xem danh mục")

// ===================== TV3: product.cpp =====================
bool addProduct(Category* cat, const string& id, const string& name, double price);
bool deleteProduct(Category* cat, const string& id);
void printProducts(Category* cat);              // chỉ sản phẩm trực thuộc danh mục
bool productIdExists(Category* root, const string& id);  // ID sản phẩm là duy nhất toàn cây
void freeProducts(Product*& head);

// ===================== TV4: report.cpp + main.cpp =====================
void printAllProducts(Category* cat);           // đệ quy qua toàn bộ cây con
void loadSampleData(Category* root);
void showMenu();