
#include <sqlite3.h>

#include "CConfiguration.h"


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


string CConfiguration::listConfig() {

   
    return NULL;
};
