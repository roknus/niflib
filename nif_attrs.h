/* Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.

   * Neither the name of the NIF File Format Library and Tools
     project nor the names of its contributors may be used to endorse
     or promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */

#ifndef _NIF_ATTRS_H_
#define _NIF_ATTRS_H_

#include <sstream>
#include <list>
#include "niflib.h"
#include "NIF_Blocks.h"
#include "NIF_IO.h"

#define endl "\r\n"

const char ATTRERR[] = "Attribute type Missmatch.";

class AAttr : public IAttr {
public:
	AAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : _name(name), _owner(owner), _first_ver(first_ver), _last_ver(last_ver) {}
	~AAttr() {}
	string GetType() const { return "void"; }
	string GetName() const { return _name; }
	//Getters
	int asInt() const { throw runtime_error(ATTRERR); }
	float asFloat() const { throw runtime_error(ATTRERR); }
	Float3 asFloat3() const { throw runtime_error(ATTRERR); }
	Matrix33 asMatrix33() const { throw runtime_error(ATTRERR); }
	blk_ref asLink() const { throw runtime_error(ATTRERR); }
	TextureSource asTextureSource() const { throw runtime_error(ATTRERR); }
	BoundingBox asBoundingBox() const { throw runtime_error(ATTRERR); }
	ConditionalInt asConditionalInt() const { throw runtime_error(ATTRERR); }
	Texture asTexture() const { throw runtime_error(ATTRERR); }
	list<blk_ref> asLinkList() const { throw runtime_error(ATTRERR); }
	//Setters
	void Set(int) { throw runtime_error(ATTRERR); }
	void Set(float) { throw runtime_error(ATTRERR); }
	void Set(Float3&) { throw runtime_error(ATTRERR); }
	void Set(string&) { throw runtime_error(ATTRERR); }
	void Set(Matrix33&) { throw runtime_error(ATTRERR); }
	void Set(blk_ref&) { throw runtime_error(ATTRERR); }
	void Set(TextureSource&) { throw runtime_error(ATTRERR); }
	void Set(BoundingBox&) { throw runtime_error(ATTRERR); }
	void Set(ConditionalInt&) { throw runtime_error(ATTRERR); }
	void Set(Texture&) { throw runtime_error(ATTRERR); }
	//Link functions
	bool HasLinks() { return false; }
	void AddLink( blk_ref block ) { cout << "AddLink" << endl; throw runtime_error(ATTRERR); }
	void AddLinks( list<blk_ref> new_links ) { cout << "AddLinkS" << endl; throw runtime_error(ATTRERR); }
	void ClearLinks() { cout << "ClearLinks" << endl; throw runtime_error(ATTRERR); }
	void RemoveLinks( blk_ref block ) { cout << "RemoveLinks" << endl; throw runtime_error(ATTRERR); }
	blk_ref FindLink( string block_type ) { cout << "FindLink" << endl; throw runtime_error(ATTRERR); }
	//Read/WriteFunctions
	void Read( ifstream& in, unsigned int version ) {
		if ( version >= _first_ver && version <= _last_ver ) {
			this->ReadAttr( in, version );
		}
	}
	void Write( ofstream& out, unsigned int version ) {
		if ( version >= _first_ver && version <= _last_ver ) {
			this->WriteAttr( out, version );
		}
	}
protected:
	//Internal Read/Write Functions
	virtual void ReadAttr( ifstream& in, unsigned int version ) = 0;
	virtual void WriteAttr( ofstream& out, unsigned int version ) = 0;

	string _name;
	IBlock * _owner;
	unsigned int _first_ver, _last_ver;
};

class lnk_ref : public blk_ref {
public:
	lnk_ref ( IBlock * owner) : _owner(owner) { /*cout << "Constructor " <<  endl;*/ InitLink(); }
	lnk_ref( IBlock * owner, int index ) : _owner(owner), blk_ref(index) { /*cout << "Constructor "  << endl;*/ InitLink(); }
	lnk_ref( IBlock * owner, blk_ref block ) : _owner(owner), blk_ref(block) { /*cout << "Constructor " << endl;*/ InitLink(); }

