#ifndef __Map_ParserXml_H__
#define __Map_ParserXml_H__

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <string>

namespace Map
{
	class CEntity;
}

using namespace std;
using namespace xercesc;

namespace Map {
	class XmlDomErrorHandler : public HandlerBase
	{
	public:
		void fatalError(const SAXParseException &exc) {
			printf("Fatal parsing error at line %d\n", (int)exc.getLineNumber());
			exit(-1);
		}
	};

	class ParserXml
	{
	protected:
		xercesc::DOMDocument* m_doc;
		XercesDOMParser*   parser = NULL;
		ErrorHandler*      errorHandler = NULL;
		std::string m_fileName;
		/* User arguments.  */
		class MapParserXml& m_mapParser;

	public:
		ParserXml(class MapParserXml& _mapParser, const std::string &xmlfile);
		~ParserXml();

		string getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
		string getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex, const char* attributeTag);
		int getRootElementCount(const char* rootElementTag);
		int getChildCount(const char* parentTag, int parentIndex, const char* childTag);
		bool parse();
	protected:
		void createParser();
		bool parseElement(DOMElement *element);
		bool parseAttributes(DOMElement *element);

	};
} //namespace Map
#endif //__Map_ParserXml_H__