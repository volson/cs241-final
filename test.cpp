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
	float get_x() { //returns x coordinate
		return (Coord::x);
	}

	float get_y() { //returns y coordinate
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

public:

	//constructor for our invisible box
	tilePos(float xmin, float xmax, float ymin, float ymax) {
		tilePos::xmin = xmin;
		tilePos::xmax = xmax;
		tilePos::ymin = ymin;
		tilePos::ymax = ymax;
	}

	tilePos() {

	}

	float get_xmin() { //returns minimum x value of tile
		return (tilePos::xmin);
	}

	float get_xmax() { //returns maximum x value of tile
		return (tilePos::xmax);
	}

	float get_ymin() { //returns minimum y value of tile
		return (tilePos::ymin);
	}

	float get_ymax() { //returns maximum y value of tile
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
	bool get_captured() {
		return (Piece::captured);
	}

	//returns if the piece belongs to the player
	bool get_player() {
		return (Piece::player);
	}

	//returns the visible circle to be drawn
	sf::CircleShape get_node() {
		return (Piece::node);
	}

	//returns if the piece is a queen
	bool get_queen() {
		return(Piece::queen);
	}

	//queens a checkers piece
	void set_queen() {
		Piece::queen = true;
	}
	//sets the position of the checkers piece
	void set_pos(Coord xy) {
		Piece::c = xy;
		Piece::node.setPosition(xy.get_x(), xy.get_y());
	}
	//returns the position of the checkers piece
	Coord get_pos() {
		return(c);
	}
	//returns the tile that the checkers piece is on
	tilePos get_tilePos() {
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
	text.setString("Welcome!\nThis is a checkers AI.\nTo play, click on one of your pieces\nand move it to the desired location.");

	sf::Text q; //the Q that marks all queens
	q.setString("Q");
	text.setFont(font);
	q.setStyle(sf::Text::Bold);

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
	string name; //remembers the name of the piece that is being moved

	sf::Clock clock; //tracks the time

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

	//all the positions!!!! i could have done this in an array...
	Coord pos1a;
	pos1a.set_x(65);
	pos1a.set_y(365);
	Coord pos1b;
	pos1b.set_x(185);
	pos1b.set_y(365);
	Coord pos1c;
	pos1c.set_x(305);
	pos1c.set_y(365);
	Coord pos1d;
	pos1d.set_x(425);
	pos1d.set_y(365);
	Coord pos1e;
	pos1e.set_x(125);
	pos1e.set_y(425);
	Coord pos1f;
	pos1f.set_x(245);
	pos1f.set_y(425);
	Coord pos1g;
	pos1g.set_x(365);
	pos1g.set_y(425);
	Coord pos1h;
	pos1h.set_x(485);
	pos1h.set_y(425);
	Coord pos1i;
	pos1i.set_x(65);
	pos1i.set_y(485);
	Coord pos1j;
	pos1j.set_x(185);
	pos1j.set_y(485);
	Coord pos1k;
	pos1k.set_x(305);
	pos1k.set_y(485);
	Coord pos1l;
	pos1l.set_x(425);
	pos1l.set_y(485);

	Coord pos2a;
	pos2a.set_x(125);
	pos2a.set_y(65);
	Coord pos2b;
	pos2b.set_x(245);
	pos2b.set_y(65);
	Coord pos2c;
	pos2c.set_x(365);
	pos2c.set_y(65);
	Coord pos2d;
	pos2d.set_x(485);
	pos2d.set_y(65);
	Coord pos2e;
	pos2e.set_x(65);
	pos2e.set_y(125);
	Coord pos2f;
	pos2f.set_x(185);
	pos2f.set_y(125);
	Coord pos2g;
	pos2g.set_x(305);
	pos2g.set_y(125);
	Coord pos2h;
	pos2h.set_x(425);
	pos2h.set_y(125);
	Coord pos2i;
	pos2i.set_x(125);
	pos2i.set_y(185);
	Coord pos2j;
	pos2j.set_x(245);
	pos2j.set_y(185);
	Coord pos2k;
	pos2k.set_x(365);
	pos2k.set_y(185);
	Coord pos2l;
	pos2l.set_x(485);
	pos2l.set_y(185);

	//allthe pieces!!!!! definitely should have been an array!
	Piece Player1a(pos1a, true, true, circle);
	Piece Player1b(pos1b, true, true, circle);
	Piece Player1c(pos1c, true, true, circle);
	Piece Player1d(pos1d, true, true, circle);
	Piece Player1e(pos1e, true, true, circle);
	Piece Player1f(pos1f, true, true, circle);
	Piece Player1g(pos1g, true, true, circle);
	Piece Player1h(pos1h, true, true, circle);
	Piece Player1i(pos1i, true, true, circle);
	Piece Player1j(pos1j, true, true, circle);
	Piece Player1k(pos1k, true, true, circle);
	Piece Player1l(pos1l, true, true, circle);

	Piece Player2a(pos2a, false, false, circle);
	Piece Player2b(pos2b, false, false, circle);
	Piece Player2c(pos2c, false, false, circle);
	Piece Player2d(pos2d, false, false, circle);
	Piece Player2e(pos2e, false, false, circle);
	Piece Player2f(pos2f, false, false, circle);
	Piece Player2g(pos2g, false, false, circle);
	Piece Player2h(pos2h, false, false, circle);
	Piece Player2i(pos2i, false, false, circle);
	Piece Player2j(pos2j, false, false, circle);
	Piece Player2k(pos2k, false, false, circle);
	Piece Player2l(pos2l, false, false, circle);

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
				tilePos(60+(i*60), 120+(i*60), 60+(j*60), 120+(j*60)); //draw the invisible representations of tiles
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //if you click your mouse
			startx = sf::Mouse::getPosition(window).x; //get a starting position
			starty = sf::Mouse::getPosition(window).y;
			//find which checker piece got clicked with lots of if statements
			if (startx<=Player1a.get_pos().get_x()+25 && startx>=Player1a.get_pos().get_x()-25 && starty<=Player1a.get_pos().get_y()+25 && starty<=Player1a.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1a);
				name = "Player1a";
			}
			else if (startx<=Player1b.get_pos().get_x()+25 && startx>=Player1b.get_pos().get_x()-25 && starty<=Player1b.get_pos().get_y()+25 && starty<=Player1b.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1b);
				name = "Player1b";
			}
			else if (startx<=Player1c.get_pos().get_x()+25 && startx>=Player1c.get_pos().get_x()-25 && starty<=Player1c.get_pos().get_y()+25 && starty<=Player1c.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1c);
				name = "Player1c";
			}
			else if (startx<=Player1d.get_pos().get_x()+25 && startx>=Player1d.get_pos().get_x()-25 && starty<=Player1d.get_pos().get_y()+25 && starty<=Player1d.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1d);
				name = "Player1d";
			}
			else if (startx<=Player1e.get_pos().get_x()+25 && startx>=Player1e.get_pos().get_x()-25 && starty<=Player1e.get_pos().get_y()+25 && starty<=Player1e.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1e);
				name = "Player1e";
			}
			else if (startx<=Player1f.get_pos().get_x()+25 && startx>=Player1f.get_pos().get_x()-25 && starty<=Player1f.get_pos().get_y()+25 && starty<=Player1f.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1f);
				name = "Player1f";
			}
			else if (startx<=Player1g.get_pos().get_x()+25 && startx>=Player1g.get_pos().get_x()-25 && starty<=Player1g.get_pos().get_y()+25 && starty<=Player1g.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1g);
				name = "Player1g";
			}
			else if (startx<=Player1h.get_pos().get_x()+25 && startx>=Player1h.get_pos().get_x()-25 && starty<=Player1h.get_pos().get_y()+25 && starty<=Player1h.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1h);
				name = "Player1h";
			}
			else if (startx<=Player1i.get_pos().get_x()+25 && startx>=Player1i.get_pos().get_x()-25 && starty<=Player1i.get_pos().get_y()+25 && starty<=Player1i.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1i);
				name = "Player1i";
			}
			else if (startx<=Player1j.get_pos().get_x()+25 && startx>=Player1j.get_pos().get_x()-25 && starty<=Player1j.get_pos().get_y()+25 && starty<=Player1j.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1j);
				name = "Player1j";
			}
			else if (startx<=Player1k.get_pos().get_x()+25 && startx>=Player1k.get_pos().get_x()-25 && starty<=Player1k.get_pos().get_y()+25 && starty<=Player1k.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1k);
				name = "Player1k";
			}
			else if (startx<=Player1l.get_pos().get_x()+25 && startx>=Player1l.get_pos().get_x()-25 && starty<=Player1l.get_pos().get_y()+25 && starty<=Player1l.get_pos().get_y()-25) {
				dragged = true;
				moved.set_piece(Player1l);
				name = "Player1l";
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
			if (name == "Player1a")
				Player1a.set_piece(moved);
			else if (name == "Player1b")
				Player1b.set_piece(moved);
			else if (name == "Player1c")
				Player1c.set_piece(moved);
			else if (name == "Player1d")
				Player1d.set_piece(moved);
			else if (name == "Player1e")
				Player1e.set_piece(moved);
			else if (name == "Player1f")
				Player1f.set_piece(moved);
			else if (name == "Player1g")
				Player1g.set_piece(moved);
			else if (name == "Player1h")
				Player1h.set_piece(moved);
			else if (name == "Player1i")
				Player1i.set_piece(moved);
			else if (name == "Player1j")
				Player1j.set_piece(moved);
			else if (name == "Player1k")
				Player1k.set_piece(moved);
			else if (name == "Player1l")
				Player1l.set_piece(moved);
		}
		//draws the checkers pieces
		window.draw(Player1a.get_node());
		if (Player1a.get_queen()) { //if the checkers piece is queened, writes a "Q" on it
			q.setPosition(Player1a.get_pos().get_x(), Player1a.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1b.get_node());
		if (Player1b.get_queen()) {
			q.setPosition(Player1b.get_pos().get_x(), Player1b.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1c.get_node());
		if (Player1c.get_queen()) {
			q.setPosition(Player1c.get_pos().get_x(), Player1c.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1d.get_node());
		if (Player1d.get_queen()) {
			q.setPosition(Player1d.get_pos().get_x(), Player1d.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1e.get_node());
		if (Player1e.get_queen()) {
			q.setPosition(Player1e.get_pos().get_x(), Player1e.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1f.get_node());
		if (Player1f.get_queen()) {
			q.setPosition(Player1f.get_pos().get_x(), Player1f.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1g.get_node());
		if (Player1g.get_queen()) {
			q.setPosition(Player1g.get_pos().get_x(), Player1g.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1h.get_node());
		if (Player1h.get_queen()) {
			q.setPosition(Player1h.get_pos().get_x(), Player1h.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1i.get_node());
		if (Player1i.get_queen()) {
			q.setPosition(Player1i.get_pos().get_x(), Player1i.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1j.get_node());
		if (Player1j.get_queen()) {
			q.setPosition(Player1j.get_pos().get_x(), Player1j.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1k.get_node());
		if (Player1k.get_queen()) {
			q.setPosition(Player1k.get_pos().get_x(), Player1k.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player1l.get_node());
		if (Player1l.get_queen()) {
			q.setPosition(Player1l.get_pos().get_x(), Player1l.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2a.get_node());
		if (Player2a.get_queen()) {
			q.setPosition(Player2a.get_pos().get_x(), Player2a.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2b.get_node());
		if (Player2b.get_queen()) {
			q.setPosition(Player2b.get_pos().get_x(), Player2b.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2c.get_node());
		if (Player2c.get_queen()) {
			q.setPosition(Player2c.get_pos().get_x(), Player2c.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2d.get_node());
		if (Player2d.get_queen()) {
			q.setPosition(Player2d.get_pos().get_x(), Player2d.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2e.get_node());
		if (Player2e.get_queen()) {
			q.setPosition(Player2e.get_pos().get_x(), Player2e.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2f.get_node());
		if (Player2f.get_queen()) {
			q.setPosition(Player2f.get_pos().get_x(), Player2f.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2g.get_node());
		if (Player2g.get_queen()) {
			q.setPosition(Player2g.get_pos().get_x(), Player2g.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2h.get_node());
		if (Player2h.get_queen()) {
			q.setPosition(Player2h.get_pos().get_x(), Player2h.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2i.get_node());
		if (Player2i.get_queen()) {
			q.setPosition(Player2i.get_pos().get_x(), Player2i.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2j.get_node());
		if (Player2j.get_queen()) {
			q.setPosition(Player2j.get_pos().get_x(), Player2j.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2k.get_node());
		if (Player2k.get_queen()) {
			q.setPosition(Player2k.get_pos().get_x(), Player2k.get_pos().get_y());
			window.draw(q);
		}
		window.draw(Player2l.get_node());
		if (Player2l.get_queen()) {
			q.setPosition(Player2l.get_pos().get_x(), Player2l.get_pos().get_y());
			window.draw(q);
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
