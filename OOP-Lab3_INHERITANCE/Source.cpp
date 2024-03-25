#include "iostream"
#include "string"
#include "chrono"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

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
	Human(string&, string&, string&, char, const chrono::year_month_day&);
	Human(const Human&);
	void SetName(string& name) { name[0] = toupper(name[0]); this->name = name; }
	void SetSurname(string& surname) { surname[0] = toupper(surname[0]); this->surname = surname; }
	void SetPatronymic(string& patronymic) { patronymic[0] = toupper(patronymic[0]); this->patronymic = patronymic; }
	void SetSex(char);
	void SetBirthday(const chrono::year_month_day&);
	string GetName() { return this->name; }
	string GetSurname() { return this->surname; }
	string GetPatronimyc() { return this->patronymic; }
	char GetSex() { return this->sex; }
	void ShowInfo();
	chrono::year_month_day GetBirthday() { return this->birthday; }
	~Human() {};
};

/**
 * @brief Конструктор класу Human за замовчуванням
*/
Human::Human() {

	name = "Unknown";
	surname = "Unknown";
	patronymic = "Unknown";
	sex = 'U';
	birthday = chrono::year(1900) / chrono::month (1) / chrono::day(1);
}

/**
 * @brief Параметричний конструктор класу Human
 * @param name Ім'я людина
 * @param surname Фамілія людини
 * @param patronymic По-батькові
 * @param sex Стать людини
 * @param birthday Дата народження
*/
Human::Human(string& name, string& surname, string&  patronymic, char sex, const chrono::year_month_day& birthday) {
	
	this->SetName(name);
	this->SetSurname(surname);
	this->SetPatronymic(patronymic);
	this->SetSex(sex);
	this->SetBirthday(birthday);
}

/**
 * @brief Конструктор копіювання класу Human
 * @param h Об'єкт для копіювання
*/
Human::Human(const Human& h) {

	this->name = h.name;
	this->surname = h.surname;
	this->patronymic = h.patronymic;
	this->sex = h.sex;
	this->birthday = h.birthday;
}

/**
 * @brief Метод-сеттер встановлення статі людини
 * @param sex Стать людини
*/
void Human::SetSex(char sex) {

	sex = toupper(sex);
	if (sex == 'M' || sex == 'W') {
		this->sex = sex;
	}
	else {
		cerr << "The sex of Human is unknown!" << endl;
		this->sex = 'U';
	}
}

/**
 * @brief Метод-сеттер встановлення дати народження людини
 * @param birhtday Дата народження людини
*/
void Human::SetBirthday(const chrono::year_month_day& birhtday) {

	this->birthday = birhtday;
	chrono::time_point now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	tm local_tm;
	localtime_s(&local_tm, &now_time);
	chrono::year_month_day today = chrono::year(local_tm.tm_year + 1900) / chrono::month(local_tm.tm_mon + 1) / chrono::day(local_tm.tm_mday);

	if (today < this->birthday || static_cast<int>(this->birthday.year()) < static_cast<int>(today.year()) - 200) {
		cerr << "Error setting the date of birthday" << endl;
		this->birthday = chrono::year(1900) / chrono::month(1) / chrono::day(1);
	}
}

/**
 * @brief Метод, який надає повну інформацію про людину
*/
void Human::ShowInfo() {
	
	cout << "\n---------------Human---------------" << endl;
	cout << ANSI_COLOR_GREEN << this->GetName() << " " << this->GetSurname() << " " << this->GetPatronimyc() << ANSI_COLOR_RESET << endl;
	cout << "Sex: " << ANSI_COLOR_GREEN << this->GetSex() << ANSI_COLOR_RESET << " Birhtday in " << ANSI_COLOR_GREEN << this->GetBirthday() << ANSI_COLOR_RESET << endl;
}

struct Book {

	string title;
	string author;
	chrono::year year;
};

