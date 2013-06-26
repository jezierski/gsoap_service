
#include <sqlite3.h>

#include "CConfiguration.h"

//@TODO objac uzycie funkcji configuration w try-catch
CConfiguration::CConfiguration() {
    database = CDatabase::getInstance();
}



CConfiguration::CConfiguration(const CConfiguration& orig) {
}

CConfiguration::~CConfiguration() {
}

CConfiguration* CConfiguration::getInstance() {
    if (!instance)
        instance = new CConfiguration();

    return instance;

}

CConfiguration* CConfiguration::instance = NULL;

int CConfiguration::putConfig(string field, string value) {
    vector<vector<string> > result = database->query(string("select value from config where field = '") + field + "'");
    
    if (result.size() > 0) {
        database->query(string("update config set value = '") + value + "' where field = '" + field + "'");
    } else {
        database->query("insert into config ('field', 'value') values('" + field + "', '" + value + "');");
    }
    return 0;
};

string CConfiguration::getConfig(string field) {
    vector<vector<string> > result = database->query(string("select value from config where field = '") + field + "'");

    if (result.size() > 0) {
        vector<vector<string> >::iterator it = result.begin();
        if ((*it).size() > 0) {
            vector<string> row = *it;
            return row.at(0);
        }
    }
    return "default parameter, todo!";
}

vector<vector<string> > CConfiguration::getConfigList(string listName) {

    vector<vector<string> > result;
    if (listName == "")
        result = database->query(string("select list_name, field, value from config"));
    else
        result = database->query(string("select list_name, field, value from config where list_name = '") + listName + "'");

    return result;
}

int CConfiguration::updateConfigList(string listName, map<string, string> configMap) {
    map< string, string>::const_iterator itr;

    database->query("delete from config where list_name = '" + listName + "'");
    for (itr = configMap.begin(); itr != configMap.end(); ++itr) {
        database->query("insert into config VALUES('" + listName + "', '" + (*itr).first + "', '" + (*itr).second + "')");
    }

    return 0;
}