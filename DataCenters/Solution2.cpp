// DataSets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;

// The solution uses 2 hash tables
// Hash Table 1 is Data Center => DataSets
// Hash Table 2 is Data Set => Data Centers

// use the input to populate these two tables. Then iterate through Hash Table 2 and Hash Table 1, 
// till all data centers in Hash Table 1 till each data center has all data sets (keys) in Hash Table 2

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

    map<int, set<int>> dataCenterToDataSets;
    map<int, set<int>>::iterator dataCenterToDataSetsIter;

    map<int, set<int>> dataSetToDataCenters;
    map<int, set<int>>::iterator dataSetsToDataCentersIter;

    int dataCenterID  = 1;
    for(list<string>::iterator iter = dataSetInfoList.begin(); iter != dataSetInfoList.end(); iter++)
    {
        char numberOfDataSets = (*iter)[0];

        dataCenterToDataSetsIter = dataCenterToDataSets.find(dataCenterID);

        set<int> dataSets;

        for(unsigned int i = 1; i < (*iter).length(); i++)
        {
            if (isdigit((*iter)[i]))
            {
                char number = (*iter)[i];
                int dataSetID = atoi(&number);
                dataSets.insert(dataSetID);

                // Also add dataset to datacenter mapping
                set<int> dataCenters;
                dataCenters.insert(dataCenterID);

                dataSetToDataCenters.insert(pair<int, set<int>>(dataSetID, dataCenters));
            }
        }

        dataCenterToDataSets.insert(pair<int, set<int>>(dataCenterID, dataSets));

        dataCenterID++;
    }

    for(dataSetsToDataCentersIter = dataSetToDataCenters.begin(); dataSetsToDataCentersIter != dataSetToDataCenters.end(); dataSetsToDataCentersIter++)
    {
        // check if data set exists in all of the data centers, if not copy it over

        for(dataCenterToDataSetsIter = dataCenterToDataSets.begin(); dataCenterToDataSetsIter != dataCenterToDataSets.end(); dataCenterToDataSetsIter++)
        {
            set<int> dataSets = dataCenterToDataSetsIter->second;

            set<int>::iterator dataSetIter = dataSets.find(dataSetsToDataCentersIter->first);

            if (dataSetIter == dataSets.end())
            {
                // Copying time <data-set-id> <source data center id> <destination data center id>
                int dataSetToBeCopied = dataSetsToDataCentersIter->first;
                int sourceDataCenterID = *((dataSetsToDataCentersIter->second).begin());
                int destinationDataCenterID = dataCenterToDataSetsIter->first;

                cout << dataSetToBeCopied << " " << sourceDataCenterID << " " << destinationDataCenterID << endl;

                // insert data set to be copied to dataCenterToDataSetsIter->second
                (dataCenterToDataSetsIter->second).insert(dataSetToBeCopied);
            }
        }
    }

    cout << "done" << endl;

    return 0;
}