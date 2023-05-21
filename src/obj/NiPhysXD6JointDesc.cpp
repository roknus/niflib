/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/obj/NiPhysXD6JointDesc.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiPhysXD6JointDesc::TYPE("NiPhysXD6JointDesc", &NiObject::TYPE);

NiPhysXD6JointDesc::NiPhysXD6JointDesc()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPhysXD6JointDesc::~NiPhysXD6JointDesc()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type& NiPhysXD6JointDesc::GetType() const
{
	return TYPE;
}

NiObject* NiPhysXD6JointDesc::Create()
{
	return new NiPhysXD6JointDesc;
}

void NiPhysXD6JointDesc::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read(in, link_stack, info);
	if(info.version >= 0x14030006)
	{
		for(unsigned int i2 = 0; i2 < 388; i2++)
		{
			NifStream(unknownBytes[i2], in, info);
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXD6JointDesc::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write(out, link_map, missing_link_stack, info);
	if(info.version >= 0x14030006)
	{
		for(unsigned int i2 = 0; i2 < 388; i2++)
		{
			NifStream(unknownBytes[i2], out, info);
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPhysXD6JointDesc::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	array_output_count = 0;
	for(unsigned int i1 = 0; i1 < 388; i1++)
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
		out << "    Unknown Bytes[" << i1 << "]:  " << unknownBytes[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXD6JointDesc::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPhysXD6JointDesc::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject*> NiPhysXD6JointDesc::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
