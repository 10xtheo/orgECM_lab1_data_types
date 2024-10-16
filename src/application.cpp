#include "application.h"
#include "utils.h"
#include <iostream>
#include <cstring>

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
            cout << "\nConverted: " << doubleNumber << "\n"; // TODO: работает кривовато - надо поправить

            bool et = extraTask();
            if (et) {
                int N;
                cout << "Enter N: ";
                cin >> N;
                for (int i = 0; i < N; ++i) {
                    cout << "Enter bit position: ";
                    unsigned int bitPos;
                    cin >> bitPos;

                    if (bitPos < 32 && bitPos >= 0) {
                        numberArray[0] = numberArray[0] ^ (1 << bitPos);
                    }

                    else if (bitPos < 64 && bitPos >= 0) {
                        bitPos = bitPos % 64;
                        numberArray[1] = numberArray[1] ^ (1 << bitPos);
                    }
                    else {
                        cout << "wrong position \n";
                    }

                }

                // Swap array elements for correct binary representation
                tempElement = numberArray[1];
                numberArray[1] = numberArray[0];
                numberArray[0] = tempElement;

                mask = 1 << order;
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

            }


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

            bool et = extraTask();
            if (et) {
                int N;
                cout << "Enter N: ";
                cin >> N;
                for (int i = 0; i < N; ++i) {
                    cout << "Enter bit position: ";
                    unsigned int bitPos;
                    cin >> bitPos;

                    symbol = symbol ^ (1 << bitPos);
                }

                mask = 1 << order;
                for (int i = 0; i <= order; i++) {
                    bits[i] = ((symbol & mask) ? '1': '0');
                    cout << ((symbol & mask) ? 1: 0);
                    mask >>= 1;
                    if ((i + 1) % 8 == 0) {
                        cout << " ";
                    }
                }

            }

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

bool TApplication::extraTask() {
    bool ch;

    cout << "Invert N bits " << "\n"
         << "1 - yes" << "\n"
         << "0 - skip" << "\n" << "> ";

    cin >> ch;
    return ch;
}
