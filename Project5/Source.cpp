#include <iostream>
#include<fstream>
#include<vector>
#include <cstring>
#include <string>

#include <Windows.h>
#include <filesystem>
#include <nlohmann/json.hpp>

#include <windows.h>
#include<conio.h>

using namespace std;

int r = 0;
enum Keys {
	UP = 72,
	DOWN = 80,
	ENTER = 13
};

void changeColor(int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, y);
}

enum color
{

	Blue = 1,
	Red = 4,
	White = 7,
	Green = 10,
	Blue2 = 11,
	Yellow = 100
};

using json = nlohmann::json;
using namespace std;

class Ingredient {
public:
	int id;
	static int ID;
	string name;
	int ingCount;
	double price;

	Ingredient() {
		id = 0;
		name = " ";
		ingCount = 0;
		price = 0;
	}


	Ingredient(string n, int c, double p) {
		id = ++ID;
		name = n;
		ingCount = c;
		price = p;
	}

	Ingredient(const Ingredient& obj) {
		id = ++ID;
		name = obj.name;
		ingCount = obj.ingCount;
		price = obj.price;
	}

	void ShowIngredient() {
		cout << name << "\t   " << ingCount << " eded \t" << price << "  AZN" << endl;
	}
};
int Ingredient::ID = 0;

class Meal {
public:
	int id;
	static int ID;
	string name;
	double price;


	Meal() {
		id = 0;
		name = " ";

		price = 0;
	}


	Meal(string n, double p) {

		name = n;
		price = p;
	}

	Meal(const Meal& obj) {
		name = obj.name;

		price = obj.price;
	}

	void ShowMeal() {
		cout << name << "\t" << price << "AZN" << endl;
	}
};

class Admin {
public:
	string username;
	string password;
	double money;
	double cost;
	double profit;
	Admin() = default;

	Admin(double m, double c) {
		money = m;
		cost = c;

	}

	Admin(double m, double c, double p) {
		money = m;
		cost = c;
		profit = p;
	}


	Admin(string usnm, string pas) {
		username = usnm;
		password = pas;
	}
};



class Menu {
public:
	double price = 0;
	string name = " ";
	vector<Meal> meals;

	Menu() {
		name = " ";
	}

	Menu(string name, double price) {
		this->name = name;
		this->price = price;
	}
};



class User {
public:
	string username;
	string password;


	User(string unm, string p) {
		username = unm;
		password = p;
	}
};

class  Sebet {
public:
	string name;
	double price;
	vector<Meal> m;

	Sebet(string n, double p) {
		name = n;
		price = p;
	}
};
void to_jsonIngredient(json& js, vector<Ingredient*>& ing) {
	for (int i = 0; i < ing.size(); i++)
	{
		json j = json{ {"name",ing[i]->name},{"count",ing[i]->ingCount},{"price",ing[i]->price} };

		js += j;

	}

	fstream f("json.ingredient.txt");
	f << js;
	f.close();

}

void from_jsonIngredient(json& js, vector<Ingredient>& ing) {



	for (int i = 0; i < js.size(); i++)
	{
		Ingredient t;
		js.at(i).at("name").get_to(ing[i].name);
		js.at(i).at("count").get_to(ing[i].ingCount);
		js.at(i).at("price").get_to(ing[i].price);
		ing.push_back(t);
	}

	fstream file("json.ingredient.txt", ios::in);
	file >> js;
	file.close();
}



void to_jsonMeal(json& js, vector<Meal*>& meal) {
	for (int i = 0; i < meal.size(); i++)
	{
		json j = json{ {"name",meal[i]->name},{"price",meal[i]->price} };

		js += j;

	}



}



void from_jsonMeal(json& js, vector<Meal>& meal) {
	for (int i = 0; i < js.size(); i++)
	{
		Meal t;
		js.at(i).at("name").get_to(meal[i].name);
		js.at(i).at("price").get_to(meal[i].price);
		meal.push_back(t);
	}
	fstream file("json.Meal.txt", ios::in);
	file >> js;
	file.close();

}

class RestaurantMenu {
public:
	double restaurantMoney = 10000;
	vector<Ingredient*> ingredient;
	vector<Meal*> meal;
	vector<Admin> admin;
	vector<Menu> menu;
	vector<Sebet> sebet;

};
void print(string* arr, int size, int x) {
	for (int i = 0; i < size; i++)
	{
		if (i == x) {
			changeColor(Red);
		}
		cout << arr[i] << endl;
		changeColor(White);
	}
}

