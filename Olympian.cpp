#include "Olympian.h

//методы класса Observer
Observer::Observer()
{
	cout << "Введите имя подписчика: ";
	cin.get();
	getline(cin, name);
	cout << "Выберите страну для ставки по биатлону: " << endl;
	bidBiathlon = changeBid();
	cout << "Выберите страну для ставки по скелетону: " << endl;
	bidSceleton = changeBid();
	cout << "Выберите страну для ставки по конькобежному спорту: " << endl;
	bidSkating = changeBid();
	cout << "Выберите страну для ставки по фигурному катанию: " << endl;
	bid_figureSkating = changeBid();
}
string Observer::changeBid()
{
point:
	cout << "|0| - Россия" << endl;
	cout << "|1| - Канада" << endl;
	cout << "|2| - Франция" << endl;
	cout << "|3| - Финляндия" << endl;
	cout << "|4| - Япония" << endl;
	int ans;
	cin >> ans;
	switch (ans)
	{
	case 0:
		return "Russia";
	case 1:
		return "Canada";
	case 2:
		return "France";
	case 3:
		return "Finland";
	case 4:
		return "Japan";
	default:
		cerr << "Некорректный ввод индекса страны. Возвращение на выбор..." << endl;
		goto point;
	}
}
void Observer::update(string in, int sport)
{
	if (bidBiathlon == in && sport == BIATHLON)
	{
		cout << "По биатлону ваша ставка прошла!" << endl; return;
	}
	else if (sport == BIATHLON)
	{
		cout << "По биатлону ваша ставка не прошла!" << endl; return;
	}
	if (bidSceleton == in && sport == SCELETON)
	{
		cout << "По скелетону ваша ставка прошла!" << endl; return;
	}
	else if (sport == SCELETON)
	{
		cout << "По скелетону ваша ставка не прошла!" << endl; return;
	}
	if (bidSkating == in && sport == SKATING)
	{
		cout << "По конькобежному спорту ваша ставка прошла!" << endl; return;
	}
	else if (sport == SKATING)
	{
		cout << "По конькобежному спорту ваша ставка не прошла!" << endl; return;
	}
	if (bid_figureSkating == in && sport == FIGURE_SKATING)
	{
		cout << "По фигурному катанию ваша ставка прошла!" << endl; return;
	}
	else if (sport == FIGURE_SKATING)
	{
		cout << "По фигурному катанию ваша ставка не прошла!" << endl; return;
	}
	cerr << "Некорректные переданные данные: указанная страна победитель " << in << endl;
}
//методы класса sportsman
istream& sportsman::setSportsman(istream& in)
{
	getline(in, family);
	getline(in, name);
	getline(in, secfamily);
	in >> power;
	in >> dexterity;
	in >> lacky;
	in >> stamina;
	return in;
}
float sportsman::getPhisData()//возвращает среднее между параметрами спортсмена
{
	float tmp = (power + dexterity + lacky + stamina) / 4.0;
	return tmp;
}
void sportsman::setCountry(string in)
{
	this->country = in;
}
//методы класса country

void country::createCountry(string filename)
{
	s = new sportsman();
	setFile(filename);
	initSportsman();
}
//инициализирует показатели спортсмена


void country::initSportsman()
{
	fs.open(filestring, ios_base::in);
	if (!fs.is_open())
	{
		cerr << "Файл с параметрами спортсмена не был открыт..." << endl;
		cerr << "Страна с которой возникла проблема: " << filestring << endl;
	}
	s->setCountry(filestring);
	s->setSportsman(fs);
	fs.close();
}
//устанавливает имя файла 
void country::setFile(string files)
{
	filestring = files;
}
//возвращает усредненные показатели спортсмена
float country::getPhisDataSportsman()
{
	return s->getPhisData();
}


//методы класса Olympians

void Olympian::subscribe(Observer* l)
{
	observers.push_back(l);
	cout << "Подписчик добавлен." << endl;
}
void Olympian::inform(int sport)
{
	for (int i = 0; i < observers.size(); i++)
	{
		cout << "Рассылка подписчику " << observers[i]->name << ":" << endl;
		observers[i]->update(winner, sport);
	}
}
//непосредственный процесс игры
void Olympian::Game()
{
	// создание стран, учавствующих в олимпийских играх
	Russia = new country();
	Canada = new country();
	France = new country();
	Finland = new country();
	Japan = new country();
	// инициализация стран, учавсвующих в ол.и.
	Russia->createCountry("russia.txt");
	Canada->createCountry("canada.txt");
	France->createCountry("france.txt");
	Finland->createCountry("finland.txt");
	Japan->createCountry("japan.txt");
	//биатлон, скелетон, конькобежный спорт, фигурное катание
	cout << "Результаты ставок по биатлону" << endl;
	winner = getResult();
	inform(BIATHLON);
	cout << "Результаты ставок по скелетону" << endl;
	winner = getResult();
	inform(SCELETON);
	cout << "Результаты ставок по конькобежному спорту" << endl;
	winner = getResult();
	inform(SKATING);
	cout << "Результаты ставок по фигурному катанию" << endl;
	winner = getResult();
	inform(FIGURE_SKATING);
}


Olympian::~Olympian()
{
	delete Russia;
	delete Canada;
	delete France;
	delete Finland;
	delete Japan;
	if (result != nullptr) delete[] result;
}

string Olympian::getResult()
{
	srand(time(NULL));
	Russia->k = Russia->getPhisDataSportsman() * (rand() % 100) / 100;
	srand(time(NULL));
	Canada->k = Canada->getPhisDataSportsman() * (rand() % 100) / 100;
	srand(time(NULL));
	France->k = France->getPhisDataSportsman() * (rand() % 100) / 100;
	srand(time(NULL));
	Finland->k = Finland->getPhisDataSportsman() * (rand() % 100) / 100;
	srand(time(NULL));
	Japan->k = Japan->getPhisDataSportsman() * (rand() % 100) / 100;

	string win = "Russia"; float wink = 0.0;
	if (wink < Canada->k)
	{
		win = "Canada";
		wink = Canada->k;
	}
	if (wink < France->k)
	{
		win = "France";
		wink = France->k;
	}
	if (wink < Finland->k)
	{
		win = "Finland";
		wink = France->k;
	}
	if (wink < Japan->k)
	{
		win = "Japan";
		wink = Japan->k;
	}
	return win;
}
