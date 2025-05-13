#include<iostream>
#include<SFML/Graphics.hpp>
#include<ctime>
#include<random>
#include<chrono>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class Drawable {
public:
	virtual ~Drawable() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
};

class GameEntity {
protected:
	sf::Vector2f position;
public:
	GameEntity(float x = 0, float y = 0) : position(x, y) {}
	virtual ~GameEntity() = default;

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	sf::Vector2f getPosition() const {
		return position;
	}
};

class Tile : public GameEntity, public Drawable
{
private:
	int value;
	char letter;
	string state;
	bool isplaced;
	bool isTemporary; 
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	int x;
	int y;
public:
	Tile(int value, char letter, string state, int x, int y)
	{
		this->value = value;
		this->letter = letter;
		this->state = state;
		this->isplaced = false;
		this->isTemporary = false;
		this->x = x;
		this->y = y;
		if (state == "Normal") {
			tileTexture.loadFromFile("images/normal.png");
			tileSprite.setTexture(tileTexture);
		}
		else if (state == "Double Letter") {
			tileTexture.loadFromFile("images/double letter.png");
			tileSprite.setTexture(tileTexture);
		}
		else if (state == "Triple Letter") {
			tileTexture.loadFromFile("images/triple letter.png");
			tileSprite.setTexture(tileTexture);
		}
		else if (state == "Double Word") {
			tileTexture.loadFromFile("images/double word.png");
			tileSprite.setTexture(tileTexture);
		}
		else if (state == "Triple Word") {
			tileTexture.loadFromFile("images/triple word.png");
			tileSprite.setTexture(tileTexture);
		}
		else if (state == "Start") {
			tileTexture.loadFromFile("images/Start.png");
			tileSprite.setTexture(tileTexture);
		}
	}
	void setValue(int value)
	{
		this->value = value;
	}
	void setLetter(char letter)
	{
		this->letter = letter;
	}
	void setState(string state)
	{
		this->state = state;
	}
	int getValue()
	{
		return value;
	}
	char getLetter()
	{
		return letter;
	}
	string getState()
	{
		return state;
	}
	bool getIsPlaced()
	{
		return isplaced;
	}
	void setIsPlaced(bool isplaced)
	{
		this->isplaced = isplaced;
	}
	bool getIsTemporary()
	{
		return isTemporary;
	}
	void setIsTemporary(bool temp)
	{
		this->isTemporary = temp;
	}

	void draw(sf::RenderWindow& window) override {
		tileSprite.setPosition(x * 40, y * 40);
		window.draw(tileSprite);

		if (letter != ' ') {
			sf::Font font;
			font.loadFromFile("poppins-black.ttf");
			sf::Text text;
			text.setFont(font);
			text.setString(letter);
			text.setCharacterSize(20);
			text.setFillColor(sf::Color::Black);

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			text.setPosition(x * 40 + 20, y * 40 + 20);

			window.draw(text);
		}
	}

	void draw(sf::RenderWindow& window, int x, int y) 
	{
		tileSprite.setPosition(x, y);
		window.draw(tileSprite);

		if (letter != ' ') {
			sf::Font font;
			font.loadFromFile("poppins-black.ttf"); 
			sf::Text text;
			text.setFont(font);
			text.setString(letter);
			text.setCharacterSize(20);
			text.setFillColor(sf::Color::Black);

			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			text.setPosition(x + 20, y + 20); 

			window.draw(text);
		}
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};

class Board
{
private:
	Tile* tiles[15][15];
public:
	Board()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				string state;
				if ((i == 7) && (j == 7))
					state = "Start";
				else if ((i == 0 && (j == 0 || j == 7 || j == 14)) ||
					(i == 7 && (j == 0 || j == 14)) ||
					(i == 14 && (j == 0 || j == 7 || j == 14))) {
					state = "Triple Word";
				}

				else if ((i == 1 && (j == 5 || j == 9)) ||
					(i == 5 && (j == 1 || j == 5 || j == 9 || j == 13)) ||
					(i == 9 && (j == 1 || j == 5 || j == 9 || j == 13)) ||
					(i == 13 && (j == 5 || j == 9))) {
					state = "Triple Letter";
				}

