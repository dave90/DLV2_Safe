/*
 * Simplifier.cpp
 *
 *  Created on: 23/mar/2015
 *      Author: Zeiven
 */


#include "Simplifier.h"
#include "ProgramGrounder.h"
namespace DLV2 {
namespace grounder {

	void Simplifier::simplifier(Rule* currentRule,const vector<vector<unsigned>>& tableSearcher)
	{
		unsigned atom_counter=0;
		unsigned index_body_atom=0;
		Atom *searchAtom=0;
		for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();++atom,++index_body_atom)
		{

			PredicateExtension* predicateExt=ProgramGrounder::predicateExtTable->getPredicateExt(index_body_atom);
			searchAtom=predicateExt->getGenericAtom((*atom));
			if(searchAtom==nullptr_t) //if atom isn't in table add in table
			{
				GenericAtom* genericBodyAtom=new GenericAtom;
				genericBodyAtom->setTerms((*atom)->getTerms());
				genericBodyAtom->setFact((*atom)->isFact());
				for(unsigned i=0;i<tableSearcher[atom_counter].size();++i)
								predicateExt->addGenericAtom(tableSearcher[atom_counter][i],genericBodyAtom);
			}


		}
	}
}
}

