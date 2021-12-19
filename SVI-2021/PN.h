#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Log.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"


namespace PN
{




	void PolishNT(LT::LexTable lexems, IT::IdTable idenfs);

	int prior(std::string line, int pos);

	int priorNT(LT::LexTable lexems, int i);
};