void AdminMenu(RestaurantMenu& rm) {
label2:
	system("cls");
	string arr[9] = { "Show Ingredient", "Add Ingredient","Show Meal","Add Meal","Change Ingredient", "Add Meal to Menu", "Remove to Menu","Statistic" ,"Quit" };

	int x = 0;

	while (true)
	{
		string cho;
		system("cls");
		print(arr, 9, x);
		char ch;
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
			if (ch == UP) {
				x = x == 0 ? 8 : x - 1;
			}
			else if (ch == DOWN) {
				x = x == 8 ? 0 : x + 1;
			}

		}
		else {
			if (x == 0 && ch == ENTER) {
			label3:
				system("cls");
				if (rm.ingredient.size() == 0) {
					cout << "Ingredient yoxdur" << endl;
					Sleep(1500);
					goto label2;

				}
				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					cout << i + 1 << ".";
					rm.ingredient[i]->ShowIngredient();
				}

				cout << "0 - Back" << endl;
				string ch1;
				cin >> ch1;
				if (ch1 == "0")
					goto label2;
				else goto label3;
			}
			else if (x == 1 && ch == ENTER) {
			labelAddIng:
				system("cls");
				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					cout << i + 1 << ".";
					rm.ingredient[i]->ShowIngredient();
				}

				string n;
				int c;
				double p;




				cout << "Ingredient name : ";
				cin >> n;

				if (n == "0") {
					goto label2;
				}
				cout << "Ingredient count : ";
				cin >> c;


				cout << "Ingredient price : ";
				cin >> p;


				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					if (n == rm.ingredient[i]->name) {
						if (rm.restaurantMoney - c * p >= 0) {
							rm.ingredient[i]->ingCount += c;
							rm.ingredient[i]->price = p;
							int cost = p * c;
							system("cls");
							cout << "Ingredient elave olundu";
							Sleep(1500);
							rm.admin.push_back(Admin(rm.restaurantMoney, cost));
							goto label2;
						}
					}
				}

				if (rm.restaurantMoney - (p * c) >= 0) {
					Ingredient* t = new Ingredient(n, c, p);
					rm.ingredient.push_back(t);
					rm.restaurantMoney = rm.restaurantMoney - (p * c);
					int cost = p * c;
					rm.admin.push_back(Admin(rm.restaurantMoney, cost));
					system("cls");
					cout << "Ingredient elave olundu";
					Sleep(1500);
					json js = json::array();
					to_jsonIngredient(js, rm.ingredient);
					fstream f("ingredient.json.momoa", ios::out);
					f << js;
					f.close();
					goto label2;

				}
				else {
					system("cls");
					cout << "pulunuz yeterli deyil" << endl;
					cout << "Kassanizdaki pul : " << rm.restaurantMoney << "AZN" << endl;
					cout << "Sifarishiniz : " << p * c << "AZN" << endl;
					Sleep(1500);
					system("cls");
					goto labelAddIng;
				}
			}
			else if (x == 2 && ch == ENTER) {
			labelMeal:
				system("cls");
				int ch;
				if (rm.meal.size() == 0) {
					cout << "Yemek elave olunmayib" << endl;
					Sleep(1500);
					goto label2;
				}
				for (int i = 0; i < rm.meal.size(); i++)
				{
					cout << i + 1 << ".";
					rm.meal[i]->ShowMeal();
				}
				cin >> ch;
				if (ch == 0)
					goto label2;
				else goto labelMeal;
			}
			else if (x == 3 && ch == ENTER) {
			labelAddMeal:
				system("cls");
				if (rm.ingredient.size() == 0) {
					cout << "Yemek elave etmek ucun ingredient yoxdur" << endl << endl;
					Sleep(1500);
					goto label2;
				}

				string name;
				double price;
				string ch;
				int count;
				cout << "Yemekler" << endl;
				for (int i = 0; i < rm.meal.size(); i++)
				{
					rm.meal[i]->ShowMeal();
				}
				cout << "0 - Back" << endl;
				cout << "Add Meal : ";
				cin >> name;

				if (name == "0") {
					goto label2;
				}


				cout << "Add price meal :";
				cin >> price;

				for (int i = 0; i < rm.meal.size(); i++)
				{
					if (rm.meal[i]->name == name) {
						cout << "bu yemek artiq movcuddur" << endl;
						Sleep(1500);
						goto labelMeal;
					}
				}
				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					cout << i + 1 << ".";
					rm.ingredient[i]->ShowIngredient();
				}
			label5:
				cout << "0 - Back" << endl;
				cout << "Terkibindeki ingredientler : ";
				cin >> ch;
				cout << "count : ";
				cin >> count;




				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					if (rm.ingredient[i]->ingCount > count) {
						if (ch == rm.ingredient[i]->name) {
							if (rm.ingredient[i]->ingCount - count != 0) {
								rm.ingredient[i]->ingCount -= count;
								Meal* t = new Meal(name, price);
								rm.meal.push_back(t);
								cout << "Yemek elave olundu" << endl;
								json js = json::array();
								to_jsonMeal(js, rm.meal);
								fstream file("json.Meal.txt");
								file >> js;
								file.close();
								Sleep(1500);
								goto label2;
							}
							else { cout << "ingredient sayis yetersizdir" << endl; 	Sleep(1500); goto labelMeal; }
						}


					}
					else { cout << "ingredient sayi yetersizdir " << endl; 	Sleep(1500); goto label3; }
				}
				cout << "bele ingredient yoxdur" << endl;
				Sleep(1500);
				goto label5;


			}
			else if (x == 4 && ch == ENTER) {
				string n;
				int count;
				int ch;
				for (int i = 0; i < rm.ingredient.size(); i++)
				{
					cout << i + 1 << ".";
					rm.ingredient[i]->ShowIngredient();
				}

				cout << "deyisdireceyiniz ingredient : ";
				cin >> n;
				cout << "1.Sayini artir\n2.Sayini azalt" << endl;
				cin >> ch;

				if (ch == 1) {
					cout << "Ne qeder artiracaqsiniz : ";
					cin >> count;
					for (int i = 0; i < rm.ingredient.size(); i++)
					{
						if (n == rm.ingredient[i]->name) {
							rm.ingredient[i]->ingCount += count;
							cout << "Successful" << endl;
							Sleep(1500);
							goto label2;
						}
						else { cout << "Bele Ingredient yoxdur"; Sleep(1500); goto label2; }
					}
				}

				else if (ch == 2) {
					cout << "Ne qeder azaldacaqsiniz : ";
					cin >> count;
					for (int i = 0; i < rm.ingredient.size(); i++)
					{
						if (n == rm.ingredient[i]->name) {
							rm.ingredient[i]->ingCount -= count;
							cout << "Successful" << endl;
							json js = json::array();
							to_jsonIngredient(js, rm.ingredient);
							fstream file("ingredient.json.momoa");
							file << js;
							file.close();
							Sleep(1500);
							goto label2;

						}
						else { cout << "Bele Ingredient yoxdur"; Sleep(1500); goto label2; }
					}
				}

			}
			else if (x == 5 && ch == ENTER) {
			labelMenu:
				string n;
				if (rm.meal.size() == 0) {
					cout << "Yemek yoxdur" << endl;
					Sleep(1500);
					goto label2;
				}

				cout << "Menu'ya elave etmek istediyiniz  yemekleri daxil edin :" << endl;

				for (int i = 0; i < rm.meal.size(); i++)
				{
					cout << i + 1 << ".";
					rm.meal[i]->ShowMeal();
				}

				cin >> n;

				if (n == "0") {
					goto label2;
				}
				double t = 0;

				for (int i = 0; i < rm.menu.size(); i++)
				{
					if (rm.menu[i].name == n) {
						cout << "Menu'da artiq bele yemek var" << endl;
						Sleep(2000);

						goto labelMeal;
					}
				}
				for (int i = 0; i < rm.meal.size(); i++)
				{
					if (n == rm.meal[i]->name) {
						t = rm.meal[i]->price;
					}
				}
				if (t == 0) {
					cout << "Bele yemek yoxdur" << endl;
					Sleep(2000);

					goto labelMeal;
				}

				rm.menu.push_back(Menu(n, t));

				cout << "Yemek menuya elave olundu" << endl;
				Sleep(2000);

				goto label2;
			}
			else if (x == 6 && ch == ENTER) {
			labelMenu2:
				string n;
				if (rm.meal.size() == 0) {
					cout << "Yemek yoxdur" << endl;
					Sleep(1500);
					goto label2;
				}
				cout << "Menu'dan cixarmaq  istediyiniz  yemekleri daxil edin :" << endl;
				for (int i = 0; i < rm.meal.size(); i++)
				{
					cout << i + 1 << ".";
					rm.meal[i]->ShowMeal();
				}

				cin >> n;

				if (n == "0") {
					goto label2;
				}
				double t = 0;

				for (int i = 0; i < rm.menu.size(); i++)
				{
					if (rm.menu[i].name == n) {

						rm.menu.erase(rm.menu.begin() + i);
						cout << "Yemek Menu'dan cixarildi" << endl;
						Sleep(2000);

						goto label2;
					}
				}
			}
			else if (x == 7 && ch == ENTER) {
			labelS:
				system("cls");
				int money = 0;
				int profit = 0;
				int cost = 0;
				string date;
				string ch;
				for (int i = 0; i < rm.admin.size(); i++)
				{
					money = rm.admin[i].money;
					profit += rm.admin[i].profit;
					cost += rm.admin[i].cost;
				}

				cout << "Money : " << money << endl;
				cout << "Cost : " << cost << endl;
				cout << "Profit : " << profit << endl;
				cout << "0.Back" << endl;
				cin >> ch;
				if (ch == "0")
					goto label2;
				else goto labelS;
			}
			else if (x == 8 && ch == ENTER) {
				break;
			}

		}

	}
}


