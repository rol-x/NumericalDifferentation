#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

double f(double x)										// Hard-coded function for numerical analysis.
{
	return x * x*x - 2 * x*x + 3 * x - 6;
}

double forwardDifferenceAt(double x, double h, int n)		// D^n[f(x)] = D[D^(n-1)[f(x+h)] - D^(n-1)[f(x)]]
{
	if (n == 1)
		return f(x + h) - f(x);
	return forwardDifferenceAt(x + h, h, n - 1) - forwardDifferenceAt(x, h, n - 1);
}

double firstDerivativeValueAt(double x, double h, int n)
{
	double finalValue = 0;
	double formulaPart = 0;
	for (int i = 1; i <= n; i++)
	{
		formulaPart = forwardDifferenceAt(x, h, i);		// i-th forward difference at point x, with step h (up to n-th difference)
		if (i % 2)
			formulaPart /= i;							// f, 1/3 f, 1/5 f, 1/7 f, etc
		else
			formulaPart /= -i;							// -1/2 f, -1/4 f, -1/6 f, etc
		finalValue += formulaPart;
	}
	return finalValue / h;
}

double * getSecondOrderCoefficients(double * initialCoefficients, int n)
{
	double * secondCoefficients = new double[n + 1];
	for (int i = 0; i <= n; i++)
		secondCoefficients[i] = 0;
	for (int i = 1; i < (n + 1) / 2; i++)
		for (int j = 1; j < (n + 1) / 2; j++)
			secondCoefficients[i + j] += initialCoefficients[i] * initialCoefficients[j];
	//for (int i = 0; i <= n; i++)
	//	cout << "\n/\\" << i << ": " << secondCoefficients[i];
	//system("pause");
	return secondCoefficients;
}

double secondDerivativeValueAt(double x, double h, int n)
{
	double finalValue = 0;
	double formulaPart = 0;
	double * initialCoefficients = new double[(n + 1) / 2];		// size = ceil[n/2]
	for (int i = 1; i <= n / 2; i++)	// for the sake of easy computation we treat i=0 as 'zero difference' which is not used
		initialCoefficients[i] = 1 / i * pow(-1, (i + 1) % 2);
	auto secondCoefficients = getSecondOrderCoefficients(initialCoefficients, n);
	for (int i = 2; i <= n; i++)
		finalValue += forwardDifferenceAt(x, h, i) * secondCoefficients[i];
	return finalValue / (h * h);
}

double derivativeValueAt(double x, double h, int n, int k)
{
	return k == 1 ? firstDerivativeValueAt(x, h, n) : secondDerivativeValueAt(x, h, n);
}

int factorial(int n)
{
	return n == 1 ? 1 : n * factorial(n - 1);
}

double errorAt(double x, double h, int n)
{
	return (forwardDifferenceAt(x, h, n + 1) / h) / factorial(n);
}

void initializeValues(int &n, double &h, double &x)
{
	system("cls");
	cout << "Enter n - the maximum order of the difference operator: ";
	cin >> n;
	cout << "Enter h - step used to determine the value of the difference operator: ";
	cin >> h;
	cout << "Enter x - the point at which the value of the derivative should be determined: ";
	cin >> x;
}

void solveForAccuracy(double x, double h, int n)
{
	double accuracy;
	double newH = h;											// New Age (pun intended)
	cout << "Enter wanted approximation accuracy: ";
	cin >> accuracy;
	do
	{
		if (accuracy < errorAt(x, newH, n))						// We tweak newH up and down, so that its error is very close to wanted accuracy
			newH *= 0.95;
		if (accuracy > errorAt(x, newH, n))
			newH *= 1.05;
	} while (abs(accuracy - abs(errorAt(x, newH, n))) > 0.0000001);
	cout << "The step value h for accuracy of " << accuracy << " is " << newH << endl;
	system("pause");
}

int main()
{
	int n, k = 1;
	double h, xi;
	initializeValues(n, h, xi);

	bool alive = true;
	while (alive)
	{
		system("cls");
		cout << "Enter n - the maximum order of the difference operator: " << n << endl;
		cout << "Enter h - step used to determine the value of the difference operator: " << h << endl;
		cout << "Enter xi - the point at which the value of the derivative should be determined: " << xi << endl << endl;
		cout << "Derivative (" << k << ") value at " << xi << " of x^3 - 2x^2 + 3x - 6: ";
		cout << derivativeValueAt(xi, h, n, k) << endl;
		cout << "Error at " << xi << ": " << errorAt(xi, h, n) << endl << endl;
		cout << "Require accuracy\t[A]\nReinitialize values\t[R]" << endl;
		cout << "Change derivative order\t[1 / 2]\nTweak (n)\t\t[B / M]\nTweak (h)\t\t[G / J]\nTweak (xi)\t\t[Z / C]" << endl;
		cout << "Quit\t\t\t[Esc]" << endl << endl;

		switch (_getch())
		{
		case 'a':
		case 'A':
			solveForAccuracy(xi, h, n);
			break;
		case 'r':
		case 'R':
			k = 1;
			initializeValues(n, h, xi);
			break;
		case 'b':
		case 'B':
			if (n > 1)
				n--;
			break;
		case 'm':
		case 'M':
			n++;
			break;
		case 'g':
		case 'G':
			if (h > 0.01)
				h -= 0.01;
			break;
		case 'j':
		case 'J':
			h += 0.01;
			break;
		case 'z':
		case 'Z':
			xi -= 0.01;
			break;
		case 'c':
		case 'C':
			xi += 0.01;
			break;
		case '1':
			k = 1;
			break;
		case '2':
			k = 2;
			break;
		case 27:
			alive = false;
			break;
		default:
			break;
		}
	}
	cout << endl;
	return 0;
}