class LibraryUser : public Human {
private:
	unsigned int number_id;
	chrono::year_month_day date_issuance_id;
	Book** books;
	unsigned int n_books;
	unsigned int monthly_payment;
	bool isActive;
public:
	LibraryUser();
	LibraryUser(const unsigned int&, const chrono::year_month_day&, const int&, const unsigned int&, const bool&, string&, string&, string&, char, const chrono::year_month_day&);
	LibraryUser(const LibraryUser&);
	void SetNumberId(const unsigned int& number_id) { this->number_id = number_id; }
	void SetDateIssuance(const chrono::year_month_day& date_issuance);
	void SetBookIssued(Book**, const int&);
	void SetMonthlyPayment(const unsigned int& monthly_payment) { this->monthly_payment = monthly_payment; }
	void SetActiveUser(const bool& isActive) { this->isActive = isActive; }
	int GetNumberId() { return this->number_id; }
	chrono::year_month_day GetDateIssuance() { return this->date_issuance_id; }
	pair <Book**, unsigned int> GetBooksIssued();
	int GetMontlyPayment() { return this->monthly_payment; }
	bool GetActiveUser() { return this->isActive; }
	int DiscountCalculation();
	int YearPaymentCalculation();
	void AddBook(const string&, const string&, const chrono::year&);
	void ShowInfo();
	~LibraryUser();
};

/**
 * @brief Конструктор класу LibraryUser за замовчуванням, який викликає конструктор класу Human за замовченням
*/
LibraryUser::LibraryUser() : Human() {

	this->number_id = 0;
	this->date_issuance_id = chrono::year(1900) / chrono::month(1) / chrono::day(1);
	this->n_books = 0;
	this->books = nullptr;
	this->monthly_payment = 0;
	this->isActive = false;
}

/**
 * @brief Параметричний конструктор класу LibraryUser, який викликає параметричний конструктор класу Human
 * @param number_id Номер читацького квитку
 * @param date_issuance_id Дата вичі читацького квитка
 * @param n_books Кількість книг, що видавались
 * @param monthly_payment Щомісячний читацький внесок
 * @param isActive Статус користувача
 * @param name Ім'я користувача
 * @param surname Фамілія користувача
 * @param patronymic По-батькові користувача
 * @param sex Стать користувача
 * @param birthday Дата народження користувача
*/
LibraryUser::LibraryUser(const unsigned int& number_id, const chrono::year_month_day& date_issuance_id, const int& n_books, const unsigned int& monthly_payment, const bool& isActive, string& name, string& surname, string& patronymic, char sex, const chrono::year_month_day& birthday) : Human(name, surname, patronymic, sex, birthday) {

	this->SetNumberId(number_id);
	this->SetDateIssuance(date_issuance_id);
	this->n_books = n_books;
	this->SetBookIssued(this->books, n_books);
	this->SetMonthlyPayment(monthly_payment);
	this->SetActiveUser(isActive);
}

/**
 * @brief Конструктор копіювання класу LibraryUser, який викликає конструктор копіювання класу Human
 * @param u Об'єкт для копіювання
*/
LibraryUser::LibraryUser(const LibraryUser& u) : Human (u) {

	this->number_id = u.number_id;
	this->date_issuance_id = u.date_issuance_id;
	this->n_books = u.n_books;
	this->monthly_payment = u.monthly_payment;
	this->isActive = u.isActive;

	if (u.books) {
		this->books = new Book * [u.n_books];
		for (int i = 0; i < static_cast<int>(n_books); i++) {
			this->books[i] = new Book(*(u.books[i]));
		}
	}
	else this->books = nullptr;
}

