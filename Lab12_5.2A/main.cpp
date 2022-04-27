#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
using namespace std;

#pragma region "Прізвища студентів"
string surnames[] =
{
	"Бурачинський",
	"Кваша",
	"Попенко",
	"Жученко",
	"Пероганич",
	"Карпінський",
	"Дроб\'язко",
	"Боровий",
	"Приступа",
	"Костюк",

	"Гайдук",
	"Грицина",
	"Балога",
	"Величковська",
	"Марченко",
	"Бершеда",
	"Лимаренко",
	"Кравченко",
	"Ластівка",
	"Бельська",
};
#pragma endregion

enum class Spec { PZ, IT, KN, AT };
string strSpec[] = { "Програмне забезпечення", "Інформаційні технології", "Компютерні науки", "Автомобільний транспорт" };

struct Student
{
	string surname;
	int course;
	Spec spec;
	double mark_physic;
	double mark_math;
	double mark_informatic;
};

Student Generate()
{
	Student s;

	s.surname = surnames[rand() % 20];
	s.course = 1 + rand() % 6;
	s.spec = Spec(rand() % 4);

	s.mark_informatic = (30 + rand() % 20) / 10.0;
	s.mark_physic = (30 + rand() % 20) / 10.0;
	s.mark_math = (30 + rand() % 20) / 10.0;
	return s;
}

void generate_to_file(string path, size_t cnt)
{
	fstream f(path, ios::binary | ios::out);
	if (f.is_open())
	{
		f.write((char*)&cnt, sizeof(cnt));
		for (size_t i = 0; i < cnt; i++)
		{
			Student s = Generate();
			size_t l = s.surname.length()+1;
			f.write((char*)&l, sizeof(l));
			f.write(s.surname.c_str(), l);
			f.write((char*)&s.course, sizeof(int));
			f.write((char*)&s.spec, sizeof(Spec));
			f.write((char*)&s.mark_physic, sizeof(double));
			f.write((char*)&s.mark_math, sizeof(double));
			f.write((char*)&s.mark_informatic, sizeof(double));
		}
	}
	else
		cout << "load_to_file()" << endl;
	f.close();
}

double avgMark(Student s)
{
	return (s.mark_informatic + s.mark_math + s.mark_physic) / 3.;
}

int CountStudent(string path)
{
	fstream f(path, ios::binary | ios::in);
	int count = 0;
	if (f.is_open())
	{
		size_t cnt;
		f.read((char*)&cnt, sizeof(size_t));
		for (size_t i = 0; i < cnt; i++)
		{
			Student s;
			size_t c;
			f.read((char*)&c, sizeof(size_t));
			char* data = new char[c];
			f.read(data, c);
			s.surname = data;
			delete[] data;
			f.read((char*)&s.course, sizeof(int));
			f.read((char*)&s.spec, sizeof(Spec));
			f.read((char*)&s.mark_physic, sizeof(double));
			f.read((char*)&s.mark_math, sizeof(double));
			f.read((char*)&s.mark_informatic, sizeof(double));
			
			if (avgMark(s) > 4.5)
				count++;
		}
	}
	else
		cout << "CountStudent()" << endl;
	f.close();

	return count;
}

void display(string path)
{
	fstream f(path, ios::binary | ios::in);
	if (f.is_open())
	{
		cout << "---------------------------------------------------------------------------------------------" << endl;
		cout << "|  №  | курс |    прізвище    |       спеціальність     | фізика | математика | інформатика |" << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		cout << left;
		size_t cnt;
		f.read((char*)&cnt, sizeof(size_t));
		for (size_t i = 0; i < cnt; i++)
		{
			Student s;
			size_t c;
			f.read((char*)&c, sizeof(size_t));
			char* data = new char[c];
			f.read(data, c);
			s.surname = data;
			delete[] data;
			f.read((char*)&s.course, sizeof(int));
			f.read((char*)&s.spec, sizeof(Spec));
			f.read((char*)&s.mark_physic, sizeof(double));
			f.read((char*)&s.mark_math, sizeof(double));
			f.read((char*)&s.mark_informatic, sizeof(double));

			cout << "|" << setw(5) << i+1 << "|"
				<< setw(6) << s.course << "|"
				<< setw(16) << s.surname << "|"
				<< setw(25) << strSpec[int(s.spec)] << "|"
				<< setw(8) << s.mark_physic << "|"
				<< setw(12) << s.mark_math << "|"
				<< setw(13) << s.mark_informatic << "|" << endl;
		}
		cout << "---------------------------------------------------------------------------------------------" << endl;
	}
	else
		cout << "display()" << endl;
	f.close();
}

enum class Mark { math, physic, informatic, nothing };
string strMark[] = { "математика", "фізика", "інформатика" };
void BestSubject(string path, Mark mark[3])
{
	fstream f(path, ios::binary | ios::in);
	if (f.is_open())
	{
		size_t cnt;
		double math = 0, physic = 0, informatic = 0;
		f.read((char*)&cnt, sizeof(size_t));
		for (size_t i = 0; i < cnt; i++)
		{
			Student s;
			size_t c;
			f.read((char*)&c, sizeof(size_t));
			char* data = new char[c];
			f.read(data, c);
			s.surname = data;
			delete[] data;
			f.read((char*)&s.course, sizeof(int));
			f.read((char*)&s.spec, sizeof(Spec));
			f.read((char*)&s.mark_physic, sizeof(double));
			f.read((char*)&s.mark_math, sizeof(double));
			f.read((char*)&s.mark_informatic, sizeof(double));

			math += s.mark_math;
			physic += s.mark_physic;
			informatic += s.mark_informatic;
		}

		math /= cnt;
		physic /= cnt;
		informatic /= cnt;

		for (size_t i = 0; i < 3; i++)
			mark[i] = Mark::nothing;

		double m = math;
		int i = 0;
		mark[i] = Mark::math;
		if (physic > m)
		{
			m = physic;
			mark[i] = Mark::physic;
		}
		if (informatic > m)
		{
			m = informatic;
			mark[i] = Mark::informatic;
		}
		if (m == math && mark[i] != Mark::math)
			mark[++i] = Mark::math;
		if (m == physic && mark[i] != Mark::physic)
			mark[++i] = Mark::physic;
		if (m == informatic && mark[i] != Mark::informatic)
			mark[++i] = Mark::informatic;
	}
	else
		cout << "CountStudent()" << endl;
	f.close();
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path;
	cout << "Введіть файл: "; getline(cin, path);
	
	display(path);
	cout << "Кількість студентів, середній бал яких вищий за 4,5: " << CountStudent(path) << endl;
	cout << "Предмет, середній бал якого найбільший: ";
	Mark m[3];
	BestSubject(path, m);
	for (size_t i = 0; i < 3; i++)
		if (m[i] != Mark::nothing)
			cout << strMark[(int)m[i]] << " ";
	cout << endl;
	return 0;
}