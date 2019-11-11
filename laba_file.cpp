
#include <iostream>
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>

using namespace std;

class book //создаение класса под названием book
{
public:// при помощи модитификатора " public" объявляем открытые поля и методы класса book

	book();
	book(char* , char* , int);
	void show_book();


protected: // при помощи модитификатора " private " объявляем закрытые поля класса book

	char title[40];
	char author[40];
	int pages;
};

book::book()//конструктор по умолчанию
{
}

book::book(char* title , char* author , int pages) // создаем конструктор класса book
{
	strcpy(this->title , title); // указатель на адрес объекта класса
	strcpy(this->author , author);
	this->pages = pages;
}

void book::show_book() // описывае функцию для вывода резултьтатов на экран
{
	cout << "_____________________________________________________________________" << endl;
	cout << " Заголовок '' " << title << " '' " << endl;
	cout << " Автор - " << author << endl;
	cout << "Количество страниц - " << pages << endl;
}

int static tmp_card=0;//переменная которая будет хранить тукущее количество объектов library_card

class library_card :public book // создаем класс library_card,который является наследником класса book
{
public://объявляем открытые поля класса library_card

	library_card();
	library_card(char*, char*, int, char*, int); //создаём интерыейс класса
	void show_card();
	void add_one_card(char*, char*, int, char*, int);
	void add_cards(int , library_card* );
	bool search( char* );

private://объявляем закрытые поля класса library_card

	char catalog[30];
	bool checked_out;
};

bool library_card::search( char* title)//функция для поиска элемента с данным названием
{
	if (strcmp(this->title,title)==0)
		return true;
	else
	{
		return false;
	}
}

void library_card::add_cards(int max_tmp_card,  library_card* library)//заполняем массив library_cards данными
{
	char title[40];
	char author[40];
	int pages;
	char cat[30];
	int check;
	
	int i = 0;
	char z;
	do
	{
		cout << "Ведите название книги   ";  cin >> title;
		cout << "Введите имя автора   ";  cin >> author;
		cout << "Введите число страниц   ";  cin >> pages;
		cout << "Введите жанр ";  cin >> cat;
		cout << "Введите отметку о проверке ";  cin >> check;
		library[i]=library_card(title, author, pages, cat, check);
		tmp_card++;
		i++;
		cout << "Будете вводить еще?(y/n)";
		cin >> z;
	} while (z=='y' && i < max_tmp_card);
}

void library_card::add_one_card(char* title, char* author, int pages, char* catalog, int checked_out)
{
	strcpy(this->title ,title); 
	strcpy(this->author , author);
	this->pages = pages;
	strcpy(this->catalog , catalog);
	this->checked_out = checked_out;
	tmp_card++;//увеличим начение общего количества объектов, тк мы добавляем новый
}

library_card::library_card()//конструктор по умолчанию
{

}

library_card::library_card(char* title, char* author, int pages, char* catalog, int checked_out) :book(title, author, pages) //вызываем конструктор
{
	strcpy(this->catalog , catalog); 
	this->checked_out = checked_out;
}

void library_card::show_card()
{

	show_book(); // вызов функции базового класса
	cout << " catalog: " << catalog << endl;
	//создаём проверку
	if
		(checked_out == 1) cout << " ПРОВЕРКА БЫЛА СОВЕРШЕННА " << endl;
	else
		cout << " ПРОВЕРКИ НЕ БЫЛО" << endl;
	cout << "______________________________________________________________" << endl;
}

class File
{
private:
	ifstream tmp_read;
	ofstream tmp_write;

	char file_name[20];
	library_card tmp;
public:
	File()
	{
		cout << "Введите имя файла" << endl;
		cin >> file_name;
	}
	
	void f_read(); //читаем данные из файла
	void f_write(library_card*library);//записываем данные в файл
	void add();//добавляем одиночную library_card в файл
	void del();//удаляем один объект из файла
	void menu(library_card*);//меню для работы с файлом
};

