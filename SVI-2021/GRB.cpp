#include "GRB.h"
#include "stdafx.h"
#define GRB_ERRORS_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		13,
		Rule(NS('S'), GRB_ERRORS_SERIES + 0,//???????? ???????????
			3,
			Rule::Chain(2, TS('m'), NS('B')),
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('P'), TS(';'), NS('S')),//??????? ???????
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('P'), NS('B'), NS('S'))//???????
		),
		Rule(NS('P'), GRB_ERRORS_SERIES + 0,//????????? ?????????? ???????
			2,
			Rule::Chain(3, TS('('), NS('F'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(NS('B'), GRB_ERRORS_SERIES + 0,//???? ???????
			2,
			Rule::Chain(6, TS('{'), NS('N'), TS('r'), NS('E'),TS(';'), TS('}') ),
			Rule::Chain(5, TS('{'), TS('r'), NS('E'), TS(';'), TS('}'))
		),
		Rule(NS('N'), GRB_ERRORS_SERIES + 1,
			14,
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),			
			Rule::Chain(3, TS('p'), NS('V'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(2, TS('z'),  NS('C')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('V'), TS(';'), NS('N')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';'))
		),
		Rule(NS('V'), GRB_ERRORS_SERIES + 1,
			4,
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),
		Rule(NS('E'), GRB_ERRORS_SERIES + 2,
			10,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M'))
		),
		Rule(NS('M'), GRB_ERRORS_SERIES + 3,
			4,
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E'))
		),
		Rule(NS('F'), GRB_ERRORS_SERIES + 4,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERRORS_SERIES + 5,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('C'), GRB_ERRORS_SERIES + 6,
			2,
			Rule::Chain(6, TS('('), NS('I'), TS('x'), NS('I'), TS(')'), NS('L')),
			Rule::Chain(8, TS('('), NS('I'), TS('x'), NS('I'), TS(')'), NS('K'), TS('c'), NS('L'))
		),
		Rule(NS('L'), GRB_ERRORS_SERIES + 6,//???? ???????? ???????????
			4,
			Rule::Chain(2, TS('{'), TS('}')),
			Rule::Chain(3, TS('{'), TS('}'), NS('N')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(NS('K'), GRB_ERRORS_SERIES + 6,//???? ???????? ???????????(?? ??? else)
			2,
			Rule::Chain(2, TS('{'), TS('}')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))
		),
		Rule(NS('I'), GRB_ERRORS_SERIES + 6,
			4,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')'))
		)
	);








	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) chains[i] = p[i];
	};
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++) rules[i] = p[i];
	};

	Greibach getGreibach() { return greibach; };

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	};

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	};
	
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j: -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};

};