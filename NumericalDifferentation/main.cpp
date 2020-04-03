#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

double f(double x)										// Hard-coded function for numerical analysis.
{
	return log(x);
}

double forwardDifferenceAt(double x, double h, int n)		// D^n[f(x)] = D[D^(n-1)[f(x+h)] - D^(n-1)[f(x)]]
{
	if (n == 1)
		return f(x + h) - f(x);
	return forwardDifferenceAt(x + h, h, n - 1) - forwardDifferenceAt(x, h, n - 1);
}

double * getSecondOrderCoefficients(double * initialCoefficients, int n)
{
	double * secondCoefficients = new double[n + 1];
	for (int i = 0; i <= n; i++)
		secondCoefficients[i] = 0;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			if (i + j <= n)						// we don't care about the coefficients beyond n
				secondCoefficients[i + j] += initialCoefficients[i] * initialCoefficients[j];
			else
				continue;
	for (int i = 0; i <= n; i++)
	return secondCoefficients;
}

double derivativeValueAt(double x, double h, int n, int k)
{
	double finalValue = 0;
	double * initialCoefficients = new double[n + 1];
	initialCoefficients[0] = 0;
	for (int i = 1; i <= n; i++)
		initialCoefficients[i] = pow(-1, (i + 1) % 2) / i;		// oscilating harmonic series

	double * coefficients;
	if (k == 1)
		coefficients = initialCoefficients;
	else
		coefficients = getSecondOrderCoefficients(initialCoefficients, n);

	for (int i = 2; i <= n; i++)
		finalValue += forwardDifferenceAt(x, h, i) * coefficients[i];
	return k == 1 ? finalValue / h : finalValue / (h * h);
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
	double newN = n;
	cout << "Enter wanted approximation accuracy: ";
	cin >> accuracy;
	
	do
	{
		if (accuracy > errorAt(x, newH, n))						// We tweak newH up and down, so that its error is very close to wanted accuracy
			newH *= 0.98;
		if (accuracy < errorAt(x, newH, n))
			newH *= 1.02;
	} while (abs(accuracy - abs(errorAt(x, newH, n))) > 0.001);
	
	while (abs(accuracy - abs(errorAt(x, h, newN))) > 0.001)
		newN++;
	
		cout << "The step value h for accuracy of " << accuracy << " is " << newH << endl;
	cout << "The diff. order n for accuracy of " << accuracy << " is " << newN << endl;
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
		if (k == 1)
			cout << "Error at " << xi << ": " << errorAt(xi, h, n) << endl << endl << "Require accuracy\t[A]";
		else
			cout << endl << endl;		// error formulae not found for 2nd derivative
		cout << "\nReinitialize values\t[R]" << endl;
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