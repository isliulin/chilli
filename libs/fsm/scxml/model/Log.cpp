#include "Log.h"
#include "../../common/xmlHelper.h"
#include <log4cplus/loggingmacros.h>

using namespace helper::xml;
namespace fsm{
namespace model{
	Log::Log(xmlNodePtr xNode,const std::string &sessionid,const std::string &filename)
		:Action(xNode, sessionid, filename)
	{
		log = log4cplus::Logger::getInstance("fsm.model.Log");
		m_strExpr =  XStr(xmlNodeGetContent(node)).strForm();
		m_Type = getXmlNodeAttributesValue(node,"type");
		m_strLevel = getXmlNodeAttributesValue(node,"level");
	}
	void Log::execute(Context * ctx)
	{

		if(ctx && m_Type.compare("script") == 0)
			m_strExpr = ctx->eval(m_strExpr,m_strFileName,node->line,node);

		if (m_strLevel.compare("trace") == 0){
			LOG4CPLUS_TRACE(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("debug") == 0){
			LOG4CPLUS_DEBUG(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("info") == 0){
			LOG4CPLUS_INFO(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("warn") == 0){
			LOG4CPLUS_WARN(log, m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("error") == 0){
			LOG4CPLUS_ERROR(log,m_strSession << "," << m_strExpr);
		}
		else if (m_strLevel.compare("fatal") == 0){
			LOG4CPLUS_FATAL(log, m_strSession << "," << m_strExpr);
		}
		else{

			LOG4CPLUS_INFO(log, m_strSession << "," << m_strExpr);
		}
	}
	const std::string & Log::getExpr() const
	{
		return m_strExpr;
	}
	const std::string & Log::getLevel() const
	{
		return m_strLevel;
	}

}
}
