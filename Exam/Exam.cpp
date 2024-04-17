#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "windows.h"

using namespace std;


struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;
	Date()
	{
		day = 1;
		month = 1;
		year = 2000;
	}
	Date(unsigned Day, unsigned Month, unsigned Year)
	{
		day = Day;
		month = Month;
		year = Year;
	}
	void Output() const
	{
		cout << day << "." << month << "." << year;
	}
	void Input()
	{
		cout << "Day: ";
		cin >> day;
		cout << "Month: ";
		cin >> month;
		cout << "Year: ";
		cin >> year;
	}
public:
	long long Days()
	{
		return year * 365 + (month - 1) * 31 + day;
	}
};

class Spending
{
	double money;
	int category; //категория 1 - продукты, 2 - автотовары, 3 - зоотовары, 4 - спорттовары, 5 - хозтовары, 6 - строительные товары, 7 - общественное питание, 8 - развлечения
	Date date;
public:
	Spending()
	{
		money = 0;
		category = 0;
		date = Date(1,1,1);
	}
	
	Spending(double mon, int cat, Date d)
	{
		money = mon;
		category = cat;
		date = d;
	}
	void Output() const
	{
		cout << "\nMoney: " << money;
		cout << "\nCategory: " << category;
		cout << "\nData: ";
		date.Output();
		cout << "\n";
	}

	void Input()
	{
		cout << "Ente amount: ";
		cin >> money;
		cout << "Enter category: ";
		cin >> category;
		cout << "Enter date: \n";
		date.Input();
	}

	float GetMoney() const
	{
		return money;
	}

	int GetCategory() const
	{
		return category;
	}

	bool operator<(const Spending& other) const
	{
		return money < other.money;
	}

	const Date& GetDate() const
	{
		return date;
	}
};

class MoneyStorage
{
protected:
	long long number;
	float totalMoney;
	multiset<Spending> spendings;
	float creditLimit;
public:
	bool operator<(const MoneyStorage& other) const {
		return number < other.number;
	}

	bool operator>(const MoneyStorage& other) const {
		return number > other.number;
	}

	bool operator==(const MoneyStorage& other) const {
		return number == other.number;
	}

	MoneyStorage()
	{
		number = 0;
		creditLimit = 0;
		totalMoney = 0;
	}
	MoneyStorage(long long num, float credit)
	{
		number = num;
		creditLimit = credit;
		totalMoney = 0;
	}
	MoneyStorage(long long num, float credit, float t)
	{
		number = num;
		creditLimit = credit;
		totalMoney = t;
	}
	MoneyStorage(multiset<Spending>& m, long long num, float t, float credit)
	{
		number = num;
		creditLimit = credit;
		totalMoney = t;
		spendings = m;
	}
	void LoadSpending(ifstream &inf)
	{
		int Category;
		float Money;
		Date date;
		spendings.clear();
		while (inf >> Category >> Money >> date.day >> date.month >> date.year)
		{
			Spending* spend = new Spending(Money, Category, date);
			spendings.insert(*spend);
		}
	}

	bool SaveSpending(ofstream &outf)
	{
		if (!outf) return false;
		for (auto& spending : spendings)
		{
			outf << spending.GetCategory() << endl;
			outf << spending.GetMoney() << endl;
			outf << spending.GetDate().day << endl;
			outf << spending.GetDate().month << endl;
			outf << spending.GetDate().year << endl;
		}
		return true;
	}

	virtual bool Load(string filename) 
	{
		return false;
	}
	virtual bool Save(string filename) 
	{
		return false;
	}
	virtual void Output()
	{
		cout << "\nNumber: " << number;
		cout << "\nCredit Limit: " << creditLimit;
		cout << "\nTotal Money: " << totalMoney;
	}