				else if ((i == 1 && (j == 1 || j == 13)) ||
					(i == 2 && (j == 2 || j == 12)) ||
					(i == 3 && (j == 3 || j == 11)) ||
					(i == 4 && (j == 4 || j == 10)) ||
					(i == 10 && (j == 4 || j == 10)) ||
					(i == 11 && (j == 3 || j == 11)) ||
					(i == 12 && (j == 2 || j == 12)) ||
					(i == 13 && (j == 1 || j == 13))) {
					state = "Double Word";
				}

				else if ((i == 0 && (j == 3 || j == 11)) ||
					(i == 2 && (j == 6 || j == 8)) ||
					(i == 3 && (j == 0 || j == 7 || j == 14)) ||
					(i == 6 && (j == 2 || j == 6 || j == 8 || j == 12)) ||
					(i == 8 && (j == 2 || j == 6 || j == 8 || j == 12)) ||
					(i == 11 && (j == 0 || j == 7 || j == 14)) ||
					(i == 12 && (j == 6 || j == 8)) ||
					(i == 14 && (j == 3 || j == 11))) {
					state = "Double Letter";
				}

				else {
					state = "Normal";
				}
				tiles[i][j] = new Tile(0, ' ', state, i, j);
			}
		}
	}

	~Board()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				delete tiles[i][j];
			}
		}
	}

	void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				tiles[i][j]->draw(window, j * 40, i * 40);
			}
		}
	}

	Tile* getTile(int i, int j) {
		if (i >= 0 && i < 15 && j >= 0 && j < 15)
			return tiles[i][j];
		return nullptr;
	}

	void getTemporaryTiles(Tile* tempTiles[], int& count) {
		count = 0;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (tiles[i][j]->getIsTemporary()) {
					tempTiles[count++] = tiles[i][j];
				}
			}
		}
	}

	void clearTemporaryTiles() {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (tiles[i][j]->getIsTemporary()) {
					tiles[i][j]->setLetter(' ');
					tiles[i][j]->setValue(0);
					tiles[i][j]->setIsPlaced(false);
					tiles[i][j]->setIsTemporary(false);
				}
			}
		}
	}

	void confirmTemporaryTiles() {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (tiles[i][j]->getIsTemporary()) {
					tiles[i][j]->setIsTemporary(false);
				}
			}
		}
	}

	bool getWords(string& horizontalWord, string& verticalWord, int row, int col) {
		bool foundWord = false;
		horizontalWord = "";
		verticalWord = "";

		int startCol = col;
		while (startCol > 0 && (tiles[row][startCol - 1]->getIsPlaced() || tiles[row][startCol - 1]->getIsTemporary())) {
			startCol--;
		}

		for (int j = startCol; j < 15; j++) {
			if (tiles[row][j]->getIsPlaced() || tiles[row][j]->getIsTemporary()) {
				horizontalWord += tiles[row][j]->getLetter();
			}
			else {
				break;
			}
		}

		if (horizontalWord.length() > 1) {
			foundWord = true;
		}

		int startRow = row;
		while (startRow > 0 && (tiles[startRow - 1][col]->getIsPlaced() || tiles[startRow - 1][col]->getIsTemporary())) {
			startRow--;
		}

		for (int i = startRow; i < 15; i++) {
			if (tiles[i][col]->getIsPlaced() || tiles[i][col]->getIsTemporary()) {
				verticalWord += tiles[i][col]->getLetter();
			}
			else {
				break;
			}
		}

		if (verticalWord.length() > 1) {
			foundWord = true;
		}

		return foundWord;
	}

	void getAllWords(string words[], int& count) {
		count = 0;
		bool checked[15][15] = { false };

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (tiles[i][j]->getIsTemporary() && !checked[i][j]) {
					
					int startJ = j;
					while (startJ > 0 && (tiles[i][startJ - 1]->getIsPlaced() || tiles[i][startJ - 1]->getIsTemporary())) {
						startJ--;
					}

					string word = "";
					int k = startJ;
					while (k < 15 && (tiles[i][k]->getIsPlaced() || tiles[i][k]->getIsTemporary())) {
						word += tiles[i][k]->getLetter();
						checked[i][k] = true;
						k++;
					}

					if (word.length() > 1) {
						words[count++] = word;
					}
				}
			}
		}

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				checked[i][j] = false;
			}
		}

		for (int j = 0; j < 15; j++) {
			for (int i = 0; i < 15; i++) {
				if (tiles[i][j]->getIsTemporary() && !checked[i][j]) {
					int startI = i;
					while (startI > 0 && (tiles[startI - 1][j]->getIsPlaced() || tiles[startI - 1][j]->getIsTemporary())) {
						startI--;
					}
					string word = "";
					int k = startI;
					while (k < 15 && (tiles[k][j]->getIsPlaced() || tiles[k][j]->getIsTemporary())) {
						word += tiles[k][j]->getLetter();
						checked[k][j] = true;
						k++;
					}

					if (word.length() > 1) {
						words[count++] = word;
					}
				}
			}
		}
	}
};

