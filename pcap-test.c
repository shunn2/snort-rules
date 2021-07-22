#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include "packet_str.h"

void usage() {
	printf("syntax: pcap-test <interface>\n");
	printf("sample: pcap-test wlan0\n");
}

typedef struct {
	char* dev_;
} Param;

Param param  = {
	.dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
	if (argc != 2) {
		usage();
		return false;
	}
	param->dev_ = argv[1];
	return true;
}

void print_info(Ethernet* eth, Ip* ip, Tcp* tcp)
{
    printf("=========Ethernet=========\n");
    printf("src mac: %02X:%02X:%02X:%02X:%02X:%02X\n",eth->s_mac[0],eth->s_mac[1],eth->s_mac[2],eth->s_mac[3],eth->s_mac[4],eth->s_mac[5]);
    printf("dst mac: %02X:%02X:%02X:%02X:%02X:%02X\n",eth->d_mac[0],eth->d_mac[1],eth->d_mac[2],eth->d_mac[3],eth->d_mac[4],eth->d_mac[5]);
    printf("============IP============\n");
    printf("src ip: %u.%u.%u.%u\n",ip->src[0],ip->src[1],ip->src[2],ip->src[3]);
    printf("dst ip: %u.%u.%u.%u\n",ip->dest[0],ip->dest[1],ip->dest[2],ip->dest[3]);
    printf("============TCP===========\n");
    printf("src port: %u %u\n",tcp->s_port[0],tcp->s_port[1]);
    printf("dst port: %u %u\n",tcp->d_port[0],tcp->d_port[1]);
}

int main(int argc, char* argv[]) {
	if (!parse(&param, argc, argv))
		return -1;

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
	if (pcap == NULL) {
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
		return -1;
	}

	while (true) {
		struct pcap_pkthdr* header; //PACKET START
		const u_char* packet;
		int res = pcap_next_ex(pcap, &header, &packet); //META: H BUFFER START: PACKET
		if (res == 0) continue;
		if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK) {
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
		}

        Ethernet* ethernet_h = (Ethernet*)packet;
        int ethernet_size = 14;

        if(ntohs(ethernet_h->e_type) != 0x0800)
            continue;

        Ip* ip_h = (Ip*)(packet + ethernet_size);
        int ip_size = (ip_h->VHL & 0X0F) * 4;
        if(ip_h->protocol != 0x06)
            continue;

        Tcp* tcp_h = (Tcp*)(packet + ethernet_size + ip_size);
        int tcp_size = ((tcp_h->HLR & 0xF0) >> 4) * 4;

        u_char* data = (u_char*)(packet + ethernet_size + ip_size + tcp_size);
        //int data_size = ntohs(ip_h->total_len) - (ip_size + tcp_size);

        //printf("%u bytes captured\n", header->caplen);
        print_info(ethernet_h, ip_h, tcp_h);
        printf("\n \n");
	}

	pcap_close(pcap);
}