	void Input()
	{
		cout << "Number: ";
		cin >> number;
		cout << "Credit Limit: ";
		cin >> creditLimit;
		cout << "Total Money: ";
		cin >> totalMoney;
	}
	void TopUp(float sum)
	{
		totalMoney = totalMoney + sum;
	}
	void AddSpending(Spending* spend)
	{
		totalMoney = totalMoney - spend -> GetMoney();
		spendings.insert(*spend);
	}
	long long GetNumber() const
	{
		return number;
	}
	multiset<Spending> GetSpendings() const
	{
		return spendings;
	}
};

class Card : public MoneyStorage
{
	string bankName;
public:
	Card() : MoneyStorage()
	{
		bankName = "";
	}
	Card(long long num, float credit, string name) : MoneyStorage(num, credit)
	{
		bankName = name;
	}
	Card(long long num, float credit, float t, string name) : MoneyStorage(num, credit, t)
	{
		bankName = name;
	}
	Card(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, t, credit)
	{
		bankName = name;
	}
	virtual bool Load(string filename)
	{
		ifstream inf(filename + ".card");
		if (!inf) return false;
		inf >> number >> totalMoney >> creditLimit >> bankName;
		LoadSpending(inf);
		return true;
	}

	virtual bool Save(string filename)
	{
		ofstream outf(filename + ".card");
		if (!outf) return false;
		outf << number << endl;
		outf << totalMoney << endl;
		outf << creditLimit << endl;
		outf << bankName << endl;
		SaveSpending(outf);
		return true;
	}
	virtual void Output()
	{
		cout << "Bank Name: " << bankName;
		MoneyStorage::Output();
	}
	void Input()
	{
		cout << "Bank Name: ";
		cin >> bankName;
		MoneyStorage::Input();
	}
};

class Wallet : public MoneyStorage
{
	string walletType;
public:
	Wallet() : MoneyStorage()
	{
		walletType = "";
	}
	Wallet(long long num, float credit, string type) : MoneyStorage(num, credit)
	{
		walletType = type;
	}
	Wallet(long long num, float credit, float t, string type) : MoneyStorage(num, credit, t)
	{
		walletType = type;
	}
	Wallet(multiset<Spending>& m, long long num, float t, float credit, string type) : MoneyStorage(m, num, t, credit)
	{
		walletType = type;
	}
	virtual bool Load(string filename)
	{
		ifstream inf(filename + ".wallet");
		if (!inf) return false;
		inf >> number >> totalMoney >> creditLimit >> walletType;
		LoadSpending(inf);
		return true;
	}

	virtual bool Save(string filename)
	{
		ofstream outf(filename + ".wallet");
		if (!outf) return false;
		outf << number << endl;
		outf << totalMoney << endl;
		outf << creditLimit << endl;
		outf << walletType << endl;
		SaveSpending(outf);
		return true;
	}
	void Output()
	{
		cout << "\nWallet Type: " << walletType;
		MoneyStorage::Output();
	}
	void Input()
	{
		cout << "Wallet Type: ";
		cin >> walletType;
		MoneyStorage::Input();
	}
};
class FinanceManagement
{
	set <MoneyStorage*> storages;
public:
		FinanceManagement(){ }
		void AddStorage(MoneyStorage* ptr)
		{
			storages.insert(ptr);
		}

		void DeleteStorage(long long number)
		{
			for (auto it = storages.begin(); it != storages.end(); ++it) {
				if ((*it)->GetNumber() == number) {
					delete* it;
					storages.erase(it);
					cout << "Card deleted successfully." << endl;
					return;
				}
				cout << "\nPress Enter to continue";
				string l;
				cin >> l;
			}
			cout << "Card not found." << endl;
		}

