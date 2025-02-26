#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "headers/person.h"
#include "headers/vectorOperations.h"

using namespace std;
using namespace person;
using namespace vectorOperations;

string fileName = "phoneBook.txt";

void saveToFile(PersonFriend newFriend)
{
    fstream file;
    file.open(fileName, ios::out | ios::app);
    file << newFriend.id << "|"
    << newFriend.name << "|"
    << newFriend.surname << "|"
    << newFriend.email << "|"
    << newFriend.address << "|"
    << newFriend.phoneNumber << endl;

    file.close();
}

void readFromFileIfExist(vector <PersonFriend> &friends)
{
    string line;
    PersonFriend newFriend;
    fstream file;
    file.open(fileName, ios::in);
    if (file.good())
    {
        while(getline(file, line))
        {
            vector <string> friendFromFile = addDataToVector(line);
            newFriend.assignData(friendFromFile);
            friends.push_back(newFriend);
        }
    }
    file.close();
}

string useGetline()
{
    string variable;
    cin.sync();
    getline(cin, variable);
    return variable;
}

string searchForNextHighestID(vector <PersonFriend> friends)
{
    int highestID = 0;
    if (friends.size() > 0)
    {
        highestID = friends.back().id;
    }
    return to_string(highestID + 1);
}

void addFriendToTheBook(vector <PersonFriend> &friends)
{
    PersonFriend newFriend;
    vector <string> newFriendData;
    string idForNewFriend = searchForNextHighestID(friends);

    newFriendData.push_back(idForNewFriend);

    cout << "Podaj imie: ";
    newFriendData.push_back(useGetline());

    cout << "Podaj nazwisko: ";
    newFriendData.push_back(useGetline());

    cout << "Podaj email: ";
    newFriendData.push_back(useGetline());

    cout << "Podaj adres: ";
    newFriendData.push_back(useGetline());

    cout << "Podaj numer telefonu: ";
    newFriendData.push_back(useGetline());

    newFriend.assignData(newFriendData);

    bool friendExist = false;
    for(size_t i = 0; i < friends.size(); i++)
    {
        friendExist = newFriend.isEqual(friends[i]);
    }

    if (friendExist == true)
    {
        cout << "Taka osoba juz istnieje na liscie znajomych" << endl;
    }
    else
    {
        friends.push_back(newFriend);
        saveToFile(newFriend);
    }

}

void showOneFriend(PersonFriend oneFriend)
{
    cout << "ID: " << oneFriend.id << endl;
    cout << "Imie: " << oneFriend.name << endl;
    cout << "Nazwisko: " << oneFriend.surname << endl;
    cout << "Email: " << oneFriend.email << endl;
    cout << "Adres: " << oneFriend.address << endl;
    cout << "Numer Telefonu: " << oneFriend.phoneNumber << endl << endl;
}

void showAllFriends(vector <PersonFriend> &friends)
{
    for(size_t i = 0; i < friends.size(); i++)
    {
        showOneFriend(friends[i]);
    }
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

void searchForFriendByName(vector <PersonFriend> &friends)
{
    string name;
    cout << "Podaj imie przyjaciela ktorego chcesz znalezc: ";
    name = useGetline();
    for(size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].name == name)
        {
            showOneFriend(friends[i]);
        }
    }
}

void searchForFriendBySurname(vector <PersonFriend> &friends)
{
    string surname;
    cout << "Podaj nazwisko przyjaciela ktorego chcesz znalezc: ";
    surname = useGetline();
    for(size_t i = 0; i < friends.size(); i++)
    {
        if (friends[i].surname == surname)
        {
            showOneFriend(friends[i]);
        }
    }
}

void replaceFriendsInFile(vector <PersonFriend> friends)
{
    // cleaning file
    fstream file;
    file.open(fileName, ios::out | ios::trunc);
    file.close();

    //inserting new friends
    for (size_t i = 0; i < friends.size(); i++)
    {
        saveToFile(friends[i]);
    }

}

int indexOfPersonWithGivenId(vector <PersonFriend> friends, int id)
{
    int friendIndex = -1;
    for (size_t i = 0; i < friends.size(); i++)
    {
        if(friends[i].id == id)
        {
            friendIndex = i;
        }
    }

    return friendIndex;
}

