

#ifndef CDATABASE_H
#define	CDATABASE_H
#include <sqlite3.h>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;


class CDatabase {
public:

    enum dbType {
        MAIN,
        CONFIG,
        FINANCIAL,
    };

    sqlite3 *open(string filename);
    vector<vector<string> > query(string query, dbType type = CONFIG);
    void close(sqlite3 *database);
    static CDatabase *getInstance();
    bool isDatabaseOpen();
    int putConfig(string, string);
    string getConfig(string);
    map<string, string> getConfiguration();
    vector<vector<string> > getList(string name="");
    int updateList(string, map<string, string > );
private:
    
//    /string result;

    typedef struct db {
        string name;
        string path;
        dbType type;
        sqlite3 *instance;
    } dbDescription;
    
    sqlite3 *getDb(dbType);
    list<dbDescription> databases;
    CDatabase(const CDatabase& orig);
    CDatabase();
    ~CDatabase();
    static CDatabase *instance;
    bool dbOpen;
    int callback(void *NotUsed, int argc, char **argv, char **azColName);

};

#endif	/* CDATABASE_H */

