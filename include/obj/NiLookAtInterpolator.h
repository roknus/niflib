/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NILOOKATINTERPOLATOR_H_
#define _NILOOKATINTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiInterpolator.h"
#include "nif_math.h"

namespace Niflib
{

// Forward define of referenced NIF objects
class NiNode;
class NiPoint3Interpolator;
class NiFloatInterpolator;
class NiLookAtInterpolator;
typedef Ref<NiLookAtInterpolator> NiLookAtInterpolatorRef;

/*! Unknown. */
class NiLookAtInterpolator : public NiInterpolator
{
public:
	/*! Constructor */
	NIFLIB_API NiLookAtInterpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiLookAtInterpolator();

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
	 * Retrieves the node that this interpolator is focused on.
	 * \return The node that this interpolator is focused on.
	 */
	NIFLIB_API Ref<NiNode> GetLookAt() const;

	/*!
	 * Sets the node that this interpolator will focus on.
	 * \return The new node that the interpolator will focus on, or NULL to clear the current one.
	 */
	NIFLIB_API void SetLookAt(Ref<NiNode> value);

	/*!
	 * Gets the translation of the interpolator.  Could be the necessary value to point at the
	 * referenced node in the current pose. \return The translation of the interpolator.
	 */
	NIFLIB_API Vector3 GetTranslation() const;

	/*!
	 * Sets the translation of the interpolator.  Could be the necessary value to point at the
	 * referenced node in the current pose. \param[in] value The new translation for the
	 * interpolator.
	 */
	NIFLIB_API void SetTranslation(Vector3 value);

	/*!
	 * Gets the rotation of the interpolator.  Could be the necessary value to point at the
	 * referenced node in the current pose. \return The rotation of the interpolator.
	 */
	NIFLIB_API Quaternion GetRotation() const;

	/*!
	 * Sets the rotation of the interpolator.  Could be the necessary value to point at the
	 * referenced node in the current pose. \param[in] value The new rotation for the interpolator.
	 */
	NIFLIB_API void SetRotation(Quaternion value);

	/*!
	 * Gets the scale of the interpolator.  Could be the necessary value to point at the referenced
	 * node in the current pose. \return The scale of the interpolator.
	 */
	NIFLIB_API float GetScale() const;

	/*!
	 * Sets the scale of the interpolator.  Could be the necessary value to point at the referenced
	 * node in the current pose. \param[in] value The new scale for the interpolator.
	 */
	NIFLIB_API void SetScale(float value);

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	unsigned short unknownShort;
	/*! Refers to a Node to focus on. */
	NiNode* lookAt;
	/*! Target node name. */
	IndexString target;
	/*! Translate. */
	Vector3 translation;
	/*! Rotation. */
	Quaternion rotation;
	/*! Scale. */
	float scale;
	/*! Refers to NiPoint3Interpolator. */
	Ref<NiPoint3Interpolator> unknownLink1;
	/*! Refers to a NiFloatInterpolator. */
	Ref<NiFloatInterpolator> unknownLink2;
	/*! Refers to a NiFloatInterpolator. */
	Ref<NiFloatInterpolator> unknownLink3;

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