int findIndexOfPersonYouWantToChange(vector <PersonFriend> friends, bool editUser)
{
    string consoleMessage;
    if(editUser == true)
    {
        consoleMessage = "Wpisz id przyjaciela, ktorego chcesz edytowac: ";
    }
    else
    {
        consoleMessage = "Podaj ID przyjaciela, ktorego chcesz usunac (juz nie taki przyjaciel, co?): ";
    }

    cout << consoleMessage;
    int friendID = getIntInput();
    int friendIndex = indexOfPersonWithGivenId(friends, friendID);

    while (friendIndex == -1)
    {
        cout << "Nie ma nikogo o takim ID.  Sprobuj ponownie: ";
        friendID = getIntInput();
        friendIndex = indexOfPersonWithGivenId(friends, friendID);
    }

    return friendIndex;

}

void editFriend (vector <PersonFriend> &friends)
{
    bool editUser = true;
    int friendIndex = findIndexOfPersonYouWantToChange(friends, editUser);

    cout << "Przyjaciel ktorego dane chcesz zmienic: " << endl;
    showOneFriend(friends[friendIndex]);



    while (true)
    {
        cout << "1. Zmien imie" << endl;
        cout << "2. Zmien nazwisko" << endl;
        cout << "3. Zmien email" << endl;
        cout << "4. Zmien adres" << endl;
        cout << "5. Zmien numer telefonu" << endl;
        cout << "6. Powrot do menu" << endl;
        int userChoice = getIntInput();
        switch (userChoice)
        {
        case 1:
            cout << "Podaj imie do zmiany: ";
            friends[friendIndex].name = useGetline();
            break;
        case 2:
            cout << "Podaj nazwisko do zmiany: ";
            friends[friendIndex].surname = useGetline();
            break;
        case 3:
            cout << "Podaj email do zmiany: ";
            friends[friendIndex].email = useGetline();
            break;
        case 4:
            cout << "Podaj adres do zmiany: ";
            friends[friendIndex].address = useGetline();
            break;
        case 5:
            cout << "Podaj numer telefonu do zmiany: ";
            friends[friendIndex].phoneNumber = useGetline();
            break;
        case 6:
            return;
        }

        replaceFriendsInFile(friends);

        cout << endl << "Nowe dane przyjaciela: " << endl;
        showOneFriend(friends[friendIndex]);
    }


}

void deleteFriend(vector <PersonFriend> &friends)
{
    string userChoice;
    bool editFriend = false;
    int notFriendIndex = findIndexOfPersonYouWantToChange(friends, editFriend);

    showOneFriend(friends[notFriendIndex]);

    cout << "Jestes pewien ze chcesz usunac te osobe? Wcisnij \"t\" jezeli tak, w przeciwnym wypadku wcisnij dowolny inny klawisz: ";
    userChoice = useGetline();

    if(userChoice != "t")
    {
        return;
    }

    friends.erase(friends.begin() + notFriendIndex);
    cout << "Usunieto \"przyjaciela\"" << endl;

    replaceFriendsInFile(friends);

}

bool checkIfAnyFriendsExist(vector <PersonFriend> friends)
{
    bool friendsExists = true;
    if (friends.size() <= 0)
    {
        cout << "Nie ma jeszcze nikogo na liscie, nie ma co szukac." << endl;
        friendsExists = false;
    }
    return friendsExists;
}

int main()
{
    vector <PersonFriend> friends;
    readFromFileIfExist(friends);
    int userChoice;

    while(1)
    {
        cout << "-----KSIAZKA ADRESOWA-----" << endl;
        cout << "1. Dodaj przyjaciela do ksiazki" << endl;
        cout << "2. Znajdz przyjaciela po imieniu" << endl;
        cout << "3. Znajdz przyjaciela po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich przyjaciol" << endl;
        cout << "5. Edytuj przyjaciela" << endl;
        cout << "6. Usun przyjaciela" << endl;
        cout << "9. Wyjdz z programu" << endl;
        userChoice = getIntInput();

        switch (userChoice)
        {
        case 1:
            addFriendToTheBook(friends);
            break;
        case 2:
            if (checkIfAnyFriendsExist(friends))
            {
                searchForFriendByName(friends);
            }
            break;
        case 3:
            if (checkIfAnyFriendsExist(friends))
            {
                searchForFriendBySurname(friends);
            }
            break;
        case 4:
            if (checkIfAnyFriendsExist(friends))
            {
                showAllFriends(friends);
            }
            break;
        case 5:
            if (checkIfAnyFriendsExist(friends))
            {
                editFriend(friends);
            }
            break;
        case 6:
            if (checkIfAnyFriendsExist(friends))
            {
                deleteFriend(friends);
            }
            break;
        case 9:
            exit(0);
            break;
        default:
            cout << "Nie ma takiej opcji, sprobuj ponownie" << endl;
            break;
        }

        cout << "Wcisnij dowolny przycisk by kontynuwac...";
        getchar();
        system("cls");
    }
    return 0;
}