		void Output()
		{
			for (auto& elem : storages)
			{
				elem->Output();
				cout << "\n";
			}
			cout << "Press Enter to continue";
			string l;
			cin >> l;
		}
		void TopUpStorage()
		{
			long long number;
			float money;
			Date date;
			system("cls");
			cout << "Select a number card: ";
			cin >> number;
			cout << "Enter the top-up amount: ";
			cin >> money;
			cout << "Enter date\n";
			date.Input();
			for (auto it = storages.begin(); it != storages.end(); ++it) 
			{
				if ((*it)->GetNumber() == number)
				{
					(*it) -> TopUp(money);
					cout << "Card completed successfully." << endl;	
					cout << "\nPress Enter to continue";
					string l;
					cin >> l;
					return;
				}		
			}
			cout << "Card not found." << endl;
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void AddSpendingToStorage()
		{
			long long number;
			Spending* s = new Spending;
			system("cls");
			cout << "Select a number card: ";
			cin >> number;
			s -> Input();
			for (auto it = storages.begin(); it != storages.end(); ++it)
			{
				if ((*it)->GetNumber() == number)
				{
					(*it)->AddSpending(s);
					cout << "Costs have been successfully added." << endl;
					cout << "\nPress Enter to continue";
					string l;
					cin >> l;
					return;
				}
			}
			cout << "Card not found." << endl;
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void DayReport()
		{
			Date today;
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (auto& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() != days) continue;
					spending.Output();
				}
			}
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void WeekReport()
		{
			Date today;
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (auto& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if(x.Days() < days - 6) continue;
					spending.Output();
				}
			}
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void MonthReport()
		{
			Date today;
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (auto& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if (x.Days() < days - 30) continue;
					spending.Output();
				}
			}
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void RatingWeek()
		{
			Date today;
			Spending top1;
			Spending top2;
			Spending top3;
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (const Spending& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if (x.Days() < days - 6) continue;
					if (top1.GetMoney() <= spending.GetMoney())
					{
						top3 = top2;
						top2 = top1;
						top1 = spending;
					}
					else if (top2.GetMoney() <= spending.GetMoney())
					{
						top3 = top2;
						top2 = spending;
					}
					else if (top2.GetMoney() <= spending.GetMoney())
					{
						top3 = spending;
					}
				}
			}
			if (top1.GetMoney() != 0) top1.Output();
			if (top2.GetMoney() != 0) top2.Output();
			if (top3.GetMoney() != 0) top3.Output();
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
		void RatingMonth()
		{
			Date today;
			Spending top1;
			Spending top2;
			Spending top3;
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (const Spending& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if (x.Days() < days - 30) continue;
					if (top1.GetMoney() <= spending.GetMoney())
					{
						top3 = top2;
						top2 = top1;
						top1 = spending;
					}
					else if (top2.GetMoney() <= spending.GetMoney())
					{
						top3 = top2;
						top2 = spending;
					}
					else if (top2.GetMoney() <= spending.GetMoney())
					{
						top3 = spending;
					}
				}
			}
			if (top1.GetMoney() != 0) top1.Output();
			if (top2.GetMoney() != 0) top2.Output();
			if (top3.GetMoney() != 0) top3.Output();
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}


