/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/NiBlendAccumTransformInterpolator.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type NiBlendAccumTransformInterpolator::TYPE(
	"NiBlendAccumTransformInterpolator",
	&NiBlendInterpolator::TYPE);

NiBlendAccumTransformInterpolator::NiBlendAccumTransformInterpolator()
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBlendAccumTransformInterpolator::~NiBlendAccumTransformInterpolator()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& NiBlendAccumTransformInterpolator::GetType() const
{
	return TYPE;
}

NiObject* NiBlendAccumTransformInterpolator::Create()
{
	return new NiBlendAccumTransformInterpolator;
}

void NiBlendAccumTransformInterpolator::Read(
	istream& in,
	list<unsigned int>& link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Read(in, link_stack, info);
	for(int i = 0; i < 58; i++)
	{
		NifStream(unk30[i], in, info);
	}

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendAccumTransformInterpolator::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Write(out, link_map, missing_link_stack, info);
	NifStream(unk30[0], out, info);

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBlendAccumTransformInterpolator::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	// out << NiBlendInterpolator::asString();
	// out << "  Float Value:  " << floatValue << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendAccumTransformInterpolator::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::FixLinks(objects, link_stack, missing_link_stack, info);

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBlendAccumTransformInterpolator::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiBlendInterpolator::GetRefs();
	return refs;
}

std::list<NiObject*> NiBlendAccumTransformInterpolator::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiBlendInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//


//--END CUSTOM CODE--//
