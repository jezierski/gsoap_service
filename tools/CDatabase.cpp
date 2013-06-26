
#include "CDatabase.h"
#include "CLog.h"





//map<string, string > CDatabase::getConfiguration() {
//    vector<vector<string> > configList = getList();
//    vector<vector<string> >::iterator it = configList.begin();
//    map<string, string> configMap;
//    string key, value;
//    while (it != configList.end()) {
//
//        vector<string> row = *it;
//        if (row.at(0) != "")
//            key = row.at(0) + "::" + row.at(1);
//        else
//            key = row.at(0);
//
//        value = row.at(2);
//        configMap[key] = value;
//        it++;
//    }
//    return configMap;
//}

CDatabase::CDatabase() {

    log = CLog::getInstance();

    database.path = "../db/config.db";
    database.name = "Configuration database";


    database.instance = NULL;
    database.instance = open(database.path);

    if (database.instance == NULL)
        log->put("Database handle is NULL (" + database.name + "). ", CLog::WARNING);
    else
        log->success("Using " + database.name + ": " + database.path);


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

vector<vector<string> > CDatabase::query(string query) {
    sqlite3_stmt *statement;
    vector<vector<string> > results;

    if (sqlite3_prepare_v2(database.instance, query.c_str(), -1, &statement, 0) == SQLITE_OK) {
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

    string error = sqlite3_errmsg(database.instance);

    if (error != "not an error") {
        throw string("Query [" + query + "] error: " + error);
    }
    return results;
}

CDatabase::CDatabase(const CDatabase& orig) {
}

CDatabase::~CDatabase() {


    close(database.instance);

}

CDatabase *CDatabase::instance = NULL;

CDatabase* CDatabase::getInstance() {
    if (!instance)
        instance = new CDatabase();
    return instance;

}



