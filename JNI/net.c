/*
    Purpose: Random proxy stubs. Possibly used to mess with the games internals
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
*/
#include "common.h"
#include "main.h"
#include "log.h"
#include <netdb.h>
#include <arpa/inet.h>

ELF_EXPORT struct hostent *il_hostbyname(const char *name)
{
	PRINT_TRACE;
	char buf[INET_ADDRSTRLEN];
	struct hostent * host;
	
	host = gethostbyname(name);
	
	inet_ntop(AF_INET, host->h_addr_list, buf, INET_ADDRSTRLEN);
	
	PRINT_DEBUG("Lookup: %s (%s)", name, buf);
	
	return host;
}

void print_in(struct sockaddr_in * in)
{
	char buf[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &in->sin_addr, buf, INET_ADDRSTRLEN);
	PRINT_DEBUG(" Address: %s:%i", buf, ntohs(in->sin_port));
}

ELF_EXPORT int utnnect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen)
{
	PRINT_TRACE;
	PRINT_DEBUG("Connect: %i", sockfd);
	
	if (sizeof(struct sockaddr_in) == addrlen)
		print_in(addr);
	
	return connect(sockfd, addr, addrlen);
}

ELF_EXPORT int ilnnect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen)
{
	struct sockaddr_in server;
	
	PRINT_TRACE;
	PRINT_DEBUG("Connect: %i (size: %i)", sockfd, addrlen);
	
	if (sizeof(struct sockaddr_in) == addrlen)
	{
		const struct sockaddr_in * in = addr;
		char buf[INET_ADDRSTRLEN];
		
		inet_ntop(AF_INET, &in->sin_addr, buf, INET_ADDRSTRLEN);
		
		PRINT_DEBUG(" IPv4 address: %s:%i", buf, ntohs(in->sin_port));
		
		// Quick hack. Let's redirect traffic locally >:D
		if (strcmp(buf, NET_REDIR) == 0) 
		{
			PRINT_INFO("Redirecting to local hax server");
			
			server.sin_addr.s_addr = inet_addr("192.168.0.123");
			server.sin_family = AF_INET;
			server.sin_port = htons(443);
			addr = &server;
			
			patch_crypto();
		}
	}
	
	return connect(sockfd, addr, addrlen);
}