/**
 * @brief Метод-сеттер встановлення дати отримання читацького квитку
 * @param date_issuance_id Дата отримання читацького квитку
*/
void LibraryUser::SetDateIssuance(const chrono::year_month_day& date_issuance_id) {

	this->date_issuance_id = date_issuance_id;
	chrono::time_point now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	tm local_tm;
	localtime_s(&local_tm, &now_time);
	chrono::year_month_day today = chrono::year(local_tm.tm_year + 1900) / chrono::month(local_tm.tm_mon + 1) / chrono::day(local_tm.tm_mday);
	
	if (today < this->date_issuance_id || static_cast<int>(this->date_issuance_id.year()) < static_cast<int>(today.year()) - 100) {
		cerr << "Error setting the date of issue of the reader's ticket" << endl;
		this->date_issuance_id = chrono::year(today.year()) / chrono::month(today.month()) / chrono::day(today.day());
	}
}

/**
 * @brief Метод-сеттер встановлення переліку книжок, що видавалися
 * @param books Покажчик на покажчик на об'єкти типу Book
 * @param n_books Кількість книжок
*/
void LibraryUser::SetBookIssued(Book** books, const int& n_books) {

	this->books = new Book* [n_books];
	for (int i = 0; i < n_books; i++) {
		string title = "Book Title ";
		title += to_string(rand() % 10000 + 1);
		string author = "Author ";
		author += to_string(rand() % 1000 + 1);
		chrono::year date = chrono::year(rand() % 123 + 1901);
		this->books[i] = new Book{ title, author, date };
	}
}

/**
 * @brief Метод-геттер отримання покажчика на покажчик на об'єкти типу Book і кількості книжок
 * @return Покажчик на покажчик на об'єкти типу Book та кількість книжок
*/
pair <Book**, unsigned int> LibraryUser::GetBooksIssued() {

	return make_pair(this->books, this->n_books);
}

/**
 * @brief Метод, що розраховує розмір знижки
 * @return Розмір знижки у відсотках
*/
int LibraryUser::DiscountCalculation() {

	if (this->n_books > 10) return 10;
	else if (this->n_books > 25) return 20;
	else if (this->n_books > 50) return 30;
	else if (this->n_books > 100) return 50;
	else return 0;
}

/**
 * @brief Метод, що розраховує щорічний читацький внесок з використанням знижки
 * @return Щорічний читацький внесок
*/
int LibraryUser::YearPaymentCalculation() {

	return (this->monthly_payment * 12) - (this->monthly_payment * 12 * this->DiscountCalculation() / 100);
}

/**
 * @brief Метод, що додає інформацію про книжки, що видавались
 * @param title Назва книги
 * @param author Автор книги
 * @param year Рік видання
*/
void LibraryUser::AddBook(const string& title, const string& author, const chrono::year& year) {

	this->n_books++;
	Book** new_books = new Book * [this->n_books];
	for (int i = 0; i < static_cast<int>(this->n_books) - 1; i++) {
		new_books[i] = new Book{ this->books[i]->title, this->books[i]->author, this->books[i]->year };
	}
	new_books[this->n_books - 1] = new Book{ title, author, year };
	if (this->books) {
		for (int i = 0; i < static_cast<int>(this->n_books) - 1; i++) {
			delete this->books[i];
		}
		delete[] this->books;
	}	
	this->books = new_books;
}

/**
 * @brief Метод, який надає повну інформацію про користувача бібліотеки 
*/
void LibraryUser::ShowInfo() {

	this->Human::ShowInfo();
	cout << "Have reader`s ticket number: #" << ANSI_COLOR_GREEN << this->GetNumberId() << ANSI_COLOR_RESET << " received in " << ANSI_COLOR_GREEN << this->GetDateIssuance() << ANSI_COLOR_RESET << " status is ";
	if (this->GetActiveUser()) cout << ANSI_COLOR_GREEN << "Active" << ANSI_COLOR_RESET << endl;
	else cout << ANSI_COLOR_RED << "Inactive" << ANSI_COLOR_RESET << endl;
	cout << "Payment monthly: " << ANSI_COLOR_GREEN << this->GetMontlyPayment() << ANSI_COLOR_RESET << " Payment per year: " << ANSI_COLOR_GREEN << this->YearPaymentCalculation() << ANSI_COLOR_RESET << " (sale: " << ANSI_COLOR_GREEN << this->DiscountCalculation() << "%" << ANSI_COLOR_RESET << ')' << endl;
	cout << "_________Books list_________(" << ANSI_COLOR_BLUE << this->n_books << ANSI_COLOR_RESET << ')' << endl;
	for (int i = 0; i < static_cast<int>(this->n_books); i++) {
		cout << "The " << setw(20) << left << this->books[i]->title << " by " << setw(15) << left << this->books[i]->author << " Year: " << setw(10) << left << this->books[i]->year << endl;
	}
}

