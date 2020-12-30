#include<iostream>
#include"Olympian.h"


using namespace std;
int main(void)
{
	setlocale(LC_ALL, "rus");
	Olympian* game = new Olympian();
	int ans;
	while (1)
	{
		cout << "Сделать ставки по олимпийским играм?" << endl;
		cout << "(1) - Да, хочу сделать ставки" << endl;
		cout << "(2) - Начать олимпийские игры" << endl;
		cin >> ans;
		if (ans == 1)
		{
			Observer* newObserver = new Observer();
			game->subscribe(newObserver);
		}
		else if (ans == 2)
		{
			break;
		}
	}
	cout << "Результаты ставок" << endl;
	game->Game();
	cout << "Олимпийские игры закончены, осуществляется выход из программы..." << endl;
	cin.get(); cin.get();
	return 0;
}
