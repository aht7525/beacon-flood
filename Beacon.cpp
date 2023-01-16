#include <stdio.h>
#include <stdint.h>

struct radiotap_header {
	uint8_t header_version = 0x00;
	uint8_t header_pad = 0x00;
	uint16_t header_length = 0x18;
	uint32_t header_Present_flag = 0xa000402e;
	uint32_t header_Present_flags_word = 0x820;
	uint8_t header_flags = 0x0;
	uint8_t header_data_rate = 0x2;
	uint16_t header_channel_frequency = 0x96c;
	uint16_t header_channel_flags=0x00a0;
	uint8_t header_antena_signal = 0xcf; //could edit
	uint8_t header_question=0x0;
	uint16_t header_rx_flags = 0x00;
	uint8_t header_antena_signal2 = 0xcf; //could edit
	uint8_t header_antena = 0x0;
} __attribute__((__packed__));

struct radio_information {
	uint16_t Beacon_frame_subtype = 0x0080;
	uint16_t duration = 0x0000;
	uint8_t reciver_address[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
	uint8_t source_address[6] = {0,}; //have to edit
	uint8_t bssid[6] = {0,}; //have to edit
	uint16_t sequence_number = 0x6050; //could edit

} __attribute__((__packed__));

struct wireless_management {
	uint64_t timestamp = 0x37b40d44; //could edit
	uint16_t beacon_interval = 0x00; //could edit	
	uint16_t capabilities_information = 0x0000; //could edit	
} __attribute__((__packed__));

struct tagged_parameter_ssid {
	uint8_t ssid_parameter_set = 0;
	uint8_t ssid_length = 32; //have to edit
	unsigned char ssid[32] = {0,}; //have to edit
} __attribute__((__packed__));

struct tagged_parameter_supported_rates {
	uint8_t support_rates = 0x1;
	uint8_t tag_length = 0x8;
	uint8_t aci_1 = 0x82;
	uint8_t aci_2 = 0x84;
	uint8_t aci_3 = 0x8b;
	uint8_t aci_4 = 0x96;
	uint8_t aci_5 = 0x0c;
	uint8_t aci_6 = 0x12;
	uint8_t aci_7 = 0x18;
	uint8_t aci_8 = 0x24;
} __attribute__((__packed__));

struct tagged_parameter_ds {
	uint8_t ds_parameter_set = 0x3;
	uint8_t tag_length = 0x1;
	uint8_t current_channel = 0x6;
} __attribute__((__packed__));

struct tagged_parameter_traffic {
	uint8_t traffic_parameter_set = 0x5;
	uint8_t tag_length = 0x4;
	uint8_t dtim_count = 0x1;
	uint8_t dtim_period = 0x3;
	uint8_t bitmap_control = 0x0;
	uint8_t partial_virtual_map = 0x2;
} __attribute__((__packed__));

struct tagged_erp_infomation {
	uint8_t erp_information_tag_number = 0x2a;
	uint8_t tag_length = 0x1;
	uint8_t erp_information = 0x4;
} __attribute__((__packed__));

struct tagged_extension {
	uint8_t tag_number = 0x32;
	uint8_t tag_length = 0x4;
	uint8_t rates_1 = 0x30;
	uint8_t rates_2 = 0x48;
	uint8_t rates_3 = 0x60;
	uint8_t rates_4 = 0x6c;
} __attribute__((__packed__));

struct tagged_QBS {
	uint8_t tag_number = 0xb;
	uint8_t tag_length = 5;
	uint16_t count = 0;
	uint8_t util = 0x40;
	uint16_t tmp = 0x0;
} __attribute__((__packed__));

struct tagged_HT {
	uint8_t tag_number = 0x2d;
	uint8_t tag_legnth = 0x1a;
	uint16_t info = 0x19ee;
	uint8_t mpdu = 0x1e;
	uint32_t bit_mask = 0x0000ffff;
	uint32_t bit_mask_2 = 0;
	uint16_t bit_mask_3 = 0x0;
	uint16_t data_mask = 0x0;
	uint32_t mcs_set = 0x0;
	uint16_t extension_ht = 0x0;
	uint32_t transmit_beam = 0x8810418;
	uint8_t antena_selection = 0x0;
} __attribute__((__packed__));

struct tagged_HT_infomation {
	uint8_t tag_number = 61;
        uint8_t tag_legnth = 22;
	uint8_t primary_channel = 0x6;
	uint8_t subset = 0x7;
	uint16_t subset2 = 0x0000;
	uint16_t subset3 = 0x0000;
	uint64_t tmp = 0;
	uint64_t tmp2 = 0x0;
} __attribute__((__packed__));

struct rsn_information {
	uint8_t tag_number = 0x30;
	uint8_t tag_length = 0x14;
	uint16_t rsn_version = 0x0001;
	uint32_t group_cipher = 0x04ac0f00;
	uint16_t group_suite_count = 0x1;
	uint32_t group_cipher2 = 0x04ac0f00;
	uint16_t suite_count2 = 0x1;
	uint32_t psk = 0x02ac0f00;
	uint16_t rsn_capability = 0x0000;	
} __attribute__((__packed__));

struct real_beacon_frame {
	struct radiotap_header radiotap_head;
	struct radio_information radiotap_info;
	struct wireless_management wireless_mana;
	struct tagged_parameter_ssid tagged_ssid;
	struct tagged_parameter_supported_rates tagged_rates;
	struct tagged_parameter_ds tagged_ds;
	struct tagged_parameter_traffic tagged_traf;
	struct tagged_erp_infomation tagged_erp;
	struct tagged_extension tagged_exte;
	struct tagged_QBS tagged_Q;
	struct tagged_HT tagged_H;
	struct tagged_HT_infomation tagged_H_info;
	struct rsn_information rsn_info;
} __attribute__((__packed__));

