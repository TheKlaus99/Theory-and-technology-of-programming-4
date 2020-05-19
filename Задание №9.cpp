#include <stdio.h>
#include <iostream>
#include <math.h>
#include <locale>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define _USE_MATH_DEFINES

using namespace std;


/*long double series_arcsin(long double x, long double epsilon) {

	int n = 0;
	long double s = 0;
	long double term = x;

	do {
		s = s + term;
		term = term * (2 * n + 1) * (2 * n + 1) * x * x / ((2 * n + 2) * (2 * n + 3));
		n++;
	} while (fabs(term) >= epsilon);

	return s;
}*/


bool sinus(double x) {

	if ((-1 <= x) && (x <= 1)) {
		return true;
	}
	else {
		return false;
	}

}


int main() {
	setlocale(LC_ALL, "Russian");


	HINSTANCE hLib = LoadLibrary(L"Lab_9.dll");
	if (hLib == NULL)
	{
		cout << "Ошибка! Не удается загрузить библиотеку! " << endl;
		return 0;
	}


	cout << "Загружаем библиотеку... " << endl << endl;
	typedef double (*Func)(long double, long double);

	auto pFunction = (Func)GetProcAddress(hLib, "series_arcsin");

	if (pFunction == NULL)
	{
		cout << "Не удается загрузить функцию! " << endl;
		FreeLibrary(hLib);
		return 0;
	}


	long double eps;
	long double s, e, d, id;
	int n;

	cout << "Введите точность эпсилон: ";
	cin >> eps;

	if (eps <= 0) {
		cout << endl << "Ошибка! Точность эпсилон должна быть вещественным положительным числом! " << endl << endl;
		system("pause");
		return 0;
	}

	cout << endl;

	cout << "Введите начальный X(начальное) от -1 до 1: ";
	cin >> s;

	if (!sinus(s)) {
		cout << endl << "Ошибка! X(начальное) должен быть вещественным числом, лежащим в интервале от -1 до 1! " << endl << endl;
		system("pause");
		return 0;
	}

	if (cin.fail()) {
		cout << endl << "Ошибка! Разрешены только числовое значение! " << endl << endl;
		return 0;
		system("pause");
	}

	cout << endl;

	cout << "Введите конечный X(конечное) от -1 до 1: ";
	cin >> e;

	if (!sinus(e)) {
		cout << endl << "Ошибка! X(конечное) должен быть вещественным числом, лежащим в интервале от -1 до 1! " << endl << endl;
		system("pause");
		return 0;
	}

	if (cin.fail()) {
		cout << endl << "Ошибка! Разрешены только числовое значение! " << endl << endl;
		return 0;
		system("pause");
	}

	if (e < s) {
		cout << "X(начальное) не должен превосходить X(конечное)! " << endl;
		system("pause");
		return 0;
	}

	cout << endl;

	cout << "Введите интервал Дельта X: ";
	cin >> d;

	if (d <= 0) {
		cout << "Ошибка! Интервал Дельта X должен быть положительным! " << endl << endl;
		system("pause");
		return 0;
	}

	cout << endl;

	printf("------------------------------------------------------------------------\n");

	printf("|        X       | Моя функция (X) | Функция (X)     | Шаг (X)         |\n");

	printf("------------------------------------------------------------------------\n");

	for (long double x = s; x <= e; x = x + d) {
		x = 10000000 * x;
		x = round(x);
		x = x / 10000000;
		long double Delta = sqrt(fabs(asin(x) * asin(x) - pFunction(x, eps) * pFunction(x, eps)));

		printf("|%15.9lf | %15.9lf | %15.9lf | %15.9lf | \n", x, pFunction(x, eps), asin(x), Delta);
	}

	printf("------------------------------------------------------------------------\n");

	cout << endl;

	cout << "Введите значение X(идеальное) для точного расчета от -1 до 1: ";
	cin >> id;

	if (!sinus(id)) {
		cout << endl << "X(идеальное) должен быть вещественным числом, лежащим в интервале от -1 до 1! " << endl << endl;
		system("pause");
		return 0;
	}

	if (cin.fail()) {
		cout << endl << "Ошибка! Разрешены только числовое значение! " << endl << endl;
		return 0;
		system("pause");
	}

	cout << endl;

	printf("------------------------------------------------------------------------\n");

	printf("|Точность эпсилон| Моя функция (X) | Функция (X)     | Шаг (X)         |\n");

	printf("------------------------------------------------------------------------\n");

	long double tochnost = 0.1;

	for (int i = 1; i < 8; i++) {
		long double d_i = sqrt(fabs(asin(id) * asin(id) - pFunction(id, tochnost) * pFunction(id, tochnost)));
		printf("|%15.7lf | %15.9lf | %15.9lf | %15.9lf | \n", tochnost, pFunction(id, tochnost), asin(id), d_i);
		tochnost = tochnost * 0.1;
	}

	printf("------------------------------------------------------------------------\n");

	cout << endl;

	system("pause");

	return 0;
}