class Piece 
{
private:
	int value;
	char letter;
	int amount;
	int remaining;
	sf::Texture pieceTexture;
	sf::Sprite pieceSprite;
public:

	Piece(int value, char letter, int amount)
	{
		this->value = value;
		this->letter = letter;
		this->amount = amount;
		this->remaining = amount;
	}
	int getValue()
	{
		return value;
	}
	char getLetter()
	{
		return letter;
	}
	int getAmount()
	{
		return amount;
	}

	int getRemaining()
	{
		return remaining;
	}

	void pieceOut()
	{
		remaining--;
	}

	void pieceIn()
	{
		remaining++;
	}

	void setSprite(string path)
	{
		pieceTexture.loadFromFile(path);
		pieceSprite.setTexture(pieceTexture);
	}
	void drawPiece(sf::RenderWindow& window, int x, int y)
	{
		pieceSprite.setPosition(x, y);
		window.draw(pieceSprite);
	}

	sf::FloatRect getGlobalBounds(int x, int y) {
		pieceSprite.setPosition(x, y);
		return pieceSprite.getGlobalBounds();
	}
};

class Bag
{
private:
	Piece* pieces[26];
public:
	Bag()
	{
		int values[26] = { 1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10 };
		int amounts[26] = { 9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1 };
		for (int i = 0; i < 26; i++)
		{
			pieces[i] = new Piece(values[i], 65 + i, amounts[i]);
			string p = "images/" + string(1, char(65 + i)) + ".png";
			pieces[i]->setSprite(p);
		}
	}

	~Bag()
	{
		for (int i = 0; i < 26; i++)
		{
			delete pieces[i];
		}
	}

	Piece* getPiece(int index) {
		if (index >= 0 && index < 26)
			return pieces[index];
		return nullptr;
	}
};

class Rack {
private:
	static int turn;
	Piece* pieces[7];     
	int number;           
	int filledAmount;     

public:
	Rack(int number) {
		this->number = number;
		this->filledAmount = 0;
		for (int i = 0; i < 7; i++) {
			pieces[i] = nullptr;
		}
		srand(time(0));
	}

	void fillRack(Bag& bag) {
		static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> dist(0, 25);

		for (int i = 0; i < 7; ++i) {
			if (pieces[i] == nullptr) {
				int tries = 0;
				while (tries < 50) {
					int index = dist(rng); 
					Piece* fromBag = bag.getPiece(index);
					if (fromBag && fromBag->getRemaining() > 0) {
						pieces[i] = new Piece(fromBag->getValue(), fromBag->getLetter(), 1);
						string path = "images/" + string(1, fromBag->getLetter()) + ".png";
						pieces[i]->setSprite(path);
						fromBag->pieceOut();
						filledAmount++;
						break;
					}
					tries++;
				}
			}
		}
	}

	void drawRack(sf::RenderWindow& window, int startX, int startY) {
		for (int i = 0; i < 7; ++i) {
			if (pieces[i]) {
				pieces[i]->drawPiece(window, startX + i * 50, startY);
			}
		}
	}

	Piece* getTileAt(int index) {
		if (index >= 0 && index < 7)
			return pieces[index];
		return nullptr;
	}

