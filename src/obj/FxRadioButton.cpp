/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/obj/FxRadioButton.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
using namespace Niflib;

// Definition of TYPE constant
const Type FxRadioButton::TYPE("FxRadioButton", &FxWidget::TYPE);

FxRadioButton::FxRadioButton()
	: unknownInt1((unsigned int)0)
	, unknownInt2((unsigned int)0)
	, unknownInt3((unsigned int)0)
	, numButtons((unsigned int)0)
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

FxRadioButton::~FxRadioButton()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type& FxRadioButton::GetType() const
{
	return TYPE;
}

NiObject* FxRadioButton::Create()
{
	return new FxRadioButton;
}

void FxRadioButton::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	FxWidget::Read(in, link_stack, info);
	NifStream(unknownInt1, in, info);
	NifStream(unknownInt2, in, info);
	NifStream(unknownInt3, in, info);
	NifStream(numButtons, in, info);
	buttons.resize(numButtons);
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
	{
		NifStream(block_num, in, info);
		link_stack.push_back(block_num);
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void FxRadioButton::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	FxWidget::Write(out, link_map, missing_link_stack, info);
	numButtons = (unsigned int)(buttons.size());
	NifStream(unknownInt1, out, info);
	NifStream(unknownInt2, out, info);
	NifStream(unknownInt3, out, info);
	NifStream(numButtons, out, info);
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
	{
		if(info.version < VER_3_3_0_13)
		{
			WritePtr32(&(*buttons[i1]), out);
		}
		else
		{
			if(buttons[i1] != NULL)
			{
				map<NiObjectRef, unsigned int>::const_iterator it =
					link_map.find(StaticCast<NiObject>(buttons[i1]));
				if(it != link_map.end())
				{
					NifStream(it->second, out, info);
					missing_link_stack.push_back(NULL);
				}
				else
				{
					NifStream(0xFFFFFFFF, out, info);
					missing_link_stack.push_back(buttons[i1]);
				}
			}
			else
			{
				NifStream(0xFFFFFFFF, out, info);
				missing_link_stack.push_back(NULL);
			}
		}
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string FxRadioButton::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << FxWidget::asString();
	numButtons = (unsigned int)(buttons.size());
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int  2:  " << unknownInt2 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Num Buttons:  " << numButtons << endl;
	array_output_count = 0;
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
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
		out << "    Buttons[" << i1 << "]:  " << buttons[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void FxRadioButton::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	FxWidget::FixLinks(objects, link_stack, missing_link_stack, info);
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
	{
		buttons[i1] = FixLink<FxRadioButton>(objects, link_stack, missing_link_stack, info);
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> FxRadioButton::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = FxWidget::GetRefs();
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
	{
	};
	return refs;
}

std::list<NiObject*> FxRadioButton::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = FxWidget::GetPtrs();
	for(unsigned int i1 = 0; i1 < buttons.size(); i1++)
	{
		if(buttons[i1] != NULL)
			ptrs.push_back((NiObject*)(buttons[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
