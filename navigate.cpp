#include "shared.h"
// 1. Tim danh muc theo ID
Category* findCategoryById(Category* root, const string& id) {
    // Neu cay rong thi khong tim thay
    if (root == nullptr) {
        return nullptr;
    }
    // Kiem tra ID cua danh muc hien tai
    if (root->id == id) {
        return root;
    }
    // Bat dau tu danh muc con dau tien
    Category* child = root->childHead;
    // Duyet tat ca danh muc con
    while (child != nullptr) {
        Category* result = findCategoryById(child, id);

        // Neu tim thay thi tra ve ket qua
        if (result != nullptr) {
            return result;
        }
        // Chuyen sang danh muc anh/em tiep theo
        child = child->nextSibling;
    }
    // Khong tim thay ID
    return nullptr;
}
// 2. Tim danh muc goc
Category* findRoot(Category* cat) {
    // Kiem tra danh muc co ton tai khong
    if (cat == nullptr) {
        return nullptr;
    }
    // Di nguoc len danh muc cha cho den khi gap goc
    while (cat->parent != nullptr) {
        cat = cat->parent;
    }

    // Tra ve danh muc goc
    return cat;
}
// 3. In duong dan tu danh muc goc den danh muc hien tai
void printPath(Category* cat) {
    // Kiem tra danh muc co ton tai khong
    if (cat == nullptr) {
        cout << "Khong tim thay danh muc!\n";
        return;
    }
    // Mang luu duong dan danh muc
    Category* path[100];
    int count = 0;

    // Bat dau tu danh muc hien tai
    Category* current = cat;

    // Luu danh muc hien tai va di nguoc len cha
    while (current != nullptr && count < 100) {
        path[count] = current;
        count++;

        current = current->parent;
    }

    // In duong dan theo thu tu tu goc xuong
    cout << "Duong dan danh muc: ";

    for (int i = count - 1; i >= 0; i--) {
        cout << path[i]->name;

        if (i > 0) {
            cout << " -> ";
        }
    }

    cout << "\n";
}


// 4. In danh sach danh muc con truc tiep
void printSubCategories(Category* cat) {
    // Kiem tra danh muc co ton tai khong
    if (cat == nullptr) {
        cout << "Danh muc khong ton tai!\n";
        return;
    }

    // Kiem tra danh muc co danh muc con khong
    if (cat->childHead == nullptr) {
        cout << "Danh muc nay khong co danh muc con.\n";
        return;
    }

    cout << "\nDanh sach danh muc con cua: "
         << cat->name << "\n";

    // Bat dau tu danh muc con dau tien
    Category* child = cat->childHead;

    // Duyet va in tung danh muc con
    while (child != nullptr) {
        cout << "- ID: " << child->id
             << " | Ten: " << child->name << "\n";

        child = child->nextSibling;
    }
}


// 5. In toan bo cay danh muc
void printTree(Category* root, int depth) {
    // Neu danh muc rong thi dung
    if (root == nullptr) {
        return;
    }

    // Tao khoang trang theo cap do cua cay
    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    // In ten va ID danh muc hien tai
    cout << "|-- " << root->name
         << " (ID: " << root->id << ")\n";

    // Lay danh muc con dau tien
    Category* child = root->childHead;

    // Duyet tat ca danh muc con
    while (child != nullptr) {
        // Goi de quy de in danh muc con
        printTree(child, depth + 1);

        // Chuyen sang danh muc anh/em tiep theo
        child = child->nextSibling;
    }
}


// 6. In thong tin chi tiet danh muc
void printCategoryInfo(Category* cat) {
    // Kiem tra danh muc co ton tai khong
    if (cat == nullptr) {
        cout << "Khong tim thay danh muc!\n";
        return;
    }

    cout << "\n========== THONG TIN DANH MUC ==========\n";

    // In ma va ten danh muc
    cout << "Ma danh muc: " << cat->id << "\n";
    cout << "Ten danh muc: " << cat->name << "\n";

    // Kiem tra va in danh muc cha
    if (cat->parent != nullptr) {
        cout << "Danh muc cha: "
             << cat->parent->name
             << " (ID: " << cat->parent->id << ")\n";
    }
    else {
        cout << "Danh muc cha: Khong co (Danh muc goc)\n";
    }

    // Dem so danh muc con truc tiep
    int count = 0;

    Category* child = cat->childHead;

    while (child != nullptr) {
        count++;
        child = child->nextSibling;
    }

    cout << "So danh muc con truc tiep: "
         << count << "\n";

    // Dem so san pham trong danh muc
    int productCount = 0;

    Product* product = cat->productHead;

    while (product != nullptr) {
        productCount++;
        product = product->next;
    }
    cout << "So san pham trong danh muc: "
         << productCount << "\n";
    cout << "========================================\n";
}
