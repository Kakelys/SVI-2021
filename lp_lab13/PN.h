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


	void Polish(wchar_t infile[]);

	void PolishNT(wchar_t infile[], LT::LexTable lexems, IT::IdTable idenfs);

	int prior(std::string line, int pos);

	int priorNT(LT::LexTable lexems, int i);
};