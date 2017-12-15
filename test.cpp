#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

using namespace std; 

const sf::Color boardColor(224, 171, 87); //specifies wooden color

class Coord { //coordinate class
protected:
	float x;
	float y;

public:

	Coord(float x, float y) {
		Coord::x = x;
		Coord::y = y;
	}

	Coord() {
	}

	float get_x(void) { //returns x coordinate
		return (Coord::x);
	}

	float get_y(void) { //returns y coordinate
		return (Coord::y);
	}

	void set_x(float f) { //sets x coordinate
		Coord::x = f;
	}

	void set_y(float f) { //sets y coordinate
		Coord::y = f;
	}
};

class tilePos { //invisible box containing range of x and y values demarking a tile
protected:
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	bool taken;

public:

	//constructor for our invisible box
	tilePos(float xmin, float xmax, float ymin, float ymax) {
		tilePos::xmin = xmin;
		tilePos::xmax = xmax;
		tilePos::ymin = ymin;
		tilePos::ymax = ymax;
		tilePos::taken = false;
	}

	tilePos() {

	}

	bool get_taken(void) { //returns if there's something on this tile
		return (tilePos::taken);
	}

	void set_taken(bool t) { //sets the tile to be filled or not
		tilePos::taken = t;
	}

	float get_xmin(void) { //returns minimum x value of tile
		return (tilePos::xmin);
	}

	float get_xmax(void) { //returns maximum x value of tile
		return (tilePos::xmax);
	}

	float get_ymin(void) { //returns minimum y value of tile
		return (tilePos::ymin);
	}

	float get_ymax(void) { //returns maximum y value of tile
		return (tilePos::ymax);
	}
};

class Piece { //the actual checker piece we're working with

protected:

	sf::CircleShape node; //the circle that is drawn to represent the piece
	Coord c; //the coordinates of the center of the piece
	tilePos square; //the tile that it lives on (range of x and y coordinates)
	bool queen; // true if the piece is a queen
	bool player; // true if the piece is being controlled by the player
	bool captured;

public:

	//creates a fully fledged checkers piece
	Piece(Coord xy, bool player, bool first, sf::CircleShape check) {
		Piece::queen = false; //no one starts as a queen
		Piece::c = xy; //here's your starting position
		Piece::player = player; //it's either you or the AI
		Piece::node = check; //our little circle
		Piece::captured = false; //gotta start on the board
		if (first) { //if you're starting first, you're black
			Piece::node.setOutlineColor(boardColor);
			Piece::node.setFillColor(sf::Color::Black);
		} else {
			Piece::node.setOutlineColor(sf::Color::Black);
			Piece::node.setFillColor(sf::Color::Red);
		}
		Piece::node.setPosition(Piece::c.get_x(), Piece::c.get_y());
	}

	Piece() { //an empty piece to be set at a later point
	}

	//assigns all the attributes of one piece to another
	void set_piece(Piece p) {
		Piece::queen = p.get_queen();
		Piece::c = p.get_pos();
		Piece::square = p.get_tilePos();
		Piece::player = p.get_player();
		Piece::node = p.get_node();
		Piece::captured = p.get_captured();
	}

	//says if the piece is on the board or not
	bool get_captured(void) {
		return (Piece::captured);
	}

	//returns if the piece belongs to the player
	bool get_player(void) {
		return (Piece::player);
	}

	//returns the visible circle to be drawn
	sf::CircleShape get_node() {
		return (Piece::node);
	}

	//returns if the piece is a queen
	bool get_queen(void) {
		return(Piece::queen);
	}

	//queens a checkers piece
	void set_queen(void) {
		Piece::queen = true;
	}
	//sets the position of the checkers piece
	void set_pos(Coord xy) {
		Piece::c = xy;
		Piece::node.setPosition(xy.get_x(), xy.get_y());
	}
	//returns the position of the checkers piece
	Coord get_pos(void) {
		return(c);
	}
	//returns the tile that the checkers piece is on
	tilePos get_tilePos(void) {
		return (Piece::square);
	}

};

