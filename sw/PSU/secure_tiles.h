#ifndef SECURE_TILES_H
#define SECURE_TILES_H


#include <stdint.h>
#include <stdlib.h>


// ---------------------------------- defines -----------------------
#define SST_FAILURE 1
#define SST_SUCCESS 0

#define	TILE_1_ID	0
#define TILE_2_ID 	1
#define TILE_3_ID 	2

#define	TILE_1_ADDR	0xA0010000
#define TILE_2_ADDR 0xA0020000
#define TILE_3_ADDR 0xA0030000

#define RP_NUM_OF_RP		3
#define TILE_NUM_OF_TILES	RP_NUM_OF_RP
#define DFX_MAX_NUM_OF_IP	10
#define	IP_MAX_NUM_OF_BIT	RP_NUM_OF_RP


/////////////////////////////////////////////	Bitstream	///////////////////////////////

/*
 *
 */
typedef struct
{
    uint32_t* data;		//address of the bit file in DRAM
    uint32_t size;		//size of the file
}bitstream_t;



/*
*    Everything necessary to load the bitstreams from SD card to DRAM.
*                        SD_card -> DRAM
*/
uint8_t bitstream_init(bitstream_t* bit, const char* file_path);





/////////////////////////////////////////////	IP		///////////////////////////////
/*
 * descrives and IP
 */
typedef struct
{
	uint32_t id;		//id of the IP
	bitstream_t* bits[IP_MAX_NUM_OF_BIT];	//array of Bitstream that represent this IP in the different TILEs. The TILE is associated with the index of the array.
}ip_t;

/*
 * request an ID for this IP
 */
uint8_t ip_init_ip(ip_t*, uint32_t);
/*
 * add an bitstream to an IP
 * returns error if there is already and bistream with the same ID
 */
uint8_t ip_add_bitstream(ip_t*, bitstream_t* , uint32_t tile_id);


//////////////////////////////////////////	TILE	//////////////////////////////////
typedef enum
{
	ACTIVE,
	AVAIL,

}tile_status;
/*
 *
 */
typedef struct
{
	bitstream_t* clear_bit;
	uint32_t *base_ptr;
	uint32_t ip_running;
	tile_status status;
}tile_t;

/*
 * initilaizes a tile
 */
uint8_t tile_init(tile_t* til);



////////////////////////////////////////////	DFX //////////////////////////////////
typedef struct
{
	tile_status tiles[3];
}sst_status;

typedef struct
{
	uint32_t status;
	tile_t tiles[TILE_NUM_OF_TILES];
	ip_t* ips[DFX_MAX_NUM_OF_IP];
}sst_t;




/*
*    initialization of dfx standalone
*    Everything necessary to get the DFX controller up and running.
*/
uint8_t sst_init(sst_t* dfx);

/*
*    Every operation necessary to load the bitstream to the RP
*                        DRAM -> RP
*                           DFX_trigger
*/
uint8_t sst_load_ip(sst_t* sst, ip_t* id, uint32_t tile_num);



#endif // SECURE_TILES_H
