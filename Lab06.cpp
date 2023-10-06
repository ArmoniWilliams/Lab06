#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
	string background = "images1/backgrounds/prague.png";
	string foreground = "images1/characters/yoda.png";
	string greenscreenColor = "0, 255,0";

	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();

	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	Vector2u sz = foregroundImage.getSize();
	Color greenscreen = Color::Green; // Default green screen color

	if (sz.x > 0 && sz.y > 0) {
		greenscreen = foregroundImage.getPixel(0, 0);
	}

	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {
			// These two loops will run the code inside for each pixel in the background image
				// You can access the current pixel at x,y like so:
				Color example = foregroundImage.getPixel(x, y);
			// Color objects store the individual channel values like example.r example.g and example.b
				if (example.r >= greenscreen.r - 50 && example.r <= greenscreen.r + 50 && example.g >= greenscreen.g - 50 && example.g <= greenscreen.g + 50 && example.b >= greenscreen.b - 50 && example.b <= greenscreen.b + 50 ) {
					foregroundImage.setPixel(x, y, backgroundImage.getPixel(x, y)); // replace green screen color with pixel from the background image
				}
		}
	}
	// By default, just show the foreground image
	RenderWindow window(VideoMode(1024, 768), "Here's the output");
	Sprite sprite1;
	Texture tex1;
	tex1.loadFromImage(foregroundImage);
	sprite1.setTexture(tex1);

	window.clear();
	window.draw(sprite1);
	window.display();
	while (true);
}