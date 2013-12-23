/* 
 * File:   CFirmwareLoader.cpp
 * Author: jezierski
 * 
 * Created on December 23, 2013, 9:30 AM
 */

#include "CFirmwareLoader.h"
#include "CFirmwareBuffer.h"

CFirmwareLoader::CFirmwareLoader() {
    log = CLog::getInstance();
}

//CFirmwareLoader::CFirmwareLoader(const CFirmwareLoader& orig) {
//}

CFirmwareLoader::~CFirmwareLoader() {
}

void CFirmwareLoader::printFileList() {
    vector<string> fileList;
    if (getdir("../firmware", fileList)) {
        log->error("Reading firmware path failed or directory not found");
        return;
    }
    log->put("Firmware files list:");
    int index = 1;
    for (string fileName : fileList) {
        log->put(to_string(index++) + ".\t" + fileName);
    }
}

CFirmwareBuffer CFirmwareLoader::readFile(string filename) {

    RawData data;
    CFirmwareBuffer buffer;
    CBuffer dataBuffer;
    string fileContent;
    ifstream myfile;
    myfile.open("../firmware/" + filename);

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            fileContent = "";
            myfile >> fileContent;
            if (fileContent != "") {
                data = parseData(fileContent);
                if (checkInputData(data)) {
                    dataBuffer = getData(data);
                    if (dataBuffer.getLength()) {
                        buffer.addData(getAddress(data), dataBuffer);
                    }
                } else {
                    throw string("Incorrect firmware file");
                }
            }
        }
        myfile.close();
    } else
        throw string("Unable to open file " + filename);

    return buffer;

}

bool CFirmwareLoader::checkCRC(RawData &input) {
    unsigned char crc = 0;
    for (unsigned char d : input) {
        crc += d;
    }
    return crc == 0;
}

bool CFirmwareLoader::checkInputData(RawData &input) {
    if (input.size() >= 5) {
        unsigned int inputSize = input[OFFSET_FIRMWARE_LENGTH] + 5;
        return (inputSize == input.size()) && checkCRC(input);
    }
    return false;
}

unsigned int CFirmwareLoader::getAddress(RawData &input) {
    unsigned int address = 0;
    if (input.size() >= 4) {
        address |= ((input[OFFSET_FIRMWARE_ADDR] << 8) & 0xff00);
        address |= ((input[OFFSET_FIRMWARE_ADDR + 1] << 0) & 0x00ff);
    }
    return address;
}

CBuffer CFirmwareLoader::getData(RawData &input) {
    CBuffer buffer;
    if (input.size() > 5) {
        for (size_t i = 0; i < input[OFFSET_FIRMWARE_LENGTH]; i++) {
            buffer << (unsigned char) input[OFFSET_FIRMWARE_DATA + i];
        }
    }
    return buffer;
}

RawData CFirmwareLoader::parseData(string &input) {
    RawData data;
    unsigned int index = 0;
    if (input[index] == ':') {
        index++;
        while (index <= (input.length() - 2)) {
            data.push_back(static_cast<unsigned char> (fromString<unsigned int>(input.substr(index, 2), 1)));
            index += 2;
        }
    }
    return data;
}