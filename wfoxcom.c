#include "winsock2.h"
#include "ws2tcpip.h"

#include "windows.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\MsWSock.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\WS2_32.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\OneCore.Lib")



/////////////////////////////////////////

int power(int base, int N)
{
	int rVal = 1;
	
	for (int i = 0; i < N; i++)
	{
		rVal *= base;
	}
	
	return rVal;
}


///////////////////////////////////////


void checksum(unsigned short *alphaIn, int length, void* out, int outL)
{
	//BYTE* alphaInB;
	//alphaInB = alphaIn;
	
	unsigned long sum = 0;
	
	for (int i = 0; i < length; i++)
	{
		sum += alphaIn[i];
		
		if (sum & 0xFFFF0000)
		{
			sum &= 0xFFFF;
			sum++;
		}
		// from davie and petersen, see "computer networks: a systems approach"
	}
	
	unsigned short sum_prime = ~(sum & 0xFFFF);
	
	BYTE* bOut;
	
	bOut = out;
	
	BYTE* sierra;
	
	sierra = &sum_prime;
	
	for (int i = 0; i < outL; i++)
	{
		*bOut = sierra[i];
		
		bOut++;
	}
}


/////////////////////////////////////////


BOOL sErr(SOCKET sierra)
{	
	if (sierra == INVALID_SOCKET)
	{
		printf("invalid socket: ");
		
		int socketErr = WSAGetLastError();
		
		printf(" %d, ",socketErr);
		
		switch (socketErr)
		{
			case WSANOTINITIALISED:
				printf("wsastartup call must initialize the socket first.\n");
				return FALSE;
				
			case WSAENETDOWN:
				printf("network subsystem failed.\n");
				return FALSE;
				
			case WSAEAFNOSUPPORT:
				printf("specified address family not supported.\n");
				return FALSE;
				
			case WSAEFAULT:
				printf("buffer or to paramters are not part of user address space or tolen is too small.\n");
				return FALSE;
				
			case WSAEINPROGRESS:
				printf("blocking windows sockets 1.1 call in progress or service provider is still processing a callback function.\n");
				return FALSE;
				
				
			case WSAEINVAL:
				printf("group not valid or wsaprotocol_info struct incomplete or socket triple <af,type,and protocol> not supported.\n");
				return FALSE;
				
			case WSAEINVALIDPROVIDER:
				printf("service provider returned a version other than 2.2.\n");
				return FALSE;
				
			case WSAEINVALIDPROCTABLE:
				printf("service provider returned an invalid or incomplete procedure table.\n");
				return FALSE;
				
			case WSAEMFILE:
				printf("no more socket descriptors available.\n");
				return FALSE;
				
			case WSAENOBUFS:
				printf("no buffer space available, cannot create socket.\n");
				return FALSE;
				
			case WSAEPROTONOSUPPORT:
				printf("protocol not supported.\n");
				return FALSE;
				
			case WSAEPROTOTYPE:
				printf("specified protocol is the wrong type for the socket.\n");
				return FALSE;
			
			default:
				printf("undefined error.\n");
				return FALSE;
		}
	}
	
	return TRUE;
}


///////////////////////////////////////


BOOL sockErrSwitch(int sockErr)
{	
	if (sockErr != 0)
	{
		printf("socket error: ");
		
		sockErr = WSAGetLastError();
		
		printf(" %d, ",sockErr);
	
		switch (sockErr)
		{
			case WSANOTINITIALISED:
				printf("must call wsastartup first\n");
				return FALSE;
				
			case WSAENETDOWN:
				printf("network subsystem failure.\n");
				return FALSE;
				
			case WSAENOTSOCK:
				printf("descriptor is not a socket.\n");
				return FALSE;
				
			case WSAEINPROGRESS:
				printf("block windows sockets 1.1 call in progress, or the service provider is still processing a callback function.\n");
				return FALSE;
				
			case WSAEINTR:
				printf("blocking windows socket 1.1 call canceled through wsacancelblockingcall.\n");
				return FALSE;
				
			case WSAEWOULDBLOCK:
				printf("socket is nonblocking, but l_onoff member of linger structure is set to nonzero and l_linger of linger struct has a non-zero timeout.\n");
				return FALSE;
			
			case WSAEFAULT:
				printf("invalid pointer address or incorrect buffer size used in the socket function call.\n");
				return FALSE;
		
			default:
				printf("unknown error.\n");
				return FALSE;
		}
	}
	
	return TRUE;
}