		void RatingWeekCategory()
		{
			Date today;
			float sumcategory[9]{ 0,0,0,0,0,0,0,0,0 };
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (const Spending& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if (x.Days() < days - 6) continue;
					sumcategory[spending.GetCategory()] += spending.GetMoney();
				}
			}
			int top1 = 0;
			int top2 = 0;
			int top3 = 0;
			for (int i = 0; i < 5; i++)
			{
				if (sumcategory[top1] <= sumcategory[i])
				{
					top3 = top2;
					top2 = top1;
					top1 = i;
				}
				else if (sumcategory[top2] <= sumcategory[i])
				{
					top3 = top2;
					top2 = i;
				}
				else if (sumcategory[top3] <= sumcategory[i])
				{
					top3 = i;
				}
			}
			if (sumcategory[top1] != 0) cout << "Category: " << top1 << " Sum: " << sumcategory[top1] << endl;
			if (sumcategory[top2] != 0) cout << "Category: " << top2 << " Sum: " << sumcategory[top2] << endl;
			if (sumcategory[top3] != 0) cout << "Category: " << top3 << " Sum: " << sumcategory[top3] << endl;
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}


		void RatingMonthCategory()
		{
			Date today;
			float sumcategory[9] { 0,0,0,0,0,0,0,0,0 };
			cout << "Enter date\n";
			today.Input();
			long long  days = today.Days();
			for (auto& card : storages)
			{
				for (const Spending& spending : card->GetSpendings())
				{
					Date x = spending.GetDate();
					if (x.Days() > days) continue;
					if (x.Days() < days - 30) continue;
					sumcategory[spending.GetCategory()] += spending.GetMoney();
				}
			}
			int top1 = 0;
			int top2 = 0;
			int top3 = 0;
			for (int i = 0; i < 5; i++)
			{
				if (sumcategory[top1] <= sumcategory[i])
				{
					top3 = top2;
					top2 = top1;
					top1 = i;
				}
				else if (sumcategory[top2] <= sumcategory[i])
				{
					top3 = top2;
					top2 = i;
				}
				else if (sumcategory[top3] <= sumcategory[i])
				{
					top3 = i;
				}
			}
			if (sumcategory[top1] != 0) cout << "Category: " << top1 << " Sum: " << sumcategory[top1] << endl;
			if (sumcategory[top2] != 0) cout << "Category: " << top2 << " Sum: " << sumcategory[top2] << endl;
			if (sumcategory[top3] != 0) cout << "Category: " << top3 << " Sum: " << sumcategory[top3] << endl;
			cout << "\nPress Enter to continue";
			string l;
			cin >> l;
		}
	};


int main()
{
	Spending spending1(340.0, 2, Date(6, 5, 2000));
	Spending spending2(500.0, 4, Date(7, 5, 2000));
	Spending spending3(21300.0, 1, Date(1, 1, 2000));
	Spending spending4(500.0, 2, Date(10, 5, 2000));
	Spending spending5(6500.0, 4, Date(1, 1, 2000));
	Spending spending6(500.0, 2, Date(1, 10, 2000));
	Spending spending7(32400.0, 3, Date(5, 5, 2000));
	Spending spending8(870.0, 1, Date(1, 1, 2000));
	Spending spending9(4500.0, 2, Date(14, 5, 2000));
	MoneyStorage* stor_ptr1;
	MoneyStorage* stor_ptr2;
	stor_ptr1 = new Card(5555555555555555, 2000, 100000, "Oschadbank");
	stor_ptr2 = new Wallet(11111, 1000, 70000, "Paypal");

	FinanceManagement PaymentSystem;
	PaymentSystem.AddStorage(stor_ptr1);
	PaymentSystem.AddStorage(stor_ptr2);
	stor_ptr1->AddSpending(&spending1);
	stor_ptr2->AddSpending(&spending2);
	stor_ptr2->AddSpending(&spending3);
	stor_ptr1->AddSpending(&spending4);
	stor_ptr2->AddSpending(&spending5);
	stor_ptr1->AddSpending(&spending6);
	stor_ptr2->AddSpending(&spending7);
	stor_ptr2->AddSpending(&spending8);
	stor_ptr1->AddSpending(&spending9);

	stor_ptr1->Save("Card1");
	stor_ptr2->Save("Card2");
	stor_ptr1->Load("Card1");
	stor_ptr2->Load("Card2");
	unsigned operation;
	do
	{
		system("cls");
		cout << "\nChoose operation\n";
		cout << "1  - Top up storage\n";
		cout << "2  - Add spending to storage\n";
		cout << "3  - Show storages\n";
		cout << "4  - Show day report\n";  
		cout << "5  - Show week report\n"; 
		cout << "6  - Show month report\n";
		cout << "7  - Show week rating\n"; 
		cout << "8  - Show month rating\n";
		cout << "9  - Show week rating for categories\n";
		cout << "10 - Show month rating for categories\n";
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
	stor_ptr1->Save("Card1");
	stor_ptr2->Save("Card2");
}
