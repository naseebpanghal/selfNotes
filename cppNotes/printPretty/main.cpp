#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

		/* Enter your code here */
		cout << left;

		cout << fixed;
		//        cout << nouppercase << showbase << hex << setprecision(0) << A << endl;
		cout << nouppercase << showbase << hex << static_cast<long int>(A) << endl;
		//cout << setprecision(2) << setw(15) << setfill('_') << showpos << B << endl;
		cout << right;
		cout << setw(15) << setfill('_') << showpos << setprecision(2) << B << endl;

		cout << scientific;
		cout << setprecision(9) << uppercase << noshowpos << C << endl;

	}
	return 0;

}
