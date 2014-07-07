#include "Functionmodel.h"
#include <log4cplus/loggingmacros.h>
#include "Function.h"

namespace fsm{
namespace model{


Functionmodel::Functionmodel(xmlNodePtr xnode,const std::string &session, const std::string &filename):
	Action(xnode, session, filename)
{
	log = log4cplus::Logger::getInstance("fsm.model.Functionmodel");
}

void Functionmodel::execute(fsm::Context * ctx){
	//LOG4CPLUS_TRACE(log,m_strSession << ",execute starting...");

	bool bFindData = false;
	for (xmlNodePtr funNode = node->children ; funNode !=  NULL; funNode = funNode->next)
	{
		if(funNode->type != XML_ELEMENT_NODE ||
			!xmlStrEqual(funNode->name, BAD_CAST("function")))
			continue;
		bFindData = true;
		model::Function fun(funNode,m_strSession,m_strFileName);
		fun.execute(ctx);
	}
	if (!bFindData)
	{
		LOG4CPLUS_WARN(log,"not find data element in this functionmodel.");
	}
	//LOG4CPLUS_TRACE(log,m_strSession << ",execute end.");
}

Functionmodel::~Functionmodel(void)
{
}
}//end namespace model
}// end namespace fsm
