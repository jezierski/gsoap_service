
#include "CDatabase.h"

int CDatabase::putConfig(string field, string value) {
    vector<vector<string> > result = query(string("select value from config where field = '") + field + "'", CDatabase::CONFIG);
    
    if (result.size() > 0) {
        query(string("update config set value = '") + value + "' where field = '" + field + "'", CDatabase::CONFIG);
    } else {
        query("insert into config ('field', 'value') values('" + field + "', '" + value + "');", CDatabase::CONFIG);
    }
    return 0;
};

/**
 * 
 * @param listName
 * @param configMap
 * @return 
 */
int CDatabase::updateList(string listName, map<string, string> configMap) {
    map< string, string>::const_iterator itr;

    query("delete from config where list_name = '" + listName + "'", CDatabase::CONFIG);
    for (itr = configMap.begin(); itr != configMap.end(); ++itr) {
        query("insert into config VALUES('" + listName + "', '" + (*itr).first + "', '" + (*itr).second + "')");
    }

    return 0;
}

/**
 * 
 * @param listName
 * @return 
 */
vector<vector<string> > CDatabase::getList(string listName) {

    vector<vector<string> > result;
    if (listName == "")
        result = query(string("select list_name, field, value from config"), CDatabase::CONFIG);
    else
        result = query(string("select list_name, field, value from config where list_name = '") + listName + "'", CDatabase::CONFIG);

    return result;
}

string CDatabase::getConfig(string field) {
    vector<vector<string> > result = query(string("select value from config where field = '") + field + "'", CDatabase::CONFIG);

    if (result.size() > 0) {
        vector<vector<string> >::iterator it = result.begin();
        if ((*it).size() > 0) {
            vector<string> row = *it;
            return row.at(0);
        }
    }
    return "default parameter, todo!";
}

bool CDatabase::isDatabaseOpen() {
    return dbOpen;
}

map<string, string > CDatabase::getConfiguration() {
    vector<vector<string> > configList = getList();
    vector<vector<string> >::iterator it = configList.begin();
    map<string, string> configMap;
    string key, value;
    while (it != configList.end()) {
        
        vector<string> row = *it;
        if (row.at(0) != "")
            key = row.at(0)+"::"+row.at(1);
        else
            key = row.at(0);
        
        value = row.at(2);
        configMap[key] = value;
            it++;
    }
    return configMap;
}

CDatabase::CDatabase() {


    dbDescription db;
    db.instance = NULL;

    db.path = "../db/config.db";
    db.type = CONFIG;
    db.name = "Configuration database";
    databases.push_back(db);

    list<dbDescription>::iterator dbs = databases.begin();
    while (dbs != databases.end()) {
        (*dbs).instance = NULL;
        (*dbs).instance = open((*dbs).path);

        if ((*dbs).instance == NULL)
            cout << "Database handle is NULL (" << (*dbs).name << "). " << endl;
        else
            cout << "Using " << (*dbs).name << ": " << (*dbs).path << endl;
        dbs++;
    }
}

sqlite3 *CDatabase::open(string filename) {

    sqlite3 *database;
    if (sqlite3_open(filename.c_str(), &database) == SQLITE_OK)
        return database;

    throw string("Couldn't find database: " + filename);
}

void CDatabase::close(sqlite3 *database) {
    sqlite3_close(database);
}

sqlite3 *CDatabase::getDb(dbType type) {
    list<dbDescription>::iterator dbs = databases.begin();
    while (dbs != databases.end()) {
        if (type == (*dbs).type) {
            return (*dbs).instance;
        }
        dbs++;
    }
    throw string("Error, no database found for this type.");
    return NULL;
}

vector<vector<string> > CDatabase::query(string query, dbType type) {
    sqlite3_stmt *statement;
    vector<vector<string> > results;

    if (sqlite3_prepare_v2(getDb(type), query.c_str(), -1, &statement, 0) == SQLITE_OK) {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while (true) {
            result = sqlite3_step(statement);

            if (result == SQLITE_ROW) {
                vector<string> values;
                for (int col = 0; col < cols; col++) {
                    values.push_back((char*) sqlite3_column_text(statement, col));
                }
                results.push_back(values);
            } else {
                break;
            }
        }

        sqlite3_finalize(statement);
    }

    string error = sqlite3_errmsg(getDb(type));

    if (error != "not an error"){
        throw string("Query [" + query + "] error: " + error);
    }
    return results;
}

CDatabase::CDatabase(const CDatabase& orig) {
}

CDatabase::~CDatabase() {

    list<dbDescription>::iterator dbs = databases.begin();
    while (dbs != databases.end()) {

        close((*dbs).instance);
        dbs++;
    }
}

CDatabase *CDatabase::instance = NULL;

CDatabase* CDatabase::getInstance() {
    if (!instance)
        instance = new CDatabase();
    return instance;

}



