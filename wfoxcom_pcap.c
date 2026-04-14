#include "winsock2.h"
#include "ws2tcpip.h"

#include "windows.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h"

#include "pcap.h"

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\MsWSock.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\WS2_32.Lib")

#pragma comment(lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.26100.0\\um\\x64\\OneCore.Lib")

#pragma comment(lib, "C:\\Program Files\\WpdPack\\Lib\\x64\\wpcap.lib")



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
	
	str macIn = argv[argc - 5];
	str ipIn = argv[argc - 4];
	str macOut = argv[argc - 3];
	str ipOut = argv[argc - 2];
	str iota = argv[argc - 1];
	
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
	
	unsigned short fL = 42 + foxtrotL;
	
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
	
	char perr[PCAP_ERRBUF_SIZE];
	
	pcap_if_t *devices;
	
	int delta = pcap_findalldevs(&devices,perr);
	
	pcap_if_t *deviceInstant;
	
	deviceInstant = devices;
	
	str iotaDevice;
	
	while (deviceInstant->next != NULL)
	{
		printf(
			"%s\n%s\n\n",
			deviceInstant->name,
			deviceInstant->description
		);
		
		for (int i = 1; i < strLength(deviceInstant->description); i++)
		{
			if (
				strCompare(
					strSubI(
						0,
						i,
						deviceInstant->description
					),
					iota
				) == 1
			)
			{
				iotaDevice = deviceInstant->name;
				
				goto devicecheck;
			}
		}
		
		deviceInstant = deviceInstant->next;
	}
	
	printf("couldn't find device.\n");
	pcap_freealldevs(devices);
	
	goto endoffunction;
	
	devicecheck:{};
	
	pcap_t *p;

	p = pcap_create(iotaDevice,perr);
	
	if (p == NULL)
	{
		printf("couldn't start pcap handle.\n");
		printf("%s\n",perr);
		
		pcap_freealldevs(devices);
		
		goto endoffunction;
	}
	
	if (pcap_activate(p) != 0)
	{
		printf("could not activate handle.\n");
		
		goto endoffunction;
	}
	
	pcap_sendpacket(
		p,
		frame,
		fL
	);
	
	pcap_freealldevs(devices);
	
	endoffunction:{};
}