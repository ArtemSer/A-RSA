#include <string>

#ifndef A_RSA_FUNCTIONAL_H
#define A_RSA_FUNCTIONAL_H

#endif //A_RSA_FUNCTIONAL_H

int displayMenu() {
    int choice;
    std::cout << "--- A-RSA ---\n"
                 "1. Generate keys\n"
                 "2. Encrypt message\n"
                 "3. Decrypt message\n"
                 "4. Exit\n"
                 "option > ";
    std::cin >> choice;
    return choice;
}

void generateKeyPair() {
    std::cout << "Generating keys ..." << std::endl << std::endl;
    // Генерация двух чисел и выбор двух простых чисел.
    srand((unsigned) time(nullptr));
    // use c++ random library instead of Rand()
    int p = rand() % 100,
            q = rand() % 100,
            p_simple = sundaram(p),
            q_simple = sundaram(q);
    //Находим число RsaModule.
    auto RsaModule = static_cast<unsigned int>(p_simple * q_simple);
    //Генерация числа exponentOfDecryption и проверка его на взаимопростоту
    //с числом ((p_simple-1)*(q_simple-1)).
    int exponentOfDecryption = 0, d_simple = 0;
    while (d_simple != 1) {
        exponentOfDecryption = rand() % 100;
        d_simple = gcd(exponentOfDecryption, ((p_simple - 1) * (q_simple - 1)));
    }
    //Определение числа exponentOfEncryption, для которого является истинным
    //соотношение (exponentOfEncryption*exponentOfDecryption)%((p_simple-1)*(q_simple-1))=1.
    unsigned int exponentOfEncryption = 0, e_simple = 0;
    while (e_simple != 1) {
        exponentOfEncryption += 1;
        e_simple = (exponentOfEncryption * exponentOfDecryption) % ((p_simple - 1) * (q_simple - 1));
    }
///Сгенерированные ключи.
    std::cout << " - Open key: \t" << '[' << std::setw(6) << exponentOfEncryption << ',' << std::setw(6) << RsaModule
              << ']' << std::endl;
    std::cout << " - Secret key: \t" << '[' << std::setw(6) << exponentOfDecryption << ',' << std::setw(6) << RsaModule
              << ']' << std::endl << std::endl;
}

void encryptMessage() {
    int size, exponentOfEncryption, RsaModule;
    std::cout << "Enter please the size of message: ";
    std::cin >> size;
    std::cout << "Enter please the Open key : ";
    std::cin >> exponentOfEncryption;
    std::cout << "Enter please the RsaModule: ";
    std::cin >> RsaModule;
    std::cout << "Please enter the text to encrypt below." << std::endl;
    std::cin.ignore();
    auto *Text = new char[size];
    std::cin.get(Text, size);
    std::cout << "Text is = " << Text << std::endl;
    std::cin.ignore();
    auto *CryptoText = new unsigned int[size];
    //Получение из введённых данных десятичного кода ASCII и
    //дальнейшее его преобразование по формуле ci = (mj^exponentOfEncryption)%RsaModule.
    int AsciiKey = 301;
    int c;
    std::cout << std::endl
              << std::setw(5) << "Text" << std::setw(10) << "ASCII"
              << std::setw(20) << "CryptoText/Block#" << "---------------------"
              << std::endl;

    for (int j = 0; j < size; j++) {
        c = 1;
        int ASCIIcode = (static_cast<int>(Text[j])) + AsciiKey;
        for (unsigned int i = 0; i < exponentOfEncryption; i++) {
            c *= ASCIIcode;
            c %= RsaModule;
        }
        CryptoText[j] = static_cast<unsigned int>(c);
        AsciiKey += 1;
    }
    for (int j = 0; j < size - 1; j++)
        std::cout << std::setw(5) << Text[j]
                  << std::setw(10) << static_cast<int>(Text[j])
                  << std::setw(20) << CryptoText[j] << std::endl;
    std::cout << "Your encrypted text is [ ";
    for (int i = 0; i < size - 1; i++) std::cout << CryptoText[i] << " ";
    std::cout << size << " ]" << std::endl;
    delete[] Text;
    delete[] CryptoText;
}

void decryptMessage() {
    int size, exponentOfDecryption, RsaModule;
    std::cout << "Enter please the size of message: ";
    std::cin >> size;
    auto *encryptedText = new int[size];
    std::cout << "Please enter the text to decrypt below. \n "
                 "NOTE: use spaces to divide blocks" << std::endl;
    for (int i = 0; i < size; i++) std::cin >> encryptedText[i];
    std::cout << "Enter please the Secret key: ";
    std::cin >> exponentOfDecryption;
    std::cout << "Enter please the RsaModule : ";
    std::cin >> RsaModule;

    auto *decryptedText = new unsigned int[size];
    //Расшифровка полученного кода по формуле mi = (ci^exponentOfDecryption)%RsaModule
    //и перевод его в десятичный код ASCII.
    std::cout << std::endl
              << std::setw(20) << "CryptoText/Block#"
              << std::setw(14) << "ASCII"
              << std::setw(14) << "Text"
              << std::endl;
    int AsciiKey = 301;
    int m;
    for (int j = 0; j < size; j++) {
        m = 1;
        for (unsigned int i = 0; i < exponentOfDecryption; i++) {
            m = m * encryptedText[j];
            m = m % RsaModule;
        }
        m = m - AsciiKey;
        decryptedText[j] = static_cast<unsigned int>(m);
        AsciiKey += 1;
    }
    for (int j = 0; j < size - 1; j++)
        std::cout << std::setw(20) << encryptedText[j]
                  << std::setw(14) << decryptedText[j]
                  << std::setw(14) << static_cast<char>(decryptedText[j])
                  << std::endl;
    std::cout<< "Message: ";
    for (int i = 0; i < size; i++) std::cout << static_cast<char>(decryptedText[i]);
    std::cout << std::endl;
    delete[] encryptedText;
    delete[] decryptedText;

}