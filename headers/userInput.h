#ifndef USERINPUT_H_INCLUDED
#define USERINPUT_H_INCLUDED

namespace userInput
{
    string useGetline()
    {
        string variable;
        cin.sync();
        getline(cin, variable);
        return variable;
    }

    int getIntInput()
    {
        string userInput;
        while(1)
        {
            userInput = useGetline();

            if (userInput.length() != 1)
            {
                cout << "Nieoczekiwana wartosc, sprobuj ponownie." << endl;
                continue;
            }
            else
            {
                if (isdigit(userInput[0]))
                {
                    return stoi(userInput);
                }
                else
                {
                    cout << "To nie jest liczba, sprobuj ponownie." << endl;
                }
            }
        }
    }
}

#endif // USERINPUT_H_INCLUDED
