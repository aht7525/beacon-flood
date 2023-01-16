#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Beacon.cpp"
#include <stdlib.h>
#include <time.h>

void usage() {
	printf("syntax: beacon-flood <interface> <ssid-list-file>\n");
	printf("sample: pcap-test wlan0 ssid-list-file.txt\n");
}

void monitor_mode(char* interface){
	char command[100];

	sprintf(command,"sudo ifconfig %s down",interface);
	system(command);
	memset(command,0,sizeof(command));

	sprintf(command,"sudo iwconfig %s mode monitor",interface);
	system(command);
	memset(command,0,sizeof(command));

	sprintf(command,"sudo ifconfig %s up",interface);
	system(command);
	memset(command,0,sizeof(command));

	sprintf(command,"sudo airodump-ng %s",interface);
	system(command);
}

typedef struct {
	char* dev_;
	char* ssid_list_;
} Param;

Param param = {
};

bool parse(Param* param, int argc, char* argv[]) {
	if (argc != 3) {
		usage();
		return false;
	}
	param->dev_ = argv[1];
	param->ssid_list_ = argv[2];
	return true;
}

void bssid_to_string(uint8_t *bssid,char* byte){
	sprintf(byte,"%02x:%02x:%02x:%02x:%02x:%02x",bssid[0],bssid[1],bssid[2],bssid[3],bssid[4],bssid[5]);
}

int main(int argc, char* argv[]) {

	char errbuf[PCAP_ERRBUF_SIZE];
	char ssid_list[100];
	int count = 0;
	if (!parse(&param, argc, argv))
		return -1;
	if(strlen(param.dev_) > 30){
		printf("Too long interface...\n");
		return -1;
	}
	//monitor_mode(param.dev_);

	pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);
    	if (pcap == NULL) {
        	fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
        	return -1;
    	}

	FILE* ssid_file = fopen(param.ssid_list_, "rb");
    	if (ssid_file == NULL){ //check file
        	printf("File not Found!\n");
        	return -1;
    	}
	
	struct real_beacon_frame fake_beacon_frame[100];
	uint8_t fake_bssid[6] = {0,};
	srand(time(0));
	while(fgets(ssid_list,sizeof(ssid_list),ssid_file) != NULL && count < 100){ //read_ssid and maximum 100
		for(int i = 3;i<6;i++){
			fake_bssid[i] = rand()%0xfe; //make fake bssid
		}
		fake_bssid[0] = 0x70;
		fake_bssid[1] = 0x5d;
		fake_bssid[2] = 0xcc;
		memcpy(fake_beacon_frame[count].radiotap_info.source_address,fake_bssid,6); //make fake bssid
		memcpy(fake_beacon_frame[count].radiotap_info.bssid,fake_bssid,6); //make fake bssid
		memcpy(fake_beacon_frame[count].tagged_ssid.ssid,ssid_list,32); //input ssid
		//fake_beacon_frame[count].tagged_ssid.ssid[strlen(ssid_list)-1] = 0; //edit ssid \n -> 0
		count++;
	}
	
	unsigned char dump_bssid[18] = {0,};
	
	while(1){
		for(int i = 0;i<count;i++){
			if (pcap_sendpacket(pcap, (unsigned char*)&fake_beacon_frame[i], sizeof(fake_beacon_frame[i])) != 0){
            			printf("Fail sendpacket\n");
            			exit (-1);
        		}
			bssid_to_string(fake_beacon_frame[i].radiotap_info.bssid,(char *)dump_bssid);
			printf("[BSSID] : %s | [SSID] : %.32s send!\n",dump_bssid,fake_beacon_frame[i].tagged_ssid.ssid);
			usleep(100);
		}
	}	
	printf("GOOD BYE~\n");
	pcap_close(pcap);
}
