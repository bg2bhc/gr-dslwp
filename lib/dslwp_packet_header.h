#ifndef __DSLWP_PACKET_HEADER_H__
#define __DSLWP_PACKET_HEADER_H__

#define LEN_PACKET_HEADER 			sizeof(packet_header_t)
/*
typedef struct __attribute__((__packed__))
{
	unsigned int version_number				: 3;
	unsigned int flag_type					: 1;
	unsigned int slave_header_flag				: 1;
	unsigned int application_type				: 3;
	unsigned int nid					: 8;
	unsigned int group_flag					: 2;
	unsigned int source_sequence_count			: 14;
	unsigned int packet_data_len				: 16;
} packet_header_t;
*/

typedef struct __attribute__((__packed__))
{
	unsigned int packet_data_len				: 16;
	unsigned int source_sequence_count			: 14;
	unsigned int group_flag					: 2;
	unsigned int nid					: 8;
	unsigned int application_type				: 3;
	unsigned int slave_header_flag				: 1;
	unsigned int flag_type					: 1;
	unsigned int version_number				: 3;
} packet_header_t;

#endif
