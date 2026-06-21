#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

class Todo {
private:
	string title;
	string deadline;
	string category;
	int priority;
	bool complete;

public:
	Todo(string t, string d, string c, int p) {
		title = t;
		deadline = d;
		category = c;
		priority = p;
		complete = false;
	}

	void markComplete() {
		complete = true;
	}

	void edit() {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "새 할 일 : ";
		getline(cin, title);

		cout << "기한 : ";
		getline(cin, deadline);

		cout << "카테고리 : ";
		getline(cin, category);

		cout << "우선순위 : ";
		cin >> priority;
	}

	void print() const {
		cout << (complete ? "[O] " : "[X] ")
			<< title << setw(7)
			<< deadline << setw(7)
			<< category << setw(7)
			<< "   우선순위 : " << priority << endl;
	}

	string getTitle() const {
		return title;
	}

	string getDeadline() const { 
		return deadline; 
	}

	string getCategory() const { 
		return category; 
	}

	int getPriority() const { 
		return priority; 
	}

	bool isCompleted() const { 
		return complete; 
	}
};

class TodoManager {
private:
	vector<Todo> tdm;

public:
	void addTodo() {
		showTodo();

		string t, d, c;
		int p;

		cin.clear();
		cin.ignore(10000, '\n');

		cout << "할 일 : ";
		getline(cin, t);

		cout << "기한 : ";
		getline(cin, d);

		cout << "카테고리 : ";
		getline(cin, c);

		cout << "우선순위 (1~5) : ";
		cin >> p;

		Todo td(t, d, c, p);
		tdm.push_back(td);

		cout << "추가 완료\n";

		showTodo();
	}

	void deleteTodo() {
		showTodo();

		int n;

		cout << "삭제할 할 일 번호 : ";
		cin >> n;

		if (n > 0 && n <= tdm.size()) {
			tdm.erase(tdm.begin() + n - 1);
			cout << "삭제 완료\n";

			showTodo();
		}

		else {
			cout << "잘못된 번호입니다.\n";
		}
	}

	void editTodo() {
		showTodo();
		
		int n;

		cout << "수정할 할 일 번호 : ";
		cin >> n;

		if (n > 0 && n <= tdm.size()) {
			tdm[n - 1].edit();
			cout << "수정 완료\n";

			showTodo();
		}

		else {
			cout << "잘못된 번호입니다.\n";
		}
	}

	void completeTodo() {
		showTodo();
		
		int n;

		cout << "완료할 할 일 번호 : ";
		cin >> n;

		if (n > 0 && n <= tdm.size()) {
			tdm[n - 1].markComplete();
			cout << "처리 완료\n";

			showTodo();
		}

		else {
			cout << "잘못된 번호입니다.\n";
		}
	}

	void sortPriority() {
		sort(tdm.begin(), tdm.end(), [](const Todo& a, const Todo& b) {
			return a.getPriority() > b.getPriority();
			});

		cout << "정렬 완료\n";

		showTodo();
	}

	void saveFile() {
		ofstream fout("할일.txt");

		for (const Todo& todo : tdm) {
			fout << todo.getTitle() << "|"
				<< todo.getDeadline() << "|"
				<< todo.getCategory() << "|"
				<< todo.getPriority() << "|"
				<< todo.isCompleted() << endl;
		}

		cout << "파일 저장 완료\n";

		showTodo();
	}

	void loadFile() {
		ifstream fin("할일.txt");

		if (!fin) return;

		tdm.clear();

		string t, d, c, p, cp;

		while (getline(fin, t, '|')) {
			getline(fin, d, '|');
			getline(fin, c, '|');
			getline(fin, p, '|');
			getline(fin, cp);

			Todo newTodo(t, d, c, stoi(p));

			if (cp == "1") newTodo.markComplete();

			tdm.push_back(newTodo);
		}

		fin.close();

		showTodo();
	}

	void showTodo() const {
		if (tdm.empty()) {
			cout << "\n======== 할 일 목록 ========\n";
			cout << "등록된 할 일이 없음\n\n";
			return;
		}

		cout << "\n======== 할 일 목록 ========\n";
		for (int i = 0; i < tdm.size(); i++) {
			cout << i + 1 << ") ";
			tdm[i].print();
		}

		cout << "\n";
	}
};

int main() {
	TodoManager manager;
	manager.loadFile();

	while (true) {
		system("cls");

		int option;

		cout << "1 : 할일리스트확인\n"
			<< "2 : 할일추가하기\n"
			<< "3 : 할일삭제하기\n"
			<< "4 : 할일수정하기\n"
			<< "5 : 할일완료하기\n"
			<< "6 : 우선순위정렬하기\n"
			<< "7 : 파일저장하기\n"
			<< "이외 숫자 입력 시 종료\n\n"
			<< "옵션 입력 : ";
		cin >> option;

		cout << "\n";

		switch (option) {
		case 1:
			manager.showTodo();
			break;
		case 2:
			manager.addTodo();
			break;
		case 3:
			manager.deleteTodo();
			break;
		case 4:
			manager.editTodo();
			break;
		case 5:
			manager.completeTodo();
			break;
		case 6:
			manager.sortPriority();
			break;
		case 7:
			manager.saveFile();
			break;
		default:
			cout << "프로그램을 종료합니다.\n";
			return 0;
		}
		cout << "\n계속하려면 SpaceBar 입력";
		system("pause > nul");
	}
}
