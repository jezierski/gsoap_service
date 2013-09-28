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

int homesysProxy::getCurrentTime(const char *endpoint, const char *soap_action, std::string &time)
{	struct soap *soap = this;
	struct ns1__getCurrentTime soap_tmp_ns1__getCurrentTime;
	struct ns1__getCurrentTimeResponse *soap_tmp_ns1__getCurrentTimeResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getCurrentTime(soap, &soap_tmp_ns1__getCurrentTime);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getCurrentTime(soap, &soap_tmp_ns1__getCurrentTime, "ns1:getCurrentTime", NULL)
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
	 || soap_put_ns1__getCurrentTime(soap, &soap_tmp_ns1__getCurrentTime, "ns1:getCurrentTime", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&time)
		return soap_closesock(soap);
	soap_default_std__string(soap, &time);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns1__getCurrentTimeResponse = soap_get_ns1__getCurrentTimeResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	time = soap_tmp_ns1__getCurrentTimeResponse->time;
	return soap_closesock(soap);
}

int homesysProxy::getValue(const char *endpoint, const char *soap_action, std::string id, std::string &result)
{	struct soap *soap = this;
	struct ns1__getValue soap_tmp_ns1__getValue;
	struct ns1__getValueResponse *soap_tmp_ns1__getValueResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.1.39:1234";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_tmp_ns1__getValue.id = id;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns1__getValue(soap, &soap_tmp_ns1__getValue);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getValue(soap, &soap_tmp_ns1__getValue, "ns1:getValue", NULL)
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
	 || soap_put_ns1__getValue(soap, &soap_tmp_ns1__getValue, "ns1:getValue", NULL)
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
	soap_tmp_ns1__getValueResponse = soap_get_ns1__getValueResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns1__getValueResponse->result;
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

int homesysProxy::makeRemoteAction(const char *endpoint, const char *soap_action, ns1__SDeviceDescription *device, LONG64 command, LONG64 params, std::string &result)
{	struct soap *soap = this;
	struct ns1__makeRemoteAction soap_tmp_ns1__makeRemoteAction;
	struct ns1__makeRemoteActionResponse *soap_tmp_ns1__makeRemoteActionResponse;
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
	soap_tmp_ns1__makeRemoteActionResponse = soap_get_ns1__makeRemoteActionResponse(soap, NULL, "", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	result = soap_tmp_ns1__makeRemoteActionResponse->result;
	return soap_closesock(soap);
}
/* End of client proxy code */
