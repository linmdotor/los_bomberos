#include <stdio.h>
#include "ParserXml.h"
#include "MapParserXml.h"
#include "Map\MapEntity.h"

namespace Map {
	ParserXml::ParserXml(class MapParserXml& mapParser, const std::string &xmlfile) :
		m_doc(NULL), m_mapParser(mapParser), m_fileName(xmlfile)
	{
		createParser();
		parser->parse(m_fileName.c_str());
		m_doc = parser->adoptDocument();
	}

	ParserXml::~ParserXml()
	{
		if (m_doc) m_doc->release();
	}

	string ParserXml::getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex)
	{
		XMLCh* temp = XMLString::transcode(parentTag);
		DOMNodeList* list = m_doc->getElementsByTagName(temp);
		XMLString::release(&temp);

		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		printf("num parent->getChildElementCount() %d", parent->getChildElementCount());
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
		string value;
		if (child) {
			char* temp2 = XMLString::transcode(child->getTextContent());
			value = temp2;
			XMLString::release(&temp2);
		}
		else {
			value = "";
		}
		return value;
	}

	string ParserXml::getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex,
		const char* attributeTag)
	{
		XMLCh* temp = XMLString::transcode(parentTag);
		DOMNodeList* list = m_doc->getElementsByTagName(temp);
		XMLString::release(&temp);

		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		DOMElement* child =
			dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(childIndex));
		string value;
		if (child) {
			temp = XMLString::transcode(attributeTag);
			char* temp2 = XMLString::transcode(child->getAttribute(temp));
			value = temp2;
			XMLString::release(&temp2);
		}
		else {
			value = "";
		}
		return value;
	}

	int ParserXml::getRootElementCount(const char* rootElementTag)
	{
		DOMNodeList* list = m_doc->getElementsByTagName(XMLString::transcode(rootElementTag));
		return (int)list->getLength();
	}

	int ParserXml::getChildCount(const char* parentTag, int parentIndex, const char* childTag)
	{
		XMLCh* temp = XMLString::transcode(parentTag);
		DOMNodeList* list = m_doc->getElementsByTagName(temp);
		XMLString::release(&temp);

		DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
		DOMNodeList* childList = parent->getElementsByTagName(XMLString::transcode(childTag));
		return (int)childList->getLength();
	}
	bool ParserXml::parse()
	{
		XMLCh* temp = XMLString::transcode("Map");
		DOMNodeList* list = m_doc->getElementsByTagName(temp);
		XMLString::release(&temp);

		DOMElement* root = dynamic_cast<DOMElement*>(list->item(0));


		DOMElement* childAux = root->getFirstElementChild();

		for (unsigned int i = 0; i < root->getChildElementCount(); ++i)
		{
			printf("getChildElementCount %d\n", childAux->getChildElementCount());
			printf("child1->getTagName() %s\n", XMLString::transcode(childAux->getTagName()));
			m_mapParser._entityInProgress = new Map::CEntity(XMLString::transcode(childAux->getTagName()));
			//parseAttributes(childAux);
			parseElement(childAux);


#ifdef _DEBUG
			assert(m_mapParser._entityInProgress->getType().compare("") && "No se ha establecido tipo a la entidad");
			Map::MapParserXml::TEntityList::const_iterator it, end;
			it = m_mapParser._entityList.begin();
			end = m_mapParser._entityList.end();
			for (; it != end; it++)
			{
				assert((*it)->getName().compare(m_mapParser._entityInProgress->getName()) && "Ya existe una entidad con este nombre.");
			}
#endif // _DEBUG
			m_mapParser._entityList.push_back(m_mapParser._entityInProgress);

			childAux = childAux->getNextElementSibling();
		}
		return true;
	}
	bool ParserXml::parseElement(DOMElement *element)
	{
		DOMElement* value = element->getFirstElementChild();
		for (unsigned int j = 0; j < element->getChildElementCount(); ++j)
		{
			printf("\tvalue->getTagName() %s\n", XMLString::transcode(value->getTagName()));
			printf("\tvalue->getTextContent() %s\n", XMLString::transcode(value->getTextContent()));

			std::string stringAttr = XMLString::transcode(value->getTagName());
			std::string stringValue = XMLString::transcode(value->getTextContent());

			assert(stringAttr.compare("name") && "El atributo \"name\" no se puede definir.");
			if (!stringAttr.compare("type"))
				m_mapParser._entityInProgress->setType(stringValue);
			else
				m_mapParser._entityInProgress->setAttribute(stringAttr, stringValue);

			//parseAttributes(value);

			value = value->getNextElementSibling();
		}
		return true;
	}
	bool ParserXml::parseAttributes(DOMElement *element)
	{
		DOMNamedNodeMap *attr = element->getAttributes();
		for (unsigned int z = 0; z < attr->getLength(); ++z)
		{
			printf("\tattr->item(z)->getNodeName() %s\n", XMLString::transcode(attr->item(z)->getNodeName()));
			printf("\tattr->item(z)->getTextContent() %s\n", XMLString::transcode(attr->item(z)->getTextContent()));
		}
		return true;
	}
	void ParserXml::createParser()
	{
		if (!parser)
		{
			XMLPlatformUtils::Initialize();
			parser = new XercesDOMParser();
			errorHandler = (ErrorHandler*) new XmlDomErrorHandler();
			parser->setErrorHandler(errorHandler);
		}
	}
}