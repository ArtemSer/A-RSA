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
