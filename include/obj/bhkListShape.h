/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKLISTSHAPE_H_
#define _BHKLISTSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkShapeCollection.h"

// Include structures
#include "../Ref.h"
namespace Niflib
{

// Forward define of referenced NIF objects
class bhkShape;
class bhkListShape;
typedef Ref<bhkListShape> bhkListShapeRef;

/*!
 * A list of shapes.
 *
 *         Do not put a bhkPackedNiTriStripsShape in the Sub Shapes. Use a
 *         separate collision nodes without a list shape for those.
 *
 *         Also, shapes collected in a bhkListShape may not have the correct
 *         walking noise, so only use it for non-walkable objects.
 */
class bhkListShape : public bhkShapeCollection
{
public:
	/*! Constructor */
	NIFLIB_API bhkListShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkListShape();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * A factory function used during file reading to create an instance of this type of object.
	 * \return A pointer to a newly allocated instance of this type of object.
	 */
	NIFLIB_API static NiObject* Create();

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data
	 * will be printed out. \return A string containing a summary of the information within the
	 * object in English.  This is the function that Niflyze calls to generate its analysis, so the
	 * output is the same.
	 */
	NIFLIB_API virtual string asString(bool verbose = false) const;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type& GetType() const;

	//--BEGIN MISC CUSTOM CODE--//

	/*!
	 * Retrieves the child shape objects that this body is using.
	 * \return The shape objects being used by this body.
	 */
	NIFLIB_API vector<Ref<bhkShape>> GetSubShapes() const;

	/*!
	 * Sets the child shape objects that this body is using.
	 * \param[in] shapes The shape objects being used by this body.
	 */
	NIFLIB_API void SetSubShapes(const vector<Ref<bhkShape>>& shapes);

	/*!
	 * Get the shape's material.  This determines the type of noises the object makes as it collides
	 * in Oblivion. \return The Oblivion material used by this collision shape.
	 */
	NIFLIB_API HavokMaterial GetMaterial() const;

	/*!
	 * Sets the shape's material.  This determines the type of noises the object makes as it
	 * collides in Oblivion. \param[in] value The new material for this shape to use.
	 */
	NIFLIB_API void SetMaterial(HavokMaterial value);

	/*! Helper routine for calculating mass properties.
	 *  \param[in]  density Uniform density of object
	 *  \param[in]  solid Determines whether the object is assumed to be solid or not
	 *  \param[out] mass Calculated mass of the object
	 *  \param[out] center Center of mass
	 *  \param[out] inertia Mass Inertia Tensor
	 *  \return Return mass, center, and inertia tensor.
	 */
	NIFLIB_API virtual void CalcMassProperties(
		float density,
		bool solid,
		float& mass,
		float& volume,
		Vector3& center,
		InertiaMatrix& inertia);

	//--END CUSTOM CODE--//
protected:
	/*! The number of sub shapes referenced. */
	mutable unsigned int numSubShapes;
	/*! List of shapes. */
	vector<Ref<bhkShape>> subShapes;
	/*! The shape's material. */
	HavokMaterial material;
	/*! The shape's material. */
	SkyrimHavokMaterial skyrimMaterial;
	/*! Unknown. Set to (0.0,0.0,-0.0,0.0,0.0,-0.0), where -0.0 is 0x80000000 in hex. */
	array<6, float> unknownFloats;
	/*! Count. */
	mutable unsigned int numUnknownInts;
	/*! Unknown. */
	vector<unsigned int> unknownInts;

public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read(
		istream& in,
		list<unsigned int>& link_stack,
		const NifInfo& info);
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write(
		ostream& out,
		const map<NiObjectRef, unsigned int>& link_map,
		list<NiObject*>& missing_link_stack,
		const NifInfo& info) const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks(
		const map<unsigned int, NiObjectRef>& objects,
		list<unsigned int>& link_stack,
		list<NiObjectRef>& missing_link_stack,
		const NifInfo& info);
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObjectRef> GetRefs() const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObject*> GetPtrs() const;
};

//--BEGIN FILE FOOT CUSTOM CODE--//
//--END CUSTOM CODE--//

} // namespace Niflib
#endif
