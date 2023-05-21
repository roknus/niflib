/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/obj/NiTransparentProperty.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiTransparentProperty::TYPE("NiTransparentProperty", &NiProperty::TYPE);

NiTransparentProperty::NiTransparentProperty()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiTransparentProperty::~NiTransparentProperty()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type& NiTransparentProperty::GetType() const
{
	return TYPE;
}

NiObject* NiTransparentProperty::Create()
{
	return new NiTransparentProperty;
}

void NiTransparentProperty::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::Read(in, link_stack, info);
	for(unsigned int i1 = 0; i1 < 6; i1++)
	{
		NifStream(unknown[i1], in, info);
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiTransparentProperty::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::Write(out, link_map, missing_link_stack, info);
	for(unsigned int i1 = 0; i1 < 6; i1++)
	{
		NifStream(unknown[i1], out, info);
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiTransparentProperty::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiProperty::asString();
	array_output_count = 0;
	for(unsigned int i1 = 0; i1 < 6; i1++)
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
		out << "    Unknown[" << i1 << "]:  " << unknown[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiTransparentProperty::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTransparentProperty::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject*> NiTransparentProperty::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
