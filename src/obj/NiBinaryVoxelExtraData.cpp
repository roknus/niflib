/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/NiBinaryVoxelExtraData.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/obj/NiBinaryVoxelData.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiBinaryVoxelExtraData::TYPE("NiBinaryVoxelExtraData", &NiExtraData::TYPE);

NiBinaryVoxelExtraData::NiBinaryVoxelExtraData()
	: unknownInt((unsigned int)0)
	, data(NULL)
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBinaryVoxelExtraData::~NiBinaryVoxelExtraData()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& NiBinaryVoxelExtraData::GetType() const
{
	return TYPE;
}

NiObject* NiBinaryVoxelExtraData::Create()
{
	return new NiBinaryVoxelExtraData;
}

void NiBinaryVoxelExtraData::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiExtraData::Read(in, link_stack, info);
	NifStream(unknownInt, in, info);
	NifStream(block_num, in, info);
	link_stack.push_back(block_num);

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBinaryVoxelExtraData::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write(out, link_map, missing_link_stack, info);
	NifStream(unknownInt, out, info);
	if(info.version < VER_3_3_0_13)
	{
		WritePtr32(&(*data), out);
	}
	else
	{
		if(data != NULL)
		{
			map<NiObjectRef, unsigned int>::const_iterator it =
				link_map.find(StaticCast<NiObject>(data));
			if(it != link_map.end())
			{
				NifStream(it->second, out, info);
				missing_link_stack.push_back(NULL);
			}
			else
			{
				NifStream(0xFFFFFFFF, out, info);
				missing_link_stack.push_back(data);
			}
		}
		else
		{
			NifStream(0xFFFFFFFF, out, info);
			missing_link_stack.push_back(NULL);
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBinaryVoxelExtraData::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiExtraData::asString();
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBinaryVoxelExtraData::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks(objects, link_stack, missing_link_stack, info);
	data = FixLink<NiBinaryVoxelData>(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBinaryVoxelExtraData::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiExtraData::GetRefs();
	if(data != NULL)
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject*> NiBinaryVoxelExtraData::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
