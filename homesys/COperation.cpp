/* 
 * File:   COperation.cpp
 * Author: jezierski
 * 
 * Created on 20 lipiec 2013, 21:36
 */

#include "COperation.h"
#include "CDevice.h"


COperation::COperation() {
    log = CLog::getInstance();
    initNodeFunctors();
    initSensorAttributeFunctor();
    initActorAttributeFunctor();
    initTimeAttributeFunctor();
}

//COperation::COperation(const COperation& orig) {
//}

COperation::~COperation() {
}

string COperation::readFile(string filename) {

    string fileContent;
    string text;
    ifstream myfile;
    myfile.open(filename);

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            fileContent = "";
            myfile >> fileContent;

            text += fileContent + " ";
        }
        myfile.close();
    } else
        throw string("Unable to open file " + filename);

    return text;
}

void COperation::loadOperations() {
    log->info("Loading operations...");
    string text = readFile("../xml/operations.xml");


    char* xml = new char[text.length() + 1];
    strcpy(xml, text.c_str());

    try {
        xml_document<> doc;
        doc.parse < 0 > (xml);

        xml_node<> *node;
        node = doc.first_node();

        operations.clear();
        SOperation operation;
        while (node != NULL) {
            parseNode(node->name(), node, operation);
            addOperation(operation);
            clearOperation(operation);
            node = node->next_sibling();
        }

//        for (SOperation op : operations) {
//            cout << "=>OPERATION: " << endl;
//
//            for (SDeviceCondition con : op.deviceConditions) {
//                cout << "===>DEVICE CONDITIONS:" << endl;
//                cout << "param: " << (int) (con.command) << endl;
//                cout << "condi: " << (int) (con.condition) << endl;
//                cout << "guid : " << (int) (con.device.guid) << endl;
//                cout << "luid : " << (int) (con.device.luid) << endl;
//                cout << "categ: " << (int) (con.device.category) << endl;
//                for (int i = 0; i < con.params.size(); i++) {
//                    cout << "param[" << i << "]: " << (int) (con.params[i]) << endl;
//                }
//            }
//
//            for (STimeCondition con : op.timeConditions) {
//                cout << "===>TIME CONDITIONS:" << endl;
//                cout << "condi: " << (int) (con.condition) << endl;
//                cout << "value: " << (long long) (con.time) << endl;
//
//            }
//
//            cout << "===>ACTION:" << endl;
//            cout << "param: " << (int) (op.action.command) << endl;
//            cout << "guid : " << (int) (op.action.device.guid) << endl;
//            cout << "luid : " << (int) (op.action.device.luid) << endl;
//            cout << "categ: " << (int) (op.action.device.category) << endl;
//            for (int i = 0; i < op.action.params.size(); i++) {
//                cout << "param[" << i << "]: " << (int) (op.action.params[i]) << endl;
//            }
//        }


    } catch (parse_error e) {
        log->error("XML parser error: " + string(e.what()));
        operations.clear();
        return;
    } catch (string e) {
        log->error("XML document wrong format: " + e);
        operations.clear();
        return;
    }
    log->success("Loading operations success");
}

void COperation::parseNode(string nodeName, const xml_node<>* node, SOperation &operation) {
    if (nodeFunctors.find(nodeName) == nodeFunctors.end())
        throw string("unknown node: " + nodeName);
    (this->*nodeFunctors[nodeName])(node, operation);

}

void COperation::parseSensorAttribute(string attributeName, string value, SDeviceCondition& condition) {
    if (sensorAttributeFunctors.find(attributeName) == sensorAttributeFunctors.end())
        throw string("unknown sensor attribute: " + attributeName);
    (this->*sensorAttributeFunctors[attributeName])(value, condition);

}

void COperation::parseActorAttribute(string attributeName, string value, SAction& action) {
    if (actorAttributeFunctors.find(attributeName) == actorAttributeFunctors.end())
        throw string("unknown actor attribute: " + attributeName);
    (this->*actorAttributeFunctors[attributeName])(value, action);

}

void COperation::parseTimeAttribute(string attributeName, string value, STimeCondition& condition) {
    if (timeAttributeFunctors.find(attributeName) == timeAttributeFunctors.end())
        throw string("unknown time attribute: " + attributeName);
    (this->*timeAttributeFunctors[attributeName])(value, condition);

}

void COperation::nodeOperation(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeOperation, params:" << endl;

    xml_node<> *childnode;

    childnode = node->first_node();
    while (childnode != NULL) {
        parseNode(childnode->name(), childnode, operation);
        childnode = childnode->next_sibling();
    }

}

