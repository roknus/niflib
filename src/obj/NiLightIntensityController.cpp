/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/obj/NiLightIntensityController.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiLightIntensityController::TYPE(
	"NiLightIntensityController",
	&NiFloatInterpController::TYPE);

NiLightIntensityController::NiLightIntensityController()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiLightIntensityController::~NiLightIntensityController()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type& NiLightIntensityController::GetType() const
{
	return TYPE;
}

NiObject* NiLightIntensityController::Create()
{
	return new NiLightIntensityController;
}

void NiLightIntensityController::Read(
	istream& in,
	list<unsigned int>& link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Read(in, link_stack, info);

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiLightIntensityController::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Write(out, link_map, missing_link_stack, info);

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiLightIntensityController::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiFloatInterpController::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiLightIntensityController::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiLightIntensityController::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiFloatInterpController::GetRefs();
	return refs;
}

std::list<NiObject*> NiLightIntensityController::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