	void removeTileAt(int index) {
		if (index >= 0 && index < 7 && pieces[index]) {
			delete pieces[index];
			pieces[index] = nullptr;
			filledAmount--;
		}
	}

	void addLetter(char letter, int value) {
		for (int i = 0; i < 7; i++) {
			if (pieces[i] == nullptr) {
				pieces[i] = new Piece(value, letter, 1);
				string path = "images/" + string(1, letter) + ".png";
				pieces[i]->setSprite(path);
				filledAmount++;
				break;
			}
		}
	}

	int getNumber() {
		return number;
	}

	~Rack() {
		for (int i = 0; i < 7; ++i) {
			delete pieces[i];
		}
	}
};

int Rack::turn = 1;

class Button {
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

public:
	Button(float x, float y, float width, float height, sf::Font& font, string text) {
		shape.setPosition(sf::Vector2f(x, y));
		shape.setSize(sf::Vector2f(width, height));
		shape.setFillColor(sf::Color(100, 100, 100));
		shape.setOutlineThickness(2);
		shape.setOutlineColor(sf::Color::White);

		this->text.setFont(font);
		this->text.setString(text);
		this->text.setCharacterSize(18);
		this->text.setFillColor(sf::Color::White);

		sf::FloatRect textRect = this->text.getLocalBounds();
		this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		this->text.setPosition(x + width / 2.0f, y + height / 2.0f);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

		return shape.getGlobalBounds().contains(mousePosF);
	}

	void setBackColor(sf::Color color) {
		shape.setFillColor(color);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(text);
	}
};

class Dictionary {
private:
	string filename;
public:
	Dictionary(string filename) {
		this->filename = filename;
	}

	bool isValidWord(string word) {
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}

		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Failed to open dictionary file!" << endl;
			return false;
		}

		string dictWord;
		while (getline(file, dictWord)) {
			for (int i = 0; i < dictWord.length(); i++) {
				dictWord[i] = tolower(dictWord[i]);
			}
			while (!dictWord.empty() && isspace(dictWord.back())) {
				dictWord.pop_back();
			}

			if (word == dictWord) {
				file.close();
				return true;
			}
		}

		file.close();
		return false;
	}
	bool addWordToDictionary(string word) {
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}

		ofstream file(filename, ios::app);
		if (!file.is_open()) {
			cout << "Failed to open dictionary file for writing!" << endl;
			return false;
		}

		file << endl << word;
		file.close();
		return true;
	}
};

class YesNoDialog {
private:
	Button yesButton;
	Button noButton;
	sf::Text promptText;
	bool visible;
	string invalidWords;

public:
	YesNoDialog(sf::Font& font) :
		yesButton(700, 300, 80, 40, font, "Yes"),
		noButton(800, 300, 80, 40, font, "No") {

		promptText.setFont(font);
		promptText.setCharacterSize(16);
		promptText.setFillColor(sf::Color::White);
		promptText.setPosition(625, 250);
		visible = false;
		invalidWords = "";
	}

	void show(string words) {
		visible = true;
		invalidWords = words;
		promptText.setString("Add invalid word(s) to dictionary?\n" + words);
	}

	void hide() {
		visible = false;
	}

	bool isVisible() {
		return visible;
	}

	string getInvalidWords() {
		return invalidWords;
	}

	bool isYesClicked(sf::RenderWindow& window) {
		return visible && yesButton.isMouseOver(window);
	}

	bool isNoClicked(sf::RenderWindow& window) {
		return visible && noButton.isMouseOver(window);
	}

