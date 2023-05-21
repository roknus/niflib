/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/NiAutoNormalParticles.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiAutoNormalParticles::TYPE("NiAutoNormalParticles", &NiParticles::TYPE);

NiAutoNormalParticles::NiAutoNormalParticles()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiAutoNormalParticles::~NiAutoNormalParticles()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& NiAutoNormalParticles::GetType() const
{
	return TYPE;
}

NiObject* NiAutoNormalParticles::Create()
{
	return new NiAutoNormalParticles;
}

void NiAutoNormalParticles::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticles::Read(in, link_stack, info);

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAutoNormalParticles::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticles::Write(out, link_map, missing_link_stack, info);

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiAutoNormalParticles::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticles::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAutoNormalParticles::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticles::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiAutoNormalParticles::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiParticles::GetRefs();
	return refs;
}

std::list<NiObject*> NiAutoNormalParticles::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiParticles::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
