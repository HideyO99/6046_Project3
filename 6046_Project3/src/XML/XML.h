#pragma once
#include <string>
#include <pugixml/pugixml.hpp>

class XML
{
public:
	XML();
	~XML();
	
	struct MyMusic
	{
		std::string fname;
		std::string path[2];

		MyMusic();
	};

	MyMusic my_music[3];
	std::string my_fx_path[7];
	std::string my_stream_url_path[3];


	void readXML();

private:
	bool read_music(pugi::xml_document* music_xml);
	bool read_fx(pugi::xml_document* music_xml);
	bool read_stream_URL(pugi::xml_document* music_xml);
};

