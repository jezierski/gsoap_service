

#include "CBuffer.h"

CBuffer::CBuffer() {
    ready = false;
}

void CBuffer::setReady() {
    ready = true;
}

void CBuffer::printBuffer() {

    cout << hex;
    for (unsigned char c : buffer)
        cout << "0x" << (int) c << " ";

    cout << dec << endl;
    cout<<endl;
}



//////////////////////////////////////////////////////////////////////
/// Request a command from buffer
/// \param none
/// \return command

unsigned char CBuffer::getCommand() {
    return command;
}

//////////////////////////////////////////////////////////////////////
/// Requested a buffer
/// \param none
/// \return pointer to buffer

vector<unsigned char> &CBuffer::getBuffer() {
    return buffer; 
}

//////////////////////////////////////////////////////////////////////
/// Requested a single byte from buffer
/// \param index index of requested byte
/// \return requested byte

unsigned char CBuffer::getBuffer(unsigned char index) {
    if (index < len)
        return buffer[index];
    else
        return 0;
}

bool CBuffer::isReady() {
    return ready;
}

CBuffer CBuffer::subBuffer(unsigned char start, unsigned char length) {

    CBuffer subBuffer;
    unsigned char end = length + start;
    if (length == 0)
        end = buffer.size();

    for (unsigned char i = start; i < end; i++)
        subBuffer << (unsigned char) buffer[i];

    return subBuffer;
}

//////////////////////////////////////////////////////////////////////
/// Requested a buffer length
/// \param none
/// \return buffer length

size_t CBuffer::getLength() {
    return buffer.size();
}


//////////////////////////////////////////////////////////////////////
/// Operator == to compare two buffers
/// \param buf buffer to compare
/// \return equality of buffers

bool CBuffer::operator ==(CBuffer &buf) {
    if (getLength() != buf.getLength())
        return false;

    for (size_t i = 0; i < getLength(); i++) {
        if (getBuffer(i) != buf.getBuffer(i))
            return false;
    }

    return true;
}

void CBuffer::clear() {
    this->buffer.clear();
    this->ready = false;
}


//////////////////////////////////////////////////////////////////////
/// Operator = to copy all fields from selected buffer
/// \param buf selected buffer to copy data from
/// \return none

//void CBuffer::operator =(CBuffer &buf) {
// //jak bedzie potrzebne, to sie zrobi
// // delete []this->buffer;
// // this->buffer = new unsigned char[buf.len];
// // memcpy(this->buffer, buf.buffer, buf.len);
// // this->command = buf.command;
// // this->len = buf.len;
//}

CBuffer::operator string() {
    //return string((char*)&buffer[0]);
    string str = "";
    //while (auto it != buffer.end())
    // str += *(it++);
    for (unsigned char chr : buffer)
        str += chr;

    return str;
}

wstring CBuffer::getWstring() {
    //return string((char*)&buffer[0]);
    wstring str = L"";
    //while (auto it != buffer.end())
    // str += *(it++);
    for (size_t i = 0; i < buffer.size(); i += 2) {

        str += buffer[i] | ((buffer[i + 1] << 8)&0xff00);
    }
    return str;
}

CBuffer& CBuffer::operator <<(int num) {

    this->buffer.push_back(0xff & (num >> 8));
    this->buffer.push_back(0xff & (num >> 0));
    return *this;
}

CBuffer& CBuffer::operator <<(short num) {
    //to trzeba poprawić chyba
    this->buffer.push_back(0xff & (num >> 0));
    this->buffer.push_back(0xff & (num >> 8));
    return *this;
}

CBuffer& CBuffer::operator <<(unsigned int num) {

    this->buffer.push_back(0xff & (num >> 8));
    this->buffer.push_back(0xff & (num >> 0));
    return *this;
}

CBuffer& CBuffer::operator <<(unsigned char num) {


    buffer.push_back(num);
    return *this;
}

CBuffer& CBuffer::operator <<(CBuffer &buf) {

    for (size_t i = 0; i < buf.getLength(); i++)
        buffer.push_back(buf.getBuffer()[i]);
    return *this;
}

unsigned char CBuffer::operator[](unsigned int index) {
    if ((size_t) index < getLength())
        return buffer[index];
    else
        return 0;
}

CBuffer& CBuffer::operator <<(string str) {
    char *c = const_cast<char*> (str.c_str());

    while (*c != 0)
        buffer.push_back(*(c++));

    return *this;
}

CBuffer& CBuffer::operator <<(wstring str) {

    //memcpy(&(buffer[bufferPointer]), str.c_str(), str.length());
    for (size_t i = 0; i < str.length(); i++) {
        buffer.push_back(0xff & str[i]);
        buffer.push_back(0xff & (str[i] >> 8));
    }


    // string debug;
    // debug = "Buffer: ";
    //
    // for (int i = 0; i < bufferPointer; i++)
    // debug += "0x" + to_string((int) buffer[i], 1) + " ";

    //SHOW(debug)

    return *this;
}

CBuffer::~CBuffer() {

}

bool CBuffer::isACK(){
    return (this->operator [](1) == '0'); 
}

bool CBuffer::isNoData(){
    return (this->operator [](1) == '3'); 
}

unsigned char CBuffer::getErrorCode(){
    return (this->operator [](1) - 0x30); 
}