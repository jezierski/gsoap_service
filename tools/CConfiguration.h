
#ifndef CCONFIGURATION_H
#define CCONFIGURATION_H
#include <string>
#include <sstream>
#include "CDatabase.h"
#include <map>
#include <algorithm>


using namespace std;

class CConfiguration {
public:



    template <typename type>
    type getValue(string field) {
        std::istringstream is(database->getConfig(string(field)));
        type value;
        is >> value;
        return value;
    };

    template <typename type>
    map <string, type> getList(string field) {

        type value;
        vector<vector<string> > result = database->getList(field);
        map<string, type> resultSet;

        if (result.size() > 0) {
            vector<vector<string> >::iterator it = result.begin();

            while (it < result.end()) {
                if ((*it).size() > 0) {
                    vector<string> row = *it;
                    istringstream(row.at(2)) >> value;
                    resultSet[row.at(1)] = value;

                }
                it++;
            }
        }

        return resultSet;
    };

    map <string, string> getList(string field) {

        vector<vector<string> > result = database->getList(field);
        map<string, string> resultSet;

        if (result.size() > 0) {
            vector<vector<string> >::iterator it = result.begin();

            while (it < result.end()) {
                if ((*it).size() > 0) {
                    vector<string> row = *it;
                    resultSet[row.at(1)] = row.at(2);

                }
                it++;
            }
        }

        return resultSet;
    };

  
    template <typename type>
    void updateList(string listName, map<string, type> configMap) {

        typename map<string, type>::iterator itr;
        map<string, string> config;


        for (itr = configMap.begin(); itr != configMap.end(); ++itr) {
            stringstream ss;
            ss << (*itr).second;
            config[(*itr).first] = ss.str();
        }

        database->updateList(listName, config);
    }

    void updateList(string listName, map<string, string> configMap) {

        typename map<string, string>::iterator itr;
        map<string, string> config;


        for (itr = configMap.begin(); itr != configMap.end(); ++itr) {
            config[(*itr).first] = (*itr).second;
        }

        database->updateList(listName, config);
    }

    template <typename type>
    void setNewValue(string listName, string field, type value) {
        map<string, type> tempMap = getList<type > (listName);
        tempMap[field] = value;
        updateList<type > (listName, tempMap);
    }

    template <typename type>
    bool isValueSet(string listName, string field) {

        map <string, type> tempMap = getList<type > (listName);
        if (!tempMap.size())
            return false;

        if (!tempMap.count(field))
            return false;

        return true;

    }

   
    template <typename type>
    int setValue(string value, type field) {
        return database->putConfig(value, field);

    }



    string listConfig();

    virtual ~CConfiguration();
    static CConfiguration* getInstance();



private:
    CConfiguration();
    CConfiguration(const CConfiguration& orig);
    static CConfiguration *instance;
    CDatabase *database;
    string ver;
};

#endif  /* CCONFIGURATION_H */