	//Copy Constructors
	lnk_ref( const lnk_ref & rh ) {
		/*cout << "Copy constructor " << endl;*/
		//Kill previous link
		KillLink();
		_owner = rh._owner;
		blk_ref::operator=(rh);
		//Set New Link
		InitLink();
	}
	//Destructor
	~lnk_ref() { /*cout << "Destructor " << endl;*/ KillLink(); /*cin.get();*/}
	//Assignment Operator
	lnk_ref & operator=(const blk_ref & rh ) { 
		if ( blk_ref(*this)!= rh ) {
			//Kill previous link
			KillLink();
			blk_ref::operator=(rh);
			//Set New Link
			InitLink();
		}

		return *this;
	}
	void set_block( IBlock * block ) {
		/*cout << "set_block " << endl;*/
		//Use assignment operator code
		operator=( blk_ref(block) );
	}
	void set_index( int index ) { 
		/*cout << "set_index " << endl;*/
		//Use assigntment operator code
		operator=( blk_ref(index) );
	}
	IBlock * owner() const {
		if ( _owner == NULL ) {
			throw runtime_error("Link reference owner is NULL.");
		} else {
			return _owner;
		}
	}

private:
	IBlock * _owner;
	void InitLink() {
		//cout << "+ Reference " << this << endl;
		//Add parent at new link site
		if ( _block != NULL ) {
			//Get internal interface
			IBlockInternal * bk_intl = (IBlockInternal*)_block->QueryInterface( BlockInternal );
			if ( bk_intl != NULL ) {
				bk_intl->AddParent( blk_ref(_owner) );
			}
		}
	}
	void KillLink() {
		//cout << "- Reference " << this << endl;
		//Remove cross-reference at previous location
		if ( _block != NULL ) {
			//Get internal interface
			IBlockInternal * bk_intl = (IBlockInternal*)_block->QueryInterface( BlockInternal );
			if ( bk_intl != NULL ) {
				bk_intl->RemoveParent( _owner );
			}
		}
	}
	lnk_ref( const blk_ref & rh ); // Intentionally Undefined
};

class IntAttr : public AAttr {
public:
	IntAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~IntAttr() {}
	string GetType() const { return "int"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << data;

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

class ShortAttr : public AAttr {
public:
	ShortAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~ShortAttr() {}
	string GetType() const { return "short"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUShort( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUShort( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << data;

		return out.str();
	}
	int asInt() const { return int(data); }
	void Set(int n ) { data = short(n); }
private:
	short data;
};

class ByteAttr : public AAttr {
public:
	ByteAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~ByteAttr() {}
	string GetType() const { return "byte"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadByte( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteByte( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << int(data);

		return out.str();
	}
	int asInt() const { return int(data); }
	void Set(int n ) { data = char(n); }
private:
	char data;
};

class FloatAttr : public AAttr {
public:
	FloatAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0.0f) {}
	~FloatAttr() {}
	string GetType() const { return "float"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadFloat( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteFloat( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << data;

		return out.str();
	}
	float asFloat() const { return data; }
	void Set(float n ) { data = n; }
private:
	float data;
};

class Float3Attr : public AAttr {
public:
	Float3Attr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver) : AAttr(name, owner, first_ver, last_ver) {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
	}
	~Float3Attr() {}
	string GetType() const { return "float3"; }
	void ReadAttr( ifstream& in, unsigned int version ) { 
		data[0] = ReadFloat( in );
		data[1] = ReadFloat( in );
		data[2] = ReadFloat( in );
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteFloat( data[0], out );
		WriteFloat( data[1], out );
		WriteFloat( data[2], out );
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << "(" << setw(5) << data[0] << ", " << setw(5) << data[1] << ", " << setw(5) << data[2] << " )";
		
		return out.str();
	}
	Float3 asFloat3() const { return data; }
	void Set(Float3& n) { data = n; }
	
	//vector<float> asFloatList() const {
	//	vector<float> list(3);
	//	list[0] = data[0];	list[1] = data[1];	list[2] = data[2];
	//	return list;
	//}
	//void Set(vector<float> n ) {
	//	if ( n.size() != 3)
	//		throw runtime_error("List size must equal 3");
	//	data[0] = n[0];	data[1] = n[1];	data[2] = n[2];
	//}
private:
	Float3 data;
};

class StringAttr : public AAttr {
public:
	StringAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ) {}
	~StringAttr() {}
	string GetType() const { return "string"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadString( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteString( data, out ); }
	string asString() const { return data; }
	void Set(string & n) { data = n; }
private:
	string data;
};

class LinkAttr : public AAttr {
public:
	LinkAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), link( owner ) {}
	~LinkAttr() {}
	string GetType() const { return "link"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		////Remove all links beloning to this attribute
		//_owner->RemoveAttrLinks(this);

		////Add a new link with read in link
		//blk_link l;
		//l.attr = this;
		//l.block = ReadUInt( in );
		//_owner->AddLink(l);

		//Set block index only
		link.set_index( ReadUInt( in ) );
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteUInt( link.get_index(), out );
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << link;

		return out.str();
	}
	bool HasLinks() { return true; }
	list<blk_ref> asLinkList() const { 
		list<blk_ref> out;

		out.push_back( blk_ref(link) );

		return out; 
	}
	void ClearLinks() { link = blk_ref(-1); }
	void AddLinks( list<blk_ref> new_links ) {
		//Just take the first one
		link = *(new_links.begin());
	}

	blk_ref asLink() const { return blk_ref(link); }
	void Set( blk_ref & n ) { link = n; }
private:
	lnk_ref link;
};

class FlagsAttr : public AAttr {
public:
	FlagsAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~FlagsAttr() {}
	string GetType() const { return "flags"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUShort( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUShort( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << data;
		short t = data;
		for (uint i = 0; i < 16; ++i) {
			if((t & 1) !=0) {
				out << endl << "   Bit " << i + 1 << " set ";
			}
			t >>= 1;
		}

		return out.str();
	}
	int asInt() const { return int(data); }
	void Set(int n ) { data = short(n); }
private:
	short data;
};

class MatrixAttr : public AAttr {
public:
	MatrixAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ) {
		data[0][0] = 1.0f;	data[0][1] = 0.0f;	data[0][2] = 0.0f;
		data[1][0] = 0.0f;	data[1][1] = 1.0f;	data[1][2] = 0.0f;
		data[2][0] = 0.0f;	data[2][1] = 0.0f;	data[2][2] = 1.0f;
	}
	~MatrixAttr() {}
	string GetType() const { return "matrix33"; }
	void ReadAttr( ifstream& in, unsigned int version ) { 
		for (int c = 0; c < 3; ++c) {
			for (int r = 0; r < 3; ++r) {
				data[r][c] = ReadFloat( in );
			}
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		for (int c = 0; c < 3; ++c) {
			for (int r = 0; r < 3; ++r) {
				WriteFloat( data[r][c], out );
			}
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << endl
			<< "   |" << setw(6) << data[0][0] << "," << setw(6) << data[0][1] << "," << setw(6) << data[0][2] << " |" << endl
			<< "   |" << setw(6) << data[1][0] << "," << setw(6) << data[1][1] << "," << setw(6) << data[1][2] << " |" << endl
			<< "   |" << setw(6) << data[2][0] << "," << setw(6) << data[2][1] << "," << setw(6) << data[2][2] << " |";
		
		return out.str();
	}
	Matrix33 asMatrix33() const {
		return data;
		//for (int c = 0; c < 3; ++c) {
		//	for (int r = 0; r < 3; ++r) {
		//		out[r][c] = data[r][c];
		//	}
		//}
	}
	void Set( Matrix33 & n ) {
		for (int c = 0; c < 3; ++c) {
			for (int r = 0; r < 3; ++r) {
				data[r][c] = n[r][c];
			}
		}
	}

	//vector<float> asFloatList() const {
	//	vector<float> list(9);
	//	list[0] = data[0][0];	list[1] = data[0][1];	list[2] = data[0][2];
	//	list[0] = data[1][0];	list[1] = data[1][1];	list[2] = data[1][2];
	//	list[0] = data[2][0];	list[1] = data[2][1];	list[2] = data[2][2];
	//	return list;
	//}
	//void Set(vector<float> n ) {
	//	if ( n.size() != 9)
	//		throw runtime_error("List size must equal 9");

	//	data[0][0] = n[0];	data[0][1] = n[1];	data[0][2] = n[2];
	//	data[1][0] = n[0];	data[1][1] = n[1];	data[1][2] = n[2];
	//	data[2][0] = n[0];	data[2][1] = n[1];	data[2][2] = n[2];
	//}
private:
	Matrix33 data;
};

class BoneAttr : public AAttr {
public:
	BoneAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr(name, owner, first_ver, last_ver) {}
	~BoneAttr() {}
	void ReadAttr( ifstream& in, unsigned int version ) {
		ISkinInstInternal * data = (ISkinInstInternal*)_owner->QueryInterface( SkinInstInternal );
		if ( data != NULL ) {
			data->ReadBoneList( in );
		} else {
			throw runtime_error ("Attempted to use a bone list attribute on a block that doesn't support it.");
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		ISkinInstInternal * data = (ISkinInstInternal*)_owner->QueryInterface( SkinInstInternal );
		blk_ref data_blk = _owner->GetAttr("Data")->asLink();
		if ( data_blk.is_null() == false )  {
			//Get Bone data from data block
			ISkinData * data = (ISkinData*)data_blk->QueryInterface( ID_SKIN_DATA );
			vector<blk_ref> bones = data->GetBones();

			//Write bone indices to file
			WriteUInt( uint(bones.size()), out );
			for (uint i = 0; i < bones.size(); ++i ) {
				WriteUInt( bones[i].get_index(), out );
			}
		}
		else {
			//No data, so write zero for no bones
			WriteUInt( 0, out );
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		//See if there is a data block
		blk_ref data_blk = _owner->GetAttr("Data")->asLink();
		if ( data_blk.is_null() == false )  {
			//Get Bone data from data block
			ISkinData * data = (ISkinData*)data_blk->QueryInterface( ID_SKIN_DATA );
			vector<blk_ref> bones = data->GetBones();

			//Print Bone List
			for (uint i = 0; i < bones.size(); ++i ) {
				out << endl << "   " << bones[i];
			}
			if ( bones.size() == 0 ) {
				out << "None";
			}
		}
		else {
			//No data, so write none
			out << "None";
		}

		return out.str();
	}
};

typedef list<lnk_ref> LinkSetList;
typedef LinkSetList::iterator LinkSetIt;

class LinkGroupAttr : public AAttr {
public:
	LinkGroupAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ) {}
	~LinkGroupAttr() {}
	string GetType() const { return "linkgroup"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		int len = ReadUInt( in );
		//cout << "Link Group Size:  " << len << endl;

		if ( len > 1000 ) {
			throw runtime_error("Unlikley number of links found. (>1000)");
		}

		for (int i = 0; i < len; ++i ) {
			int index = ReadUInt( in );
			if (index != -1 )
				AddLink( blk_ref( index ) );
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		//Write the number of links
		WriteUInt( uint(links.size()), out );
		//cout << "Link Group Size:  " << uint(links.size()) << endl;

		if ( links.size() > 1000 ) {
			throw runtime_error("You probably shouldn't write more than 1000 links");
		}

		//Write the block indices
		for (LinkSetIt it = links.begin(); it != links.end(); ++it ) {
			WriteUInt( it->get_index(), out );
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		for (LinkSetList::const_iterator it = links.begin(); it != links.end(); ++it ) {
			out << endl << "   " << *it;
		}
		if (links.size() == 0 ) {
			out << "None";
		}

		return out.str();
	}

	bool HasLinks() { return true; }

	list<blk_ref> asLinkList() const { 
		list<blk_ref> out;

		for (LinkSetList::const_iterator it = links.begin(); it != links.end(); ++it ) {
			out.push_back( blk_ref(*it) );
		}

		return out; 
	}

	void AddLink( blk_ref block ) {
		links.push_back( lnk_ref(_owner, block) );
	}

	void AddLinks( list<blk_ref> new_links ) {
		//Add new list of links
		list<blk_ref>::iterator it;
		for (it = new_links.begin(); it != new_links.end(); ++it ) {
			lnk_ref l(_owner, *it );
			try {
				links.push_back( l );
			}
			catch( exception & e ) {
				cout << "Error:  " << e.what() << endl;
			}
		}
	}

	blk_ref FindLink( string block_type ) {
		//Find the first link with the requested block type
		for (LinkSetList::const_iterator it = links.begin(); it != links.end(); ++it ) {
			if ( (*it)->GetBlockType() == block_type )
				return blk_ref(*it);
		}

		//No block was found, so return a null one
		return blk_ref(-1);
	}

	void ClearLinks() { links.clear(); }

	void RemoveLinks( blk_ref block ) {
		//Remove all links that match this block
		links.remove( lnk_ref( _owner, block ) );
	}
private:
	LinkSetList links;
};

class BBoxAttr : public AAttr {
public:
	BBoxAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ) {
		data.isUsed = false;
		
		data.unknownInt = 0;

		data.translation.x = 0.0f;	data.translation.y = 0.0f;	data.translation.z = 0.0f;

		data.rotation[0][0] = 1.0f;	data.rotation[0][1] = 0.0f;	data.rotation[0][2] = 0.0f;
		data.rotation[1][0] = 0.0f;	data.rotation[1][1] = 1.0f;	data.rotation[1][2] = 0.0f;
		data.rotation[2][0] = 0.0f;	data.rotation[2][1] = 0.0f;	data.rotation[2][2] = 1.0f;

		data.radius.x = 0.0f;
		data.radius.y = 0.0f;
		data.radius.z = 0.0f;
	}
	~BBoxAttr() {}
	string GetType() const { return "bbox"; }
	void ReadAttr( ifstream& in, unsigned int version ) { 
		data.isUsed = ReadBool( in, version );
		if ( data.isUsed ){
			data.unknownInt = ReadUInt( in );
			data.translation.x = ReadFloat( in );
			data.translation.y = ReadFloat( in );
			data.translation.z = ReadFloat( in );
			for (int c = 0; c < 3; ++c) {
				for (int r = 0; r < 3; ++r) {
					data.rotation[r][c] = ReadFloat( in );
				}
			}
			data.radius.x = ReadFloat( in );
			data.radius.y = ReadFloat( in );
			data.radius.z = ReadFloat( in );
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteBool( data.isUsed, out, version );
		if ( data.isUsed ){
			WriteUInt( data.unknownInt, out );
			WriteFloat( data.translation.x, out );
			WriteFloat( data.translation.y, out );
			WriteFloat( data.translation.z, out );
			for (int c = 0; c < 3; ++c) {
				for (int r = 0; r < 3; ++r) {
					WriteFloat(data.rotation[r][c], out );
				}
			}
			WriteFloat( data.radius.x, out );
			WriteFloat( data.radius.y, out );
			WriteFloat( data.radius.z, out );
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		if ( data.isUsed ) {
			out << endl
				<< "   Position:  " << "(" << setw(5) << data.translation.x << ", " << setw(5) << data.translation.y << ", " << setw(5) << data.translation.z << " )" << endl
				<< "   Rotation:"  << endl
				<< "      |" << setw(5) << data.rotation[0][0] << ", " << setw(5) << data.rotation[0][1] << ", " << setw(5) << data.rotation[0][2] << " |" << endl
				<< "      |" << setw(5) << data.rotation[1][0] << ", " << setw(5) << data.rotation[1][1] << ", " << setw(5) << data.rotation[1][2] << " |" << endl
				<< "      |" << setw(5) << data.rotation[2][0] << ", " << setw(5) << data.rotation[2][1] << ", " << setw(5) << data.rotation[2][2] << " |" << endl
				<< "   X Radius:  " << data.radius.x << endl
				<< "   Y Radius:  " << data.radius.y << endl
				<< "   Z Radius:  " << data.radius.z;
		} 
		else {
			out << "None";
		}

		return out.str();
	}
	BoundingBox asBoundingBox() const { return data; }
	void Set(BoundingBox& n ) { data = n; }

private:
	BoundingBox data;
};

class CIntAttr : public AAttr {
public:
	CIntAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ) {
		data.isUsed = false;
		data.unknownInt = 0;
	}
	~CIntAttr() {}
	string GetType() const { return "condint"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		data.isUsed = ReadBool( in, version );
		if (data.isUsed) {
			data.unknownInt = ReadUInt( in );
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) { 
		WriteBool( data.isUsed, out, version );
		if (data.isUsed) {
			WriteUInt( data.unknownInt, out );
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		if (data.isUsed) {
			out << data.unknownInt;
		}
		else {
			out << "None";
		}

		return out.str();
	}
	ConditionalInt asConditionalInt() const { return data; }
	void Set(ConditionalInt & n ) {
		data.isUsed = n.isUsed;
		data.unknownInt = n.unknownInt;
	}
private:
	ConditionalInt data;
};

class VertModeAttr : public AAttr {
public:
	VertModeAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~VertModeAttr() {}
	string GetType() const { return "vertmode"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "Source Ingore";
				break;
			case 1:
				out << "Source Emmisive";
				break;
			case 2:
				out << "Source Amb Diff";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

class LightModeAttr : public AAttr {
public:
	LightModeAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~LightModeAttr() {}
	string GetType() const { return "lightmode"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "Emmisive";
				break;
			case 1:
				out << "Emmisive Amb Diff";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};



    //int vertex     - vertex mode:
    //                 0 - source ignore
    //                 1 - source emmisive
    //                 2 - source amb diff

    //int light      - lighting mode:
    //                 0 - lighting emmisive
    //  1 - lighting emmisive amb diff

class TextureAttr : public LinkAttr {
public:
	TextureAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver, bool isBumpMap = false ) : LinkAttr(name, owner, first_ver, last_ver),  _isBumpMap(isBumpMap) {
		memset( &data, 0, sizeof(data) );
	}
	~TextureAttr() {}
	string GetType() const { return "texture"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		data.isUsed = ReadBool( in, version );
		if ( data.isUsed ) {	
			//Read in link for TextureSource
			LinkAttr::ReadAttr( in, version );

			data.clampMode = TexClampMode( ReadUInt( in ) );
			data.filterMode = TexFilterMode( ReadUInt( in ) );
			data.textureSet = ReadUInt( in );
			data.PS2_L = ReadUShort( in );
			data.PS2_K = ReadUShort( in );

			//unknownShort exists up to version 4.1.0.12
			if ( version <= VER_4_1_0_12) {
				data.unknownShort = ReadUShort( in );
			}

			if ( _isBumpMap ) {
				data.bmLumaScale = ReadFloat( in );
				data.bmLumaOffset = ReadFloat( in );
				data.bmMatrix[0][0] = ReadFloat( in );
				data.bmMatrix[1][0] = ReadFloat( in );
				data.bmMatrix[0][1] = ReadFloat( in );
				data.bmMatrix[1][1] = ReadFloat( in );
			}
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteBool( data.isUsed, out, version );
		if ( data.isUsed ) {
			//Write link
			LinkAttr::WriteAttr( out, version );

			WriteUInt( data.clampMode, out );
			WriteUInt( data.filterMode, out );
			WriteUInt( data.textureSet, out );
			WriteUShort( data.PS2_L, out );
			WriteUShort( data.PS2_K, out );
			//unknownShort exists up to version 4.1.0.12
			if ( version <= VER_4_1_0_12 ) {
				WriteUShort( data.unknownShort, out );
			}
			if ( _isBumpMap ) {
				WriteFloat( data.bmLumaScale, out );
				WriteFloat( data.bmLumaOffset, out );
				WriteFloat( data.bmMatrix[0][0], out );
				WriteFloat( data.bmMatrix[1][0], out );
				WriteFloat( data.bmMatrix[0][1], out );
				WriteFloat( data.bmMatrix[1][1], out );
			}
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		if ( data.isUsed ) {
			out << endl
				<< "   Source:  " << asLink() << endl
				<< "   Clamp Mode:  ";
			switch ( data.clampMode ) {
				case CLAMP_S_CLAMP_T:
					out << "Clamp S Clamp T";
					break;
				case CLAMP_S_WRAP_T:
					out << "Clamp S Wrap T";
					break;
				case WRAP_S_CLAMP_T:
					out << "Wrap S Clamp T";
					break;
				case WRAP_S_WRAP_T:
					out << "Wrap S Wrap T";
					break;
				default:
					out << "!Invalid Value! - " << data.clampMode;
				break;
			}
			out << endl
				<< "   Filter Mode:  ";
			switch ( data.filterMode ) {
				case FILTER_NEAREST:
					out << "Nearest";
					break;
				case FILTER_BILERP:
					out << "Biliner";
					break;
				case FILTER_TRILERP:
					out << "Trilinear";
					break;
				case FILTER_NEAREST_MIPNEAREST:
					out << "Nearest, Mip Nearest";
					break;
				case FILTER_NEAREST_MIPLERP:
					out << "Nearest, Mip Linear";
					break;
				case FILTER_BILERP_MIPNEAREST:
					out << "Bilinear, Mip Nearest";
					break;
				default:
					out << "!Invalid Value! - " << data.clampMode;
				break;
			}
			
			out << endl
				<< "   Texture Set:  " << data.textureSet << endl
				<< "   PS2 L Setting:  " << data.PS2_L << endl
				<< "   PS2 K Setting:  " << data.PS2_K << endl
				<< "   Unknown Short:  " << data.unknownShort;
			if ( _isBumpMap ) {
				out << endl
					<< "   BumpMap Info:" << endl
					<< "      Luma Offset:  " << data.bmLumaOffset << endl
					<< "      Luma Scale:  " << data.bmLumaScale << endl
					<< "      Matrix:" << endl
					<< "         |" << setw(6) << data.bmMatrix[0][0] << "," << setw(6) << data.bmMatrix[0][1] << " |" << endl
					<< "         |" << setw(6) << data.bmMatrix[1][0] << "," << setw(6) << data.bmMatrix[1][1] << " |" << endl;
			}
		} else {
			out << "None";
		}

		return out.str();
	}
	Texture asTexture() const { return data; }
	void Set( Texture &n ) {
		data.isUsed = n.isUsed;
		data.clampMode = n.clampMode;
		data.filterMode = n.filterMode;
		data.textureSet = n.textureSet;
		data.PS2_L = n.PS2_L;
		data.PS2_K = n.PS2_K;
		data.unknownShort = n.unknownShort;
		data.bmLumaOffset = n.bmLumaOffset;
		data.bmLumaScale = n.bmLumaScale;
		data.bmMatrix[0][0] = n.bmMatrix[0][0];
		data.bmMatrix[0][1] = n.bmMatrix[0][1];
		data.bmMatrix[1][0] = n.bmMatrix[1][0];
		data.bmMatrix[1][1] = n.bmMatrix[1][1];
	}
private:
	Texture data;
	IBlock * _owner;
	bool _isBumpMap;
};

    //int isPresent
    //if(isPresent != 0)
    //    int source          - index of NiSourceTexture record
    //    int clamp           - clamp mode:
    //                          0 - clamp clamp
    //                          1 - clamp wrap
    //                          2 - wrap clamp
    //                          3 - wrap wrap
    //    int set(?)
    //    int unknown

    //    short ps2_L         = 0
    //    short ps2_K         = -2 or -75
    //    short unknown2      = 0 or 0x0101 (=257)

class ApplyModeAttr : public AAttr {
public:
	ApplyModeAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~ApplyModeAttr() {}
	string GetType() const { return "applymode"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "Replace";
				break;
			case 1:
				out << "Decal";
				break;
			case 2:
				out << "Modulate";
				break;
			case 3:
				out << "Hilight";
				break;
			case 4:
				out << "Hilight2";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}	
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

    //int apply         - apply mode:
    //                    0 - replace
    //                    1 - decal
    //                    2 - modulate
    //                    3 - hilight
    //                    4 - hilight2

class TexSourceAttr : public LinkAttr {
public:
	TexSourceAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : LinkAttr(name, owner, first_ver, last_ver) {}
	~TexSourceAttr() {
		memset(&data, 0, sizeof(data) );
	}
	string GetType() const { return "texsource"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		data.useExternal = ( ReadByte( in ) != 0 );
		if ( data.useExternal ) {
			data.fileName = ReadString( in );
		} else {
			data.unknownByte = ReadByte( in );

			//Read link for Pixel Data
			LinkAttr::ReadAttr( in, version );
		}
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteByte( byte(data.useExternal), out );
		if ( data.useExternal ) {
			WriteString( data.fileName, out );
		} else {
			WriteByte ( data.unknownByte, out );
			//Write link for Pixel Data
			LinkAttr::WriteAttr( out, version );
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << endl;
		if ( data.useExternal ) {
			out << "   Location:  External" << endl
				<< "   File Name:  " << data.fileName;
		} else {
			out << "   Location:  Internal" << endl
				<< "   Unknown Byte:  " << int(data.unknownByte) << endl
				<< "   Pixel Data:  " << asLink();
		}

		return out.str();
	}
	TextureSource asTextureSource() const { return data; }
	void Set( TextureSource &n ) {
		data.useExternal = n.useExternal;
		data.unknownByte = n.unknownByte;
		data.fileName = n.fileName;
	}
private:
	TextureSource data;
	IBlock * _owner;
};

class PixelLayoutAttr : public AAttr {
public:
	PixelLayoutAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~PixelLayoutAttr() {}
	string GetType() const { return "pixellayout"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "Palettised";
				break;
			case 1:
				out << "16-bit High Color";
				break;
			case 2:
				out << "32-bit True Color";
				break;
			case 3:
				out << "Compressed";
				break;
			case 4:
				out << "Bump Map";
				break;
			case 5:
				out << "Default";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

//typedef enum {
//   PALETTISED = 0,
//   HIGH_COLOR_16 = 1,
//   TRUE_COLOR_32 = 2,
//   COMPRESSED = 3,
//   BUMPMAP = 4,
//   PIX_DEFAULT = 5
//} SMB_PixelLayout;

class MipMapFormatAttr : public AAttr {
public:
	MipMapFormatAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~MipMapFormatAttr() {}
	string GetType() const { return "mipmapformat"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "No";
				break;
			case 1:
				out << "Yes";
				break;
			case 2:
				out << "Default";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

//typedef enum {
//   MIPMAP_NO = 0,
//   MIPMAP_YES = 1,
//   MIPMAP_MIP_DEFAULT = 2,
//} SMB_MipMapFormat;

class AlphaFormatAttr : public AAttr {
public:
	AlphaFormatAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr( name, owner, first_ver, last_ver ), data(0) {}
	~AlphaFormatAttr() {}
	string GetType() const { return "alphaformat"; }
	void ReadAttr( ifstream& in, unsigned int version ) { data = ReadUInt( in ); }
	void WriteAttr( ofstream& out, unsigned int version ) { WriteUInt( data, out ); }
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		switch ( data ) {
			case 0:
				out << "None";
				break;
			case 1:
				out << "Binary";
				break;
			case 2:
				out << "Smooth";
				break;
			case 3:
				out << "Default";
				break;
			default:
				out << "!Invalid Value! - " << data;
				break;
		}

		return out.str();
	}
	int asInt() const { return data; }
	void Set(int n ) { data = n; }
private:
	int data;
};

class NodeAncestorAttr : public AAttr {
public:
	NodeAncestorAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr(name, owner, first_ver, last_ver) {}
	~NodeAncestorAttr() {}
	string GetType() const { return "nodeancestor"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		ReadUInt(in);
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteUInt( _owner->GetParent()->GetBlockNum(), out );
	}
	blk_ref FindNodeAncestor() const {
		//Find first ancestor that is a node
		blk_ref block(_owner);
		blk_ref par;
		while ( true ) {
			//Get parent
			par = block->GetParent();

			//If parent is null, we're done - there are no node ancestors so return a null reference
			if (par.is_null() == true)
				return blk_ref(-1);

			//If parent is a node, return it
			if ( QueryNode(par) != NULL ) {
				return par;
			}

			//We didn't find a node this time, set block to par and try again
			block = par;
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << FindNodeAncestor();

		return out.str();
	}
	blk_ref asLink() const { return FindNodeAncestor(); }
};

class SkeletonRootAttr : public AAttr {
public:
	SkeletonRootAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr(name, owner, first_ver, last_ver) {}
	~SkeletonRootAttr() {}
	string GetType() const { return "skeletonroot"; }
	void ReadAttr( ifstream& in, unsigned int version ) {
		original_root = ReadUInt( in );  //Read data but do nothing with it
	}
	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteUInt( FindRoot().get_index(), out );
	}
	blk_ref FindRoot() const {
		//Find Skeleton Root - first node in ancestry that has 'not a skin influence' flag set
		blk_ref block(_owner);
		blk_ref par;
		int flags;
		while ( true ) {
			//Get parent
			par = block->GetParent();

			//If parent is null, we're done - every node is an influence or there are no nodes
			//Probably shouldn't happen
			if (par.is_null() == true) {
				return block;

			}

			//If parent is a node and its 'not a skin influence' flag is set, it is the root for this skeleton
			if ( par->QueryInterface(ID_NODE) != NULL ) {
				flags = par->GetAttr("Flags")->asInt();

				if ( (flags & 8) != 0 ) {
					return par;
				}
			}

			//We didn't find the root this time, set block to par and try again
			block = par;
		}
	}
	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		blk_ref root;
		root = FindRoot();
		out << root;

		return out.str();
	}
	blk_ref asLink() const { return FindRoot(); }
private:
	int original_root;
};

class ParticleGroupAttr : public AAttr {
public:
	ParticleGroupAttr( string name, IBlock * owner, unsigned int first_ver, unsigned int last_ver ) : AAttr(name, owner, first_ver, last_ver) {}
	~ParticleGroupAttr() {}
	string GetType() const { return "particlegroup"; }

	void ReadAttr( ifstream& in, unsigned int version ) {
		num_particles = ReadUShort( in );
		num_valid = ReadUShort( in );

		particles.resize(num_particles);
		for ( int i = 0; i < num_particles; ++i ) {
			for (int c = 0; c < 3; ++c) {
				for (int r = 0; r < 3; ++r) {
					particles[i].unk_matrix[r][c] = ReadFloat( in );
				}
			}
			particles[i].unk_short = ReadUShort( in );
			particles[i].vert_id = ReadUShort( in );
		}
	}

	void WriteAttr( ofstream& out, unsigned int version ) {
		WriteUShort( num_particles, out );
		WriteUShort( num_valid, out );

		for ( int i = 0; i < num_particles; ++i ) {
			for (int c = 0; c < 3; ++c) {
				for (int r = 0; r < 3; ++r) {
					WriteFloat( particles[i].unk_matrix[r][c], out );
				}
			}

			WriteUShort( particles[i].unk_short, out );
			WriteUShort( particles[i].vert_id, out );
		}
	}

	string asString() const {
		stringstream out;
		out.setf(ios::fixed, ios::floatfield);
		out << setprecision(1);

		out << "Num Particles:  " << num_particles << endl
			<< "Num Valid:  " << num_valid << endl
			<< "Particles:" << endl;

		for ( int i = 0; i < num_particles; ++i ) {
			out << "   Particle " << i << ":" << endl;
			const Matrix33 & m = particles[i].unk_matrix;
			out << "      |" << setw(6) << m[0][0] << "," << setw(6) << m[0][1] << "," << setw(6) << m[0][2] << " |" << endl
				<< "      |" << setw(6) << m[1][0] << "," << setw(6) << m[1][1] << "," << setw(6) << m[1][2] << " |" << endl
				<< "      |" << setw(6) << m[2][0] << "," << setw(6) << m[2][1] << "," << setw(6) << m[2][2] << " |" << endl;

			out << "      Unknown Short:  " << particles[i].unk_short << endl
				<< "      Vertex ID:  " << particles[i].vert_id << endl;
		}
		return out.str();
	}
	
private:
	struct Particle {
		Matrix33 unk_matrix;
		short unk_short;
		short vert_id;
	};
	short num_particles;
	short num_valid;
	vector<Particle> particles;
};


#endif
