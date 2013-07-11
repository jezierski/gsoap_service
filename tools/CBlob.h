/* 
 * File:   CBlob.h
 * Author: jezierski
 *
 * Created on 29 czerwiec 2013, 10:17
 */

#ifndef CBLOB_H
#define	CBLOB_H

#include <map>
#include <iostream>
using namespace std;

class CBlob {
public:
    CBlob();
//    CBlob(const CBlob& orig);
    virtual ~CBlob();
    
    template <typename type>
    void put(type &t){
        get<type>() = t;
    }
    
    template<typename type>
    type &get(){
        cout<<"a: "<<a<<endl;
        static map<int, type> m;
        cout<<"m: "<<m.size()<<endl;
        cout<<"init: "<<init<<endl;
        return m[a];
    }
    
private:
    static int init;
    int a;
};

#endif	/* CBLOB_H */

