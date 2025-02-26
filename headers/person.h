#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

using namespace std;

namespace person
{
    struct PersonFriend
    {
        int id;
        string name, surname, email, address, phoneNumber;

        void assignData(vector <string> newFriendData)
        {
            this->id = stoi(newFriendData[0]);
            this->name = newFriendData[1];
            this->surname = newFriendData[2];
            this->email = newFriendData[3];
            this->address = newFriendData[4];
            this->phoneNumber = newFriendData[5];
        }

        bool isEqual(PersonFriend differentFriend)
        {
            bool result = true;
            if (this->name != differentFriend.name ||
                this->surname != differentFriend.surname ||
                this->email != differentFriend.email ||
                this->address != differentFriend.address ||
                this->phoneNumber != differentFriend.phoneNumber)
            {
                result = false;
            }

            return result;
        }

    };
}

#endif // PERSON_H_INCLUDED
