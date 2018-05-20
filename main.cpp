#include <ctime>
#include <iomanip>
#include <iostream>
/* Including functions */
#include "sundaramAlgorythm.h"
#include "evklidAlgorythm.h"
#include "functional.h"

using namespace std;

int main() {
    while (true) {
        int choice = displayMenu();
        if (choice == 1) generateKeyPair();
        else if (choice == 2) encryptMessage();
        else if (choice == 3) decryptMessage();
        else if (choice == 4) break;
    }
}
//
////Ввод шифруемых данных.
//
//

//    //Массив для хранения шифротекста.
//
//    auto *Tdecrypt = new unsigned int[MAX];
//    //Расшифровка полученного кода по формуле mi = (ci^exponentOfDecryption)%RsaModule
//    //и перевод его в десятичный код ASCII.
//
//    b = 301;
//    int m;
//    for (int j = 0; j < MAX; j++) {
//        m = 1;
//        for (unsigned int i = 0; i < exponentOfDecryption; i++) {
//            m = m * CryptoText[j];
//            m = m % RsaModule;
//        }
//        m = m - b;
//        Tdecrypt[j] = static_cast<unsigned int>(m);
//        b += 1;
//    }
//    for (int j = 0; j < MAX - 1; j++) {
//        cout << setw(5) << Text[j] << setw(6) << static_cast<int>(Text[j]) << setw(20)
//             << CryptoText[j] << setw(14) << Tdecrypt[j] << setw(14) << static_cast<char>(Tdecrypt[j]) << endl;
//    }
//    delete[] Tdecrypt;
//    return 0;
//}
//
