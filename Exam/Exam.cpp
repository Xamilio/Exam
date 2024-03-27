#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;


struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;
	void Output() const;  // вывод даты
	void Input(); // ввод даты с клавиатуры
};
struct Time
{
	
};
bool isLeap(int year);    // функция для определения, високосным ли является год


int diff_between_dates(Date begin_date, Date end_date); // функция, определяющая количество дней между 2-мя датами датами
// эта функция нужна для отчета по затратам за неделю

class Spending
{
	float money;
	int category;  // категория 1 - продукты, 2 - автотовары, 3 - зоотовары, 4 - спорттовары, 5 - хозтовары, 6 - строительные товары, 7 - общественное питание, 8 - развлечения
	Date date;
public:
	Spending()
	{

	}
	Spending(float mon, int cat, Date d, Time t)
	{

	}
	void Output() const
	{

	}
	void Input()
	{

	}
	float GetMoney() const
	{

	}
	float GetCategory() const
	{

	}
	bool operator<(const Spending b) const
	{

	}
	const Date& GetDate() const
	{

	}
	const Time& GetTime() const
	{

	}
};

class MoneyStorage
{
protected:
	long long number;
	float totalMoney;
	multiset<Spending> spendings;
	float creditLimit;  // если кредитный лимит > 0, то карта кредитная, иначе - дебетовая
public:
	MoneyStorage()
	{

	}
	MoneyStorage(long long num, float credit)
	{

	}
	MoneyStorage(multiset<Spending>& m, long long num, float t, float credit)
	{

	}
	virtual void Output() = 0;

	void Input() 
	{

	}
	void TopUp()
	{

	}
	void AddSpending()
	{

	}
	long long GetNumber() const
	{

	}
	multiset<Spending> GetSpendings() const
	{

	}
};

class Card : public MoneyStorage
{
	string bankName;
public:
	Card()
	{

	}
	Card(long long num, float credit, string name)
	{

	}
	Card(multiset<Spending>& m, long long num, float t, float credit, string name)
	{

	}

	void Output()
	{

	}
	void Input()
	{

	}
};

class Wallet : public MoneyStorage
{
	string walletType;
public:
	Wallet()
	{

	}
	Wallet(long long num, float credit, string type)
	{

	}
	Wallet(multiset<Spending>& m, long long num, float t, float credit, string type)
	{

	}
	void Output()
	{

	}
	void Input()
	{

	}
};
	class FinanceManagement
	{
		set <MoneyStorage*> storages;
	public:
		FinanceManagement()
		{

		}
		void AddStorage(MoneyStorage* ptr)
		{

		}
		void DeleteStorage(int number)
		{

		}
		void Output()
		{

		}
		void TopUpStorage()
		{
			int operation;
			MoneyStorage* card = nullptr;
			do
			{
				system("cls");
				if (card == nullptr)
				{
					cout << "\nSelect a card\n";
				}
				else
				{
					cout << "\nChange card\n";
				}
				set<MoneyStorage*>::const_iterator it; // оголошуємо ітератор
				it = storages.begin(); // присвоюємо йому початковий елемент set-у
				while (it != storages.end()) // поки ітератор не досяг останнього елементу
				{
					cout << *it. << " "; // виводимо значення елементу, на який вказує ітератор
					++it; // і переходимо до наступного елементу
				}
				//cout << "1  - карта 1\n";
				//cout << "2  - карта 2\n";
				//cout << "3  - кошелек\n";
				if (card != nullptr)
				{
					cout << "4 - Enter the top-up amount\n";
				}
				cout << "5 - Exit\n";
				cin >> operation;
				switch (operation)
				{
				case 1:
					//PaymentSystem.TopUpStorage(); // карта 1
					break;
				case 2:
					//PaymentSystem.AddSpendingToStorage(); // карта 2
					break;
				case 3:
					//PaymentSystem.Output(); //  карта 3
					break;
				case 3:
					//PaymentSystem.Output(); //  карта 3
					break;
				case 4:
					cout << "Bye!\n";
					break;
				default:
					cout << "This operation does not exist!\n";
				}
			} while (operation != 11);
		}
		void AddSpendingToStorage()
		{

		}
		void DayReport()
		{

		}
		void WeekReport()
		{

		}
		void RatingWeek()
		{

		}
		void MonthReport()
		{

		}
		void RatingMonth()
		{

		}
		void RatingMonthCategory()
		{

		}
		void RatingWeekCategory()
		{

		}
	};


int main()
{
	MoneyStorage* stor_ptr1;  // указатель на базовый абстрактный класс "Хранилище денег"
	MoneyStorage* stor_ptr2;
	stor_ptr1 = new Card(5555555555555555, 2000, "Oschadbank"); // создаём банковскую карточку
	stor_ptr2 = new Wallet(11111, 1000, "Paypal");   // создаём Paypal-кошелёк

	FinanceManagement PaymentSystem; // создаём систему управления финансами
	PaymentSystem.AddStorage(stor_ptr1); // добавляем в систему "храналища денег"
	PaymentSystem.AddStorage(stor_ptr2);
	PaymentSystem.Output();
	unsigned operation;
	do
	{
		system("cls");
		cout << "\nChoose operation\n";
		cout << "1  - Top up storage\n";  // пополнить карту или кошелёк
		cout << "2  - Add spending to storage\n";  // произвести оплату с карты или кошелька
		cout << "3  - Show storages\n";  // посмотреть состояние всех карт и кошельков, включая затраты, которые осуществлялись
		cout << "4  - Show day report\n";  // посмотреть ответ по затратам за день с записью в файл
		cout << "5  - Show week report\n";  // посмотреть ответ по затратам за неделю с записью в файл
		cout << "6  - Show month report\n";  // посмотреть ответ по затратам за месяц с записью в файл
		cout << "7  - Show week rating\n";  // посмотреть ТОП-3 затрат за неделю с записью в файл
		cout << "8  - Show month rating\n";  // посмотреть ТОП-3 затрат за месяц с записью в файл
		cout << "9  - Show week rating for categories\n";  // посмотреть ТОП-3 категорий за неделю с записью в файл
		cout << "10 - Show month rating for categories\n";  // посмотреть ТОП-3 категорий за месяц с записью в файл
		cout << "11 - Exit\n";
		cin >> operation;
		switch (operation)
		{
		case 1:
			PaymentSystem.TopUpStorage();
			break;
		case 2:
			PaymentSystem.AddSpendingToStorage();
			break;
		case 3:
			PaymentSystem.Output();
			break;
		case 4:
			PaymentSystem.DayReport();
			break;
		case 5:
			PaymentSystem.WeekReport();
			break;
		case 6:
			PaymentSystem.MonthReport();
			break;
		case 7:
			PaymentSystem.RatingWeek();
			break;
		case 8:
			PaymentSystem.RatingMonth();
			break;
		case 9:
			PaymentSystem.RatingWeekCategory();
			break;
		case 10:
			PaymentSystem.RatingMonthCategory();
			break;
		case 11:
			cout << "Bye!\n";
			break;
		default:
			cout << "This operation does not exist!\n";
		}
	} while (operation != 11);
}