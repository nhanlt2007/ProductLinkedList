#include "shared.h"

// Tạo danh mục gốc, không có cha. Độ phức tạp O(1).
Category* createRoot(const string& idIn, const string& nameIn) {
    string id = trim(idIn), name = trim(nameIn);
    if (!isValidId(id)) {
        cout << "Loi: ID khong hop le (1-20 ky tu, chi gom chu, so, _ hoac -).\n";
        return nullptr;
    }
    if (!isValidName(name)) {
        cout << "Loi: Ten danh muc khong duoc rong va toi da 60 ky tu.\n";
        return nullptr;
    }
    return new Category(id, name, nullptr);
}

// Thêm danh mục con vào cuối danh sách con của parent.
// Độ phức tạp O(N + k): N để kiểm tra trùng ID cả cây, k để đi tới con cuối.
Category* addCategory(Category* parent, const string& idIn, const string& nameIn) {
    if (parent == nullptr) {
        cout << "Loi: Danh muc cha khong ton tai.\n";
        return nullptr;
    }
    string id = trim(idIn), name = trim(nameIn);
    if (!isValidId(id)) {
        cout << "Loi: ID khong hop le (1-20 ky tu, chi gom chu, so, _ hoac -).\n";
        return nullptr;
    }
    if (!isValidName(name)) {
        cout << "Loi: Ten danh muc khong duoc rong va toi da 60 ky tu.\n";
        return nullptr;
    }
    // ID không được trùng với bất kỳ danh mục nào trong cây, nên tìm từ gốc
    if (findCategoryById(findRoot(parent), id) != nullptr) {
        cout << "Loi: ID danh muc '" << id << "' da ton tai.\n";
        return nullptr;
    }

    Category* c = new Category(id, name, parent);
    if (parent->childHead == nullptr) {
        parent->childHead = c;          // cha chưa có con nào
    } else {
        Category* last = parent->childHead;
        while (last->nextSibling != nullptr) last = last->nextSibling;
        last->nextSibling = c;          // nối vào sau con cuối
    }
    return c;
}

// Đổi tên danh mục, ID giữ nguyên. Độ phức tạp O(N) vì phải tìm theo ID.
bool editCategoryName(Category* root, const string& idIn, const string& newNameIn) {
    string id = trim(idIn), name = trim(newNameIn);
    Category* c = findCategoryById(root, id);
    if (c == nullptr) {
        cout << "Loi: Khong tim thay danh muc co ID '" << id << "'.\n";
        return false;
    }
    if (!isValidName(name)) {
        cout << "Loi: Ten danh muc khong duoc rong va toi da 60 ky tu.\n";
        return false;
    }
    c->name = name;
    return true;
}

// Xóa danh mục, chỉ xóa được khi không có con và không có sản phẩm.
// root là tham chiếu vì nếu xóa luôn gốc thì phải gán root = nullptr.
// Độ phức tạp O(N + k): tìm danh mục, rồi tìm node đứng trước trong danh sách con.
bool deleteCategory(Category*& root, const string& idIn) {
    string id = trim(idIn);
    Category* c = findCategoryById(root, id);
    if (c == nullptr) {
        cout << "Loi: Khong tim thay danh muc co ID '" << id << "'.\n";
        return false;
    }
    if (c->childHead != nullptr) {
        cout << "Loi: Danh muc con co danh muc con, khong the xoa.\n";
        return false;
    }
    if (c->productHead != nullptr) {
        cout << "Loi: Danh muc con co san pham, khong the xoa.\n";
        return false;
    }

    // trường hợp xóa gốc
    if (c->parent == nullptr) {
        delete c;
        root = nullptr;
        return true;
    }

    // gỡ c ra khỏi danh sách con của cha
    Category* p = c->parent;
    if (p->childHead == c) {
        p->childHead = c->nextSibling;      // c là con đầu tiên
    } else {
        Category* prev = p->childHead;      // tìm node đứng ngay trước c
        while (prev != nullptr && prev->nextSibling != c) prev = prev->nextSibling;
        if (prev != nullptr) prev->nextSibling = c->nextSibling;
    }
    delete c;
    return true;
}

// Giải phóng cả cây: xóa các con trước, rồi sản phẩm, rồi tới chính nó.
// Phải lưu nextSibling trước khi xóa con, xóa rồi thì không đọc lại được.
// Độ phức tạp O(N + P), P là tổng số sản phẩm.
void freeTree(Category*& root) {
    if (root == nullptr) return;
    Category* c = root->childHead;
    while (c != nullptr) {
        Category* nxt = c->nextSibling;
        freeTree(c);
        c = nxt;
    }
    freeProducts(root->productHead);
    delete root;
    root = nullptr;
}
