#ifndef FILEOPERATIONS_H_INCLUDED
#define FILEOPERATIONS_H_INCLUDED
#include "person.h"
#include "vectorOperations.h"

using namespace std;
using namespace person;
using namespace vectorOperations;

namespace fileOperation
{
    string fileName = "phoneBook.txt";

    void saveSinglePersonToFile(PersonFriend newFriend, fstream &file)
    {
        file << newFriend.id << "|"
        << newFriend.name << "|"
        << newFriend.surname << "|"
        << newFriend.email << "|"
        << newFriend.address << "|"
        << newFriend.phoneNumber << endl;
    }

    void saveToFile(PersonFriend newFriend)
    {
        fstream file;
        file.open(fileName, ios::out | ios::app);
        saveSinglePersonToFile(newFriend, file);
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

}

#endif // FILEOPERATIONS_H_INCLUDED
