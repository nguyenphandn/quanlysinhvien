#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

template<typename T>

class tArr
{
private:
	int cap;
	int nrOfEl;
	T **arr;

public:
	tArr(int size = 5);
	~tArr();

	void initialize(int from);
	void expand();
	void push(const T &element);
	//int findIndex(const T& element);
	void remove(int index);
	const int& size()const { return this->nrOfEl; }

	T& operator[] (const int index);
};

//constructor
template<typename T>
tArr<T>::tArr(int size)
{
	this->cap = size;
	this->nrOfEl = 0;
	this->arr = new T*[this->cap];

	initialize(this->nrOfEl);
}

//destructor
template<typename T>
tArr<T>::~tArr()
{
	for (size_t i = 0; i < nrOfEl; i++)
	{
		delete this->arr[i];
	}
	delete[]this->arr;
}

//operator
template<typename T>
T& tArr<T>::operator[](const int index)
{
	if (index < 0 || index >= this->nrOfEl)
		throw("OUT OF BOUDNS!");

	return *this->arr[index];
}

//make elements from current size (nrOfEl number of elements) to capacity (cap) become null
template<typename T>
void tArr<T>::initialize(int from)
{
	for (size_t i = from; i < cap; i++)
	{
		this->arr[i] = nullptr;
	}
}

//double the capacity of array
template<typename T>
void tArr<T>::expand()
{
	this->cap *= 2;

	T **tempArr = new T*[this->cap];

	for (size_t i = 0; i < this->nrOfEl; i++)
	{
		tempArr[i] = this->arr[i];
	}

	delete[]this->arr;

	this->arr = tempArr;

	initialize(this->nrOfEl);
}

//add a new element to array, if it exceeds the capacity, perform expand()
template<typename T>
void tArr<T>::push(const T& element)
{
	if (this->nrOfEl >= this->cap)
	{
		this->expand();
	}

	this->arr[this->nrOfEl++] = new T(element);
}

////find index of element
//template<typename T>
//int findIndex(const T& element)
//{
//	for (int i = 0; i < this->nrOfEl; i++)
//	{
//		if (*this->arr[i] == element)
//		{
//			return i;
//		}
//	}
//	return -1;
//}

//remove element at index
template<typename T>
void tArr<T>::remove(int index)
{
	T** tempArr = new T * [this->cap];
	copy(this->arr, this->arr + index, tempArr);
	copy(this->arr + index + 1, this->arr + this->nrOfEl, tempArr + index);
	delete[]this->arr;
	this->arr = tempArr;
	this->nrOfEl--;
}

