/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for licence. */

#include "../../include/gen/BoundingBox.h"
using namespace Niflib;

//Constructor
BoundingBox::BoundingBox() : unknownInt((uint)1) {};

//Copy Constructor
BoundingBox::BoundingBox( const BoundingBox & src ) {
	*this = src;
};

//Copy Operator
BoundingBox & BoundingBox::operator=( const BoundingBox & src ) {
	this->unknownInt = src.unknownInt;
	this->translation = src.translation;
	this->rotation = src.rotation;
	this->radius = src.radius;
	return *this;
};

//Destructor
BoundingBox::~BoundingBox() {};