void COperation::nodeCondition(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeCondition, params:" << endl;

    xml_node<> *childnode;

    childnode = node->first_node();
    while (childnode != NULL) {
        parseNode(childnode->name(), childnode, operation);
        childnode = childnode->next_sibling();
    }

}

void COperation::nodeAction(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeAction, params:" << endl;
    xml_node<> *childnode;

    childnode = node->first_node();
    while (childnode != NULL) {
        parseNode(childnode->name(), childnode, operation);
        childnode = childnode->next_sibling();
    }
}

void COperation::nodeSensor(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeSensor, params:" << endl;
    operation.deviceConditions.push_back(parseSensor(node));

}

void COperation::nodeActor(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeActor, params:" << endl;
    operation.action = parseActor(node);

}

void COperation::nodeTime(const xml_node<>* node, SOperation &operation) {
    //    cout << "nodeTime, params:" << endl;
    operation.timeConditions.push_back(parseTime(node));
}

void COperation::initNodeFunctors() {
    nodeFunctors["operation"] = &COperation::nodeOperation;
    nodeFunctors["condition"] = &COperation::nodeCondition;
    nodeFunctors["action"] = &COperation::nodeAction;
    nodeFunctors["sensor"] = &COperation::nodeSensor;
    nodeFunctors["actor"] = &COperation::nodeActor;
    nodeFunctors["time"] = &COperation::nodeTime;
}

void COperation::initSensorAttributeFunctor() {
    sensorAttributeFunctors["guid"] = &COperation::parseGUID;
    sensorAttributeFunctors["luid"] = &COperation::parseLUID;
    sensorAttributeFunctors["cat"] = &COperation::parseCategory;
    sensorAttributeFunctors["param"] = &COperation::parseCommand;
    sensorAttributeFunctors["comp"] = &COperation::parseCondition;
    sensorAttributeFunctors["val"] = &COperation::parseParams;
}

void COperation::initActorAttributeFunctor() {
    actorAttributeFunctors["guid"] = &COperation::parseGUID;
    actorAttributeFunctors["luid"] = &COperation::parseLUID;
    actorAttributeFunctors["cat"] = &COperation::parseCategory;
    actorAttributeFunctors["param"] = &COperation::parseCommand;
    actorAttributeFunctors["val"] = &COperation::parseParams;
}

void COperation::initTimeAttributeFunctor() {
    timeAttributeFunctors["comp"] = &COperation::parseCondition;
    timeAttributeFunctors["val"] = &COperation::parseParams;
}

SDeviceCondition COperation::parseSensor(const xml_node<>* node) {
    SDeviceCondition condition;
    int attributes = 0;
    for (xml_attribute<> *attr = node->first_attribute();
            attr; attr = attr->next_attribute()) {
        //        cout << "atr name: " << attr->name() << ", val: " << attr->value() << endl;
        attributes++;
        parseSensorAttribute(string(attr->name()), string(attr->value()), condition);
    }
    if (attributes != 6) {
        throw string("Wrong sensor parameters number, should be 6, got " + to_string(attributes));
    }
    return condition;
}

void COperation::parseParams(string input, Params &params) {
    int len = input.length();
    if (len % 2 || len > 10) {
        throw string("VALUE wrong format");
    }
    long long nmb = fromString<long long>(input, 1);
    for (int i = len / 2; i > 0; i--) {
        params.push_back((nmb >> (8 * (i - 1))) & 0xff);
    }
}

STimeCondition COperation::parseTime(const xml_node<>* node) {
    STimeCondition timeCondition;
    int attributes = 0;
    for (xml_attribute<> *attr = node->first_attribute();
            attr; attr = attr->next_attribute()) {
        //        cout << "atr name: " << attr->name() << ", val: " << attr->value() << endl;
        attributes++;
        parseTimeAttribute(string(attr->name()), string(attr->value()), timeCondition);
    }
    if (attributes != 2) {
        throw string("Wrong time parameters number, should be 2, got " + to_string(attributes));
    }
    return timeCondition;
}

SAction COperation::parseActor(const xml_node<>* node) {
    SAction action;
    int attributes = 0;
    for (xml_attribute<> *attr = node->first_attribute();
            attr; attr = attr->next_attribute()) {
        //        cout << "atr name: " << attr->name() << ", val: " << attr->value() << endl;
        attributes++;
        parseActorAttribute(string(attr->name()), string(attr->value()), action);
    }
    if (attributes != 5) {
        throw string("Wrong action parameters number, should be 5, got " + to_string(attributes));
    }
    return action;
}

