/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/obj/BSMasterParticleSystem.h"
#include "../../include/FixLink.h"
#include "../../include/NIF_IO.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

// Definition of TYPE constant
const Type BSMasterParticleSystem::TYPE("BSMasterParticleSystem", &NiNode::TYPE);

BSMasterParticleSystem::BSMasterParticleSystem()
	: maxEmitterObjects((unsigned short)0)
	, numParticleSystems((int)0)
{
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSMasterParticleSystem::~BSMasterParticleSystem()
{
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type& BSMasterParticleSystem::GetType() const
{
	return TYPE;
}

NiObject* BSMasterParticleSystem::Create()
{
	return new BSMasterParticleSystem;
}

void BSMasterParticleSystem::Read(istream& in, list<unsigned int>& link_stack, const NifInfo& info)
{
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiNode::Read(in, link_stack, info);
	NifStream(maxEmitterObjects, in, info);
	NifStream(numParticleSystems, in, info);
	particleSystems.resize(numParticleSystems);
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
	{
		NifStream(block_num, in, info);
		link_stack.push_back(block_num);
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMasterParticleSystem::Write(
	ostream& out,
	const map<NiObjectRef, unsigned int>& link_map,
	list<NiObject*>& missing_link_stack,
	const NifInfo& info) const
{
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::Write(out, link_map, missing_link_stack, info);
	numParticleSystems = (int)(particleSystems.size());
	NifStream(maxEmitterObjects, out, info);
	NifStream(numParticleSystems, out, info);
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
	{
		if(info.version < VER_3_3_0_13)
		{
			WritePtr32(&(*particleSystems[i1]), out);
		}
		else
		{
			if(particleSystems[i1] != NULL)
			{
				map<NiObjectRef, unsigned int>::const_iterator it =
					link_map.find(StaticCast<NiObject>(particleSystems[i1]));
				if(it != link_map.end())
				{
					NifStream(it->second, out, info);
					missing_link_stack.push_back(NULL);
				}
				else
				{
					NifStream(0xFFFFFFFF, out, info);
					missing_link_stack.push_back(particleSystems[i1]);
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

std::string BSMasterParticleSystem::asString(bool verbose) const
{
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiNode::asString();
	numParticleSystems = (int)(particleSystems.size());
	out << "  Max Emitter Objects:  " << maxEmitterObjects << endl;
	out << "  Num Particle Systems:  " << numParticleSystems << endl;
	array_output_count = 0;
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
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
		out << "    Particle Systems[" << i1 << "]:  " << particleSystems[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMasterParticleSystem::FixLinks(
	const map<unsigned int, NiObjectRef>& objects,
	list<unsigned int>& link_stack,
	list<NiObjectRef>& missing_link_stack,
	const NifInfo& info)
{
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::FixLinks(objects, link_stack, missing_link_stack, info);
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
	{
		particleSystems[i1] = FixLink<NiAVObject>(objects, link_stack, missing_link_stack, info);
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSMasterParticleSystem::GetRefs() const
{
	list<Ref<NiObject>> refs;
	refs = NiNode::GetRefs();
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
	{
		if(particleSystems[i1] != NULL)
			refs.push_back(StaticCast<NiObject>(particleSystems[i1]));
	};
	return refs;
}

std::list<NiObject*> BSMasterParticleSystem::GetPtrs() const
{
	list<NiObject*> ptrs;
	ptrs = NiNode::GetPtrs();
	for(unsigned int i1 = 0; i1 < particleSystems.size(); i1++)
	{
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
