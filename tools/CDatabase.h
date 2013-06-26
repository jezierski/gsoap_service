

#ifndef CDATABASE_H
#define	CDATABASE_H
#include <sqlite3.h>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>
#include <map>
#include "CLog.h"
using namespace std;


class CDatabase {
public:

 

    sqlite3 *open(string filename);
    vector<vector<string> > query(string query);
    void close(sqlite3 *database);
    static CDatabase *getInstance();

    
    
    
//    map<string, string> getConfiguration();
    
    
private:
    
//    /string result;

    typedef struct db {
        string name;
        string path;
        sqlite3 *instance;
    }db;
    
    db database;
    CDatabase(const CDatabase& orig);
    CDatabase();
    ~CDatabase();
    static CDatabase *instance;
    
    CLog *log;

};

#endif	/* CDATABASE_H */

