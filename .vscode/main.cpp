#include "shared.h"
#include <cstdlib>
#include <limits>

using namespace std;

// ==================== NHAP LIEU ====================

static string readLine(const string& prompt) {
    cout << prompt;

    string s;
    if (!getline(cin, s)) {
        cout << "\nTam biet!\n";
        exit(0);
    }

    return trim(s);
}

static int readInt(const string& prompt) {
    string s = readLine(prompt);

    if (s.empty() || s.size() > 15)
        return -1;

    char* endPtr = nullptr;
    long value = strtol(s.c_str(), &endPtr, 10);

    if (*endPtr != '\0')
        return -1;

    return (int)value;
}

static bool readPrice(const string& prompt, double& out) {
    string s = readLine(prompt);

    if (s.empty())
        return false;

    char* endPtr = nullptr;
    out = strtod(s.c_str(), &endPtr);

    return (*endPtr == '\0');
}

// ==================== DU LIEU MAU ====================

void loadSampleData(Category* root) {
    if (root == nullptr) return;

    Category* dienTu = addCategory(root, "DT", "Dien tu");
    Category* giaDung = addCategory(root, "GD", "Gia dung");
    Category* thoiTrang = addCategory(root, "TT", "Thoi trang");

    Category* laptop = addCategory(dienTu, "LAP", "Laptop");
    Category* phone = addCategory(dienTu, "PHONE", "Dien thoai");

    Category* gaming = addCategory(laptop, "GAME", "Gaming");
    Category* ultrabook = addCategory(laptop, "ULTRA", "Ultrabook");

    Category* deep1 = addCategory(gaming, "D1", "Tang1");
    Category* deep2 = addCategory(deep1, "D2", "Tang2");
    Category* deep3 = addCategory(deep2, "D3", "Tang3");

    addProduct(phone, "P01", "iPhone 15", 22000000);
    addProduct(phone, "P02", "Samsung S24", 19000000);

    addProduct(laptop, "P03", "Dell Inspiron", 18000000);
    addProduct(laptop, "P04", "HP Pavilion", 17500000);

    addProduct(gaming, "P05", "Asus ROG", 35000000);
    addProduct(gaming, "P06", "Acer Nitro", 25000000);

    addProduct(ultrabook, "P07", "MacBook Air", 27000000);

    addProduct(giaDung, "P08", "May hut bui", 3500000);

    // thoiTrang de rong de test xoa danh muc
    (void)thoiTrang;
    (void)deep3;
}

// ==================== MENU ====================

void showMenu() {
    cout << "\n========== QUAN LY SAN PHAM THEO DANH MUC ==========\n"
         << " 1. Tao danh muc moi\n"
         << " 2. Sua ten danh muc\n"
         << " 3. Xoa danh muc\n"
         << " 4. Xem cay danh muc\n"
         << " 5. Xem danh muc con\n"
         << " 6. Tim duong dan toi mot danh muc\n"
         << " 7. Them san pham\n"
         << " 8. Xoa san pham\n"
         << " 9. Xem san pham trong danh muc\n"
         << "10. Xem tat ca san pham (gom con chau)\n"
         << " 0. Thoat\n";
}

// ==================== MAIN ====================

int main() {
    Category* root = createRoot("ROOT", "Ten cua hang");

    loadSampleData(root);

    while (true) {
        showMenu();

        int choice = readInt("\nNhap lua chon: ");

        switch (choice) {
        case 0:
            freeTree(root);
            cout << "Tam biet!\n";
            return 0;

        case 1: {
            string parentId = readLine("ID danh muc cha: ");

            Category* parent = findCategoryById(root, parentId);

            if (!parent) {
                cout << "Khong tim thay danh muc cha.\n";
                break;
            }

            string id = readLine("ID moi: ");
            string name = readLine("Ten danh muc: ");

            if (addCategory(parent, id, name))
                cout << "Them thanh cong.\n";
            else
                cout << "Them that bai.\n";

            break;
        }

        case 2: {
            string id = readLine("ID danh muc: ");
            string newName = readLine("Ten moi: ");

            if (editCategoryName(root, id, newName))
                cout << "Cap nhat thanh cong.\n";
            else
                cout << "Cap nhat that bai.\n";

            break;
        }

        case 3: {
            string id = readLine("ID danh muc can xoa: ");

            if (deleteCategory(root, id))
                cout << "Xoa thanh cong.\n";
            else
                cout << "Khong the xoa.\n";

            break;
        }

        case 4:
            printTree(root);
            break;

        case 5: {
            string id = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, id);

            if (!cat)
                cout << "Khong tim thay.\n";
            else
                printSubCategories(cat);

            break;
        }

        case 6: {
            string id = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, id);

            if (!cat)
                cout << "Khong tim thay.\n";
            else
                printPath(cat);

            break;
        }

        case 7: {
            string catId = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, catId);

            if (!cat) {
                cout << "Khong tim thay danh muc.\n";
                break;
            }

            string pid = readLine("ID san pham: ");
            string pname = readLine("Ten san pham: ");

            double price;

            if (!readPrice("Gia: ", price)) {
                cout << "Gia khong hop le.\n";
                break;
            }

            if (addProduct(cat, pid, pname, price))
                cout << "Them thanh cong.\n";
            else
                cout << "Them that bai.\n";

            break;
        }

        case 8: {
            string catId = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, catId);

            if (!cat) {
                cout << "Khong tim thay danh muc.\n";
                break;
            }

            string pid = readLine("ID san pham: ");

            if (deleteProduct(cat, pid))
                cout << "Xoa thanh cong.\n";
            else
                cout << "Khong tim thay san pham.\n";

            break;
        }

        case 9: {
            string id = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, id);

            if (!cat)
                cout << "Khong tim thay.\n";
            else
                printProducts(cat);

            break;
        }

        case 10: {
            string id = readLine("ID danh muc: ");

            Category* cat = findCategoryById(root, id);

            if (!cat)
                cout << "Khong tim thay.\n";
            else
                printAllProducts(cat);

            break;
        }

        default:
            cout << "Lua chon khong hop le.\n";
        }
    }

    return 0;
}