/**
 * @brief Деструктор класу LibraryUser
*/
LibraryUser::~LibraryUser() {

	for (int i = 0; i < static_cast<int>(this->n_books); i++) {
		delete this->books[i];
	}
	delete[] this->books;
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки типу int
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cout << "Enter int data: ";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки типу unsigned int
*/
void CheckUnsignedData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cout << "Enter unsigned int data: ";
			cin >> x;
			cin.ignore(666, '\n');
		}
		if (x < 0) {
			cerr << "You entered a negative number! Please enter correct data:";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

/**
 * @brief Функція, яка перевіряє чи наданий рік є високосним
 * @param year Рік для перевірки 
 * @return true, якщо так, false - ні
*/
bool isLeapYear(const int& year) {

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return true;
	}
	else return false;
}

int main() {

	int work = 1;
	string tmp;
	char tmp_s;
	int tmp_i;
	int tmp_day, tmp_month, tmp_year;
	string name = "Daniel";
	string surname = "Rayni";
	string patronymic = "Olomenko";

	LibraryUser u(50, chrono::year(2020) / chrono::month(10) / chrono::day(14), 10, 250, false, name, surname, patronymic, 'm', chrono::year(1990) / chrono::month(10) / chrono::day(25));
	LibraryUser u2 = u;

	while (work != 0) {
		switch (work) {
		case 1:
			u.ShowInfo();
			break;
		case 2:
			cout << "Book adeded" << endl; u.AddBook("Harry Poter", "Rowling", chrono::year(2000));
			break;
		case 3:
			cout << "Enter new name: "; cin >> tmp; u.SetName(tmp);
			break;
		case 4:
			cout << "Enter new surname: "; cin >> tmp; u.SetSurname(tmp);
			break;
		case 5: 
			cout << "Enter new patronymic: "; cin >> tmp; u.SetPatronymic(tmp);
			break;
		case 6:
			cout << "Enter new sex: "; cin >> tmp_s; u.SetSex(tmp_s); if (cin.fail()) { cin.clear(); }
			break;
		case 7:
			cout << "Enter new year of birthday (ex. 2020): "; cin >> tmp_year; CheckUnsignedData(tmp_year); while (tmp_year < 1900 || tmp_year > 3000) { cerr << "Error entering the year of birthday! Retry: "; cin >> tmp_year; CheckUnsignedData(tmp_year); }
			cout << "Enter new month of birthdday (ex. 10): "; cin >> tmp_month; CheckUnsignedData(tmp_month); while (tmp_month < 1 || tmp_month > 12) { cerr << "Error entering the month of birthday! Retry: "; cin >> tmp_month; CheckUnsignedData(tmp_month); }
			cout << "Enter new day of birhday (ex. 14): "; cin >> tmp_day; CheckUnsignedData(tmp_day);
			if (tmp_month == 1 || tmp_month == 3 || tmp_month == 5 || tmp_month == 7 || tmp_month == 8 || tmp_month == 10 || tmp_month == 12){
				while (tmp_day > 31 || tmp_day < 1) {
					cerr << "Error entering the day of birthday (max 31 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 4 || tmp_month == 6 || tmp_month == 9 || tmp_month == 11) {
				while (tmp_day > 30 || tmp_day < 1) {
					cerr << "Error entering the day of birthday (max 30 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 2 && !isLeapYear(tmp_year)) {
				while (tmp_day > 28 || tmp_day < 1) {
					cerr << "Error entering the day of birthday (max 28 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 2 && isLeapYear(tmp_year)) {
				while (tmp_day > 29 || tmp_day < 1) {
					cerr << "Error entering the day of birthday (max 29 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			u.SetBirthday(chrono::year(tmp_year) / chrono::month(tmp_month) / chrono::day(tmp_day));
			break;
		case 8:
			cout << "Enter new number id: "; cin >> tmp_i; CheckUnsignedData(tmp_i); u.SetNumberId(static_cast<unsigned int>(tmp_i));
			break;
		case 9:
			cout << "Enter new monthtly payment: "; cin >> tmp_i; CheckUnsignedData(tmp_i); u.SetMonthlyPayment(static_cast<unsigned int>(tmp_i));
			break;
		case 10:
			cout << "Enter 1 to Activate user / 0 - Inactivate: "; cin >> tmp_i; CheckData(tmp_i); if (tmp_i == 0) u.SetActiveUser(false); else u.SetActiveUser(true);
			break;
		case 11:
			cout << "Enter new year of issuance id (ex. 2020): "; cin >> tmp_year; CheckUnsignedData(tmp_year); while (tmp_year < 1900 || tmp_year > 3000) { cerr << "Error entering the year of issuance id! Retry: "; cin >> tmp_year; CheckUnsignedData(tmp_year); }
			cout << "Enter new month of issuance id (ex. 10): "; cin >> tmp_month; CheckUnsignedData(tmp_month); while (tmp_month < 1 || tmp_month > 12) { cerr << "Error entering the month of issuance id! Retry: "; cin >> tmp_month; CheckUnsignedData(tmp_month); }
			cout << "Enter new day of issuance id (ex. 14): "; cin >> tmp_day; CheckUnsignedData(tmp_day);
			if (tmp_month == 1 || tmp_month == 3 || tmp_month == 5 || tmp_month == 7 || tmp_month == 8 || tmp_month == 10 || tmp_month == 12) {
				while (tmp_day > 31 || tmp_day < 1) {
					cerr << "Error entering the day of issuance id (max 31 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 4 || tmp_month == 6 || tmp_month == 9 || tmp_month == 11) {
				while (tmp_day > 30 || tmp_day < 1) {
					cerr << "Error entering the day of issuance id (max 30 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 2 || !isLeapYear(tmp_year)) {
				while (tmp_day > 28 || tmp_day < 1) {
					cerr << "Error entering the day of issuance id (max 28 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			else if (tmp_month == 2 && isLeapYear(tmp_year)) {
				while (tmp_day > 29 || tmp_day < 1) {
					cerr << "Error entering the day of issuance id (max 29 days)! Retry: ";
					cin >> tmp_day;
					CheckUnsignedData(tmp_day);
				}
			}
			u.SetDateIssuance(chrono::year(tmp_year) / chrono::month(tmp_month) / chrono::day(tmp_day));
			break;
		default:
			work = 0;
			break;
		}
		if (work != 0) {
			cout << "_____________Menu_____________" << endl;
			cout << setw(25) << left << "Show info" << "- 1" << endl;
			cout << setw(25) << left << "Add book" << "- 2" << endl;
			cout << setw(25) << left << "Change name" << "- 3" << endl;
			cout << setw(25) << left << "Change surname" << "- 4" << endl;
			cout << setw(25) << left << "Change patronymic" << "- 5" << endl;
			cout << setw(25) << left << "Change sex" << "- 6" << endl;
			cout << setw(25) << left << "Change date of birhday" << "- 7" << endl;
			cout << setw(25) << left << "Change number id" << "- 8" << endl;
			cout << setw(25) << left << "Change monthtly payment" << "- 9" << endl;
			cout << setw(25) << left << "Change status" << "- 10" << endl;
			cout << setw(25) << left << "Change date issuance id" << "- 11" << endl;
			cout << setw(25) << left << "Exit" << "- 0" << endl;
			cin >> work;
			CheckData(work);
		}
	}

	return 0;
}