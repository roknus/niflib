/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/obj/BSLightingShaderPropertyFloatController.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type BSLightingShaderPropertyFloatController::TYPE(
	"BSLightingShaderPropertyFloatController",
	&NiFloatInterpController::TYPE);

BSLightingShaderPropertyFloatController::BSLightingShaderPropertyFloatController()
	: targetVariable(LSCV_UNKNOWN_FLOAT_2)
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSLightingShaderPropertyFloatController::~BSLightingShaderPropertyFloatController()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type& BSLightingShaderPropertyFloatController::GetType() const
{
	return TYPE;
}

NiObject* BSLightingShaderPropertyFloatController::Create()
{
	return new BSLightingShaderPropertyFloatController;
}

void BSLightingShaderPropertyFloatController::Read(
	istream& in,
	list<unsigned int>& link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Read(in, link_stack, info);
	NifStream(targetVariable, in, info);

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLightingShaderPropertyFloatController::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Write(out, link_map, missing_link_stack, info);
	NifStream(targetVariable, out, info);

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSLightingShaderPropertyFloatController::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiFloatInterpController::asString();
	out << "  Target Variable:  " << targetVariable << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLightingShaderPropertyFloatController::FixLinks(
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

std::list<NiObjectRef> BSLightingShaderPropertyFloatController::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiFloatInterpController::GetRefs();
	return refs;
}

std::list<NiObject*> BSLightingShaderPropertyFloatController::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
LightingShaderControlledVariable BSLightingShaderPropertyFloatController::GetTargetVariable() const
{
	return targetVariable;
}

void BSLightingShaderPropertyFloatController::SetTargetVariable(
	LightingShaderControlledVariable value)
{
	targetVariable = value;
}
//--END CUSTOM CODE--//
