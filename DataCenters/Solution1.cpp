// DataCenters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct DataCenter
{
    int ID;
    vector<int> dataSets;
} DataCenter;


void CompareAndUpdateDataSets(DataCenter& dc1, DataCenter& dc2)
{
    unsigned int dc1Counter = 0;
    unsigned int dc2Counter = 0;

    vector<int>::iterator iter;

    // Sort the data set container

    sort(dc1.dataSets.begin(), dc1.dataSets.end());

    sort(dc2.dataSets.begin(), dc2.dataSets.end());

    while (dc1Counter < dc1.dataSets.size() && dc2Counter < dc2.dataSets.size())
    {
        if (dc1.dataSets[dc1Counter] != dc2.dataSets[dc2Counter])
        {
            if (dc1.dataSets[dc1Counter] < dc2.dataSets[dc2Counter])
            {
                // Copy smaller value from dc1 to dc2
                iter = dc2.dataSets.begin();
                dc2.dataSets.insert(iter + dc2Counter, dc1.dataSets[dc1Counter]);
                cout << dc1.dataSets[dc1Counter] << " " << dc1.ID << " " << dc2.ID << endl;
            }
            else
            {
                // Copy smaller value from dc2 to dc1
                iter = dc1.dataSets.begin();
                dc1.dataSets.insert(iter + dc1Counter, dc2.dataSets[dc2Counter]);
                cout << dc2.dataSets[dc2Counter] << " " << dc2.ID << " " << dc1.ID << endl;
            }
        }

        dc1Counter++;
        dc2Counter++;
    }

    while (dc1.dataSets.size() != dc2.dataSets.size())
    {
        if (dc1Counter < dc1.dataSets.size())
        {
            // Copy from dc1 to dc2
            iter = dc2.dataSets.begin();
            dc2.dataSets.insert(iter + dc2Counter, dc1.dataSets[dc1Counter]);
            cout << dc1.dataSets[dc1Counter] << " " << dc1.ID << " " << dc2.ID << endl;
        }
        else
        {
            // copy from dc2 to dc1
            iter = dc1.dataSets.begin();
            dc1.dataSets.insert(iter + dc1Counter, dc2.dataSets[dc2Counter]);
            cout << dc2.dataSets[dc2Counter] << " " << dc2.ID << " " << dc1.ID << endl;
        }

        dc1Counter++;
        dc2Counter++;
    }

}

int _tmain(int argc, _TCHAR* argv[])
{
    int numberOfDataCenters;

    cin >> numberOfDataCenters;
    cin.ignore();

    list<string> dataSetInfoList;
    int count = 0; 

    for(int i = 0; i < numberOfDataCenters; i++)
    {
        string dataSetInfo;
        getline(cin, dataSetInfo, '\n');
        dataSetInfoList.push_back(dataSetInfo);
    }

    vector<DataCenter> dataCenters;
    int index  = 0;
    for(list<string>::iterator iter = dataSetInfoList.begin(); iter != dataSetInfoList.end(); iter++)
    {
        DataCenter dataCenter;

        dataCenter.ID = index + 1;

        char num = (*iter)[0];

        for(unsigned int i = 1; i < (*iter).length(); i++)
        {
            if (isdigit((*iter)[i]))
            {
                char num = (*iter)[i];
                dataCenter.dataSets.push_back(atoi(&num));
            }
        }

        dataCenters.push_back(dataCenter);

        index++;
    }

    for(unsigned int i = 0; i < dataCenters.size(); i++)
    {
        for(unsigned int j = i + 1; j < dataCenters.size(); j++)
        {
            CompareAndUpdateDataSets(dataCenters[i], dataCenters[j]);
        }
    }

    cout << "done" << endl;

    return 0;
}

