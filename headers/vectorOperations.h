#ifndef VECTOROPERATIONS_H_INCLUDED
#define VECTOROPERATIONS_H_INCLUDED

using namespace std;

namespace vectorOperations
{

    vector <string> addDataToVector(string dataToSplit)
    {
        vector <string> vectorWithData;
        string singleData;

        stringstream myStream(dataToSplit);
        while(getline(myStream, singleData, '|'))
        {
            vectorWithData.push_back(singleData);
        }
        return vectorWithData;
    }

}

#endif // VECTOROPERATIONS_H_INCLUDED
