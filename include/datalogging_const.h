/*
 * Copyright (C) 2003 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * Linux Megasquirt tuning software
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute, etc. this as long as all the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 */

#ifndef __DATALOGGING_CONST_H__
#define __DATALOGGING_CONST_H__

#include <gtk/gtk.h>
#include <structures.h>


/* logable_names[] is an array of textual names corresponding to all logable
 * variables from the MS
 */
static const gchar *logable_names[] = 
{
"HR Clock",	"MS Clock",	"RPM",		"EngineBits",	"Idle DC",
"TPS Volts",	"MAP Volts",	"BARO Volts",	"MAT Volts",	"CLT Volts",
"TPS Counts",	"MAP Counts",	"BARO Counts",	"MAT Counts",	"CLT Counts",
"TPS %",	"MAP KPA",	"BARO KPA",	"MAT (Deg)",	"CLT (Deg)",
"O2 Volts",	"O2 Counts",	"GammaE",	"BATT Volts",	"BATT Counts",
"AIRcorr",	"BAROcorr",	"EGOcorr",	"WARMcorr",	"TPSaccel",
"VE1",		"VE2",		"PW1",		"PW2",		"INJ-1 Dcycle",
"INJ-2 Dcycle",	"CycleTimeH",	"CycleTimeL",	"SparkAngle",	"BSPOT1",	"BSPOT2",	"BSPOT3"
};

static const gchar *mt_classic_names[] = 
{
"Time",		"Seconds",	"RPM",		"EngineBit",	"IdleDC",
"TPS_Volts",	"MAP_Volts",	"BARO_Volts",	"MAT_Volts",	"CLT_Volts",
"TPS_Counts",	"MAP_Counts",	"BARO_Counts",	"MAT_Counts",	"CLT_Counts",
"TP",		"MAP",		"BARO", 	"MAT",		"CLT",
"O2",		"O2_Counts",	"Gammae",	"BATT_Volts",	"BATT_Counts",
"Gair",		"Gbaro",	"Gego",		"Gwarm",	"TPSacc",
"Gve",		"Gve2",		"PW",		"PW2",		"INJ-1_Dcycle",
"INJ-2_Dcycle",	"CycleTimeH",	"CycleTimeL",	"SparkAngle",	"BSPOT1",	"BSPOT2",	"BSPOT3"
};

static const gchar *mt_full_names[] = 
{
"Time",		"SecL",		"RPM",		"Engine",	"IdleDC",
"TPS_Volts",	"MAP_Volts",	"BARO_Volts",	"MAT_Volts",	"CLT_Volts",
"TPS_Counts",	"MAP_Counts",	"BARO_Counts",	"MAT_Counts",	"CLT_Counts",
"TP",		"MAP",		"BARO", 	"MAT",		"CLT",
"O2",		"O2_Counts",	"Gammae",	"BATT_Volts",	"BATT_Counts",
"Gair",		"Gbaro",	"Gego",		"Gwarm",	"TPSacc",
"Gve",		"Gve2",		"PW",		"PW2",		"INJ-1_Dcycle",
"INJ-2_Dcycle",	"CycleTimeH",	"CycleTimeL",	"SparkAngle",	"BSPOT1",	"BSPOT2",	"BSPOT3"
};

/* logging_offset_map is a mapping between the logable_names[] list above 
 * and the byte offset into the Runtime_Common datastructure. The index 
 * is the index number of the logable variable from above, The value at that
 * index point is the offset into the struct for the data. Offset 0
 * is the first value in the struct (secl), offset 99 is a special case
 * for the Hi-Res clock which isn't stored in the structure...
 */
static const gint logging_offset_map[] =
{
        99,54,52,56,74,
        24,16, 0,20, 8,
        68,66,62,67,64,
        44,60,59,50,48,
        12,65,61, 4,63,
        69,70,71,73,72,
        57,58,36,40,28,
        32,75,76,77,78,
	79,80
};

