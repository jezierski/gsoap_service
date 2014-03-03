/* soapStub.h
   Generated by gSOAP 2.8.7 from homesys.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_ns1	"http://adjserwer.dyndns.org/soap_server/webservice/homesys.wsdl"
#include "stdsoap2.h"
#if GSOAP_H_VERSION != 20807
# error "GSOAP VERSION MISMATCH IN GENERATED CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_xsd__anyType
#define SOAP_TYPE_xsd__anyType (10)
/* Primitive xsd:anyType schema type: */
class SOAP_CMAC xsd__anyType
{
public:
	char *__item;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 10; } /* = unique id SOAP_TYPE_xsd__anyType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__anyType() { xsd__anyType::soap_default(NULL); }
	virtual ~xsd__anyType() { }
};
#endif

#ifndef SOAP_TYPE_xsd__base64Binary
#define SOAP_TYPE_xsd__base64Binary (13)
/* Base64 schema type: */
class SOAP_CMAC xsd__base64Binary
{
public:
	unsigned char *__ptr;
	int __size;
	char *id;	/* optional element of type xsd:string */
	char *type;	/* optional element of type xsd:string */
	char *options;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 13; } /* = unique id SOAP_TYPE_xsd__base64Binary */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__base64Binary() { xsd__base64Binary::soap_default(NULL); }
	virtual ~xsd__base64Binary() { }
};
#endif

#ifndef SOAP_TYPE_xsd__hexBinary
#define SOAP_TYPE_xsd__hexBinary (17)
/* hexBinary schema type: */
class SOAP_CMAC xsd__hexBinary
{
public:
	unsigned char *__ptr;
	int __size;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 17; } /* = unique id SOAP_TYPE_xsd__hexBinary */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__hexBinary() { xsd__hexBinary::soap_default(NULL); }
	virtual ~xsd__hexBinary() { }
};
#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_ns1__responseType
#define SOAP_TYPE_ns1__responseType (52)
/* ns1:responseType */
class SOAP_CMAC ns1__responseType
{
public:
	std::string result;	/* required element of type xsd:string */
	class ns1__valuesType *values;	/* required element of type ns1:valuesType */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 52; } /* = unique id SOAP_TYPE_ns1__responseType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__responseType() { ns1__responseType::soap_default(NULL); }
	virtual ~ns1__responseType() { }
};
#endif

#ifndef SOAP_TYPE_ns1__valuesType
#define SOAP_TYPE_ns1__valuesType (53)
/* ns1:valuesType */
class SOAP_CMAC ns1__valuesType
{
public:
	std::string responseMessage;	/* required element of type xsd:string */
	class ns1__valueType *values;	/* required element of type ns1:valueType */
	LONG64 numValues;	/* required element of type xsd:integer */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 53; } /* = unique id SOAP_TYPE_ns1__valuesType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__valuesType() { ns1__valuesType::soap_default(NULL); }
	virtual ~ns1__valuesType() { }
};
#endif

#ifndef SOAP_TYPE_ns1__valueType
#define SOAP_TYPE_ns1__valueType (54)
/* ns1:valueType */
class SOAP_CMAC ns1__valueType
{
public:
	std::vector<LONG64 >value;	/* required element of type xsd:integer */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 54; } /* = unique id SOAP_TYPE_ns1__valueType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__valueType() { ns1__valueType::soap_default(NULL); }
	virtual ~ns1__valueType() { }
};
#endif

#ifndef SOAP_TYPE_ns1__SDeviceDescription
#define SOAP_TYPE_ns1__SDeviceDescription (55)
/* ns1:SDeviceDescription */
class SOAP_CMAC ns1__SDeviceDescription
{
public:
	LONG64 GUID;	/* required element of type xsd:integer */
	LONG64 LUID;	/* required element of type xsd:integer */
	LONG64 category;	/* required element of type xsd:integer */
	std::string name;	/* required element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 55; } /* = unique id SOAP_TYPE_ns1__SDeviceDescription */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__SDeviceDescription() { ns1__SDeviceDescription::soap_default(NULL); }
	virtual ~ns1__SDeviceDescription() { }
};
#endif

#ifndef SOAP_TYPE_ns1__devicesList
#define SOAP_TYPE_ns1__devicesList (56)
/* ns1:devicesList */
class SOAP_CMAC ns1__devicesList
{
public:
	std::vector<ns1__SDeviceDescription * >item;	/* required element of type ns1:SDeviceDescription */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 56; } /* = unique id SOAP_TYPE_ns1__devicesList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__devicesList() { ns1__devicesList::soap_default(NULL); }
	virtual ~ns1__devicesList() { }
};
#endif

#ifndef SOAP_TYPE_ns1__filesList
#define SOAP_TYPE_ns1__filesList (57)
/* ns1:filesList */
class SOAP_CMAC ns1__filesList
{
public:
	std::vector<std::string >fileName;	/* required element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 57; } /* = unique id SOAP_TYPE_ns1__filesList */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns1__filesList() { ns1__filesList::soap_default(NULL); }
	virtual ~ns1__filesList() { }
};
#endif