void UserMenu(RestaurantMenu& rm) {
	system("cls");


	string arr[3] = { ">>>>>>>>>>             Sebet                  <<<<<<<<<<<" ,">>>>>>>>>>             Yemek secmek           <<<<<<<<<<<",">>>>>>>>>>             Back                   <<<<<<<<<<<" };
	int x = 0;
labelUser:
	while (true)
	{
		system("cls");
		cout << ">>>>>>>>>>>>>>         FAXRALI RESTORANI          <<<<<<<<<<<<<<<<" << endl;
		print(arr, 3, x);
		char ch;
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
			if (ch == UP) {
				x = x == 0 ? 2 : x - 1;
			}
			else if (ch == DOWN) {
				x = x == 2 ? 0 : x + 1;
			}

		}
		else {
			if (x == 0 && ch == ENTER) {
			labelUser1:
				int ch2;
				if (rm.sebet.size() == 0) {
					cout << "Sebet bosdur" << endl;
					Sleep(1500);
					goto labelUser;
				}
				for (int i = 0; i < rm.sebet.size(); i++)
				{
					cout << rm.sebet[i].name << " \t" << rm.sebet[i].price << "AZN" << endl;
				}
				cin >> ch2;
				if (ch == 0)
					goto labelUser;
				else goto labelUser1;
			}
			else if (x == 1 && ch == ENTER) {
				cout << "Yemekleri sebetinize elave etmek ucun adini yazin" << endl;
				string n;
				cin >> n;

				if (rm.meal.size() == 0) {
					cout << "Yemek yoxdur" << endl;
					Sleep(1500);
					goto labelUser;
				}

				for (int i = 0; i < rm.menu.size(); i++)
				{
					cout << i + 1 << ".";
					cout << rm.menu[i].name << "\t" << rm.menu[i].price << "AZN" << endl;
				}
				for (int i = 0; i < rm.meal.size(); i++)
				{
					if (rm.meal[i]->name == n) {
						rm.sebet.push_back(Sebet(n, rm.meal[i]->price));
						rm.meal.erase(rm.meal.begin() + i);
						rm.menu.erase(rm.menu.begin() + i);

						cout << "Sebete elave olundu" << endl;
						Sleep(1500);
						goto labelUser;

					}
				}
				cout << "Bele yemek yoxdur" << endl;
				Sleep(1500);
				goto labelUser;
			}
			else if (x == 2 && ch == ENTER) {
				break;
			}
		}
	}


}


