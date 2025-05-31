#include "cxxopts.hpp"
#include "fileref.h"
#include "tag.h"
#include <iostream>

void list(const cxxopts::ParseResult &result)
{
	for (auto filename: result["files"].as<std::vector<std::string>>())
	{
		std::cout << "\033[36mFilename\033[m: \033[1;37m" << filename << "\033[m" << std::endl;

		TagLib::FileRef f(filename.c_str());

		if (f.isNull())
		{
		}
		else
		{
			TagLib::Tag *tag = f.tag();

			if (tag)
			{
				std::cout << "\033[36mArtist  \033[m: " << tag->artist()  << std::endl;
				std::cout << "\033[36mTitle   \033[m: " << tag->title()   << std::endl;
				std::cout << "\033[36mAlbum   \033[m: " << tag->album()   << std::endl;
				std::cout << "\033[36mYear    \033[m: " << tag->year()    << std::endl;
				std::cout << "\033[36mGenre   \033[m: " << tag->genre()   << std::endl;
				std::cout << "\033[36mTrack   \033[m: " << tag->track()   << std::endl;
//				std::cout << "\033[36mDisc    \033[m: " << tag->disc()    << std::endl;
				std::cout << "\033[36mComment \033[m: " << tag->comment() << std::endl;
				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl;
}

void update(const cxxopts::ParseResult &result)
{
	for (auto filename: result["files"].as<std::vector<std::string>>())
	{
		TagLib::FileRef f(filename.c_str());

		if (f.isNull())
		{
		}
		else
		{
			TagLib::Tag *tag = f.tag();

			if (tag)
			{
				if (result.count("artist"))
					tag->setArtist(result["artist"].as<std::string>());

				if (result.count("title"))
					tag->setTitle(result["title"].as<std::string>());

				if (result.count("album"))
					tag->setAlbum(result["album"].as<std::string>());

				if (result.count("year"))
					tag->setYear(result["year"].as<unsigned int>());

				if (result.count("genre"))
				{
					std::string genre = result["genre"].as<std::string>();

					if (genre == "-")
						genre = "";

					tag->setGenre(genre);
				}

				if (result.count("track"))
					tag->setTrack(result["track"].as<unsigned int>());

//				if (result.count("disc"))	// DISCNUMBER
//					tag->setDisc(result["disc"].as<unsigned int>());

				if (result.count("comment"))
				{
					std::string comment = result["comment"].as<std::string>();

					if (comment == "-")
						comment = "";

					tag->setComment(comment);
				}

				f.save();
			}
		}
	}
}

int main(int argc, char *argv[])
{
	cxxopts::Options options("id3tags", "Read/modify ID3 tags\n");

	options.add_options()
		("h,help", "Print usage")

		("l,list", "List tags", cxxopts::value<bool>()->default_value("false"))

		("a,artist",  "Artist",  cxxopts::value<std::string>())
		("t,title",   "Title",   cxxopts::value<std::string>())
		("A,album",   "Album",   cxxopts::value<std::string>())
		("y,year",    "Year",    cxxopts::value<unsigned int>())
		("g,genre",   "Genre",   cxxopts::value<std::string>())
		("T,track",   "Track",   cxxopts::value<unsigned int>())
//		("d,disc",    "Disc",    cxxopts::value<unsigned int>())
		("c,comment", "Comment", cxxopts::value<std::string>())

		("files", "List of files", cxxopts::value<std::vector<std::string>>())
	;

	options.parse_positional({"files"});

	auto result = options.parse(argc, argv);

	if (result.count("help"))
	{
		std::cout << options.help() << std::endl;
		exit(0);
	}

	if (result.count("files"))
	{
		if (result.count("list"))
			list(result);
		else
			update(result);
	}

	return 0;
}