void File::menu(library_card*library)
{
	int i;
	char z;
	do
	{
		cout << "1. Записать в файл " << endl;
		cout << "2. Прочитать из файла " << endl;
		cout << "3. Добавить в файл" << endl;
		cout << "4. Удалить из файла " << endl;
		cin >> i;
		switch (i)
		{
		case 1: f_write(library); break;
		case 2: f_read(); break;
		case 3: add(); break;
		case 4: del(); break;
		default:
			cout << "Выберите верный пункт " << endl;
			break;
		}
		cout << "Будете еще работать с файлом?(y/n)" << endl;
		cin >> z;
	} while (z=='y');
}

void File:: f_read() //читаем данные из файла
{
	tmp_read.open(file_name);
	if (!tmp_read.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	while (tmp_read.read((char*)&tmp, sizeof(library_card)))
	{
		tmp.show_card();
	}
	cout << endl;
	tmp_read.close();
}

void File::f_write(library_card*library) //записываем данные в файл
{
	tmp_write.open(file_name, ofstream::app);
	if (!tmp_write.is_open()) 
	{
		cout << "Ошибка открытия файла" << endl;
	}
	for (int i = 0; i < tmp_card; i++)
	{
		tmp_write.write((char*)&library[i], sizeof(library_card));
	}
	tmp_write.close();
}

void File::add()
{
	tmp_write.open(file_name, ofstream::app);
	if (!tmp_write.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}

	char title[40];
	char author[40];
	int pages;
	char cat[30];
	int check;

	char z;
	do
	{
		cout << "Ведите название книги   ";  cin >> title;
		cout << "Введите имя автора   ";  cin >> author;
		cout << "Введите число страниц   ";  cin >> pages;
		cout << "Введите жанр ";  cin >> cat;
		cout << "Введите отметку о проверке ";  cin >> check;
		tmp.add_one_card(title, author, pages, cat, check); //создание объекта производного класса
		tmp_write.write((char*)&tmp, sizeof(library_card));
		cout << "Будете вводить еще?(y/n)";
		cin >> z;
	} while (z == 'y');

	tmp_write.close();
}

void File::del()
{
	tmp_read.open(file_name);
	if (!tmp_read.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	library_card* tmp_library = new library_card[tmp_card];
	int i = 0;
	bool flag=false;

	cout << "Введите имя книги, карточку которой хотите удалить" << endl;
	char title[40];
	cin >> title;
	while (tmp_read.read((char*)&tmp, sizeof(library_card)))
	{
		if (tmp.search(title))
		{
			tmp_card--;
			flag = true;//если найден элемент, который мы будем удалять
		}
			
		else
			tmp_library[i++] = tmp;
			
	}
	tmp_read.close();

	cout << endl;
	//перезаписываем файл актуальными данными после удаления элемента
	if (flag)
	{
		tmp_write.open(file_name, ofstream::trunc);
		if (!tmp_write.is_open())
		{
			cout << "Ошибка открытия файла" << endl;
		}
		for (int i = 0; i < tmp_card; i++)
		{
			tmp_write.write((char*)&tmp_library[i], sizeof(library_card));
		}
		tmp_write.close();
	}
	else
		cout << "Не найдено подходящего для удаления элемента" << endl;
}

class Worker//вспомогательный класс, который обеспечивает доступ к классу library_card
{
private:
	library_card tmp_work;
public:
	void work(int, library_card*);
};

void Worker::work(int max_tmp_card, library_card* library)
{
	tmp_work.add_cards(max_tmp_card, library);
}

int main()
{
	setlocale(LC_ALL, "rus");
	//char file_name[20] = "New_File.txt";//Записываем имя файла для работы с ним
	cout << " Выполнила Надежда Рожковец " << endl;

	cout << "Введите количество карточек в библиотеке " << endl;
	int max_tmp_card;
	cin >> max_tmp_card;
	
	library_card *library = new library_card[max_tmp_card];
	

	Worker work_obj;
	work_obj.work(max_tmp_card, library);


	//char title[40] = " Алиса в Стране Чудес "; // выделяем память и присваеваем нужное значение для названия
	//char author[40] = " Кэрролл Л.";// выделяем память и присваеваем нужное значение для автора
	//book obj(title, author, 324); //создаём объекта класса
	//char cat[30] = " Сказки ";
	//library_card ob(title, author, 144, cat, 1); //создание объекта производного класса
	
	File obj_file;
	obj_file.menu(library);
	/*obj_file.f_write();
	obj_file.f_read();*/

}
