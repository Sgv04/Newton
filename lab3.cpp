#include <iostream>
#include <locale.h>
#include <cmath>
#include <stdio.h>
using namespace std;
double function(double a, double b, double c, double x1, double x2) {
	double f = a * pow(x1, 2) + b * x1 * x2 + c * pow(x2, 2);
	return f;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	double x1[20], x2[20], e1, e2;
	double f[20], f_x1[20], f_x2[20], grad[20];
	double A, B, C;
	int k, M, flag = 1;
	printf("Введите функцию вида f(x1, x2) = A * x1^2 + B * x1 * x2 + C * x2^2\n");
	printf("Введите через пробел A, B, C:\n");
	scanf_s("%lf %lf %lf", &A, &B, &C);
	printf("Введите через пробел X01 и X02:\n");
	scanf_s("%lf %lf", &x1[0], &x2[0]);
	printf("Введите через пробел e1 и e2:\n");
	scanf_s("%lf %lf", &e1, &e2);
	cout << "Введите М:\n";
	scanf_s("%d", &M);
	//A = 2, B = 0.5, C = 2, x1[0] = 1.5, x2[0] = 0.5, e1 = 0.15, e2 = 0.2, M = 10;
	printf("Дана функция f(x1, x2) = (%lf)*x1^2 + (%lf)*x1*x2 + (%lf)*x2^2\n", A, B, C);
	printf("Шаг 1: Заданы x0={%lf, %lf}, e1=%lf, e2=%lf, M=%d,\n\t grad[0] = (%lf * x1 + %lf * x2; %lf * x1 + %lf * x2) H = {%lf, %lf, %lf, %lf}\n", x1[0], x2[0], e1, e2, M, 2 * A, B, B, 2 * C, 2 * A, B, B, 2 * C);
	k = 0;
	printf("Шаг 2: k=0\n");
	while (flag) {
		printf("\n\nГруппа шагов %d:\n", k);
		f[k] = function(A, B, C, x1[k], x2[k]);
		f_x1[k] = 2 * A * x1[k] + B * x2[k];
		f_x2[k] = B * x1[k] + 2 * C * x2[k];
		cout << "Шаг 3: Вычисляем градиент grad(x[" << k << "]) = (" << f_x1[k] << ", " << f_x2[k] <<")\n";
		grad[k] = sqrt(pow(f_x1[k], 2) + pow(f_x2[k], 2));
		cout << "Шаг 4: Вычислим ||grad[" << k << "]|| = " << grad[k];
		if (grad[k] > e1) {
			printf("> %lf\n", e1);
			printf("Шаг 5: Проверим условие k>=M: ");
			if (k < M) {
				printf("k=%d < %d=M\n", k, M);
				double H[2][2];
				H[0][0] = 2 * A;
				H[0][1] = B;
				H[1][0] = B;
				H[1][1] = 2 * C;
				double detH = H[0][0] * H[1][1] - H[1][0] * H[0][1];
				printf("Шаг 6: Матрица H(x) = {%lf, %lf, %lf, %lf} = %lf\n", H[0][0], H[0][1], H[1][0], H[1][1], detH);
				double _H[2][2];
				_H[0][0] = (1 / detH) * H[1][1];
				_H[0][1] = (-1 / detH) * H[1][0];
				_H[1][0] = (-1 / detH) * H[0][1];
				_H[1][1] = (1 / detH) * H[0][0];
				double det_H = _H[0][0] * _H[1][1] - _H[1][0] * _H[0][1];
				printf("Шаг 7: Матрица H^-1(x) = {%lf, %lf, %lf, %lf} = %lf\n", _H[0][0], _H[0][1],
					_H[1][0], _H[1][1], det_H);
				printf("Шаг 8: Условие H^-1(x) > 0 выполнено\n");
				double d1 = -((_H[0][0] * f_x1[k]) + (_H[0][1] * f_x2[k]));
				double d2 = -((_H[1][0] * f_x1[k]) + (_H[1][1] * f_x2[k]));
				printf("Шаг 9: Определим d[%d] = -H^-1(x) * grad(x1, x1) = (%lf, %lf)\n", k, d1, d2);
				x1[k + 1] = x1[k] + 1 * d1;
				x2[k + 1] = x2[k] + 1 * d2;
				cout << "Шаг 10: Вычислим x[" << k + 1 << "] = x[" << k << "] + * d[" << k << "] = (" << x1[k + 1] << ", " << x2[k + 1] << ")\n";
					if (((sqrt(pow(x1[k + 1] - x1[k], 2) + pow(x2[k + 1] - x2[k], 2)) < e2) && (abs(f[k +1] - f[k]) < e2)) && ((sqrt(pow(x1[k] - x1[k - 1], 2) + pow(x2[k] - x2[k - 1], 2)) < e2) && (abs(f[k]- f[k - 1]) < e2))) 
					{
						printf("\t||x[%d]-x[%d]|| < e2\n", k + 1, k);
						f[k + 1] = function(A, B, C, x1[k + 1], x2[k + 1]);
						printf("Шаг 11: Оба условия выполнены, x = x[%d] = (%lf, %lf)\n", k + 1, x1[k + 1], x2[k + 1]);
						flag = 0;
					}
					else {
						printf("\t||x[%d]-x[%d]|| > e2, условие не выполнено\n", k + 1, k);
						k++;
						printf("\tk=%d\n", k);
					}
					f[k] = function(A, B, C, x1[k], x2[k]);
					cout << "f(" << x1[k] << ", " << x2[k] << ") = " << f[k];
			}
			else {
				printf("k=%d >= %d=M\n", k, M);
				f[k] = function(A, B, C, x1[k], x2[k]);
				cout << "f(" << x1[k] << ", " << x2[k] << ") = " << f[k];
				flag = 0;
			}
		}
		else {
			printf(" <= %lf\n", e1);
			f[k] = function(A, B, C, x1[k], x2[k]);
			cout << "f(" << x1[k] << ", " << x2[k] << ") = " << f[k];
			flag = 0;
		}
	}
}

