#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Book 클래스 정의
class Book {
public:
    string title;
    string author;

    // 생성자
    Book(string t, string a) : title(t), author(a) {}

    // 책 정보 출력
    void display() const {
        cout << "제목: " << title << ", 작가: " << author << endl;
    }
};

// BookManager 클래스 정의
class BookManager {
private:
    vector<Book> books;  // Book 객체들을 저장할 벡터

public:
    // 책 추가
    void addBook(string title, string author) {
        books.push_back(Book(title, author));
        cout << "책 \"" << title << "\"이(가) 등록되었습니다." << endl;
    }

    // 제목으로 책 검색
    Book* findBookByTitle(string title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;  // 책이 없으면 nullptr 반환
    }

    // 작가로 책 검색
    Book* findBookByAuthor(string author) {
        for (auto& book : books) {
            if (book.author == author) {
                return &book;
            }
        }
        return nullptr;  // 책이 없으면 nullptr 반환
    }

    // 모든 책 출력
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "등록된 책이 없습니다." << endl;
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
    }

    // 제목으로 책 검색 (getBookByTitle)
    Book* getBookByTitle(string title) {
        return findBookByTitle(title);  // findBookByTitle과 동일
    }

    // 작가로 책 검색 (getBookByAuthor)
    Book* getBookByAuthor(string author) {
        return findBookByAuthor(author);  // findBookByAuthor와 동일
    }
};

// BorrowManager 클래스 정의
class BorrowManager {
private:
    unordered_map<string, int> stock;  // 책 제목을 키로 하여 재고 수를 관리

public:
    // 책의 재고 초기화
    void initializeStock(Book& book, int quantity = 3) {
        stock[book.title] = quantity;
        cout << "책 \"" << book.title << "\"의 재고가 " << quantity << "권으로 초기화되었습니다." << endl;
    }

    // 책 대여
    void borrowBook(string title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << "책 \"" << title << "\"을(를) 대여하cor였습니다." << endl;
        }
        else {
            cout << "책 \"" << title << "\"은(는) 대여할 수 없습니다." << endl;
        }
    }

    // 책 반납
    void returnBook(string title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << "책 \"" << title << "\"을(를) 반납하였습니다." << endl;
        }
        else {
            cout << "책 \"" << title << "\"은(는) 존재하지 않거나 반납할 수 없습니다." << endl;
        }
    }

    // 책 재고 상태 출력
    void displayStock() const {
        if (stock.empty()) {
            cout << "재고가 없습니다." << endl;
            return;
        }
        for (const auto& entry : stock) {
            cout << "제목: " << entry.first << ", 재고: " << entry.second << "권" << endl;
        }
    }
};

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    // 책 등록
    bookManager.addBook("프로그래밍 입문", "홍길동");
    bookManager.addBook("파이썬 완벽 가이드", "김철수");
    bookManager.addBook("데이터베이스 이론", "이영희");

    // 책 추가 후 재고 초기화
    Book* book1 = bookManager.getBookByTitle("프로그래밍 입문");
    Book* book2 = bookManager.getBookByTitle("파이썬 완벽 가이드");
    Book* book3 = bookManager.getBookByTitle("데이터베이스 이론");

    if (book1) borrowManager.initializeStock(*book1);
    if (book2) borrowManager.initializeStock(*book2);
    if (book3) borrowManager.initializeStock(*book3);

    // 모든 책 출력
    cout << "\n모든 책 목록:" << endl;
    bookManager.displayAllBooks();
    cout << endl;

    // 책 대여
    cout << "책 대여:" << endl;
    borrowManager.borrowBook("프로그래밍 입문");
    borrowManager.borrowBook("파이썬 완벽 가이드");
    borrowManager.borrowBook("알고리즘 개론");  // 대여할 수 없는 책
    borrowManager.displayStock();
    cout << endl;

    // 책 반납
    cout << "책 반납:" << endl;
    borrowManager.returnBook("프로그래밍 입문");
    borrowManager.returnBook("알고리즘 개론");  // 존재하지 않는 책
    borrowManager.displayStock();
    cout << endl;

    return 0;
}