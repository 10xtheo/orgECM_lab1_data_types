#include "application.h"
#include "utils.h"
#include <iostream>

using namespace std;


TApplication::TApplication() {

}

int TApplication::exec() {
    int ch;

    while (true) {
        cin.clear(); // Clearing the input stream from possible errors
        cin.sync();
        ch = menu();

        switch (ch) {
        case 2: {
            short int order = sizeof(int) * 8 - 1; // TODO: мб вынести через template
            unsigned int mask = 1 << order;
            char bits[64];

            union {
                int numberArray [2] = {};
                double doubleNumber;
            };

            cout << "\n" << "Enter a double precision number: ";
            cin >> doubleNumber;
            if (!cin.good()) {
                cout << "\n" << "You entered an incorrect value";
                break;
            }

            // Swap array elements for correct binary representation
            int tempElement = numberArray[1];
            numberArray[1] = numberArray[0];
            numberArray[0] = tempElement;

            for (int j = 0; j < 2; j++) { // TODO: мб вынести в отдельную функцию
                for (int i = 0; i <= order; i++) {
                    bits[j*(order+1) + i] = ((numberArray[j] & mask) ? '1': '0');
                    cout << ((numberArray[j] & mask) ? 1: 0);
                    mask >>= 1;
                    if (!j && i == 11 || !j && !i) {
                        cout << " ";
                    }
                }
                mask = 1 << order;
            }

            unsigned long long doubleBitsValue = bitsToNumber(bits, 64);
            memcpy(&doubleNumber, &doubleBitsValue, sizeof(double));
            cout << "\nConverted: " << doubleNumber; // TODO: работает кривовато - надо поправить

            break;
        }
        case 1: {
            char bits[8];
            char symbol;
            short int order = sizeof(char) * 8 - 1;
            unsigned int mask = 1 << order;

            cout << "\n" << "Enter an char: ";
            cin >> symbol;
            if (!cin.good()) {
                cout << "\n" << "You entered an incorrect value";
                break;
            }

            for (int i = 0; i <= order; i++) {
                bits[i] = ((symbol & mask) ? '1': '0');
                cout << ((symbol & mask) ? 1: 0);
                mask >>= 1;
                if ((i + 1) % 8 == 0) {
                    cout << " ";
                }
            }
            cout << "\nConverted: " << (char) bitsToNumber(bits, 8);
            break;
        }
        case 0: {
            return 0;
        }
        default: {
            cout << "\n" << "There is no case with this number" << "\n";
            break;
        }
        }
    }
    return 0;
}


int TApplication::menu() {
    int ch;

    cout << "\nNavigation:" << "\n"
         << "2 Binary representation in memory of a double" << "\n"
         << "1 Binary representation in memory of a char" << "\n"
         << "0 - exit" << "\n" << "> ";

    cin >> ch;
    if (!cin.good()) return -1;

    return ch;
}