///////////////////////////////////////

void assignData(int lowerBoundIn, int lowerBoundOut, int magnitude, void* alphaIn, void* alphaOut)
{	
	BYTE* alpha_primeIn = alphaIn;
	if (magnitude < 0)
	{
		alpha_primeIn += lowerBoundIn + abs(magnitude) - 1;
	}
	else
	{
		alpha_primeIn += lowerBoundIn;
	}
	
	BYTE* alpha_primeOut = alphaOut;
	alpha_primeOut += lowerBoundOut;
	
	for (int i = 0; i < abs(magnitude); i++)
	{
		*alpha_primeOut = *alpha_primeIn;
		if (magnitude < 0)
		{
			alpha_primeIn--;
		}
		else
		{
			alpha_primeIn++;
		}
		
		alpha_primeOut++;
	}
}


///////////////////////////////////////

void macToAlloc(int index, str sierra, void* delta)
{
	BYTE* delta_prime;
	
	delta_prime = delta + index;
	
	BYTE bravo = 0;
	
	str hexValues = "0123456789ABCDEF";
	
	for (int i = 0; i < strLength(sierra); i += 3)
	{
		bravo = 0;
		
		for (int i_b = 0; i_b < 2; i_b++)
		{
			for (int i_h = 0; i_h < strLength(hexValues); i_h++)
			{
				if (hexValues[i_h] == sierra[i + i_b] | hexValues[i_h] == sierra[i + i_b] - ('A' - 'a'))
				{
					bravo += (BYTE)(i_h * power(16, 1 - i_b));
				}
			}
		}
		
		*delta_prime = bravo;
		
		delta_prime++;
	}
}


///////////////////////////////////////

void ip4StrToAlloc(str address, void* alphaIn)
{
	BYTE* alpha_primeIn = alphaIn;
	
	int index = 0;
	int addrL = strLength(address);
	int byte_count = 0;
	
	while (byte_count < 4)
	{
		int index_up = index;
		
		while (index_up < addrL)
		{
			if (address[index_up] == '.')
			{
				break;
			}
			
			index_up++;
		}
		
		str byte = calloc(
			index_up - index,
			sizeof(BYTE)
		);
		
		for (int i = 0; i < index_up - index; i++)
		{
			byte[i] = (BYTE)address[index + i];
		}
		
		*alpha_primeIn = (BYTE)strToL(
			byte,
			10
		);
		
		index = index_up + 1;
		
		alpha_primeIn++;
		byte_count++;
	}
}


///////////////////////////////////////


BOOL eCheck()
{
	HANDLE hotel = NULL;
	
	if (OpenProcessToken(
		GetCurrentProcess(),
		TOKEN_QUERY,
		&hotel))
	{
		TOKEN_ELEVATION eToken;
		
		DWORD teSize = sizeof(TOKEN_ELEVATION);
		
		if (GetTokenInformation(
				hotel,
				TokenElevation,
				&eToken,
				sizeof(eToken),
				&teSize
			) && eToken.TokenIsElevated)
			{
				return TRUE;
			}
	}
	
	return FALSE;
}


///////////////////////////////////////

