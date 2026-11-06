#include "shared.h"
#include <iomanip>

bool productIdExists(Category* root, const string& id)
{
    if (root == nullptr)
        return false;
    for (Product* p = root->productHead; p != nullptr; p = p->next)
        if (p->id == id)
            return true;
    for (Category* c = root->childHead; c != nullptr; c = c->nextSibling)
        if (productIdExists(c, id))
            return true;
    return false;
}

bool addProduct(Category* cat, const string& id, const string& name, double price)
{
    if (cat == nullptr)
    {
        cout << "Loi: Danh muc khong ton tai.\n";
        return false;
    }

    string cleanId   = trim(id);
    string cleanName = trim(name);

    if (!isValidId(cleanId))
    {
        cout << "Loi: ID san pham khong hop le (1-20 ky tu, chi gom chu, so, _ hoac -).\n";
        return false;
    }

    if (!isValidName(cleanName))
    {
        cout << "Loi: Ten san pham khong duoc rong va toi da 60 ky tu.\n";
        return false;
    }

    // isfinite loại cả NaN lẫn vô cùng
    if (!isfinite(price) || price < 0)
    {
        cout << "Loi: Gia phai la so khong am.\n";
        return false;
    }

    // Kiểm tra trùng ID trên TOÀN CÂY
    if (productIdExists(findRoot(cat), cleanId))
    {
        cout << "Loi: ID san pham '" << cleanId << "' da ton tai.\n";
        return false;
    }
    Product* newProduct = new Product(cleanId, cleanName, price);
    if (cat->productHead == nullptr)
    {
        cat->productHead = newProduct;
        return true;
    }
    Product* current = cat->productHead;
    while (current->next != nullptr)
        current = current->next;
    current->next = newProduct;
    return true;
}

bool deleteProduct(Category* cat, const string& id)
{
    if (cat == nullptr)
        return false;
    string cleanId = trim(id);
    Product* current  = cat->productHead;
    Product* previous = nullptr;
    while (current != nullptr)
    {
        if (current->id == cleanId)
        {
            if (previous == nullptr)
                cat->productHead = current->next;
            else
                previous->next = current->next;
            delete current;
            return true;
        }
        previous = current;
        current  = current->next;
    }
    return false;
}

void printProducts(Category* cat)
{
    if (cat == nullptr)
    {
        cout << "Danh muc khong ton tai.\n";
        return;
    }
    cout << "\n===== DANH SACH SAN PHAM =====\n";
    cout << "Danh muc: " << cat->name << "\n";
    if (cat->productHead == nullptr)
    {
        cout << "(Danh muc chua co san pham)\n";
        return;
    }
    ios_base::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();
    cout << fixed << setprecision(2);
    for (Product* p = cat->productHead; p != nullptr; p = p->next)
    {
        cout << "ID : " << p->id << "\n";
        cout << "Ten: " << p->name << "\n";
        cout << "Gia: " << p->price << "\n";
cout << "-----------------------------\n";
    }
    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}

void freeProducts(Product*& head)
{
    while (head != nullptr)
    {
        Product* temp = head;
        head = head->next;
        delete temp;
    }
}