int CheckAdmin() {
labelAdmin:
	system("cls");
	RestaurantMenu r;

	string username;
	string password;

	string usnm = "huseyn";
	string pas = "12345";
	Admin admin(usnm, pas);

	cout << "(0 - Back) Admin username : ";
	cin >> username;




	if (username == admin.username) {
		cout << "Password : ";
		cin >> password;
		if (password == admin.password) {
			cout << "Successfull" << endl;
			Sleep(1500);

			return 1;
		}
		else { cout << "Wrong Password" << endl; Sleep(1500); goto labelAdmin; }
	}
	else if (username == "0") {
		return 0;
	}
	else {
		cout << "Wrong Username" << endl; Sleep(1500); goto labelAdmin;
	}

}





int main() {
	RestaurantMenu rm;
	string arr[3] = { "Admin","User","Quit" };
	;

	int x = 0;
label1:
	while (true)
	{
		system("cls");
		print(arr, 3, x);
		char ch;
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
			if (ch == UP) {
				x = x == 0 ? 2 : x - 1;
			}
			else if (ch == DOWN) {
				x = x == 2 ? 0 : x + 1;
			}

		}
		else {
			if (x == 0 && ch == ENTER) {
				if (r == 0) {
					if (CheckAdmin()) {
						r = 1;
						AdminMenu(rm);
					}
					else goto label1;
				}
				else if (r == 1) {
					AdminMenu(rm);
				}
			}
			else if (x == 1 && ch == ENTER) {
				UserMenu(rm);
			}
			else if (x == 2 && ch == ENTER) {
				cout << "Goodbye" << endl;
				Sleep(1500);
				system("pause");
				break;
			}


		}
	}




}