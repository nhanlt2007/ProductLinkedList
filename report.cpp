#include "shared.h"

static int printAllProductsRecursive(Category* cat) {
    if (cat == nullptr) return 0;

    int total = 0;

    if (cat->productHead != nullptr) {
        cout << "\n===== DANH MUC: "
             << cat->name
             << " (" << cat->id << ") =====\n";

        Product* p = cat->productHead;
        while (p != nullptr) {
            cout << "ID: " << p->id
                 << " | Ten: " << p->name
                 << " | Gia: " << p->price
                 << '\n';

            ++total;
            p = p->next;
        }
    }

    Category* child = cat->childHead;
    while (child != nullptr) {
        total += printAllProductsRecursive(child);
        child = child->nextSibling;
    }

    return total;
}

void printAllProducts(Category* cat) {
    if (cat == nullptr) {
        cout << "Danh muc khong ton tai.\n";
        return;
    }

    int total = printAllProductsRecursive(cat);

    if (total == 0) {
        cout << "Khong co san pham nao trong cay danh muc nay.\n";
    } else {
        cout << "\nTong so san pham: " << total << '\n';
    }
}
