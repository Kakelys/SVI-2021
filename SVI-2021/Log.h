#pragma once
#include <fstream>
#include "Error.h"
#include "In.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "MFST.h"
namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, std::string c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	void WriteLexResult(LOG log, IT::IdTable, LT::LexTable);
	void WriteSintxResult(LOG log, MFST::Mfst);
	void Close(LOG log);
};
