#include<iostream>
#include<string>
#include<math.h>
#include<cctype>
#include<string>
#include<conio.h>
using namespace std;
string N;
string M[100];
int n;

void input() {
	int flag = 1;
	do {
		flag = 1;
		cout << "Nhap vao so phan tu cua day: ";
		cin >> N;
		for (int i = 0; i < N.length(); i++) {
			if (N[i] < '0' || N[i] >'9') {
				cout << "So vua nhap khong hop le.";
				flag = 0;
				break;
			}
		}

	} while (flag == 0);
	n = stoi(N);
	for (int i = 0; i < n; i++) {
		cout << "\nNhap vao phan tu thu " << i + 1 << " :";
		cin >> M[i];
		int m = M[i].length();
		if (M[i][0] != '0' && M[i][0] != '1' &&
			M[i][0] != '2' && M[i][0] != '3' &&
			M[i][0] != '4' && M[i][0] != '5' &&
			M[i][0] != '6' && M[i][0] != '7' &&
			M[i][0] != '8' && M[i][0] != '9' &&
			M[i][0] != '-') {
			cout << "\nSo vua nhap khong hop le. Vui long nhap lai!";
			i--;
			continue;
		}
		for (int j = 1; j < m; j++) {
			if (M[i][j] < '0' || M[i][j] > '9') {
				cout << "\nSo vua nhap khong hop le. Vui long nhap lai!";
				i--;
				break;
			}
		}
	}
}

void output() {
	cout << "\nDay so la: ";
	for (int i = 0; i < n; i++) {
		cout << M[i] << " ";
	}
}

int convert(string s) {
	if (s[0] == '-') {
		int m = s.length();
		int sum = 0;
		int temp = m;
		for (int i = 1; i < temp; i++) {
			sum += ((s[i] - '0') * pow(10, m - 2));
			m--;
		}
		return 0 - sum;
	}
	int m = s.length();
	int sum = 0;
	int temp = m;
	for (int i = 0; i < temp; i++) {
		sum += ((s[i] - '0') * pow(10, m - 1));
		m--;
	}
	return sum;
}

void find(int k) {
	int flag = 0;
	for (int i = 0; i < n; i++) {
		int tmp = convert(M[i]);
		if (tmp == k) {
			flag = 1;
			cout << "\nSo can tim o vi tri thu " << i << ".";
		}
	}
	if (flag == 0) cout << "\nKhong ton tai so " << k << " trong day.";
}

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

void Swap() {
	int i, j;
	cout << "\nNhap vao 2 phan tu muon doi cho.";
	do {
		cin >> i >> j;
		if ((i <0 || i>n) && (j <0 || j>n)) {
			cout << "\n2 so vua nhap khong hop le. Vui long nhap lai.";
		}
	} while ((i <0 || i>n) && (j <0 || j>n));

	swap(M[i], M[j]);
}

void reverse() {
	for (int i = 0; i < n / 2; i++) {
		swap(M[i], M[n - 1 - i]);
	}
}

void sort() {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (convert(M[i]) > convert(M[j])) {
				swap(M[i], M[j]);
			}
		}
	}
}

int tinhTong() {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int tmp = convert(M[i]);
		sum += tmp;
	}
	return sum;
}


void add(string tmp, int i) {
	int m = tmp.length();
	if (tmp[0] != '0' && tmp[0] != '1' &&
		tmp[0] != '2' && tmp[0] != '3' &&
		tmp[0] != '4' && tmp[0] != '5' &&
		tmp[0] != '6' && tmp[0] != '7' &&
		tmp[0] != '8' && tmp[0] != '9' &&
		tmp[0] != '-') {
		cout << "\nSo vua nhap khong hop le. Vui long nhap lai!";
		return;
	}
	for (int j = 1; j < m; j++) {
		if (M[i][j] < '0' || M[i][j] > '9') {
			cout << "\nSo vua nhap khong hop le. Vui long nhap lai!";
			return;
		}
	}
	int tmp1 = convert(tmp);
	if (i < 0) {
		cout << "\nKhong the them phan tu.";
		return;
	}
	else if (i < n) {
		for (int j = n; j > i; j--) {
			M[j] = M[j - 1];
		}
		char tmp2[100];
		_itoa_s(tmp1, tmp2, 10);
		M[i] = tmp2;
		n++;
	}
	else {
		char tmp2[20];
		_itoa_s(tmp1, tmp2, 10);
		M[n] = tmp2;
		n++;
	}
}

void erase(int i) {
	if (i < 0) {
		cout << "\nKhong the xoa phan tu.";
		return;
	}
	else if (i < n) {
		for (int j = i; j < n; j++) {
			M[j] = M[j + 1];
		}
		n--;
	}
	else {
		cout << "\nKhong the xoa phan tu.";
		return;
	}
}

void menu() {
	cout << "\n-------------------------------------------------" << endl;
	cout << "1. Nhap vao day so." << endl;
	cout << "2. Tim phan tu trong day so." << endl;
	cout << "3. Tinh tong day so." << endl;
	cout << "4. Doi cho 2 phan tu bat ki trong day so." << endl;
	cout << "5. Dao nguoc day so. " << endl;
	cout << "6. Sap xep cac phan tu trong day so. " << endl;
	cout << "7. Them phan tu trong day so. " << endl;
	cout << "8. Xoa phan tu trong day so. " << endl;
	cout << "9. In ra day so." << endl;
	cout << "\n-------------------------------------------------" << endl;
}

int main() {
	int luachon;
	do {
		menu();

		do {
			string luachon1;
			int flag0 = 1;
			do {
				flag0 = 1;
				cout << "Nhap vao lua chon: ";
				cin >> luachon1;
				for (int i = 0; i < luachon1.length(); i++) {
					if (luachon1[i] < '0' || luachon1[i] > '9') {
						cout << "So vua nhap khong hop le.";
						flag0 = 0;
						break;
					}
				}

			} while (flag0 == 0);
			luachon = stoi(luachon1);
			if (luachon < 1 || luachon >9) {
				cout << "\nSo vua nhap khong hop le. Vui long nhap lai!";
			}
		} while (luachon < 1 || luachon >9);

		if (luachon == 1) {
			input();
		}
		if (luachon == 2) {
			int k;
			cout << "\nNhap vao so can tim: ";
			cin >> k;
			find(k);
		}
		if (luachon == 3) {
			cout << "Tong cua day so la: " << tinhTong();
		}
		if (luachon == 4) {
			Swap();
		}
		if (luachon == 5) {
			reverse();
		}
		if (luachon == 6) {
			sort();
		}
		if (luachon == 7) {
			int k;
			string tmp;
			cout << "\nNhap vao phan tu muon them: ";
			cin >> tmp;
			cout << "\nNhap vao vi tri muon them: ";
			cin >> k;
			add(tmp, k);
		}
		if (luachon == 8) {
			int l;
			cout << "\nNhap vao vi tri muon xoa: ";
			cin >> l;
			erase(l);
		}
		if (luachon == 9) {
			output();
		}
	} while (1);
}