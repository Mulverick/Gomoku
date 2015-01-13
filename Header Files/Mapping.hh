#ifndef MAPPING_HH_
# define	MAPPING_HH_

# include	"Utils.hh"

/*# define FIVE_WHITE (1 << 2)
# define FOUR_WHITE (1 << 3)
# define THREE_WHITE (1 << 4)
# define FIVE_BLACK (1 << 5)
# define FOUR_BLACK (1 << 6)
# define THREE_BLACK (1 << 7)*/

# define FOUR_WHITE (1 << 2)
# define THREE_WHITE (1 << 3)
# define FOUR_BLACK (1 << 4)
# define THREE_BLACK (1 << 5)

struct Patern
{
	bool upblack = true;
	bool upwhite = true;
	bool downwhite = true;
	bool downblack = true;

	bool rightblack = true;
	bool rightwhite = true;
	bool leftwhite = true;
	bool leftblack = true;

	bool uprightblack = true;
	bool uprightwhite = true;
	bool downleftwhite = true;
	bool downleftblack = true;

	bool downrightblack = true;
	bool downrightwhite = true;
	bool upleftwhite = true;
	bool upleftblack = true;

	int nbvertblack = 1;
	int nbvertwhite = 1;

	int nbhoriblack = 1;
	int nbhoriwhite = 1;

	int nbdionblack = 1;
	int nbdionwhite = 1;

	int nbditwblack = 1;
	int nbditwwhite = 1;

	bool end = false;
};

class Mapping
{
public:
	Mapping();
	Mapping(char * const *map);
	~Mapping();
	void	nearPlaces(Vector<int> const &pos, char * const *board, char * const *map, int color);
	void	updateMap(char * const *map);
	void	simpleUpdate(char * const *map);
	char	**getMap();
private:
	char	**_board;

	void	HorizontalPatern(Vector<int> const &pos, char * const *board, char * const *map, Patern *patern, int i);
	void	VerticalPatern(Vector<int> const &pos, char * const *board, char * const *map, Patern *patern, int i);
	void	DiagonalOnePatern(Vector<int> const &pos, char * const *board, char * const *map, Patern *patern, int i);
	void	DiagonaltwoPatern(Vector<int> const &pos, char * const *board, char * const *map, Patern *patern, int i);
	void	CheckPatern(Vector<int> const &pos, char * const *board, char * const *map);
};

#endif // !MAPPING_HH_
