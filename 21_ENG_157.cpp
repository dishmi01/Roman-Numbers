#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getRomanValue(char character) 
{
    switch (character) 
    {
        case 'i':
        case 'I':
            return 1;
        case 'v':
        case 'V':
            return 5;
        case 'x':
        case 'X':
            return 10;
        case 'l':
        case 'L':
            return 50;
        case 'c':
        case 'C':
            return 100;
        default:
            return -1;
    }
}

bool suitableRomanCharacter (string romanNumber)
{
    //checking whether the series of characters are acceptable roman characters
    for(int i=0; i<romanNumber.size(); i++)
    {
        bool correct = 	romanNumber[i] == 'i' ||  romanNumber[i] == 'I' ||  romanNumber[i] == 'v' ||  romanNumber[i] == 'V' ||
			            romanNumber[i] == 'x' ||  romanNumber[i] == 'X' ||  romanNumber[i] == 'l' ||  romanNumber[i] == 'L' ||
			            romanNumber[i] == 'c' ||  romanNumber[i] == 'C';

        if (!correct) {
			return false;
		}
    }

    // chacking whether the repeated chracters exeeds the limit
    int iC = 0, vC = 0, xC = 0, lC = 0, cC = 0; // count of each characters
    for (int i = 0; i < romanNumber.size(); i++) 
    {
			switch (romanNumber[i]) {
			case 'i':
			case 'I':
				iC++; vC = 0; xC = 0; lC = 0; cC = 0;
				break;

            case 'v':
            case 'V':
                iC = 0; vC++; xC = 0; lC = 0; cC = 0;
				break;

            case 'x':
            case 'X':
                iC = 0; vC = 0; xC++; lC = 0; cC = 0;
				break;

            case 'l':
            case 'L':
                iC = 0; vC = 0; xC = 0; lC++; cC = 0;
				break;

            case 'c':
            case 'C':
                iC = 0; vC = 0; xC = 0; lC = 0; cC++;
				break;

            default:
                break;

            }
    }

    // if the specific character limit exeeds
    if (iC > 3)
			return false;
	if (vC > 1)
			return false;
	if (xC > 3)
			return false;
	if (lC > 1)
			return false;
	if (cC > 2)
			return false;
    

    for (int i = 0; i < romanNumber.size() - 1; i++) 
    {
        char present = romanNumber[i];
		char next = romanNumber[i+1];
        //char previous = romanNumber[i+3];

        if ((present == 'i' || present == 'I') && (next == 'c' || next == 'C'))
        {
            return false;
        }
        if ((present == 'v' || present == 'V') && (next == 'c' || next == 'C'))
        {
            return false;
        }
        if ((present == 'l' || present == 'L') && (next == 'c' || next == 'C'))
        {
            return false;
        }
        /*if((previous = 'x' || previous == 'X') && (present == 'x' || present == 'X') && (next == 'c' || next == 'C'))
        {
            return false;
        }*/

    }


    for (int i = 0; i < romanNumber.size() - 1; i++) 
    {
		int present = getRomanValue(romanNumber[i+1]);
		int next = getRomanValue(romanNumber[i+2]);
        int previous = getRomanValue(romanNumber[i]);
        //int preprevious = getRomanValue(romanNumber[i-1]);

            if (present <next && present == previous)
            {
                return false;
            }
            /*else
            if (preprevious == previous)
            {
                return false;
            }*/
			else
            if (present < next) {
				switch (next) {
				case 5: // 5 -1
					if (present != 1)
						return false;
					break;

				case 10: // 10 - 1
					if (present != 1)
						return false;
					break;

				case 50: // 50 - 10
					if (present != 10)
						return false;
					break;

				case 100: // 100 - 10
					if (present != 10)
						return false;
					break;

				default:
					break;
				}
			}
            //}
			i++;
		}
        
        return true;
}

int HinduArabicNumber(const string& romanNumber) {
    int result = 0;
    int prevValue = 0;

    for(int i = romanNumber.length() - 1; i >= 0; i--) // calculating from reverse order
    {
        char character = tolower(romanNumber[i]); // Convert to lowercase for case-insensitivity
        int value = getRomanValue(character);

        if (value < prevValue) 
            result -= value; 
        else 
        {
            result += value;
        }
        prevValue = value;
    }

    return result;
}

int main ()
{
    ifstream inputFile("roman_numbers.txt");

    if (!inputFile) 
    {
        cout << "Error! Unable to open input file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            if (suitableRomanCharacter(line)) {
                int hinduArabicNumber = HinduArabicNumber(line);
                cout << line << " = " << hinduArabicNumber << endl;
            } else {
                cout << line << " = error" << endl;
            }
        }
    }

    inputFile.close();

}