/* mt_classic_order[] is an arry signifying the ORDER that the variables 
 * are displayed in the logfile.  This is done ONLY to make the logs 
 * 100% compatible with ms-tweek3K. -1 means it's not logged, anything from
 * 1 on up signifies the order in which they get logged to the logfile...
 */
static const gint mt_classic_order[] = 
{
	-1, 0, 1, 4,-1,
	-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,
	-1, 2,-1,-1,-1,
	 3,-1,10,-1,-1,
	 6, 8, 5, 7,-1,
	 9,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,
	-1,-1
};

/* mt_full_order[] is an arry signifying the ORDER that the variables 
 * are displayed in the logfile.  This is done ONLY to make the logs 
 * 100% compatible with ms-tweek3K. -1 means it's not logged, anything from
 * 0 on up signifies the order in which they get logged to the logfile...
 */
static const gint mt_full_order[] = 
{
	 0, 1, 2, 8,-1,
	-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,
	 4, 3,-1, 6, 7,
	 5,-1,13,-1,-1,
	10,12, 9,11,14,
	15,17,16,18,-1.
	-1,-1,-1,-1,-1,
	-1,-1
};

/* Size of each logable variable in BYTES, so 4 = a 32 bit var 
 * This strange array is needed only forthe fact that the datalogging
 * functions get all of their data from the Runtime_Common struct.
 * that struct has been deigned (And is necessary) to have all the 
 * largest varibles first (floats before shorts before chars), so that
 * the structure can be referenced in array notation, this way all data
 * is accessible by the appropriate index.
 * The values in this array correspond to the size of the referenced
 * variable in that Runtime_Common struct.
 */
static const gint logging_datasizes_map[] =
{
        FLOAT,UCHAR,SHORT,UCHAR,UCHAR,
        FLOAT,FLOAT,FLOAT,FLOAT,FLOAT,
        UCHAR,UCHAR,UCHAR,UCHAR,UCHAR,
        FLOAT,UCHAR,UCHAR,SHORT,UCHAR,
        FLOAT,UCHAR,UCHAR,FLOAT,UCHAR,
        UCHAR,UCHAR,UCHAR,UCHAR,UCHAR,
        UCHAR,UCHAR,FLOAT,FLOAT,FLOAT,
        FLOAT,UCHAR,UCHAR,UCHAR,UCHAR,
	UCHAR,UCHAR
};


static struct Limits limits[]= {
{ 0.0,4294967269.0},/* 0 HR clock */
{ 0.0,255.0},	/* 1 MS clock */
{ 0.0,25500.0},	/* 2 RPM */
{ 0.0,255.0},	/* 3 EngineBit */
{ 0.0,100.0},	/* 4 IdleDC */
{ 0.0,5.0},	/* 5 TPS Volts */
{ 0.0,5.0},	/* 6 MAP Volts */
{ 0.0,5.0},	/* 7 BARO Volts */
{ 0.0,5.0},	/* 8 MAT Volts */
{ 0.0,5.0},	/* 9 CLT Volts */
{ 0.0,255.0},	/* 10 TPS Counts */
{ 0.0,255.0},	/* 11 MAP Counts */
{ 0.0,255.0},	/* 12 BARO Counts */
{ 0.0,255.0},	/* 13 MAT Counts */
{ 0.0,255.0},	/* 14 CLT Counts */
{ 0.0,100.0},	/* 15 TPS % */
{ 0.0,255.0},	/* 16 MAP (in KPA) */
{ 0.0,255.0},	/* 17 Baro (in KPA) */
{ -40.0,215.0},	/* 18 MAT (in DEG) */
{ -40.0,215.0},	/* 19 CLT (in DEG) */
{ 0.0,5.0},	/* 20 O2 Volts */
{ 0.0,255.0},	/* 21 O2 Counts */
{ 0.0,255.0},	/* 22 Gammae */
{ 0.0,18.0},	/* 23 BATT Volts */
{ 0.0,255.0},	/* 24 BATT Counts */
{ 0.0,255.0},	/* 25 AirCorr */
{ 0.0,255.0},	/* 26 BAROCorr */
{ 0.0,255.0},	/* 27 EGOCorr */
{ 0.0,255.0},	/* 28 WARMCorr */
{ 0.0,255.0},	/* 29 TpsAccel */
{ 0.0,255.0},	/* 30 VE1 */
{ 0.0,255.0},	/* 31 VE2 */
{ 0.0,25.5},	/* 32 PW1 */
{ 0.0,25.5},	/* 33 PW2 */
{ 0.0,100.0},	/* 34 Dcycle1 */
{ 0.0,100.0},	/* 35 Dcycle2 */
{ 0.0,255.0},	/* 36 CycleTimeH */
{ 0.0,255.0},	/* 37 CycleTimeL */
{ 0.0,90.0},	/* 38 SparkAngle */
{ 0.0,255.0},	/* 39 BSPOT1 */
{ 0.0,255.0},	/* 40 BSPOT2 */
{ 0.0,255.0}	/* 41 BSPOT3 */
};