void COperation::parseGUID(string value, SDeviceCondition& condition) {
    unsigned int guid = fromString<unsigned int>(value);
    if (guid != 0) {
        condition.device.guid = guid;
    } else {
        throw string("Sensor GUID cannot be null");
    }
}

void COperation::parseLUID(string value, SDeviceCondition& condition) {
    unsigned int luid = fromString<unsigned int>(value);
    //if (luid != 0) {
    condition.device.luid = static_cast<unsigned char> (luid);
    // } else {
    //     throw string("sensor LUID cannot be null");
    // }
}

void COperation::parseCategory(string value, SDeviceCondition& condition) {
    unsigned int cat = fromString<unsigned int>(value);
    if (cat != 0) {
        condition.device.category = static_cast<EDeviceCategory> (cat);
    } else {
        throw string("Sensor CATEGORY cannot be null");
    }
}

void COperation::parseCommand(string value, SDeviceCondition& condition) {
    unsigned int param = fromString<unsigned int>(value);
    if (param != 0) {
        condition.command = static_cast<Command> (param);
    } else {
        throw string("Sensor PARAMETER cannot be null");
    }
}

void COperation::parseCondition(string value, SDeviceCondition& condition) {
    if (value == "equal") {
        condition.condition = ECondition::Equal;
    } else if (value == "less") {
        condition.condition = ECondition::Less;
    } else if (value == "more") {
        condition.condition = ECondition::More;
    } else if (value == "lessequal") {
        condition.condition = ECondition::LessOrEqual;
    } else if (value == "moreequal") {
        condition.condition = ECondition::MoreOrEqual;
    } else {
        throw string("sensor CONDITION unknown");
    }
}

void COperation::parseParams(string value, SDeviceCondition& condition) {
    Params params;
    parseParams(value, params);
    condition.params = params;
}

//void COperation::parseParams(string value, long long& time){
//    int len = input.length();
//    if (len % 2 || len > 10) {
//        throw string("VALUE wrong format");
//    }
//    long long nmb = fromString<long long>(input, 1);
//    for (int i = len / 2; i > 0; i--) {
//        params.push_back((nmb >> (8 * (i - 1))) & 0xff);
//    }
//}

void COperation::parseCondition(string value, STimeCondition& condition) {
    if (value == "equal") {
        condition.condition = ECondition::Equal;
    } else if (value == "less") {
        condition.condition = ECondition::Less;
    } else if (value == "more") {
        condition.condition = ECondition::More;
    } else if (value == "lessequal") {
        condition.condition = ECondition::LessOrEqual;
    } else if (value == "moreequal") {
        condition.condition = ECondition::MoreOrEqual;
    } else {
        throw string("time CONDITION unknown");
    }
}

void COperation::parseParams(string value, STimeCondition& condition) {
    long long param = fromString<long long>(value);
    if (param != 0) {
        condition.time = param;
    } else {
        throw string("Time VALUE cannot be null");
    }
}

void COperation::parseGUID(string value, SAction& action) {
    unsigned int guid = fromString<unsigned int>(value);
    if (guid != 0) {
        action.device.guid = guid;
    } else {
        throw string("Actor GUID cannot be null");
    }
}

void COperation::parseLUID(string value, SAction& action) {
    unsigned int luid = fromString<unsigned int>(value);
    //if (luid != 0) {
        action.device.luid = static_cast<unsigned char> (luid);
    //} else {
   //     throw string("actor LUID cannot be null");
   // }
}

void COperation::parseCategory(string value, SAction& action) {
    unsigned int cat = fromString<unsigned int>(value);
    if (cat != 0) {
        action.device.category = static_cast<EDeviceCategory> (cat);
    } else {
        throw string("Actor CATEGORY cannot be null");
    }
}

void COperation::parseCommand(string value, SAction& action) {
    unsigned int param = fromString<unsigned int>(value);
    if (param != 0) {
        action.command = static_cast<Command> (param);
    } else {
        throw string("Actor PARAMETER cannot be null");
    }
}

void COperation::parseParams(string value, SAction& action) {
    Params params;
    parseParams(value, params);
    Blob b;
    b[BLOB_ACTION_PARAMETER].put<Params>(params);
    action.params = b;
}

void COperation::addOperation(SOperation operation) {
    if (operation.action.device.guid != 0
            && (operation.deviceConditions.size()
            || operation.timeConditions.size()))
        operations.push_back(operation);
}

void COperation::clearOperation(SOperation &operation) {
    operation.action.command = operation.action.device.address = operation.action.device.guid = operation.action.device.luid = 0;
    operation.action.params.clear();
    operation.deviceConditions.clear();
    operation.timeConditions.clear();
}

list<SOperation> COperation::getOperations() {
    return operations;
}