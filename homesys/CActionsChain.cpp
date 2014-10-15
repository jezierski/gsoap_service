/* 
 * File:   CActionsChain.cpp
 * Author: jezierski
 * 
 * Created on August 8, 2013, 7:27 PM
 */

#include "CActionsChain.h"
#include "CActionTranslator.h"

CActionsChain::CActionsChain() {
    log = CLog::getInstance();
    initNodeFunctors();
    initActionAttributeFunctor();
}

//CActionsChain::CActionsChain(const CActionsChain& orig) {
//}

CActionsChain::~CActionsChain() {
}

string CActionsChain::readFile(string filename) {

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

void CActionsChain::loadActionsChain() {
    log->info("Loading actions chain...");
    string text = readFile("../xml/actions_chain.xml");


    char* xml = new char[text.length() + 1];
    strcpy(xml, text.c_str());

    try {
        xml_document<> doc;
        doc.parse < 0 > (xml);

        xml_node<> *node;
        node = doc.first_node();

        chains.clear();
        SChain chain;
        
        if (not string(node->name()).compare("action_chains")) {
            node = node->first_node();
        } else {
            throw string("action_chain XML file wrong format");
        }
        while (node != NULL) {
            parseNode(node->name(), node, chain);
            addChain(chain);
            clearChain(chain);
            node = node->next_sibling();
        }

        //        for (SChain op : chains) {
        //            cout << "=>CHAIN: " << endl;
        //
        //
        //            cout << "===>ACTION:" << endl;
        //            cout << "param: " << (int) (op.action.command) << endl;
        //            cout << "guid : " << (int) (op.action.device.guid) << endl;
        //            cout << "luid : " << (int) (op.action.device.luid) << endl;
        //            cout << "categ: " << (int) (op.action.device.category) << endl;
        //            for (int i = 0; i < op.action.params.size(); i++) {
        //                cout << "param[" << i << "]: " << (int) (op.action.params[i]) << endl;
        //            }
        //
        //            cout << "===>REACTION:" << endl;
        //            cout << "param: " << (int) (op.reaction.command) << endl;
        //            cout << "guid : " << (int) (op.reaction.device.guid) << endl;
        //            cout << "luid : " << (int) (op.reaction.device.luid) << endl;
        //            cout << "categ: " << (int) (op.reaction.device.category) << endl;
        //            for (int i = 0; i < op.reaction.params.size(); i++) {
        //                cout << "param[" << i << "]: " << (int) (op.reaction.params[i]) << endl;
        //            }
        //
        //        }


    } catch (parse_error e) {
        log->error("XML parser error: " + string(e.what()));
        chains.clear();
        return;
    } catch (string e) {
        log->error("XML document wrong format: " + e);
        chains.clear();
        return;
    }
    log->success("Loading actions chain success");

}

bool CActionsChain::isChainExist(SAction& action) {
    for (SChain chain : chains) {
        if (chain.action.device.category == action.device.category
                && chain.action.device.guid == action.device.guid
                && chain.action.device.luid == action.device.luid
                && chain.action.command == action.command
                && compareParams(chain.action.params, action.params)) {

            action.command = chain.reaction.command;
            action.device = chain.reaction.device;
            action.params = chain.reaction.params;
            return true;
        }

    }

    return false;
}

bool CActionsChain::compareParams(Blob param1, Blob param2) {
    LONG64 p1 = paramsToLL(param1[BLOB_ACTION_PARAMETER].get<Params>());
    LONG64 p2 = paramsToLL(param2[BLOB_ACTION_PARAMETER].get<Params>());
    return p1 == p2;
}

void CActionsChain::parseNode(string nodeName, const xml_node<>* node, SChain &chain) {
    if (nodeFunctors.find(nodeName) == nodeFunctors.end())
        throw string("unknown node: " + nodeName);
    (this->*nodeFunctors[nodeName])(node, chain);

}

void CActionsChain::parseActionAttribute(string attributeName, string value, SAction& action) {
    if (actionAttributeFunctors.find(attributeName) == actionAttributeFunctors.end())
        throw string("unknown action attribute: " + attributeName);
    (this->*actionAttributeFunctors[attributeName])(value, action);

}

void CActionsChain::initNodeFunctors() {
    nodeFunctors["chain"] = &CActionsChain::nodeChain;
    nodeFunctors["action"] = &CActionsChain::nodeAction;
    nodeFunctors["reaction"] = &CActionsChain::nodeReaction;
}

void CActionsChain::initActionAttributeFunctor() {
    actionAttributeFunctors["guid"] = &CActionsChain::parseGUID;
    actionAttributeFunctors["luid"] = &CActionsChain::parseLUID;
    actionAttributeFunctors["cat"] = &CActionsChain::parseCategory;
    actionAttributeFunctors["param"] = &CActionsChain::parseCommand;
    actionAttributeFunctors["val"] = &CActionsChain::parseParams;
}

void CActionsChain::nodeChain(const xml_node<>* node, SChain &chain) {
    //    cout << "nodeOperation, params:" << endl;

    xml_node<> *childnode;

    childnode = node->first_node();
    while (childnode != NULL) {
        parseNode(childnode->name(), childnode, chain);
        childnode = childnode->next_sibling();
    }

}

void CActionsChain::nodeAction(const xml_node<>* node, SChain &chain) {
    //    cout << "nodeAction, params:" << endl;
    xml_node<> *childnode;

    childnode = node->first_node();
    if (childnode != NULL) {
        chain.action = parseAction(childnode);
    } else {
        throw string("Action not defined");
    }
}

void CActionsChain::nodeReaction(const xml_node<>* node, SChain &chain) {
    //    cout << "nodeAction, params:" << endl;
    xml_node<> *childnode;

    childnode = node->first_node();
    if (childnode != NULL) {
        chain.reaction = parseReaction(childnode);
    } else {
        throw string("Action not defined");
    }
}

SAction CActionsChain::parseAction(const xml_node<>* node) {
    SAction action;
    int attributes = 0;
    for (xml_attribute<> *attr = node->first_attribute();
            attr; attr = attr->next_attribute()) {
        //        cout << "atr name: " << attr->name() << ", val: " << attr->value() << endl;
        attributes++;
        parseActionAttribute(string(attr->name()), string(attr->value()), action);
    }
    if (attributes != 5) {
        throw string("Wrong action parameters number, should be 5, got " + to_string(attributes));
    }
    return action;
}

SAction CActionsChain::parseReaction(const xml_node<>* node) {
    SAction action;
    int attributes = 0;
    for (xml_attribute<> *attr = node->first_attribute();
            attr; attr = attr->next_attribute()) {
        //        cout << "atr name: " << attr->name() << ", val: " << attr->value() << endl;
        attributes++;
        parseActionAttribute(string(attr->name()), string(attr->value()), action);
    }
    if (attributes != 5) {
        throw string("Wrong reaction parameters number, should be 5, got " + to_string(attributes));
    }
    return action;
}

void CActionsChain::parseGUID(string value, SAction& action) {
    unsigned int guid = fromString<unsigned int>(value);
    if (guid != 0) {
        action.device.guid = guid;
    } else {
        throw string("Actor GUID cannot be null");
    }
}

void CActionsChain::parseLUID(string value, SAction& action) {
    unsigned int luid = fromString<unsigned int>(value);
    //if (luid != 0) {
    action.device.luid = static_cast<unsigned char> (luid);
    //} else {
    //     throw string("actor LUID cannot be null");
    // }
}

void CActionsChain::parseCategory(string value, SAction& action) {
    unsigned int cat = fromString<unsigned int>(value);
    if (cat != 0) {
        action.device.category = static_cast<EDeviceCategory> (cat);
    } else {
        throw string("Actor CATEGORY cannot be null");
    }
}

void CActionsChain::parseCommand(string value, SAction& action) {
    unsigned int param = fromString<unsigned int>(value);
    if (param != 0) {
        action.command = static_cast<Command> (param);
    } else {
        throw string("Actor PARAMETER cannot be null");
    }
}

void CActionsChain::parseParams(string value, SAction& action) {
    Params params;
    parseParams(value, params);
    Blob b;
    b[BLOB_ACTION_PARAMETER].put<Params>(params);
    action.params = b;
}

void CActionsChain::parseParams(string input, Params &params) {
    int len = input.length();
    if (len % 2 || len > 10) {
        throw string("VALUE wrong format");
    }
    LONG64 nmb = fromString<LONG64>(input, 1);
    for (int i = len / 2; i > 0; i--) {
        params.push_back((nmb >> (8 * (i - 1))) & 0xff);
    }
}

void CActionsChain::addChain(SChain chain) {
    if (chain.action.device.guid != 0
            && chain.reaction.device.guid != 0)
        chains.push_back(chain);
}

void CActionsChain::clearChain(SChain &chain) {
    chain.action.command = chain.action.device.address = chain.action.device.guid = chain.action.device.luid = 0;
    chain.reaction.command = chain.reaction.device.address = chain.reaction.device.guid = chain.reaction.device.luid = 0;
}
