/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/NiAVObjectPalette.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiAVObjectPalette::TYPE("NiAVObjectPalette", &NiObject::TYPE);

NiAVObjectPalette::NiAVObjectPalette()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiAVObjectPalette::~NiAVObjectPalette()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& NiAVObjectPalette::GetType() const
{
	return TYPE;
}

NiObject* NiAVObjectPalette::Create()
{
	return new NiAVObjectPalette;
}

void NiAVObjectPalette::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read(in, link_stack, info);

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAVObjectPalette::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write(out, link_map, missing_link_stack, info);

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiAVObjectPalette::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAVObjectPalette::FixLinks(
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

std::list<NiObjectRef> NiAVObjectPalette::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject*> NiAVObjectPalette::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
