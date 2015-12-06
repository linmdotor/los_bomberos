/**
@file MapParserXml.cpp

Contiene la implementación de la clase que encapsula el parseo de mapas en xml.

@see Map::MapParserXml

@author Daniel Parra Lopez
@date Diciembre, 2015
*/

#include <fstream>
#include <sstream>
#include <cassert>

#include "MapEntity.h"
#include "MapParserXml.h"
#include "ParserXml.h"

namespace Map {

	MapParserXml* MapParserXml::_instance = 0;

	//--------------------------------------------------------

	MapParserXml::MapParserXml() : _traceScanning(false),
							  _traceParsing(false),
							  _entityInProgress(0)
	{
		_instance = this;

	} // MapParserXml

	//--------------------------------------------------------

	MapParserXml::~MapParserXml()
	{
		releaseEntityList();
		_instance = 0;

	} // ~MapParserXml
	
	//--------------------------------------------------------

	bool MapParserXml::Init()
	{
		assert(!_instance && "Segunda inicialización de Map::MapParserXml no permitida!");

		new MapParserXml();
		return true;

	} // Init

	//--------------------------------------------------------

	void MapParserXml::Release()
	{
		assert(_instance && "Map::MapParserXml no está inicializado!");
		if(_instance)
		{
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool MapParserXml::parseFile(const std::string &filename)
	{
		ParserXml parser(*this, filename);
		return parser.parse();
	} // parseFile

	//--------------------------------------------------------

	void MapParserXml::error(const class location& l,
			   const std::string& m)
	{
		printf("%s", m);
		//std::cerr << l << ": " << m << std::endl;
	} // error

	//--------------------------------------------------------

	void MapParserXml::error(const std::string& m)
	{
		std::cerr << m << std::endl;
	} // error

	//--------------------------------------------------------
		
	void MapParserXml::releaseEntityList()
	{
		while(!_entityList.empty())
		{
			_entityInProgress = _entityList.back();
			_entityList.pop_back();
			delete _entityInProgress;
		}
	}

} // namespace Map
