#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <string>
#include <vector>
#include <list>

class IHash;

class IDownload
{
public:
	enum category {
		CAT_NONE=0,
		CAT_MAPS,
		CAT_MODS,
		CAT_LUAWIDGETS,
		CAT_AIBOTS,
		CAT_LOBBYCLIENTS,
		CAT_MEDIA,
		CAT_OTHER,
		CAT_REPLAYS,
		CAT_SPRINGINSTALLERS,
		CAT_TOOLS
	} cat;

	IDownload(const std::string& filename="", category cat=CAT_NONE);
	~IDownload();
	/**
	 *
	 *	add a mirror to the download specified
	 */
	bool addMirror(const std::string& url);
	bool addDepend(const std::string& depend);
	std::string name; //name, in most cases the filename to save to
	std::list<std::string> depend; //list of all depends
	bool downloaded; //file was downloaded?
	/**
	 *	returns the string name of a category
	 */
	const std::string getCat(category cat);
	/**
	 *	returns first url
	 */
	const std::string getUrl();
	/**
	 *
	 */
	const std::string& getMirror(const int i);
	int getMirrorCount();
	/**
	*	size of pieces, last piece size can be different
	*/
	int piecesize;
	enum PIECE_STATE {
		STATE_NONE,        // nothing was done with this piece
		STATE_DOWNLOADING, // piece is currently downloaded
		STATE_FINISHED,    // piece downloaded successfully + verified
	};
	struct piece {
		IHash* sha;
		PIECE_STATE state;
	};
	/**
	 *	sha1 sum of pieces
	 */
	std::vector<struct piece> pieces; //FIXME: make private
	IHash* hash;

	/**
	 *	file size
	 */
	int size;
private:
	std::list<std::string> mirror;

};

#endif