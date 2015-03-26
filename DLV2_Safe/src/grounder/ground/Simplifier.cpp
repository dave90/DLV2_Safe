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

	void Simplifier::simplifier(Rule* currentRule,const vector<vector<unsigned>>& tableSearcher, vector<bool>& atom_undef_inbody)
	{
		Rule* ruleSemplified=new Rule;
		unsigned size_body=currentRule->getSizeBody();
		unsigned index_body_atom=0;
		unsigned index_head_atom=0;
		Atom *searchAtom=0;
		for(auto atom=currentRule->getBeginBody();atom!=currentRule->getEndBody();++atom,++index_body_atom)
		{
			if(!atom_undef_inbody[index_body_atom])
					if(!((*atom)->isNegative() && StatementDependency::getInstance()->isPredicateNegativeStratified((*atom)->getPredicate()->getIndex())))
					{
						(*atom)->~Atom();
						size_body--;
						continue;
					}
			PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((*atom)->getPredicate()->getIndex());
			searchAtom=predicateExt->getGenericAtom((*atom));

			if(searchAtom!=nullptr) //if atom is in table check if it is true or not
			{
				if((searchAtom->isFact() && !searchAtom->isNegative()) )
				{
					//if this atom is true i have to delete it from rule
					(*atom)->~Atom();
					size_body--;
				}

			}
		}

		bool headTrue=false;

		if(size_body==0 && currentRule->getSizeHead()==1)
		{
			headTrue=true;
		}
			for(auto atom=currentRule->getBeginHead();atom!=currentRule->getEndHead();++atom,++index_head_atom)
			{
				PredicateExtension* predicateExt=PredicateExtTable::getInstance()->getPredicateExt((*atom)->getPredicate()->getIndex());
				searchAtom=predicateExt->getGenericAtom((*atom));
				if(searchAtom==nullptr)
				{
					GenericAtom* genericHeadAtom=new GenericAtom;
					genericHeadAtom->setTerms((*atom)->getTerms());
					genericHeadAtom->setFact(headTrue);
					for(unsigned i=0;i<tableSearcher[index_head_atom].size();++i)
						predicateExt->addGenericAtom(tableSearcher[index_head_atom][i],genericHeadAtom);
				}
			}
	}




}
}