	void update(sf::RenderWindow& window) {
		if (visible) {
			if (yesButton.isMouseOver(window)) {
				yesButton.setBackColor(sf::Color(150, 150, 150));
			}
			else {
				yesButton.setBackColor(sf::Color(100, 100, 100));
			}

			if (noButton.isMouseOver(window)) {
				noButton.setBackColor(sf::Color(150, 150, 150));
			}
			else {
				noButton.setBackColor(sf::Color(100, 100, 100));
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		if (visible) {
			window.draw(promptText);
			yesButton.draw(window);
			noButton.draw(window);
		}
	}
};

int main()
{
	Board board;
	Bag bag;
	sf::RenderWindow window(sf::VideoMode(1100, 600), "Scrabble Game");
	window.setFramerateLimit(60);
	sf::Event event;
	Rack* racks[4];
	Dictionary dictionary("dictionary.txt"); 

	int selectedRackIndex = -1;
	int selectedRow = -1;
	int selectedCol = -1;
	int activeRack = 0; 
	int scores[4] = { 0, 0, 0, 0 };

	sf::Font font;
	if (!font.loadFromFile("poppins-black.ttf")) {
		cerr << "Failed to load font" << endl;
		return -1;
	}
	Button placeButton(700, 550, 100, 40, font, "Place");

	Button cancelButton(825, 550, 100, 40, font, "Cancel");

	YesNoDialog yesNoDialog(font);

	sf::Text statusText;
	statusText.setFont(font);
	statusText.setCharacterSize(18);
	statusText.setFillColor(sf::Color::White);
	statusText.setPosition(625, 100);
	statusText.setString("Select a tile on the board");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(650, 50);
	scoreText.setString("Player 1: 0 | Player 2: 0 | Player 3: 0 | Player 4: 0");

	for (int i = 0; i < 4; i++) {
		racks[i] = new Rack(i + 1);
		racks[i]->fillRack(bag);
	}


	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				if (yesNoDialog.isVisible()) {
					if (yesNoDialog.isYesClicked(window)) {
						
						string invalidWords = yesNoDialog.getInvalidWords();
						stringstream ss(invalidWords);
						string word;
						while (ss >> word) {
							dictionary.addWordToDictionary(word);
						}

						Tile* tempTiles[225];
						int tempCount = 0;
						board.getTemporaryTiles(tempTiles, tempCount);

						int moveScore = 0;

						string words[50]; 
						int wordCount = 0;
						board.getAllWords(words, wordCount);

						for (int w = 0; w < wordCount; w++) {
							int wordScore = 0;
							int wordMultiplier = 1;
							for (int i = 0; i < 15; i++) {
								for (int j = 0; j < 15; j++) {
									
									if (board.getTile(i, j)->getLetter() == words[w][0]) {
									
										bool foundHorizontal = true;
										for (int k = 0; k < words[w].length(); k++) {
											if (j + k >= 15 || board.getTile(i, j + k)->getLetter() != words[w][k]) {
												foundHorizontal = false;
												break;
											}
										}

										bool foundVertical = true;
										for (int k = 0; k < words[w].length(); k++) {
											if (i + k >= 15 || board.getTile(i + k, j)->getLetter() != words[w][k]) {
												foundVertical = false;
												break;
											}
										}

										if (foundHorizontal) {
											for (int k = 0; k < words[w].length(); k++) {
												Tile* currentTile = board.getTile(i, j + k);
												int letterValue = currentTile->getValue();

												if (currentTile->getIsTemporary()) {
													if (currentTile->getState() == "Double Letter") {
														letterValue *= 2;
													}
													else if (currentTile->getState() == "Triple Letter") {
														letterValue *= 3;
													}

													if (currentTile->getState() == "Double Word") {
														wordMultiplier *= 2;
													}
													else if (currentTile->getState() == "Triple Word") {
														wordMultiplier *= 3;
													}
												}
												wordScore += letterValue;
											}
											break;
										}
										else if (foundVertical) {
											for (int k = 0; k < words[w].length(); k++) {
												Tile* currentTile = board.getTile(i + k, j);
												int letterValue = currentTile->getValue();
												if (currentTile->getIsTemporary()) {
													if (currentTile->getState() == "Double Letter") {
														letterValue *= 2;
													}
													else if (currentTile->getState() == "Triple Letter") {
														letterValue *= 3;
													}
													if (currentTile->getState() == "Double Word") {
														wordMultiplier *= 2;
													}
													else if (currentTile->getState() == "Triple Word") {
														wordMultiplier *= 3;
													}
												}
												wordScore += letterValue;
											}
											break; 
										}
									}
								}
							}
							wordScore *= wordMultiplier;
							moveScore += wordScore;
						}
						scores[activeRack] += moveScore;

						board.confirmTemporaryTiles();
						statusText.setString("Words added to dictionary! +" + to_string(moveScore) + " points");

						scoreText.setString("Player 1: " + to_string(scores[0]) +
							" | Player 2: " + to_string(scores[1]) +
							" | Player 3: " + to_string(scores[2]) +
							" | Player 4: " + to_string(scores[3]));

						racks[activeRack]->fillRack(bag);
						activeRack = (activeRack + 1) % 4;

						yesNoDialog.hide();
					}
					else if (yesNoDialog.isNoClicked(window)) {
						Tile* tempTiles[225];
						int tempCount = 0;
						board.getTemporaryTiles(tempTiles, tempCount);

						for (int i = 0; i < tempCount; i++) {
							char letter = tempTiles[i]->getLetter();
							int value = tempTiles[i]->getValue();
							racks[activeRack]->addLetter(letter, value);
						}

						board.clearTemporaryTiles();
						statusText.setString("Move canceled. Try again.");

						yesNoDialog.hide();
					}
				}

				else if (placeButton.isMouseOver(window)) {
					
					Tile* tempTiles[225]; 
					int tempCount = 0;
					board.getTemporaryTiles(tempTiles, tempCount);

					if (tempCount > 0) {
						string words[50];
						int wordCount = 0;
						board.getAllWords(words, wordCount);

						bool allValid = true;
						string invalidWords = "";

						for (int i = 0; i < wordCount; i++) {
							if (!dictionary.isValidWord(words[i])) {
								allValid = false;
								invalidWords += words[i] + " ";
							}
						}

						if (allValid) {
							int moveScore = 0;

							string words[50]; 
							int wordCount = 0;
							board.getAllWords(words, wordCount);

							for (int w = 0; w < wordCount; w++) {
								int wordScore = 0;
								int wordMultiplier = 1;
								for (int i = 0; i < 15; i++) {
									for (int j = 0; j < 15; j++) {
										if (board.getTile(i, j)->getLetter() == words[w][0]) {
											bool foundHorizontal = true;
											for (int k = 0; k < words[w].length(); k++) {
												if (j + k >= 15 || board.getTile(i, j + k)->getLetter() != words[w][k]) {
													foundHorizontal = false;
													break;
												}
											}

											bool foundVertical = true;
											for (int k = 0; k < words[w].length(); k++) {
												if (i + k >= 15 || board.getTile(i + k, j)->getLetter() != words[w][k]) {
													foundVertical = false;
													break;
												}
											}

											if (foundHorizontal) {
												for (int k = 0; k < words[w].length(); k++) {
													Tile* currentTile = board.getTile(i, j + k);
													int letterValue = currentTile->getValue();

													if (currentTile->getIsTemporary()) {
														if (currentTile->getState() == "Double Letter") {
															letterValue *= 2;
														}
														else if (currentTile->getState() == "Triple Letter") {
															letterValue *= 3;
														}

														if (currentTile->getState() == "Double Word") {
															wordMultiplier *= 2;
														}
														else if (currentTile->getState() == "Triple Word") {
															wordMultiplier *= 3;
														}
													}
													wordScore += letterValue;
												}
												break; 
											}
											else if (foundVertical) {
												for (int k = 0; k < words[w].length(); k++) {
													Tile* currentTile = board.getTile(i + k, j);
													int letterValue = currentTile->getValue();

													if (currentTile->getIsTemporary()) {
														if (currentTile->getState() == "Double Letter") {
															letterValue *= 2;
														}
														else if (currentTile->getState() == "Triple Letter") {
															letterValue *= 3;
														}

														if (currentTile->getState() == "Double Word") {
															wordMultiplier *= 2;
														}
														else if (currentTile->getState() == "Triple Word") {
															wordMultiplier *= 3;
														}
													}
													wordScore += letterValue;
												}
												break;
											}
										}
									}
								}

								wordScore *= wordMultiplier;
								moveScore += wordScore;
							}

							scores[activeRack] += moveScore;

							scoreText.setString("Player 1: " + to_string(scores[0]) +
								" | Player 2: " + to_string(scores[1]) +
								" | Player 3: " + to_string(scores[2]) +
								" | Player 4: " + to_string(scores[3]));
							board.confirmTemporaryTiles();
							statusText.setString("Valid word(s)! +" + to_string(moveScore) + " points");

							racks[activeRack]->fillRack(bag);

							activeRack = (activeRack + 1) % 4;
						}
						else {
							yesNoDialog.show(invalidWords);
							statusText.setString("Invalid word(s). Add to dictionary?");
						}

						selectedRow = -1;
						selectedCol = -1;
						selectedRackIndex = -1;
					}
					else {
						statusText.setString("No tiles placed yet!");
					}
				}
				else if (cancelButton.isMouseOver(window)) {
					Tile* tempTiles[225];
					int tempCount = 0;
					board.getTemporaryTiles(tempTiles, tempCount);

					for (int i = 0; i < tempCount; i++) {
						char letter = tempTiles[i]->getLetter();
						int value = tempTiles[i]->getValue();
						racks[activeRack]->addLetter(letter, value);
					}

					board.clearTemporaryTiles();
					statusText.setString("Move canceled. Try again.");

					selectedRow = -1;
					selectedCol = -1;
					selectedRackIndex = -1;
				}
				else if (mousePos.x < 600 && mousePos.y < 600) {
					int row = mousePos.y / 40;
					int col = mousePos.x / 40;

					if (row >= 0 && row < 15 && col >= 0 && col < 15) {
						Tile* tile = board.getTile(row, col);
						if (!tile->getIsPlaced()) {
							selectedRow = row;
							selectedCol = col;
							statusText.setString("Tile selected. Now select a piece from your rack.");
						}
						else {
							statusText.setString("This tile is already occupied.");
						}
					}
				}
				else if (selectedRow != -1 && selectedCol != -1) {
					for (int i = 0; i < 7; ++i) {
						Piece* p = racks[activeRack]->getTileAt(i);
						if (p) {
							int rackY = activeRack * 80 + 200;
							sf::FloatRect bounds = p->getGlobalBounds(625 + i * 50, rackY);

							if (bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
								selectedRackIndex = i;

								Tile* tile = board.getTile(selectedRow, selectedCol);
								tile->setLetter(p->getLetter());
								tile->setValue(p->getValue());
								tile->setIsPlaced(true);
								tile->setIsTemporary(true);

								racks[activeRack]->removeTileAt(selectedRackIndex);

								selectedRow = -1;
								selectedCol = -1;
								selectedRackIndex = -1;

								statusText.setString("Piece placed. Select another tile or click Place.");
								break;
							}
						}
					}
				}
			}
		}