void main(int argc, str* argv)
{
	BOOL elevation = eCheck();
	
	if (elevation == FALSE)
	{
		printf("command requires elevation.\n");
		
		goto endoffunction;
	}
		
	if (argc < 5)
	{
		printf("invalid args\n");
		
		goto endoffunction;
	}
	
	#define udp 1
	
	BYTE type = 0;
	
	unsigned short portIn = 0;
	unsigned short portOut = 0;
	
	BYTE ttl = 56;
	
	str path_in = NULL;
	
	
	for (int i = 0; i < argc; i++)
	{
		if (
			strCompare(
				argv[i],
				"type"
				) == 1
		)
		{
			i++;

			if (
				strCompare(
					argv[i],
					"udp"
				) == 1
			)
			{
				type = udp;
					
				if (
					i + 1 < argc
					&& strCompare(
						argv[i + 1],
						"p"
					) == 1
				)
				{
					i += 2;
						
					portIn = strToL(argv[i], 10);
						
					i++;
						
					portOut = strToL(argv[i], 10);
						
				}
			}
		}
		
		else if(
			strCompare(
				argv[i],
				"f"
			) == 1
		)
		{
			i++;
			
			path_in = argv[i];
		}
		
		else if(
			strCompare(
				argv[i],
				"ttl"
			) == 1
		)
		{
			i++;
			
			ttl = (BYTE)strToL(argv[i], 10);
		}
	}
	
	str macIn = argv[argc - 4];
	str ipIn = argv[argc - 3];
	str macOut = argv[argc - 2];
	str ipOut = argv[argc - 1];
	
	///////////////////
	//copy payload data
	///////////////////
	
	FILE *foxtrot;
	unsigned int foxtrotL = 0;
	BYTE* payload;
	
	if (path_in != NULL)
	{
		errno_t echo = fopen_s(&foxtrot, path_in, "rb");
		
		if (echo != 0)
		{
			printf("error opening file.\n");
			
			goto endoffunction;
		}
		
		fseek(
			foxtrot,
			0,
			SEEK_END
		);
		
		foxtrotL = ftell(foxtrot);
		
		fseek(
			foxtrot,
			0,
			0
		);
		
		payload = calloc(foxtrotL, sizeof(BYTE));
		
		for (int i = 0; i < foxtrotL; i++)
		{
			fseek(
				foxtrot,
				0,
				i
			);
			
			payload[i] = getc(foxtrot);
		}
		
		fclose(foxtrot);
	}


	
	////////////////
	//allocate frame
	////////////////
	
	unsigned short fL = 56 + foxtrotL;
	
	BYTE* frame = calloc(fL, sizeof(BYTE));
	
	//////////////////////
	//start of 802.x frame
	//////////////////////
	BYTE* mac = calloc(6, sizeof(BYTE));
	
	macToAlloc(
		0,
		macOut,
		mac
	);
	
	for (int i = 0; i < 6; i++)
	{
		frame[i] = mac[i];
	}
	
	macToAlloc(
		0,
		macIn,
		mac
	);
	
	for (int i = 0; i < 6; i++)
	{
		frame[6 + i] = mac[i];
	}
	
	frame[12] = 8;
	frame[13] = 0;
	
	////////////////////
	//start of ip header
	////////////////////
	
	frame[14] = 4 * 16 + 5; //ipv4 + 20 byte header
	
	frame[15] = 0;	// standard differentiated services, no explicit congestion notification
	
	BYTE* fLB;
	
	fLB = &fL+1;
	
	for (int i = 0; i < 2; i++)
	{
		frame[16 + i] = *fLB; // total length byte
		
		fLB--;
	}
	
	frame[18] = (BYTE)rand();
	frame[19] = (BYTE)rand();
	// random ident
	
	frame[20] = power(2,7);
	frame[21] = 0;
	// don't fragment flag and 0 frag offset
	
	frame[22] = ttl;
	
	switch(type)
	{
		case udp:
			frame[23] = 17;
			break;
		
		default:
			break;
	}
	// protocol type
	
	BYTE* ipInAlpha = calloc(4, sizeof(BYTE));
	BYTE* ipOutAlpha = calloc(4, sizeof(BYTE));
	
	ip4StrToAlloc(
		ipIn,
		ipInAlpha
	);
	
	ip4StrToAlloc(
		ipOut,
		ipOutAlpha
	);
	
	for (int i = 0; i < 4; i++)
	{
		frame[26 + i] = ipInAlpha[i];
	}
	// ipv4 source
	
	for (int i = 0; i < 4; i++)
	{
		frame[30 + i] = ipOutAlpha[i];
	}
	// ipv4 destination
	
	BYTE* check = calloc(2, sizeof(BYTE));
	
	checksum(
		frame + 14,
		10,
		check,
		2
	);
	
	for (int i = 0; i < 2; i++)
	{
		frame[24 + i] = check[i];
	}
	// ipv4 checksum
	
	
	
	//////////////////
	//start udp header
	//////////////////
	
	BYTE* sierra;
	
	sierra = &portIn;
	
	for (int i = 1; i >= 0; i--)
	{
		frame[34 + i] = *sierra;
		
		sierra++;
	}
	// port in
	
	sierra = &portOut;
	
	for (int i = 1; i >= 0; i--)
	{
		frame[36 + i] = *sierra;
		
		sierra++;
	}
	// port out
	
	unsigned short udpL = 8 + foxtrotL;
	
	sierra = &udpL;
	
	for (int i = 1; i >= 0; i--)
	{
		frame[38 + i] = *sierra;
		
		sierra++;
	}
	// udp length
	
	
	unsigned int pseudoL = 20 + foxtrotL;
	
	if (pseudoL % 2 != 0)
	{
		pseudoL++;
	}
	
	
	BYTE* udpPseudoHeader = calloc(pseudoL, sizeof(BYTE));
	
	assignData(
		26,			// lowerboundin
		0,			// lowerboundout
		8,			// length
		frame,		// alpha in
		udpPseudoHeader	// alpha out
	);
	// assign ipv4 addresses to pseudoheader
	
	udpPseudoHeader[9] = frame[23];
	// assign ipv4 header protocol
	
	assignData(
		38,			// lowerboundin
		10,			// lowerboundout
		2,			// length
		frame,		// alpha in
		udpPseudoHeader	// alpha out
	);
	// assing udp length
	
	assignData(
		34,			// lowerboundin
		12,			// lowerboundout
		4,			// length
		frame,		// alpha in
		udpPseudoHeader	// alpha out
	);
	// assign udp source and destination
	
	assignData(
		38,			// lowerboundin
		16,			// lowerboundout
		2,			// length
		frame,		// alpha in
		udpPseudoHeader	// alpha out
	);
	// assing udp length
	
	assignData(
		0,				// lowerboundin
		20,				// lowerboundout
		foxtrotL,		// length
		payload,		// alpha in
		udpPseudoHeader	// alpha out
	);
	// assing payload
	
	
	
	check = calloc(2, sizeof(BYTE));

	checksum(
		udpPseudoHeader,
		pseudoL / 2,
		check,
		2
	);
	
	for (int i = 0; i < 2; i++)
	{
		frame[40 + i] = check[i];
	}
	// udp checksum
	
	
	////////////////////
	//start payload data
	////////////////////
	
	assignData(
		0,				// lowerboundin
		42,				// lowerboundout
		foxtrotL,		// length
		payload,		// alpha in
		frame			// alpha out
	);
	// assing payload to frame
	
	
	//////////////
	//start socket
	//////////////
	
	WSADATA whiskeyData = { 0 };
	
	LPBYTE whiskeyVersion = calloc(2,sizeof(BYTE));
	
	int byteCount = 0;
	
	while (byteCount < 2)
	{
		*whiskeyVersion = (BYTE)2;
		whiskeyVersion++;
		byteCount++;
	}
	
	whiskeyVersion -= byteCount;
	
	int startupErr = WSAStartup(
		(WORD)whiskeyVersion,			// wVersionRequired
		&whiskeyData					// lpWSAData
	);
	
	if (startupErr != 0)
	{
		printf("couldn't start wsa: ");
		
		switch (startupErr)
		{
			case WSASYSNOTREADY:
				printf("underlying network subsystem not ready for coms\n");
				goto endoffunction;
			
			case WSAVERNOTSUPPORTED:
				printf("the requested version of winsock not supported\n");
				goto endoffunction;
				
			case WSAEINPROGRESS:
				printf("blocking windows socket 1.1 op in progress\n");
				goto endoffunction;
				
			case WSAEPROCLIM:
				printf("task limit reached\n");
				goto endoffunction;
				
			case WSAEFAULT:
				printf("lpWSAData parameter is not a valid pointer\n");
				goto endoffunction;
			
			default:
				printf("undefined error\n");
				goto endoffunction;
		}
	}
	
	
	SOCKET sierraSock = socket(
		AF_UNSPEC,
		SOCK_RAW,
		IPPROTO_RAW
	);
	
	BOOL sierraSocketErr = sErr(sierraSock);
	
	if (sierraSocketErr == FALSE)
	{
		printf("couldn't open socket for request.\n");
		
		goto endoffunction;
	}
	
	int socketAway = send(
		sierraSock,
		frame,
		fL,
		0
	);
	
	printf("socket away.\n");
	
	if (socketAway == SOCKET_ERROR)
	{
		printf("socket error %u\n", WSAGetLastError());
	}
	
	closesocket(sierraSock);
	
	
	endoffunction:{};
}
