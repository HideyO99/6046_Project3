#include "XML.h"
#include <iostream>

XML::XML()
{
}

XML::~XML()
{
}

void XML::readXML()//std::string fname, std::string fpath)
{
	bool call_result = false;
	pugi::xml_document* music_xml = new pugi::xml_document();
	pugi::xml_parse_result result = music_xml->load_file("sound_list.xml");
	if (!result) 
	{
		std::cout << "Unable to load XML file" << std::endl;
		delete music_xml;
		return ;
	}
	std::cout << "Loaded XML" << std::endl;

	//read music
	call_result = read_music(music_xml);
	if (call_result)
	{
		std::cout << "Loaded Music path from XML" << std::endl;
	}

	//pugi::xml_object_range<pugi::xml_node_iterator> music = music_xml.child("music").children();
	//if (music.empty()) 
	//{
	//	std::cout<<"There are no entries"<<std::endl;
	//	return ;
	//}

	//pugi::xml_node_iterator music_i;
	//int i = 0;
	//int j = 0;
	//for (music_i = music.begin(); music_i != music.end(); ++music_i)
	//{
	//	pugi::xml_node fname = *music_i;
	//	pugi::xml_node_iterator musicit;
	//	//std::string s = fname.child_value();
	//	my_music[i].fname = fname.child_value();
	//	my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\n'), my_music[i].fname.cend());	//remove \n
	//	my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\t'), my_music[i].fname.cend());	//remove \t
	//	for (musicit = fname.children().begin(); musicit != fname.children().end(); ++musicit)
	//	{
	//		pugi::xml_node pathNode = *musicit;

	//		if (!pathNode.children().empty())
	//		{
	//			my_music[i].path[j] = pathNode.child_value();
	//			j++;
	//		}
	//	}
	//	i++; 
	//	j = 0;
	//}
	
	//read fx
	call_result = read_fx(music_xml);
	if (call_result)
	{
		std::cout << "Loaded FX path from XML" << std::endl;
	}
	//pugi::xml_object_range<pugi::xml_node_iterator> fx = music_xml.child("fx").children();
	//if (fx.empty())
	//{
	//	std::cout << "There are no entries" << std::endl;
	//	return;
	//}

	//pugi::xml_node_iterator fx_i;
	//i = j = 0;

	//for (fx_i = fx.begin(); fx_i != fx.end(); fx_i++)
	//{
	//	pugi::xml_node fx_path = *fx_i;
	//	pugi::xml_node_iterator fx_it;
	//	for (fx_it = fx_path.children().begin(); fx_it != fx_path.children().end(); fx_it++)
	//	{
	//		pugi::xml_node pathNode = *fx_it;
	//		if (!pathNode.children().empty())
	//		{
	//			my_fx_path[i] = pathNode.child_value();
	//			i++;
	//		}
	//	}
	//}
	
	
	call_result = read_stream_URL(music_xml);
	if (call_result)
	{
		std::cout << "Loaded Streaming URL from XML" << std::endl;
	}
	//music_xml.~xml_document();
	delete music_xml;
}

bool XML::read_music(pugi::xml_document* music_xml)
{
	pugi::xml_object_range<pugi::xml_node_iterator> music = music_xml->child("music").children();
	if (music.empty())
	{
		std::cout << "There are no music entries" << std::endl;
		return false;
	}

	pugi::xml_node_iterator music_i;
	int i = 0;
	int j = 0;
	for (music_i = music.begin(); music_i != music.end(); ++music_i)
	{
		pugi::xml_node fname = *music_i;
		pugi::xml_node_iterator musicit;
		//std::string s = fname.child_value();
		my_music[i].fname = fname.child_value();
		my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\n'), my_music[i].fname.cend());	//remove \n
		my_music[i].fname.erase(std::remove(my_music[i].fname.begin(), my_music[i].fname.end(), '\t'), my_music[i].fname.cend());	//remove \t
		for (musicit = fname.children().begin(); musicit != fname.children().end(); ++musicit)
		{
			pugi::xml_node pathNode = *musicit;

			if (!pathNode.children().empty())
			{
				my_music[i].path[j] = pathNode.child_value();
				j++;
			}
		}
		i++;
		j = 0;
	}

	return true;
}

bool XML::read_fx(pugi::xml_document* music_xml)
{
	pugi::xml_object_range<pugi::xml_node_iterator> fx = music_xml->child("fx").children();
	if (fx.empty())
	{
		std::cout << "There are no fx entries" << std::endl;
		return false;
	}

	pugi::xml_node_iterator fx_i;
	int i = 0;
	int j = 0;

	for (fx_i = fx.begin(); fx_i != fx.end(); fx_i++)
	{
		pugi::xml_node fx_path = *fx_i;
		pugi::xml_node_iterator fx_it;
		for (fx_it = fx_path.children().begin(); fx_it != fx_path.children().end(); fx_it++)
		{
			pugi::xml_node pathNode = *fx_it;
			if (!pathNode.children().empty())
			{
				my_fx_path[i] = pathNode.child_value();
				i++;
			}
		}
	}

	return true;
}

bool XML::read_stream_URL(pugi::xml_document* music_xml)
{
	pugi::xml_object_range<pugi::xml_node_iterator> stream = music_xml->child("stream").children();
	if (stream.empty())
	{
		std::cout << "There are no stream URL entries" << std::endl;
		return false;
	}

	pugi::xml_node_iterator stream_i;
	int i = 0;
	int j = 0;

	for (stream_i = stream.begin(); stream_i != stream.end(); stream_i++)
	{
		pugi::xml_node stream_path = *stream_i;
		pugi::xml_node_iterator stream_it;
		for (stream_it = stream_path.children().begin(); stream_it != stream_path.children().end(); stream_it++)
		{
			pugi::xml_node pathNode = *stream_it;
			if (!pathNode.children().empty())
			{
				my_stream_url_path[i] = pathNode.child_value();
				i++;
			}
		}
	}

	return true;
}

XML::MyMusic::MyMusic()
{
	path[0] = "";
	path[1] = "";
}
