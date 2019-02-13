/**
 * \file noff.h 
 * \brief Data structures defining the Nachos Object Code Format
 *
 * Data structures defining the Nachos Object Code Format
 *
 *  Basically, we only know about three types of segments:
 *	code (read-only), initialized data, and unitialized data
 */

/// magic number denoting Nachos object code file
#define NOFFMAGIC	0xbadfad 	

/**
 * \struct segment
 */
typedef struct segment {
  /// location of segment in virt addr space
  int virtualAddr;
  
  /// location of segment in this file
  int inFileAddr;

  /// size of segment
  int size;			
} Segment;

/**
 * \struct noffHeader
 */
typedef struct noffHeader {
   /// should be NOFFMAGIC
   int noffMagic;

   /// executable code segment
   Segment code;

   /// initialized data segment
   Segment initData;

   /**
    * \brief uninitialized data segment --
    * should be zero'ed before use 
    */
   Segment uninitData;
} NoffHeader;
