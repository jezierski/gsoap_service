/* soaphomesysService.cpp
   Generated by gSOAP 2.8.7 from homesys.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soaphomesysService.h"

homesysService::homesysService()
{	homesysService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

homesysService::homesysService(const struct soap &_soap) : soap(_soap)
{ }

homesysService::homesysService(soap_mode iomode)
{	homesysService_init(iomode, iomode);
}

homesysService::homesysService(soap_mode imode, soap_mode omode)
{	homesysService_init(imode, omode);
}

homesysService::~homesysService()
{ }

void homesysService::homesysService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
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
};

void homesysService::destroy()
{	soap_destroy(this);
	soap_end(this);
}

#ifndef WITH_PURE_VIRTUAL
homesysService *homesysService::copy()
{	homesysService *dup = SOAP_NEW_COPY(homesysService(*(struct soap*)this));
	return dup;
}
#endif

int homesysService::soap_close_socket()
{	return soap_closesock(this);
}

int homesysService::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int homesysService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int homesysService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int homesysService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int homesysService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void homesysService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void homesysService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *homesysService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void homesysService::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *homesysService::soap_header()
{	return this->header;
}

int homesysService::run(int port)
{	if (soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				return this->error;
			soap_destroy(this);
			soap_end(this);
		}
	}
	else
		return this->error;
	return SOAP_OK;
}

SOAP_SOCKET homesysService::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET homesysService::accept()
{	return soap_accept(this);
}

int homesysService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->max_keep_alive > 0 && !--k)
			this->keep_alive = 0;
#endif

		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if (dispatch() || (this->fserveloop && this->fserveloop(this)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns1__getCurrentTime(homesysService*);
static int serve_ns1__getValue(homesysService*);
static int serve_ns1__switchPort(homesysService*);
static int serve_ns1__makeRemoteAction(homesysService*);
static int serve_ns1__getDevicesList(homesysService*);

int homesysService::dispatch()
{	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns1:getCurrentTime"))
		return serve_ns1__getCurrentTime(this);
	if (!soap_match_tag(this, this->tag, "ns1:getValue"))
		return serve_ns1__getValue(this);
	if (!soap_match_tag(this, this->tag, "ns1:switchPort"))
		return serve_ns1__switchPort(this);
	if (!soap_match_tag(this, this->tag, "ns1:makeRemoteAction"))
		return serve_ns1__makeRemoteAction(this);
	if (!soap_match_tag(this, this->tag, "ns1:getDevicesList"))
		return serve_ns1__getDevicesList(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve_ns1__getCurrentTime(homesysService *soap)
{	struct ns1__getCurrentTime soap_tmp_ns1__getCurrentTime;
	struct ns1__getCurrentTimeResponse soap_tmp_ns1__getCurrentTimeResponse;
	soap_default_ns1__getCurrentTimeResponse(soap, &soap_tmp_ns1__getCurrentTimeResponse);
	soap_default_ns1__getCurrentTime(soap, &soap_tmp_ns1__getCurrentTime);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__getCurrentTime(soap, &soap_tmp_ns1__getCurrentTime, "ns1:getCurrentTime", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->getCurrentTime(soap_tmp_ns1__getCurrentTimeResponse.time);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__getCurrentTimeResponse(soap, &soap_tmp_ns1__getCurrentTimeResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getCurrentTimeResponse(soap, &soap_tmp_ns1__getCurrentTimeResponse, "ns1:getCurrentTimeResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getCurrentTimeResponse(soap, &soap_tmp_ns1__getCurrentTimeResponse, "ns1:getCurrentTimeResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns1__getValue(homesysService *soap)
{	struct ns1__getValue soap_tmp_ns1__getValue;
	struct ns1__getValueResponse soap_tmp_ns1__getValueResponse;
	soap_default_ns1__getValueResponse(soap, &soap_tmp_ns1__getValueResponse);
	soap_default_ns1__getValue(soap, &soap_tmp_ns1__getValue);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__getValue(soap, &soap_tmp_ns1__getValue, "ns1:getValue", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->getValue(soap_tmp_ns1__getValue.id, soap_tmp_ns1__getValueResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__getValueResponse(soap, &soap_tmp_ns1__getValueResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getValueResponse(soap, &soap_tmp_ns1__getValueResponse, "ns1:getValueResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getValueResponse(soap, &soap_tmp_ns1__getValueResponse, "ns1:getValueResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns1__switchPort(homesysService *soap)
{	struct ns1__switchPort soap_tmp_ns1__switchPort;
	struct ns1__switchPortResponse soap_tmp_ns1__switchPortResponse;
	soap_default_ns1__switchPortResponse(soap, &soap_tmp_ns1__switchPortResponse);
	soap_default_ns1__switchPort(soap, &soap_tmp_ns1__switchPort);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__switchPort(soap, &soap_tmp_ns1__switchPort, "ns1:switchPort", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->switchPort(soap_tmp_ns1__switchPort.pinNo, soap_tmp_ns1__switchPortResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__switchPortResponse(soap, &soap_tmp_ns1__switchPortResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__switchPortResponse(soap, &soap_tmp_ns1__switchPortResponse, "ns1:switchPortResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__switchPortResponse(soap, &soap_tmp_ns1__switchPortResponse, "ns1:switchPortResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns1__makeRemoteAction(homesysService *soap)
{	struct ns1__makeRemoteAction soap_tmp_ns1__makeRemoteAction;
	struct ns1__makeRemoteActionResponse soap_tmp_ns1__makeRemoteActionResponse;
	soap_default_ns1__makeRemoteActionResponse(soap, &soap_tmp_ns1__makeRemoteActionResponse);
	soap_default_ns1__makeRemoteAction(soap, &soap_tmp_ns1__makeRemoteAction);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__makeRemoteAction(soap, &soap_tmp_ns1__makeRemoteAction, "ns1:makeRemoteAction", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->makeRemoteAction(soap_tmp_ns1__makeRemoteAction.device, soap_tmp_ns1__makeRemoteAction.command, soap_tmp_ns1__makeRemoteAction.params, soap_tmp_ns1__makeRemoteActionResponse.result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__makeRemoteActionResponse(soap, &soap_tmp_ns1__makeRemoteActionResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__makeRemoteActionResponse(soap, &soap_tmp_ns1__makeRemoteActionResponse, "ns1:makeRemoteActionResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__makeRemoteActionResponse(soap, &soap_tmp_ns1__makeRemoteActionResponse, "ns1:makeRemoteActionResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns1__getDevicesList(homesysService *soap)
{	struct ns1__getDevicesList soap_tmp_ns1__getDevicesList;
	struct ns1__getDevicesListResponse _param_1;
	soap_default_ns1__getDevicesListResponse(soap, &_param_1);
	soap_default_ns1__getDevicesList(soap, &soap_tmp_ns1__getDevicesList);
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	if (!soap_get_ns1__getDevicesList(soap, &soap_tmp_ns1__getDevicesList, "ns1:getDevicesList", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->getDevicesList(soap_tmp_ns1__getDevicesList.category, _param_1);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns1__getDevicesListResponse(soap, &_param_1);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__getDevicesListResponse(soap, &_param_1, "ns1:getDevicesListResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__getDevicesListResponse(soap, &_param_1, "ns1:getDevicesListResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
