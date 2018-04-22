#include <ctime>
#include <iomanip>
#include <iostream>
/* Including functions */
#include "sundaramAlgorythm.h"
#include "evklidAlgorythm.h"

using namespace std;

int main() {
    cout << "Generating keys ..." << endl << endl;
    // Генерация двух чисел и выбор двух простых чисел.
    srand((unsigned) time(nullptr));
    // use c++ random library instead of Rand()
    int p = rand() % 100,
            q = rand() % 100,
            p_simple = sundaram(p),
            q_simple = sundaram(q);
    //Находим число n.
    auto n = static_cast<unsigned int>(p_simple * q_simple);
    //Генерация числа d и проверка его на взаимопростоту
    //с числом ((p_simple-1)*(q_simple-1)).
    int d = 0, d_simple = 0;
    while (d_simple != 1) {
        d = rand() % 100;
        d_simple = gcd(d, ((p_simple - 1) * (q_simple - 1)));
    }
    //Определение числа e, для которого является истинным
    //соотношение (e*d)%((p_simple-1)*(q_simple-1))=1.
    unsigned int e = 0, e_simple = 0;
    while (e_simple != 1) {
        e += 1;
        e_simple = (e * d) % ((p_simple - 1) * (q_simple - 1));
    }
///Сгенерированные ключи.
    cout << " - Open key: \t" << '[' << setw(12) << e << ',' << setw(12) << n << ']' << endl;
    cout << " - Secret key: \t" << '[' << setw(12) << d << ',' << setw(12) << n << ']' << endl << endl;
//Ввод шифруемых данных.
    const int MAX = 10;
    auto *Text = new char[MAX];
    cout << "Please enter the text to encrypt below." << endl;
    cin.get(Text, MAX);
    //Массив для хранения шифротекста.
    auto *CryptoText = new unsigned int[MAX];
    auto *Tdecrypt = new unsigned int[MAX];
    //Получение из введённых данных десятичного кода ASCII и
    //дальнейшее его преобразование по формуле ci = (mj^e)%n.
    int b = 301;
    int c;
    cout << endl
         << setw(5) << "Text" << setw(10) << "ASCII"
         << setw(20) << "CryptoText/Block#" << setw(14)
         << "ASCIIdecrypt" << setw(14) << "Text decrypt" << endl
         << "------------------------------------------------------------" << endl;
    for (int j = 0; j < MAX; j++) {
        c = 1;
        int ASCIIcode = (static_cast<int>(Text[j])) + b;
        for (unsigned int i = 0; i < e; i++) {
            c = c * ASCIIcode;
            c = c % n;
        }
        CryptoText[j] = static_cast<unsigned int>(c);
        b += 1;
    }
    //Расшифровка полученного кода по формуле mi = (ci^d)%n
    //и перевод его в десятичный код ASCII.

    b = 301;
    int m;
    for (int j = 0; j < MAX; j++) {
        m = 1;
        unsigned int i = 0;
        while (i < d) {
            m = m * CryptoText[j];
            m = m % n;
            i++;
        }
        m = m - b;
        Tdecrypt[j] = static_cast<unsigned int>(m);
        b += 1;
    }
    for (int j = 0; j < MAX - 1; j++) {
        cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) << setw(20)
             << CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) << static_cast<char>(Tdecrypt[j]) << endl;
    }
    delete[] Text;
    delete[] CryptoText;
    delete[] Tdecrypt;
    return 0;
}

