#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Book Ŭ���� ����
class Book {
public:
    string title;
    string author;

    // ������
    Book(string t, string a) : title(t), author(a) {}

    // å ���� ���
    void display() const {
        cout << "����: " << title << ", �۰�: " << author << endl;
    }
};

// BookManager Ŭ���� ����
class BookManager {
private:
    vector<Book> books;  // Book ��ü���� ������ ����

public:
    // å �߰�
    void addBook(string title, string author) {
        books.push_back(Book(title, author));
        cout << "å \"" << title << "\"��(��) ��ϵǾ����ϴ�." << endl;
    }

    // �������� å �˻�
    Book* findBookByTitle(string title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;  // å�� ������ nullptr ��ȯ
    }

    // �۰��� å �˻�
    Book* findBookByAuthor(string author) {
        for (auto& book : books) {
            if (book.author == author) {
                return &book;
            }
        }
        return nullptr;  // å�� ������ nullptr ��ȯ
    }

    // ��� å ���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "��ϵ� å�� �����ϴ�." << endl;
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
    }

    // �������� å �˻� (getBookByTitle)
    Book* getBookByTitle(string title) {
        return findBookByTitle(title);  // findBookByTitle�� ����
    }

    // �۰��� å �˻� (getBookByAuthor)
    Book* getBookByAuthor(string author) {
        return findBookByAuthor(author);  // findBookByAuthor�� ����
    }
};

// BorrowManager Ŭ���� ����
class BorrowManager {
private:
    unordered_map<string, int> stock;  // å ������ Ű�� �Ͽ� ��� ���� ����

public:
    // å�� ��� �ʱ�ȭ
    void initializeStock(Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        cout << "å \"" << book.title << "\"�� ��� " << quantity << "������ �ʱ�ȭ�Ǿ����ϴ�." << endl;
    }

    // å �뿩
    void borrowBook(string title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << "å \"" << title << "\"��(��) �뿩��cor�����ϴ�." << endl;
        }
        else {
            cout << "å \"" << title << "\"��(��) �뿩�� �� �����ϴ�." << endl;
        }
    }

    // å �ݳ�
    void returnBook(string title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << "å \"" << title << "\"��(��) �ݳ��Ͽ����ϴ�." << endl;
        }
        else {
            cout << "å \"" << title << "\"��(��) �������� �ʰų� �ݳ��� �� �����ϴ�." << endl;
        }
    }

    // å ��� ���� ���
    void displayStock() const {
        if (stock.empty()) {
            cout << "��� �����ϴ�." << endl;
            return;
        }
        for (const auto& entry : stock) {
            cout << "����: " << entry.first << ", ���: " << entry.second << "��" << endl;
        }
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    // å ���
    bookManager.addBook("���α׷��� �Թ�", "ȫ�浿");
    bookManager.addBook("���̽� �Ϻ� ���̵�", "��ö��");
    bookManager.addBook("�����ͺ��̽� �̷�", "�̿���");

    // å �߰� �� ��� �ʱ�ȭ
    Book* book1 = bookManager.getBookByTitle("���α׷��� �Թ�");
    Book* book2 = bookManager.getBookByTitle("���̽� �Ϻ� ���̵�");
    Book* book3 = bookManager.getBookByTitle("�����ͺ��̽� �̷�");

    if (book1) borrowManager.initializeStock(*book1);
    if (book2) borrowManager.initializeStock(*book2);
    if (book3) borrowManager.initializeStock(*book3);

    // ��� å ���
    cout << "\n��� å ���:" << endl;
    bookManager.displayAllBooks();
    cout << endl;

    // å �뿩
    cout << "å �뿩:" << endl;
    borrowManager.borrowBook("���α׷��� �Թ�");
    borrowManager.borrowBook("���̽� �Ϻ� ���̵�");
    borrowManager.borrowBook("�˰��� ����");  // �뿩�� �� ���� å
    borrowManager.displayStock();
    cout << endl;

    // å �ݳ�
    cout << "å �ݳ�:" << endl;
    borrowManager.returnBook("���α׷��� �Թ�");
    borrowManager.returnBook("�˰��� ����");  // �������� �ʴ� å
    borrowManager.displayStock();
    cout << endl;

    return 0;
}