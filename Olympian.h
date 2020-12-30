#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <string>
#include<ctime>
#include<cstdlib>

enum {BIATHLON , SCELETON, FIGURE_SKATING, SKATING};


using namespace std;

class Observer
{
	string name; //имя подписчика
	string bidBiathlon; //ставка на биатлон
	string bidSceleton;//ставка на скелетон
	string bidSkating; //ставка на конькобежный спорт
	string bid_figureSkating; //ставка на фигурное катание
public:
	Observer();
	string changeBid();
	void update(string in, int sport);
	friend class Olympian;
};

class sportsman
{
	string family;				//фамилия
	string name;				//имя
	string secfamily;			//отчество
	string country;				//страна
	float power = 0;				//сила
	float dexterity = 0;			//ловкость
	float lacky = 0;				//удача
	float stamina = 0;			//выносливость
public:
	// метод инициализации свойств спортсмена
	istream& setSportsman(istream& in);
	float getPhisData();
	void setCountry(string in);

};
//Из внешнего файла загружаются данные по каждому спортсмену: ФИО, страна, сила, ловкость, удача, выносливость.
class country
{

	sportsman* s; // здесь будет указатель на спортсмена
	fstream fs;//файл с которого будут считываться данные об спортмене
	string filestring; // здесь будет хранится строка с именем файла, где будет спортсменус
public:
	float k = 0.0;	//коэффициент с учетом нандомного стечения обстоятельств
	// метод создания новой страны, в качестве входного параметра -строка с названием файла с информацией о спортсмене
	void createCountry(string filename);
	//инициализирует показатели спортсмена
	void initSportsman();
	//устанавливает имя файла 
	void setFile(string files);
	//возвращает усредненные показатели спортсмена
	float getPhisDataSportsman();
	~country()
	{
		delete s;
	}
};


class Olympian
{
	vector<Observer*> observers; //база подписчиков
	int count = 5; //count of country - количество стран, учавствующих в ОИ
	//перечисление стран, на каждую страну приходится по спортсмену
	country* Russia;			
	country* Canada;
	country* France;
	country* Finland;
	country* Japan;
	string winner;	//победитель
	float* result = new float[count];
	//получение коэффициента выиграша спортсмена стран
	string getResult();
public:
	//подписка
	void subscribe(Observer* l);

	void inform(int sport);
	//непосредственный процесс игры
	void Game();
	~Olympian();
};
