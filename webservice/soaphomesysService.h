/* soaphomesysService.h
   Generated by gSOAP 2.8.7 from homesys.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soaphomesysService_H
#define soaphomesysService_H
#include "soapH.h"
class SOAP_CMAC homesysService : public soap
{ public:
	/// Constructor
	homesysService();
	/// Constructor with copy of another engine state
	homesysService(const struct soap&);
	/// Constructor with engine input+output mode control
	homesysService(soap_mode iomode);
	/// Constructor with engine input and output mode control
	homesysService(soap_mode imode, soap_mode omode);
	/// Destructor, also frees all deserialized data
	virtual ~homesysService();
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Initializer used by constructor
	virtual	void homesysService_init(soap_mode imode, soap_mode omode);
	/// Create a copy
	virtual	homesysService *copy() SOAP_PURE_VIRTUAL;
	/// Close connection (normally automatic)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Return sender-related fault to sender
	virtual	int soap_senderfault(const char *string, const char *detailXML);
	/// Return sender-related fault with SOAP 1.2 subcode to sender
	virtual	int soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML);
	/// Return receiver-related fault to sender
	virtual	int soap_receiverfault(const char *string, const char *detailXML);
	/// Return receiver-related fault with SOAP 1.2 subcode to sender
	virtual	int soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML);
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Run simple single-thread iterative service on port until a connection error occurs (returns error code or SOAP_OK), use this->bind_flag = SO_REUSEADDR to rebind for a rerun
	virtual	int run(int port);
	/// Bind service to port (returns master socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET bind(const char *host, int port, int backlog);
	/// Accept next request (returns socket or SOAP_INVALID_SOCKET)
	virtual	SOAP_SOCKET accept();
	/// Serve this request (returns error code or SOAP_OK)
	virtual	int serve();
	/// Used by serve() to dispatch a request (returns error code or SOAP_OK)
	virtual	int dispatch();

	///
	/// Service operations (you should define these):
	/// Note: compile with -DWITH_PURE_VIRTUAL for pure virtual methods
	///

	/// Web service operation 'getCurrentTime' (returns error code or SOAP_OK)
	virtual	int getCurrentTime(std::string &time) SOAP_PURE_VIRTUAL{
            return SOAP_OK;
        }

	/// Web service operation 'getValue' (returns error code or SOAP_OK)
	virtual	int getValue(std::string id, std::string &result) SOAP_PURE_VIRTUAL{
            return SOAP_OK;
        }

	/// Web service operation 'switchPort' (returns error code or SOAP_OK)
	virtual	int switchPort(std::string pinNo, std::string &result) SOAP_PURE_VIRTUAL{
            return SOAP_OK;
        }

	/// Web service operation 'makeRemoteAction' (returns error code or SOAP_OK)
	virtual	int makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &_param_1) SOAP_PURE_VIRTUAL{
            return SOAP_OK;
        }

	/// Web service operation 'getDevicesList' (returns error code or SOAP_OK)
	virtual	int getDevicesList(LONG64 category, struct ns1__getDevicesListResponse &_param_2) SOAP_PURE_VIRTUAL{
            return SOAP_OK;
        }
};
#endif
