#include "iostream"
#include "string"
#include "chrono"

using namespace std;

class Human {
private:
	string name;
	string surname;
	string patronymic;
	char sex;
	chrono::year_month_day birthday;
public:
	Human();
	Human(const string&, const string&, const string&, const char&, const chrono::year_month_day&);
	void SetName(const string&);
	void SetSurname(const string&);
	void SetPatronymic(const string&);
	void SetSex(const char&);
	void SetBirthday(const chrono::year_month_day);
	string GetName() { return this->name; }
	string GetSurname() { return this->surname; }
	string GetPatronimyc() { return this->patronymic; }
	char GetSex() { return this->sex; }
	chrono::year_month_day GetBirthday() { return this->birthday; }
	~Human();
};

Human::Human() {

	name = "Unknown";
	surname = "Unknown";
	patronymic = "Unknown";
	sex = 'U';
	birthday;
}

int main() {


	return 0;
}