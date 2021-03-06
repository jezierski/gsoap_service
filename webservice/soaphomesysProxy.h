/* soaphomesysProxy.h
   Generated by gSOAP 2.8.7 from homesys.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soaphomesysProxy_H
#define soaphomesysProxy_H
#include "soapH.h"

class SOAP_CMAC homesysProxy : public soap
{ public:
	/// Endpoint URL of service 'homesysProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	homesysProxy();
	/// Constructor with copy of another engine state
	homesysProxy(const struct soap&);
	/// Constructor with endpoint URL
	homesysProxy(const char *url);
	/// Constructor with engine input+output mode control
	homesysProxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	homesysProxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	homesysProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~homesysProxy();
	/// Initializer used by constructors
	virtual	void homesysProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
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

	/// Web service operation 'getXML' (returns error code or SOAP_OK)
	virtual	int getXML(std::string id, std::string &result) { return getXML(NULL, NULL, id, result); }
	virtual	int getXML(const char *endpoint, const char *soap_action, std::string id, std::string &result);

	/// Web service operation 'searchNewDevices' (returns error code or SOAP_OK)
	virtual	int searchNewDevices(LONG64 category, struct ns1__searchNewDevicesResponse &_param_1) { return searchNewDevices(NULL, NULL, category, _param_1); }
	virtual	int searchNewDevices(const char *endpoint, const char *soap_action, LONG64 category, struct ns1__searchNewDevicesResponse &_param_1);

	/// Web service operation 'setDeviceName' (returns error code or SOAP_OK)
	virtual	int setDeviceName(ns1__SDeviceDescription *device, std::string name, std::string &response) { return setDeviceName(NULL, NULL, device, name, response); }
	virtual	int setDeviceName(const char *endpoint, const char *soap_action, ns1__SDeviceDescription *device, std::string name, std::string &response);

	/// Web service operation 'saveXML' (returns error code or SOAP_OK)
	virtual	int saveXML(std::string id, std::string body, std::string &result) { return saveXML(NULL, NULL, id, body, result); }
	virtual	int saveXML(const char *endpoint, const char *soap_action, std::string id, std::string body, std::string &result);

	/// Web service operation 'switchPort' (returns error code or SOAP_OK)
	virtual	int switchPort(std::string pinNo, std::string &result) { return switchPort(NULL, NULL, pinNo, result); }
	virtual	int switchPort(const char *endpoint, const char *soap_action, std::string pinNo, std::string &result);

	/// Web service operation 'makeRemoteAction' (returns error code or SOAP_OK)
	virtual	int makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &_param_2) { return makeRemoteAction(NULL, NULL, device, command, params, _param_2); }
	virtual	int makeRemoteAction(const char *endpoint, const char *soap_action, ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &_param_2);

	/// Web service operation 'getDevicesList' (returns error code or SOAP_OK)
	virtual	int getDevicesList(LONG64 category, struct ns1__getDevicesListResponse &_param_3) { return getDevicesList(NULL, NULL, category, _param_3); }
	virtual	int getDevicesList(const char *endpoint, const char *soap_action, LONG64 category, struct ns1__getDevicesListResponse &_param_3);

	/// Web service operation 'getFilesList' (returns error code or SOAP_OK)
	virtual	int getFilesList(struct ns1__getFilesListResponse &_param_4) { return getFilesList(NULL, NULL, _param_4); }
	virtual	int getFilesList(const char *endpoint, const char *soap_action, struct ns1__getFilesListResponse &_param_4);

	/// Web service operation 'uploadFirmware' (returns error code or SOAP_OK)
	virtual	int uploadFirmware(std::string fileName, struct ns1__uploadFirmwareResponse &_param_5) { return uploadFirmware(NULL, NULL, fileName, _param_5); }
	virtual	int uploadFirmware(const char *endpoint, const char *soap_action, std::string fileName, struct ns1__uploadFirmwareResponse &_param_5);
};
#endif
