//
//  MenuMeterNet.h
//
// 	Constants and other definitions for the Net Meter
//
//	Copyright (c) 2002-2014 Alex Harper
//
// 	This file is part of MenuMeters.
//
// 	MenuMeters is free software; you can redistribute it and/or modify
// 	it under the terms of the GNU General Public License version 2 as
//  published by the Free Software Foundation.
//
// 	MenuMeters is distributed in the hope that it will be useful,
// 	but WITHOUT ANY WARRANTY; without even the implied warranty of
// 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// 	GNU General Public License for more details.
//
// 	You should have received a copy of the GNU General Public License
// 	along with MenuMeters; if not, write to the Free Software
// 	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//


///////////////////////////////////////////////////////////////
//
//	Constants
//
///////////////////////////////////////////////////////////////

// Widths of the various displays
#define kNetArrowDisplayWidth				13
// #define kNetNumberDisplayGapWidth			2
#define kNetDisplayGapWidth					0

// Top network processes
#define kNetProcessCountMin					0
#define kNetProcessCountMax					25
#define kNetProcessCountDefault				5

// String for primary interface selection (primary interface)
#define kNetPrimaryInterface				@"primary"

///////////////////////////////////////////////////////////////
//
//	Preference information
//
///////////////////////////////////////////////////////////////

// Pref dictionary keys
#define kNetIntervalPref					@"NetInterval"
#define kNetDisplayModePref					@"NetDisplayMode"
#define kNetDisplayOrientationPref			@"NetOrientation"
#define kNetThroughputLabelPref				@"NetThroughputLabel"
#define kNetThroughput1KBoundPref			@"NetThroughput1KBound"
#define kNetThroughputBitsPref				@"NetThroughputBits"
#define kNetGraphStylePref					@"NetGraphStyle"
#define kNetGraphLengthPref					@"NetGraphLength"
#define kNetScaleModePref					@"NetScaleMode"
#define kNetScaleCalcPref					@"NetScaleCalc"
#define kNetPreferInterfacePref				@"NetPreferInterface"
#define kNetTransmitColorPref				@"NetTransmitColor"
#define kNetReceiveColorPref				@"NetReceiveColor"
#define kNetMaxProcessCountPref				@"NetMaxProcessCount"
#define kNetInactiveColorPref				@"NetInactiveColor"

// Display modes
enum {
	kNetDisplayArrows						= 1,
	kNetDisplayThroughput					= 2,
	kNetDisplayGraph						= 4
};
#define kNetDisplayDefault					(kNetDisplayGraph | kNetDisplayThroughput)

// Display orientation
enum {
	kNetDisplayOrientTxRx		= 0,
	kNetDisplayOrientRxTx
};
#define kNetDisplayOrientationDefault		kNetDisplayOrientRxTx

// Timer
#define kNetUpdateIntervalMin				0.5
#define kNetUpdateIntervalMax				20.0
#define kNetUpdateIntervalDefault			1.0

// Net scaling types
enum {
	kNetScaleInterfaceSpeed		= 0,
	kNetScalePeakTraffic
};
#define kNetScaleDefault					kNetScalePeakTraffic

// Net scaling calcs
enum {
	kNetScaleCalcLinear			= 0,
	kNetScaleCalcSquareRoot,
	kNetScaleCalcCubeRoot,
	kNetScaleCalcLog
};
#define kNetScaleCalcDefault				kNetScaleCalcCubeRoot

// Graph display
#define kNetGraphWidthMin					11
#define kNetGraphWidthMax					88
#define kNetGraphWidthDefault				44

// Net graph styles
enum {
	kNetGraphStyleStandard		= 0,
	kNetGraphStyleCentered,
	kNetGraphStyleOpposed,
	kNetGraphStyleInverseOpposed
};
#define kNetGraphStyleDefault				kNetGraphStyleCentered

// Throughput label
#define kNetThroughputLabelDefault			NO

// Thoughput 1K bound
#define kNetThroughput1KBoundDefault		YES

// Thoughput Bits per second
#define kNetThroughputBitsDefault			NO

// Colors
											// Moss green
#define kNetTransmitColorDefault			[NSColor colorWithDeviceRed:0.839f green:0.839f blue:0.839f alpha:1.0f]
											// Brick red
#define kNetReceiveColorDefault				[NSColor whiteColor]
											// Light grey
#define kNetInactiveColorDefault			[NSColor secondaryLabelColor]
