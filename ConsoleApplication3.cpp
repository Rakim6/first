//Программа для записи деталей, сохраняет название детали, кол-во выпущенных и день недели выпуска
#include <string>
#include <iostream> 
#include <iomanip> 
#include <string> 
#include <fstream> 
#include <cstdio> 
using namespace std;
//Глобавльные переменные 
int alldetali, summ; //Переменная кол-ва книг 
string fileimya; //Переменная названия создаваемого файла 

//Структура книги, которая объединяет в себе параметры 
struct detal
{
	string nazvanie;
	int Kolvo;
	char denned;
}*a;//Указатель на структуру(для удобства вызова) 

//Перед использованием функиций, необходимо их объявить(почти как переменные) 
void detaliin();
void detalisort();
void detaliscreen();
void detaliscreen1();
void QuickSortKolvo();
void Vstavki();
void linemenu();
void plusdetal();
void minusdetal();

//Функция меню и ее тело 
void menu()
{
	int a; //Переменная выбранного пункта 
	cout << "Учет деталей" << endl;
	cout << "1. Ввод деталей в таблицу" << endl;
	cout << "2. Сортировка деталей" << endl;
	cout << "3. Показать файл" << endl;
	cout << "4. Редактирование файла" << endl;
	cout << "5.Завершение работы" << endl;
	cout << "Ваш выбор: ";
	cin >> a;
	switch (a)
	{
	case 1: detaliin(); break; //В кейсах указываешь функцию 
	case 2: detalisort(); break;
	case 3: detaliscreen(); break;
	case 4: linemenu(); break;
	case 5: cout << "Завершение работы"; exit(0);
	default: cout << "Ошибка" << endl;
	}
}
//Функция ввода книг и их сохранение 
void detaliin()
{
	char otvet;
	cout << "Сколько деталей? ";
	cin >> alldetali; //Запоминает кол-во книг(1 книга - 1 строка) 
	a = new detal[alldetali]; //Создаем структуру с указанным кол-вом строк 
	for (int i = 0; i < alldetali; i++)
	{
		cout << "Деталь #" << i + 1 << endl;
		cout << "Введите название детали: ";
		cin >> a[i].nazvanie;//Как пример тут видно как пользоваться структурами 
		cout << "Введите количество: ";
		cin >> a[i].Kolvo;
		cout << "День недели, когда выпущена?(M-S): ";
		cin >> a[i].denned;
	}
	cout << "Сохранить данные в файл?(+/-) ";
	cin >> otvet;
	if (otvet == '+')
	{
		char answer;
		cout << "Имя файла: ";
		cin >> fileimya; //Переменная имени файла, обязательно пишем с расширением 
		ofstream fout(fileimya); //Создание этого файла 
		for (int i = 0; i < alldetali; i++)
			fout << a[i].nazvanie << " " << a[i].Kolvo << " " << a[i].denned << endl; //Записываем данные в файл 
		ifstream fin; //Класс, что бы начать считывание файла(вместо fin можно что угодно) 
		fin.open(fileimya);//Открываем файл 
		do
		{
			fin >> a[summ].nazvanie >> a[summ].Kolvo >> a[summ].denned;//Считываем файл, тк в конце создается пустая строка(из-за неё потом не работает QuickSort) 
			summ++;
		} while (fin.good());//Условие означает что цикл работает пока считывается файл 
		cout << "Показать готовый файл?(+/-) ";
		cin >> answer;
		if (answer == '+')
			detaliscreen(); //Вызов функции отображения 
		if (answer == '-')
			menu();//Возвращаемся в менюшку 

	}
	if (otvet == '-')
		menu();

}
//Функция вывода на экран 
void detaliscreen1()
{
	ifstream fin; //Класс, что бы начать считывание файла(вместо fin можно что угодно) 
	fin.open(fileimya);//Открываем файл 
	summ = 0;
	do
	{
		fin >> a[summ].nazvanie >> a[summ].Kolvo >> a[summ].denned;//Считываем файл, тк в конце создается пустая строка(из-за неё потом не работает QuickSort) 
		summ++;
	} while (fin.good());
	cout << setw(28) << "Название" << setw(17) << "Количество" << setw(20) << "День выпуска" << endl;//Делаем шапку 
	for (int i = 0; i < alldetali; i++)
		cout << setw(3) << i + 1 << setw(15) << a[i].nazvanie << setw(15) << a[i].Kolvo << setw(15) << a[i].denned << endl;//Выводим данные из переменных на экран 
	menu();//Возвращаемся в менюшку 
}

void detaliscreen()
{
	cout << setw(28) << "Название" << setw(17) << "Количество" << setw(20) << "День выпуска" << endl;//Делаем шапку 
	for (int i = 0; i < alldetali; i++)
		cout << setw(3) << i + 1 << setw(15) << a[i].nazvanie << setw(15) << a[i].Kolvo << setw(15) << a[i].denned << endl;//Выводим данные из переменных на экран 
	menu();//Возвращаемся в менюшку 
}
//Подменю сортировки 
void detalisort()
{
	int s;
	cout << "Сортировка деталей" << endl;
	cout << "1. Вставками" << endl;
	cout << "2. QuickSort" << endl;
	cout << "3. Назад в меню" << endl;
	cout << "Ваш выбор: ";
	cin >> s;
	switch (s)
	{
	case 1: Vstavki(); break;
	case 2: QuickSortKolvo(); break;
	case 3: menu(); break;
	default: cout << "Ошибка" << endl;
	}
}