/* Tooltips for each of the above.... */
static const gchar * logable_names_tips[] = 
{
"\"HR Clock\" is a High resolution clock recorded to the logfile by this pc when data arrives, resolution of 1 millisecond (stored in seconds)",
"\"MS Clock\" is the MegaSquirt clock returned by the ECU, this runs from 0-255 and recylcles indefinitely, resolution 1 second.",
"\"RPM\" Is the engine RPM, stored in the log as it's actual RPM, resolution 100RPM",
"\"EngineBits\" is a bitfield containing information such as cranking/running, accel enrich, decel mode and warmup enrichment.  It require decoding, use the information in globals.h for the \"engine\" union.",
"\"IdleDC\" is the duty cycle for the Idle control (ONLY available when using dualtable firmware",
"\"TPS Volts\" is the reading from the Throttle Position sensor converted to volts. Range is 0-5 volts, resolution of 19.6 millivolts (8 bits)",
"\"MAP Volts\" is the reading from the Manifold Absolute Pressure sensor converted to volts. Range is 0-5 volts, resolution of 19.6 millivolts (8 bits)",
"\"BARO Volts\" is the reading from the Manifold Absolute Pressure sensor before engine startup converted to volts. Range is 0-5 volts, resolution of 19.6 millivolts (8 bits)",
"\"MAT Volts\" is the reading from the Manifold Air Temperature sensor converted to volts. Range is 0-5 volts, resolution of 19.6 millivolts (8 bits)",
"\"CLT Volts\" is the reading from the Engine CooLant Temperature sensor converted to volts. Range is 0-5 volts, resolution of 19.6 millivolts (8 bits)",
"\"TPS Counts\" is the raw ADC counts from the Throttle Position sensor reading. Range is 0-255 counts, resolution of 1 counts",
"\"MAP Counts\" is the raw ADC counts from the Manifold Absolute Pressure sensor reading. Range is 0-255 counts, resolution of 1 counts",
"\"BARO Counts\" is the raw ADC counts from the Manifold Absolute Pressure sensor before engine startup. Range is 0-255 counts, resolution of 1 counts",
"\"MAT Counts\" is the raw ADC counts from the Manifold Air Temperature sensor reading. Range is 0-255 counts, resolution of 1 counts",
"\"CLT Counts\" is the raw ADC counts from the CooLant Temperature sensor reading. Range is 0-255 counts, resolution of 1 counts",
"\"TPS %\" is the Throttle Position in percentage of open (based on counts, a count of 255 is equal to 100% open)",
"\"MAP KPA\" is the Manifold Absolute Pressure in KPA (Kilopascals), 100KPA is atmospheric pressure at seal level.",
"\"BARO KPA\" is the Manifold Absolute Pressure BEFORE engine startup in KPA (Kilopascals), 100KPA is atmospheric pressure at seal level.",
"\"MAT (Deg)\", is the Manifold Air Temperature in conventional thermal units (centigrade of fahrenheit depending on what you've set in the General Tab)",
"\"CLT (Deg)\", is the Engine CooLant Temperature in conventional thermal units (centigrade of fahrenheit depending on what you've set in the General Tab)",
"\"O2 Volts\" is the Exhaust Oxygen Sensor voltage. Range 0-5 Volts, resolution 19.6 mv",
"\"O2 Counts\" is the raw ADC counts for the Exhaust Gas Oxygen reading, Range 0-255, resolution 1 count",
"\"GammaE\" is the summation of ALL enrichments (temp enrich,accel enrich, warmup enrich, etc..) in the MegaSquirt ECU.",
"\"BATT Volts\" is the Battery voltage in DC volts",
"\"BATT Counts\" is the raw ADC counts for the Battery Voltage input, Range 0-255, resolution 1 count",
"\"AIRcorr\" is the Air temperature correction factor.  This is expressed as a percentage, 100 being NO enrichment, anything over 100 causes additional fuel to be added,  less than 100 means less fuel.",
"\"BAROcorr\" is the Barometer correction factor.  This is expressed as a percentage, 100 being NO enrichment, anything over 100 causes additional fuel to be added,  less than 100 means less fuel.",
"\"EGOcorr\" is the Exhaust Gas Correction factor.  This is expressed as a percentage, 100 being NO enrichment, anything over 100 causes additional fuel to be added,  less than 100 means less fuel. The EGO Feedback settings on the Enrichments tab have the most effect on this parameter.",
"\"WARMcorr\" is the Warmup Correction factor.  This influenced by the Coolant Temp sensor input and the Warmup Enrichment bins on the Enrichments tab.  This is expressed as a percentage, 100 being NO enrichment, anything over 100 causes additional fuel to be added,  less than 100 means less fuel.",
"\"TPSaccel\" is the amount of Acceleration enrichment being dispensed. Units are in milliseconds x10, so 10 ms shows upa as 100 in the log",
"\"VE1\" is the instantaneous volumetric efficiency that the MS calculating fuel for for channel 1. NOTE: Dualable variants can have differing values for each table.  For standard MegaSquirts this is the global VE, as both injector channels run off of one table.",
"\"VE2\" is the instantaneous volumetric efficiency for the MS for table 2 (Dualtable code variants ONLY), this value is undefined for standard MegaSquirt ECU's",
"\"PW1\" is the pulsewidth in milliseconds for the injectors tied to channel 1. (and channel two for NON-dualtable MegaSquirt).",
"\"PW2\" is the pulsewidth in millisecondws for the injectors tied to channel 2. (Dualtable ONLY, this is undefined for standard MegaSquirt)",
"\"INJ-1 Dcycle\" is the injector Duty cycle for channel 1 (and channel 2 on standard MegaSquirt ECU's)",
"\"INJ-2 Dcycle\" is the injectior Duty Cycle for channel 2 (Dualtable code variants ONLY, this is undefiend for Standard MegaSquirts)", 
"\"CycleTimeH\" is unknown (from MegaSquirtnEDIS  code)", 
"\"CycleTimeL\" is unknown (from MegaSquirtnEDIS  code)", 
"\"SparkAngle\" is unknown (from MegaSquirtnEDIS  code)", 
"\"BSPOT1\" is one of three blank spots returned in the runtime variables for standard MegaSquirt ECUs. Some of the less known MS variants use these to communicate back additional data.  These are loggable just for this reasons.  Units are 0-255, resolution of 1.",
"\"BSPOT2\" is one of three blank spots returned in the runtime variables for standard MegaSquirt ECUs. Some of the less known MS variants use these to communicate back additional data.  These are loggable just for this reasons.  Units are 0-255, resolution of 1.",
"\"BSPOT3\" is one of three blank spots returned in the runtime variables for standard MegaSquirt ECUs. Some of the less known MS variants use these to communicate back additional data.  These are loggable just for this reasons.  Units are 0-255, resolution of 1."
};
#endif