int main() {

	//creates the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Checkers");

	//loads the font
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf")) 
		return EXIT_FAILURE;

	sf::Text text; //our text variable
	text.setPosition(555, 500); //sets position of text to bottom right corner
	text.setFont(font); //sets font to arial
	text.setCharacterSize(15); //sets font size to 15px
	//lists an opening message
	text.setString("Welcome!\nThis is a checkers AI.\nTo play, click on one of your pieces\nthen click the desired location.");

	vector<sf::Text> queens;
	sf::Text q; //the Q that marks all queens
	q.setString("  Q");
	q.setFont(font);
	for (int i = 0; i < 24; i++) 
		queens.push_back(q); //creates separate text objects for all possible queens so they can be drawn multiple times

	//our winner text!
	sf::Text win("Congratulations! You win!", font, 20);
	win.setPosition(555, 500);

	//our loser text :(
	sf::Text lose("Sorry! You lose!", font, 20);
	lose.setPosition(555, 500);

	int counter1 = 0; //counts number of pieces player captured
	int counter2 = 0; //counts number of pieces AI captured

	bool dragged = false; //true if the checkers piece is being moved
	Piece moved; //a holder piece for the piece that is being moved
	int name; //remembers the place of the piece that is being moved

	//creates the board
	sf::RectangleShape outerBoard;
	sf::RectangleShape innerBoard;
	outerBoard.setSize(sf::Vector2f(500, 500));
	innerBoard.setSize(sf::Vector2f(480, 480));
	innerBoard.setOutlineThickness(3);
	innerBoard.setOutlineColor(sf::Color::Black);
	outerBoard.setFillColor(boardColor);
	innerBoard.setFillColor(boardColor);
	outerBoard.setPosition(50, 50);
	innerBoard.setPosition(60, 60);

	//creates a visible representation of the tiles on our board
	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(60, 60));
	
	//creates the general aspects of those circles onscreen
	sf::CircleShape circle;
	circle.setRadius(25);
	circle.setOutlineThickness(2);

	//all the positions!!
	vector<Coord> Player1pos; //the positions for the checkers pieces for our player
	vector<Coord> Player2pos;//the positions for the checkers pieces for our AI
	for (int i = 0; i < 4; i++) {
		Coord c(65+(i*120), 365);
		Player1pos.push_back(c);
	}
	for (int i = 0; i < 4; i++) {
		Coord c(125+(i*120), 425);
		Player1pos.push_back(c);
	}
	for (int i = 0; i < 4; i++) {
		Coord c(65+(i*120), 485);
		Player1pos.push_back(c);
	}

	for (int i = 0; i < 4; i++) {
		Coord c(125+(i*120), 65);
		Player2pos.push_back(c);
	}
	for (int i = 0; i < 4; i++) {
		Coord c(65+(i*120), 125);
		Player2pos.push_back(c);
	}
	for (int i = 0; i < 4; i++) {
		Coord c(125+(i*120), 185);
		Player2pos.push_back(c);
	}

	vector<tilePos> tileposes;
	//initializing the tilePos!
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tilePos ti(60+(i*60), 120+(i*60), 60+(j*60), 120+(j*60)); //draw the invisible representations of tiles
			tileposes.push_back(ti);
		}
	}

	vector<Piece> Player1; //these are all the checkers pieces for our player
	vector<Piece> Player2; //these are all the checkers pieces for our AI

	//time to initialize all the checkers pieces!
	for (int i = 0; i < 12; i++) {
		Piece p(Player1pos[i], true, true, circle);
		Player1.push_back(p);
		Piece o(Player2pos[i], false, false, circle);
		Player2.push_back(o);
	}

	for (int i = 0; i < 64; i++) { //sets tilePoses to taken if they are filled
		for (int j = 0; j < 12; j++) {
			if (Player1[j].get_pos().get_x() <= tileposes[i].get_xmax() && Player1[j].get_pos().get_x() >= tileposes[i].get_xmin() && Player1[j].get_pos().get_y() <= tileposes[i].get_ymax() && Player1[j].get_pos().get_y() >= tileposes[i].get_ymin())
				tileposes[i].set_taken(true);
		}
		for (int k = 0; k < 12; k++) {
			if (Player2[k].get_pos().get_x() <= tileposes[i].get_xmax() && Player2[k].get_pos().get_x() >= tileposes[i].get_xmin() && Player2[k].get_pos().get_y() <= tileposes[i].get_ymax() && Player2[k].get_pos().get_y() >= tileposes[i].get_ymin())
				tileposes[i].set_taken(true);
		}
	}

	//below this line is the stuff that will actually be happening/updating
	while(window.isOpen()) {
		sf::Event event; //check for new things!
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) //check for someone trying to escape the game!
				window.close(); //close the game
		}
		
		window.clear(); //clear the screen
		window.draw(outerBoard); //draw the board
		window.draw(innerBoard);

		//TILES!!
		for (int i = 0; i < 8; i++) { 
			for (int j = 0; j < 8; j++) {
				tile.setPosition((60+(i*60)), (60+(j*60))); //draw the visible tiles
				if (i%2 == j%2) {
					tile.setFillColor(boardColor);
				} else {
					tile.setFillColor(sf::Color::Black);
				}
				window.draw(tile); //DRAW THE TILE
			}
		}

		float startx = 0; //needs to be initialized, i guess
		float starty = 0; //these will be the starting mouse position when the mouse gets pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dragged) { //if you click your mouse
			startx = sf::Mouse::getPosition(window).x; //get a starting position
			starty = sf::Mouse::getPosition(window).y;
			//find which checker piece got clicked with lots of if statements
			for (int i = 0; i < 12; i++) {
				if (startx<=Player1[i].get_pos().get_x()+25 && startx>=Player1[i].get_pos().get_x()-25 && starty <= Player1[i].get_pos().get_y()+25 && starty<=Player1[i].get_pos().get_y()-25) {
					dragged = true;
					moved.set_piece(Player1[i]);
					//at this point it would be good to set the old tilePos
					//as empty, but I'm not sure how I want to go about that
					name = i;
				}
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && dragged) {
			float currx = sf::Mouse::getPosition(window).x; //get the new mouse position
			float curry = -sf::Mouse::getPosition(window).y;
			float dx = currx - startx; //get the change in position
			float dy = curry - starty;
			Coord n;
			n.set_x(moved.get_pos().get_x()+dx); //make a new coordinate based on the new position
			n.set_y(moved.get_pos().get_y()+dy);
			moved.set_pos(n);
			dragged = false; //you're not dragging a checker piece anymore
			Player1[name].set_piece(moved);
			//at this point it would be good to set the piece as its new tilePos
			//but I'm also not sure how I want to do that
		}
		//draws the checkers pieces
		for (int i = 0; i < 12; i++) {
			window.draw(Player1[i].get_node());
			if (Player1[i].get_queen()) {
				queens[i].setPosition(Player1[i].get_pos().get_x(), Player1[i].get_pos().get_y()+8);
				window.draw(queens[i]);
			}
		}
		for (int i = 0; i < 12; i++) {
			window.draw(Player2[i].get_node());
			if (Player2[i].get_queen()) {
				queens[i+12].setPosition(Player2[i].get_pos().get_x(), Player2[i].get_pos().get_y()+8);
				window.draw(queens[i+12]);
			}
		}
		if (counter1 == 12) { //writes win text if you capture all the AI's pieces
			window.draw(win);
		} else if (counter2 == 12) { //writes lose text if the AI captures all your pieces
			window.draw(lose);
		} else {
		window.draw(text); //writes welcome text
		}
		window.display(); //displays the full window
	}
	return EXIT_SUCCESS; //program ran successfully
}
