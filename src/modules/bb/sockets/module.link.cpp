// AUTOGENERATED. DO NOT EDIT.
// RUN `make` TO UPDATE.

#include <bb/blitz/module.h>
#include <bb/sockets/sockets.h>

BBMODULE_LINK( sockets ){
	rtSym( "$DottedIP%IP",bbDottedIP );
	rtSym( "%CountHostIPs$host_name",bbCountHostIPs );
	rtSym( "%HostIP%host_index",bbHostIP );
	rtSym( "%CreateUDPStream%port=0",bbCreateUDPStream );
	rtSym( "CloseUDPStream%udp_stream",bbCloseUDPStream );
	rtSym( "SendUDPMsg%udp_stream%dest_ip%dest_port=0",bbSendUDPMsg );
	rtSym( "%RecvUDPMsg%udp_stream",bbRecvUDPMsg );
	rtSym( "%UDPStreamIP%udp_stream",bbUDPStreamIP );
	rtSym( "%UDPStreamPort%udp_stream",bbUDPStreamPort );
	rtSym( "%UDPMsgIP%udp_stream",bbUDPMsgIP );
	rtSym( "%UDPMsgPort%udp_stream",bbUDPMsgPort );
	rtSym( "UDPTimeouts%recv_timeout",bbUDPTimeouts );
	rtSym( "%OpenTCPStream$server%server_port%local_port=0",bbOpenTCPStream );
	rtSym( "CloseTCPStream%tcp_stream",bbCloseTCPStream );
	rtSym( "%CreateTCPServer%port",bbCreateTCPServer );
	rtSym( "CloseTCPServer%tcp_server",bbCloseTCPServer );
	rtSym( "%AcceptTCPStream%tcp_server",bbAcceptTCPStream );
	rtSym( "%TCPStreamIP%tcp_stream",bbTCPStreamIP );
	rtSym( "%TCPStreamPort%tcp_stream",bbTCPStreamPort );
	rtSym( "TCPTimeouts%read_millis%accept_millis",bbTCPTimeouts );
}