void printLine(int n);
void pressAnyKey();

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	tArr<string> names;
	tArr<int> scores;

	string tmpname;
	int tmpscore;
	
	int key;
	char fileName[] = "student.txt";

    while (true) {
        cout << "CHUONG TRINH QUAN LY SINH VIEN C/C++\n";
        cout << "*************************MENU**************************\n";
        cout << "**  1. Them sinh vien.                               **\n";
        cout << "**  2. Sap xep sinh vien theo diem trung binh (GPA). **\n";
        cout << "**  3. Hien thi danh sach sinh vien.                 **\n";
        cout << "**  4. Xoa sinh vien theo ten.                       **\n";
        cout << "**  0. Thoat                                         **\n";
        cout << "*******************************************************\n";
        cout << "Nhap tuy chon: ";
        cin >> key;
        switch (key) {
        case 1:
            cout << "\n1.Them sinh vien.";
            printLine(40);

            cout << "\nNhap sinh vien thu " << names.size() + 1 << ":";
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nNhap ten cua sinh vien: ";
            getline(cin, tmpname);
            cout << "Nhap diem cua sinh vien: ";
            cin >> tmpscore;

            names.push(tmpname);
            scores.push(tmpscore);

            printLine(40);
            cout << "\nThem sinh vien thanh cong!\n";
            
            //display names and scores
            for (int i = 0; i < names.size(); i++)
            {
                cout << i << ' ' << names[i] << ' ' << scores[i] << endl;
            }

            pressAnyKey();
            break;
        case 2:
            if (names.size() > 0) {
                cout << "\n2. Sap xep sinh vien theo diem trung binh (GPA).\n";

                //bubble sort
                bool exchanges = false;
                do {
                    exchanges = false;  // assume no exchanges
                    for (int i = 0; i < names.size() - 1; i++) {
                        if (scores[i] < scores[i + 1]) {
                            int tmpsc = scores[i];
                            string tmpna = names[i];
                            names[i] = names[i + 1];
                            names[i + 1] = tmpna;
                            scores[i] = scores[i + 1];
                            scores[i + 1] = tmpsc;
                            exchanges = true;  // after exchange, must look again
                        }
                    }
                } while (exchanges);

                //display names and scores
                for (int i = 0; i < names.size(); i++)
                {
                    cout << i << ' ' << names[i] << ' ' << scores[i] << endl;
                }
            }
            else {
                cout << "\nSanh sach sinh vien trong!";
            }
            pressAnyKey();
            break;
        case 3:
            if (names.size() > 0) {
                cout << "\n7. Hien thi danh sach sinh vien.\n";
                
                //display names and scores
                for (int i = 0; i < names.size(); i++)
                {
                    cout << i << ' ' << names[i] << ' ' << scores[i] << endl;
                }
            }
            else {
                cout << "\nDanh sach sinh vien trong!";
            }
            pressAnyKey();
            break;
        case 4:
            tmpscore = 0;
            cout << "\n4. Xoa sinh vien theo ten.";
            printLine(40);
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nNhap ten cua sinh vien: ";
            getline(cin, tmpname);

            for (int i = 0; i < names.size(); i++)
            {
                if (names[i] == tmpname)
                {
                    names.remove(i);
                    scores.remove(i);
                    tmpscore++;
                }
            }

            if (tmpscore > 0)
            {
                printLine(40);
                cout << "\nXoa sinh vien thanh cong!\n";
            }
            else {
                cout << "\nTen sinh vien khong co trong danh sach!";
            }
            pressAnyKey();
            break;
        case 0:
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nBan da chon thoat chuong trinh!";
            cin.get();
            return 0;
        default:
            cout << "\nKhong co chuc nang nay!";
            cout << "\nHay chon chuc nang trong hop menu.";
            pressAnyKey();
            break;
        }
    }
	return 0;
}

//void bubbleSort(tArr<string> A, tArr<int> B) {
//    bool exchanges = false;
//    int n = A.size();
//    tArr<string> a = new string * [n];
//    int** b = new int * [n];
//    do {
//        exchanges = false;  // assume no exchanges
//        for (int i = 0; i < n - 1; i++) {
//            if (b[i] < b[i + 1]) {
//                int* tmpsc = b[i];
//                string* tmpna = a[i];
//                a[i] = a[i + 1];
//                a[i + 1] = tmpna;
//                b[i] = b[i + 1];
//                b[i + 1] = tmpsc;
//                exchanges = true;  // after exchange, must look again
//            }
//        }
//    } while (exchanges);
//    display(a, b);
//}

void printLine(int n)
{
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "_";
    }
    cout << endl;
}

void pressAnyKey()
{
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "\n\nBam phim bat ky de tiep tuc...";
    cin.get();
    system("cls");
}

//cout << "size " << iArr.size() << endl;
//
//iArr.push("Hello eve");
//iArr.push("ry one");
//iArr.push("la la");
//
//for (int i = 0; i < iArr.size(); i++)
//{
//	cout << iArr[i] << endl;
//}
//
//cout << "size " << iArr.size() << endl;
//
//iArr.remove(1);
//
//for (int i = 0; i < iArr.size(); i++)
//{
//	cout << iArr[i] << endl;
//}
//
//cout << "size " << iArr.size() << endl;
//
//
//system("PAUSE");