#ifndef SOAP_TYPE_ns1__getXMLResponse
#define SOAP_TYPE_ns1__getXMLResponse (67)
/* ns1:getXMLResponse */
struct ns1__getXMLResponse
{
public:
	std::string result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__getXML
#define SOAP_TYPE_ns1__getXML (68)
/* ns1:getXML */
struct ns1__getXML
{
public:
	std::string id;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__searchNewDevicesResponse
#define SOAP_TYPE_ns1__searchNewDevicesResponse (69)
/* ns1:searchNewDevicesResponse */
struct ns1__searchNewDevicesResponse
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns1__searchNewDevices
#define SOAP_TYPE_ns1__searchNewDevices (72)
/* ns1:searchNewDevices */
struct ns1__searchNewDevices
{
public:
	LONG64 category;	/* required element of type xsd:integer */
};
#endif

#ifndef SOAP_TYPE_ns1__setDeviceNameResponse
#define SOAP_TYPE_ns1__setDeviceNameResponse (74)
/* ns1:setDeviceNameResponse */
struct ns1__setDeviceNameResponse
{
public:
	std::string response;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__setDeviceName
#define SOAP_TYPE_ns1__setDeviceName (75)
/* ns1:setDeviceName */
struct ns1__setDeviceName
{
public:
	ns1__SDeviceDescription *device;	/* optional element of type ns1:SDeviceDescription */
	std::string name;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__saveXMLResponse
#define SOAP_TYPE_ns1__saveXMLResponse (77)
/* ns1:saveXMLResponse */
struct ns1__saveXMLResponse
{
public:
	std::string result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__saveXML
#define SOAP_TYPE_ns1__saveXML (78)
/* ns1:saveXML */
struct ns1__saveXML
{
public:
	std::string id;	/* required element of type xsd:string */
	std::string body;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__switchPortResponse
#define SOAP_TYPE_ns1__switchPortResponse (80)
/* ns1:switchPortResponse */
struct ns1__switchPortResponse
{
public:
	std::string result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__switchPort
#define SOAP_TYPE_ns1__switchPort (81)
/* ns1:switchPort */
struct ns1__switchPort
{
public:
	std::string pinNo;	/* required element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns1__makeRemoteActionResponse
#define SOAP_TYPE_ns1__makeRemoteActionResponse (82)
/* ns1:makeRemoteActionResponse */
struct ns1__makeRemoteActionResponse
{
public:
	ns1__responseType *response;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:responseType */
};
#endif

#ifndef SOAP_TYPE_ns1__makeRemoteAction
#define SOAP_TYPE_ns1__makeRemoteAction (86)
/* ns1:makeRemoteAction */
struct ns1__makeRemoteAction
{
public:
	ns1__SDeviceDescription *device;	/* optional element of type ns1:SDeviceDescription */
	LONG64 command;	/* required element of type xsd:integer */
	LONG64 params;	/* required element of type xsd:integer */
};
#endif

#ifndef SOAP_TYPE_ns1__getDevicesListResponse
#define SOAP_TYPE_ns1__getDevicesListResponse (87)
/* ns1:getDevicesListResponse */
struct ns1__getDevicesListResponse
{
public:
	ns1__devicesList *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:devicesList */
};
#endif

#ifndef SOAP_TYPE_ns1__getDevicesList
#define SOAP_TYPE_ns1__getDevicesList (91)
/* ns1:getDevicesList */
struct ns1__getDevicesList
{
public:
	LONG64 category;	/* required element of type xsd:integer */
};
#endif

#ifndef SOAP_TYPE_ns1__getFilesListResponse
#define SOAP_TYPE_ns1__getFilesListResponse (92)
/* ns1:getFilesListResponse */
struct ns1__getFilesListResponse
{
public:
	ns1__filesList *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns1:filesList */
};
#endif

#ifndef SOAP_TYPE_ns1__getFilesList
#define SOAP_TYPE_ns1__getFilesList (96)
/* ns1:getFilesList */
struct ns1__getFilesList
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (97)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (98)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (100)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (103)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (104)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif

#ifndef SOAP_TYPE__xml__lang
#define SOAP_TYPE__xml__lang (8)
typedef char *_xml__lang;
#endif

#ifndef SOAP_TYPE__xsd__schema
#define SOAP_TYPE__xsd__schema (9)
typedef char *_xsd__schema;
#endif

#ifndef SOAP_TYPE_xsd__anyURI
#define SOAP_TYPE_xsd__anyURI (12)
typedef char *xsd__anyURI;
#endif

#ifndef SOAP_TYPE_xsd__byte
#define SOAP_TYPE_xsd__byte (18)
typedef char xsd__byte;
#endif

#ifndef SOAP_TYPE_xsd__date
#define SOAP_TYPE_xsd__date (19)
typedef char *xsd__date;
#endif

#ifndef SOAP_TYPE_xsd__decimal
#define SOAP_TYPE_xsd__decimal (21)
typedef double xsd__decimal;
#endif

#ifndef SOAP_TYPE_xsd__double
#define SOAP_TYPE_xsd__double (22)
typedef double xsd__double;
#endif

#ifndef SOAP_TYPE_xsd__duration
#define SOAP_TYPE_xsd__duration (23)
typedef char *xsd__duration;
#endif

#ifndef SOAP_TYPE_xsd__float
#define SOAP_TYPE_xsd__float (25)
typedef float xsd__float;
#endif

#ifndef SOAP_TYPE_xsd__ID
#define SOAP_TYPE_xsd__ID (26)
typedef char *xsd__ID;
#endif

#ifndef SOAP_TYPE_xsd__integer
#define SOAP_TYPE_xsd__integer (28)
typedef LONG64 xsd__integer;
#endif

#ifndef SOAP_TYPE_xsd__language
#define SOAP_TYPE_xsd__language (29)
typedef char *xsd__language;
#endif

#ifndef SOAP_TYPE_xsd__long
#define SOAP_TYPE_xsd__long (30)
typedef LONG64 xsd__long;
#endif

#ifndef SOAP_TYPE_xsd__Name
#define SOAP_TYPE_xsd__Name (31)
typedef char *xsd__Name;
#endif

#ifndef SOAP_TYPE_xsd__NCName
#define SOAP_TYPE_xsd__NCName (32)
typedef char *xsd__NCName;
#endif

#ifndef SOAP_TYPE_xsd__NMTOKEN
#define SOAP_TYPE_xsd__NMTOKEN (33)
typedef char *xsd__NMTOKEN;
#endif

#ifndef SOAP_TYPE_xsd__negativeInteger
#define SOAP_TYPE_xsd__negativeInteger (34)
typedef LONG64 xsd__negativeInteger;
#endif

#ifndef SOAP_TYPE_xsd__nonNegativeInteger
#define SOAP_TYPE_xsd__nonNegativeInteger (36)
typedef ULONG64 xsd__nonNegativeInteger;
#endif

#ifndef SOAP_TYPE_xsd__nonPositiveInteger
#define SOAP_TYPE_xsd__nonPositiveInteger (37)
typedef LONG64 xsd__nonPositiveInteger;
#endif

#ifndef SOAP_TYPE_xsd__normalizedString
#define SOAP_TYPE_xsd__normalizedString (38)
typedef char *xsd__normalizedString;
#endif

#ifndef SOAP_TYPE_xsd__positiveInteger
#define SOAP_TYPE_xsd__positiveInteger (39)
typedef ULONG64 xsd__positiveInteger;
#endif

#ifndef SOAP_TYPE_xsd__QName
#define SOAP_TYPE_xsd__QName (40)
typedef char *xsd__QName;
#endif

#ifndef SOAP_TYPE_xsd__time
#define SOAP_TYPE_xsd__time (41)
typedef char *xsd__time;
#endif

#ifndef SOAP_TYPE_xsd__token
#define SOAP_TYPE_xsd__token (42)
typedef char *xsd__token;
#endif

#ifndef SOAP_TYPE_xsd__short
#define SOAP_TYPE_xsd__short (44)
typedef short xsd__short;
#endif

#ifndef SOAP_TYPE_xsd__unsignedByte
#define SOAP_TYPE_xsd__unsignedByte (45)
typedef unsigned char xsd__unsignedByte;
#endif

#ifndef SOAP_TYPE_xsd__unsignedInt
#define SOAP_TYPE_xsd__unsignedInt (46)
typedef unsigned int xsd__unsignedInt;
#endif

#ifndef SOAP_TYPE_xsd__unsignedLong
#define SOAP_TYPE_xsd__unsignedLong (47)
typedef ULONG64 xsd__unsignedLong;
#endif

#ifndef SOAP_TYPE_xsd__unsignedShort
#define SOAP_TYPE_xsd__unsignedShort (49)
typedef unsigned short xsd__unsignedShort;
#endif

#ifndef SOAP_TYPE__SOAP_ENC__actor
#define SOAP_TYPE__SOAP_ENC__actor (50)
typedef char *_SOAP_ENC__actor;
#endif

#ifndef SOAP_TYPE__SOAP_ENC__mustUnderstand
#define SOAP_TYPE__SOAP_ENC__mustUnderstand (51)
typedef int _SOAP_ENC__mustUnderstand;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */
