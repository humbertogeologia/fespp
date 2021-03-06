﻿/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014)

cedric.robert@f2i-consulting.com

This software is a computer program whose purpose is to display data formatted using Energistics standards.

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "VtkAbstractObject.h"

//----------------------------------------------------------------------------
VtkAbstractObject::VtkAbstractObject( const std::string & fileName, const std::string & name, const std::string & uuid, const std::string & uuidParent, const int & idProc, const int & maxProc):
	fileName(fileName), name(name), uuid(uuid), uuidParent(uuidParent), idProc(idProc), maxProc(maxProc)
{
}

//----------------------------------------------------------------------------
VtkAbstractObject::~VtkAbstractObject()
{
	fileName = "";
	name = "";
	uuid = "";
	uuidParent = "";

	idProc = 0;
	maxProc = 0;
}

//----------------------------------------------------------------------------
std::string VtkAbstractObject::getFileName() const
{
	return fileName;
}

//----------------------------------------------------------------------------
std::string VtkAbstractObject::getName() const
{
	return name;
}

//----------------------------------------------------------------------------
std::string VtkAbstractObject::getUuid() const
{
	return uuid;
}

//----------------------------------------------------------------------------
std::string VtkAbstractObject::getParent() const
{
	return uuidParent;
}

//----------------------------------------------------------------------------
int VtkAbstractObject::getIdProc() const
{
	return idProc;
}

//----------------------------------------------------------------------------
int VtkAbstractObject::getMaxProc() const
{
	if(maxProc==0)
		return 1;
	else
		return maxProc;
}

//----------------------------------------------------------------------------
void VtkAbstractObject::setFileName(const std::string & newFileName) 
{
	fileName = newFileName;
}

//----------------------------------------------------------------------------
void VtkAbstractObject::setName(const std::string & newName) 
{
	name = newName;
}

//----------------------------------------------------------------------------
void VtkAbstractObject::setUuid(const std::string & newUuid) 
{
	uuid = newUuid;
}

//----------------------------------------------------------------------------
void VtkAbstractObject::setParent(const std::string & newUuidParent)
{
	uuidParent = newUuidParent;
}