		if (placeButton.isMouseOver(window)) {
			placeButton.setBackColor(sf::Color(150, 150, 150));
		}
		else {
			placeButton.setBackColor(sf::Color(100, 100, 100));
		}

		if (cancelButton.isMouseOver(window)) {
			cancelButton.setBackColor(sf::Color(150, 150, 150));
		}
		else {
			cancelButton.setBackColor(sf::Color(100, 100, 100));
		}

		yesNoDialog.update(window);

		window.clear(sf::Color::Blue);
		board.draw(window);
		for (int i = 0; i < 4; i++) {
			racks[i]->drawRack(window, 625, i * 80 + 200);
			if (i == activeRack) {
				sf::RectangleShape highlight;
				highlight.setSize(sf::Vector2f(350, 40));
				highlight.setPosition(625, i * 80 + 200);
				highlight.setFillColor(sf::Color::Transparent);
				highlight.setOutlineColor(sf::Color::Yellow);
				highlight.setOutlineThickness(2);
				window.draw(highlight);
			}
		}
		if (selectedRow != -1 && selectedCol != -1) {
			sf::RectangleShape highlight;
			highlight.setSize(sf::Vector2f(40, 40));
			highlight.setPosition(selectedCol * 40, selectedRow * 40);
			highlight.setFillColor(sf::Color::Transparent);
			highlight.setOutlineColor(sf::Color::Yellow);
			highlight.setOutlineThickness(2);
			window.draw(highlight);
		}

		placeButton.draw(window);
		cancelButton.draw(window);
		window.draw(statusText);
		window.draw(scoreText);
		yesNoDialog.draw(window);

		window.display();
	}

	for (int i = 0; i < 4; i++) {
		delete racks[i];
	}

	return 0;
}