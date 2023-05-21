/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/NiFloatsExtraData.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiFloatsExtraData::TYPE("NiFloatsExtraData", &NiExtraData::TYPE);

NiFloatsExtraData::NiFloatsExtraData()
	: numFloats((unsigned int)0)
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiFloatsExtraData::~NiFloatsExtraData()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& NiFloatsExtraData::GetType() const
{
	return TYPE;
}

NiObject* NiFloatsExtraData::Create()
{
	return new NiFloatsExtraData;
}

void NiFloatsExtraData::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Read(in, link_stack, info);
	NifStream(numFloats, in, info);
	data.resize(numFloats);
	for(unsigned int i1 = 0; i1 < data.size(); i1++)
	{
		NifStream(data[i1], in, info);
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatsExtraData::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write(out, link_map, missing_link_stack, info);
	numFloats = (unsigned int)(data.size());
	NifStream(numFloats, out, info);
	for(unsigned int i1 = 0; i1 < data.size(); i1++)
	{
		NifStream(data[i1], out, info);
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiFloatsExtraData::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numFloats = (unsigned int)(data.size());
	out << "  Num Floats:  " << numFloats << endl;
	array_output_count = 0;
	for(unsigned int i1 = 0; i1 < data.size(); i1++)
	{
		if(!verbose && (array_output_count > MAXARRAYDUMP))
		{
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if(!verbose && (array_output_count > MAXARRAYDUMP))
		{
			break;
		};
		out << "    Data[" << i1 << "]:  " << data[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatsExtraData::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFloatsExtraData::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject*> NiFloatsExtraData::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<float> NiFloatsExtraData::GetData() const
{
	return data;
}

void NiFloatsExtraData::SetData(const vector<float>& n)
{
	numFloats = (unsigned int)(n.size());
	data = n;
}

//--END CUSTOM CODE--//
