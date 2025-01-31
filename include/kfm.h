#ifndef _KFM_H
#define _KFM_H

#include "Ref.h"
#include "dll_export.h"
#include <iostream>
#include <string>
#include <vector>
namespace Niflib
{

using namespace std;

// Classes used
class NiObject;

//--KFM File Format--//

// KFM Versions
const unsigned int VER_KFM_1_0 = 0x01000000;	  /*!< Kfm Version 1.0 */
const unsigned int VER_KFM_1_2_4b = 0x01020400;	  /*!< Kfm Version 1.2.4b */
const unsigned int VER_KFM_2_0_0_0b = 0x02000000; /*!< Kfm Version 2.0.0.0b */

// KFM Data Structure

struct KfmEventString
{
	unsigned int unk_int;
	string event;

	KfmEventString()
		: unk_int(0)
		, event(){};
	void Read(istream& in, unsigned int version);
	void Write(ostream& out, unsigned int version);
};

struct KfmEvent
{
	uint32_t id;
	uint32_t type;
	float duration;
	vector<KfmEventString> event_strings;

	KfmEvent()
		: id(0)
		, type(0)
		, duration(0.5f)
		, event_strings()
	{}
	void Read(istream& in, unsigned int version);
	// void Write( ostream & out, unsigned int version );
};

struct KfmAction
{
	uint32_t event_code;
	string action_name;
	string action_filename;
	unsigned int unk_int1;
	vector<KfmEvent> events;

	void Read(istream& in, unsigned int version);
	// void Write( ostream & out, unsigned int version );
};

struct Kfm
{
	uint32_t version;
	unsigned char unk_byte;
	string nif_filename;
	string master;
	uint32_t unk_int1;
	uint32_t unk_int2;
	float unk_float1;
	float unk_float2;
	vector<KfmAction> actions;
	uint32_t unk_int3;

	// Reads the given file and returns the KFM version.
	NIFLIB_API unsigned int Read(const string& file_name); // returns Kfm version
	NIFLIB_API unsigned int Read(istream& in);			   // returns Kfm version

	// Reads the NIF file and all KF files referred to in this KFM, and returns the root object of
	// the resulting NIF tree.
	NIFLIB_API Ref<NiObject> MergeActions(const string& path);
	// void Write( string const & file_name, unsigned int version );
	// void Write( ostream & out, unsigned int version );
};

} // namespace Niflib
#endif
