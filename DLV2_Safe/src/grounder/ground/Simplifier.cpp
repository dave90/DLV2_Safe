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
		unsigned size_body=currentRule->getSizeBody();
		unsigned index_body_atom=0;
		unsigned index_head_atom=0;
		Atom *searchAtom=0;
		for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();++atom,++index_body_atom)
		{

			PredicateExtension* predicateExt=ProgramGrounder::predicateExtTable->getPredicateExt(index_body_atom);
			searchAtom=predicateExt->getGenericAtom((*atom));
			if(searchAtom!=nullptr_t) //if atom is in table check if it is true or not
			{
				if(searchAtom->isFact())
				{
					//if this atom is true i have to delete it from rule
					size_body--;
				}

//				GenericAtom* genericBodyAtom=new GenericAtom;
//				genericBodyAtom->setTerms((*atom)->getTerms());
//				genericBodyAtom->setFact((*atom)->isFact());
//				for(unsigned i=0;i<tableSearcher[index_body_atom].size();++i)
//								predicateExt->addGenericAtom(tableSearcher[index_body_atom][i],genericBodyAtom);
			}


			if(size_body==0 && currentRule->getSizeHead()==1)
			{
				for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++index_head_atom)
				{
					PredicateExtension* predicateExt=ProgramGrounder::predicateExtTable->getPredicateExt(index_head_atom);
					searchAtom=predicateExt->getGenericAtom((*atom));
					if(searchAtom==nullptr_t)
					{
						GenericAtom* genericBodyAtom=new GenericAtom;
						genericBodyAtom->setTerms((*atom)->getTerms());
						genericBodyAtom->setFact((*atom)->isFact());
						for(unsigned i=0;i<tableSearcher[index_head_atom].size();++i)
							predicateExt->addGenericAtom(tableSearcher[index_head_atom][i],genericBodyAtom);
					}
				}
			}
//			for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++index_head_atom)
//			{
//
//			}
		}
	}
}
}