//QuickSort сортирующий по году 
void QuickSortKolvo()
{
	int i = 0, j = alldetali;
	float p;
	p = j / 2; //Находит среднюю строку(Пример: из 3х строк средней будет 2я) 
	do
	{
		while (a[i].Kolvo < p) i++;
		while (a[j].Kolvo > p) j--;

		if (i <= j)
		{
			swap(a[i++], a[j--]); //Меняет строки местами 
		}

	} while (i <= j);
	cout << endl;
	detaliscreen();//Функция вывода на экран 
}

void Vstavki()
{
	for (int i = 1; i <= alldetali; i++)
	{
		for (int j = i - 1; j > 0 && a[j - 1].Kolvo < a[j].Kolvo; j--)
		{
			swap(a[j - 1], a[j]);
		}

	}
	cout << endl;
	detaliscreen();
}

void linemenu()
{
	int d;
	cout << "Редактирование файла" << endl;
	cout << "1. Добавить новую деталь" << endl;
	cout << "2. Удалить последнюю деталь" << endl;
	cout << "Ваш выбор: ";
	cin >> d;
	switch (d)
	{
	case 1: plusdetal();
	case 2: minusdetal();
	default: cout << "Ошибка" << endl;;
	}

}

void plusdetal()//Добавление строк в конец файла 
{
	int h;
	ofstream fout;
	fout.open(fileimya, ios::app);//ios::app переводит курсор в конец файла, что бы записывать начал в конец 
	cout << "Сколько деталей добавить? ";
	cin >> h;
	a = new detal[alldetali + h];
	int summ1 = summ;
	for (int i = 0; i < h; i++)
	{
		cout << "Деталь №" << alldetali + i + 1 << endl;
		cout << "Введите название детали: ";
		cin >> a[alldetali + i].nazvanie;
		cout << "Введите количество: ";
		cin >> a[alldetali + i].Kolvo;
		cout << "День недели, когда выпущена?(M-S): ";
		cin >> a[alldetali + i].denned;
		fout << a[alldetali + i].nazvanie << " " << a[alldetali + i].Kolvo << " " << a[alldetali + i].denned << endl;
	}
	alldetali = alldetali + h;//Перезаписываем кол-во книг/строк 
	detaliscreen1();
}

void minusdetal()
{
	char l;
	cout << "\t\tУдаление последнего студента" << endl;
	cout << setw(28) << "Название" << setw(17) << "Количество" << setw(20) << "День выпуска" << endl;
	for (int i = 0; i < alldetali; i++)
		cout << setw(3) << i + 1 << setw(20) << a[i].nazvanie << setw(20) << a[i].Kolvo << setw(20) << a[i].denned << endl;
	cout << "Вы согласны?(+/-) ";
	cin >> l;
	summ = 0;
	if (l == '+')
	{
		ofstream fout(fileimya);
		for (int d = 0; d < alldetali - 1; d++)
		{
			fout << a[summ].nazvanie << " " << a[summ].Kolvo << " " << a[summ].denned << endl;
			summ++;
		}
	}
	if (l == '-')
	{
		menu();
	}

	alldetali = alldetali - 1;
	detaliscreen1();
}

int main()
{
	setlocale(LC_ALL, "rus");
	string* kbrdLog = new string, * kbrdPss = new string, * userAnsr = new string; // Объявление переменных string 
	string AdminLog = "log1", AdminPss = "pass1", UserLog = "log2", UserPss = "pass2"; // Логины и пароли 
	for (int perebor = 0; perebor < 3; perebor++)
	{
		cout << "Введите логин: ";
		cin >> *kbrdLog; // Ввод логина 
		if (*kbrdLog == AdminLog || *kbrdLog == UserLog) // Проверка логинов с теми, что уже внесены 
		{
			for (int i = 0; i < 3; i++)
			{
				cout << "Введите пароль " << *kbrdLog << ": ";
				cin >> *kbrdPss; // Ввод пароля 
				if (*kbrdLog == AdminLog && *kbrdPss == AdminPss) // Проверка совпадения логина и пароля Administrator 
				{
					cout << "Вошел как log1\n";
					menu();
				}
				else // Если не Administrator 
				{
					if (*kbrdLog == UserLog && *kbrdPss == UserPss) // Проверка логина и пароля User 
					{
						cout << "Вошел как log2\n";
						menu();
					}
					else // Если пароль не совпадает, то выводится это 
						cout << "Неправильный пароль\n";
					if (i == 2) // Если совершено 3 попытки, программа завершается 
					{
						cout << "Неавторизированный доступ";
						return 0;
					}

				}

			}

		}
		else // Если логин не совпадает 
		{
			cout << "Неверный логин\n";
		}
		if (perebor == 2) // Если совершено 3 попытки, программа завершается 
		{
			cout << "Неавторизированный доступ. Выход...";
			return 0;
		}

	}

}