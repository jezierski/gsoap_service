/* soaphomesysProxy.cpp
   Generated by gSOAP 2.8.7 from homesys.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soaphomesysProxy.h"

homesysProxy::homesysProxy()
{	homesysProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

homesysProxy::homesysProxy(const struct soap &_soap) : soap(_soap)
{ }

homesysProxy::homesysProxy(const char *url)
{	homesysProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

homesysProxy::homesysProxy(soap_mode iomode)
{	homesysProxy_init(iomode, iomode);
}

homesysProxy::homesysProxy(const char *url, soap_mode iomode)
{	homesysProxy_init(iomode, iomode);
	soap_endpoint = url;
}

homesysProxy::homesysProxy(soap_mode imode, soap_mode omode)
{	homesysProxy_init(imode, omode);
}

homesysProxy::~homesysProxy()
{ }

void homesysProxy::homesysProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://adjserwer.dyndns.org/soap_server/webservice/homesys.wsdl", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void homesysProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void homesysProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *homesysProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *homesysProxy::soap_fault()
{	return this->fault;
}

const char *homesysProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *homesysProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int homesysProxy::soap_close_socket()
{	return soap_closesock(this);
}

int homesysProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void homesysProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void homesysProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *homesysProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int homesysProxy::getXML(const char *endpoint, const char *soap_action, std::string id, std::string &result)
{	struct soap *soap = this;
	struct ns1__getXML soap_tmp_ns1__getXML;
	struct ns1__getXMLResponse *soap_tmp_ns1__getXMLResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__getXML.id = id;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getXML(soap, &soap_tmp_ns1__getXML);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getXML(soap, &soap_tmp_ns1__getXML, "ns1:getXML", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getXML(soap, &soap_tmp_ns1__getXML, "ns1:getXML", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result)
		return soap_closesock(soap);
	soap_default_std__string(soap, &result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns1__getXMLResponse = soap_get_ns1__getXMLResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns1__getXMLResponse->result;
	return soap_closesock(soap);
}

int homesysProxy::setDeviceName(const char *endpoint, const char *soap_action, ns1__SDeviceDescription *device, std::string name, std::string &response)
{	struct soap *soap = this;
	struct ns1__setDeviceName soap_tmp_ns1__setDeviceName;
	struct ns1__setDeviceNameResponse *soap_tmp_ns1__setDeviceNameResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__setDeviceName.device = device;
	soap_tmp_ns1__setDeviceName.name = name;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__setDeviceName(soap, &soap_tmp_ns1__setDeviceName);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__setDeviceName(soap, &soap_tmp_ns1__setDeviceName, "ns1:setDeviceName", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__setDeviceName(soap, &soap_tmp_ns1__setDeviceName, "ns1:setDeviceName", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&response)
		return soap_closesock(soap);
	soap_default_std__string(soap, &response);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns1__setDeviceNameResponse = soap_get_ns1__setDeviceNameResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	response = soap_tmp_ns1__setDeviceNameResponse->response;
	return soap_closesock(soap);
}

int homesysProxy::saveXML(const char *endpoint, const char *soap_action, std::string id, std::string body, std::string &result)
{	struct soap *soap = this;
	struct ns1__saveXML soap_tmp_ns1__saveXML;
	struct ns1__saveXMLResponse *soap_tmp_ns1__saveXMLResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__saveXML.id = id;
	soap_tmp_ns1__saveXML.body = body;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__saveXML(soap, &soap_tmp_ns1__saveXML);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__saveXML(soap, &soap_tmp_ns1__saveXML, "ns1:saveXML", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__saveXML(soap, &soap_tmp_ns1__saveXML, "ns1:saveXML", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result)
		return soap_closesock(soap);
	soap_default_std__string(soap, &result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns1__saveXMLResponse = soap_get_ns1__saveXMLResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns1__saveXMLResponse->result;
	return soap_closesock(soap);
}

int homesysProxy::switchPort(const char *endpoint, const char *soap_action, std::string pinNo, std::string &result)
{	struct soap *soap = this;
	struct ns1__switchPort soap_tmp_ns1__switchPort;
	struct ns1__switchPortResponse *soap_tmp_ns1__switchPortResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__switchPort.pinNo = pinNo;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__switchPort(soap, &soap_tmp_ns1__switchPort);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__switchPort(soap, &soap_tmp_ns1__switchPort, "ns1:switchPort", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__switchPort(soap, &soap_tmp_ns1__switchPort, "ns1:switchPort", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&result)
		return soap_closesock(soap);
	soap_default_std__string(soap, &result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns1__switchPortResponse = soap_get_ns1__switchPortResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns1__switchPortResponse->result;
	return soap_closesock(soap);
}

int homesysProxy::makeRemoteAction(const char *endpoint, const char *soap_action, ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &_param_1)
{	struct soap *soap = this;
	struct ns1__makeRemoteAction soap_tmp_ns1__makeRemoteAction;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__makeRemoteAction.device = device;
	soap_tmp_ns1__makeRemoteAction.command = command;
	soap_tmp_ns1__makeRemoteAction.params = params;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__makeRemoteAction(soap, &soap_tmp_ns1__makeRemoteAction);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__makeRemoteAction(soap, &soap_tmp_ns1__makeRemoteAction, "ns1:makeRemoteAction", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__makeRemoteAction(soap, &soap_tmp_ns1__makeRemoteAction, "ns1:makeRemoteAction", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_1)
		return soap_closesock(soap);
	soap_default_ns1__makeRemoteActionResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns1__makeRemoteActionResponse(soap, &_param_1, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int homesysProxy::getDevicesList(const char *endpoint, const char *soap_action, LONG64 category, struct ns1__getDevicesListResponse &_param_2)
{	struct soap *soap = this;
	struct ns1__getDevicesList soap_tmp_ns1__getDevicesList;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__getDevicesList.category = category;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getDevicesList(soap, &soap_tmp_ns1__getDevicesList);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getDevicesList(soap, &soap_tmp_ns1__getDevicesList, "ns1:getDevicesList", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getDevicesList(soap, &soap_tmp_ns1__getDevicesList, "ns1:getDevicesList", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_2)
		return soap_closesock(soap);
	soap_default_ns1__getDevicesListResponse(soap, &_param_2);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_ns1__getDevicesListResponse(soap, &_param_2, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
