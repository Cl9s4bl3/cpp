#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <nlohmann/json.hpp>

#define FILE "layout.json"

using json = nlohmann::json;

int del = 0;

std::vector<std::string> words;

void game() {
    std::vector<std::string> full;
    
    json data;

    std::ifstream inFile(FILE);
    inFile >> data;
    inFile.close();

    std::srand(std::time(0));

    std::string randomWord = words[std::rand() % words.size()];

    while (true) {
        std::string chari;
        std::string charo;
        std::string word;

        for (auto& item : full) {
            std::cout << item;
        }

        for (auto& character : full) {
            word += character;
        }

        if (word == randomWord) {
            std::cout << "\n\nYou've successfully finished this round. You've used 'del' " << del << " times.\n" << std::endl;
            del = 0;
            game();
            break;
        }
        
        

        std::cout << "\n\nWord to guess: " << randomWord << "\n> ";
        std::getline(std::cin, chari);

        if (chari == "del") {
            if (full.size() <= 0) {
                std::cout << "\nNo characters added yet." << std::endl;
            }
            else {
                full.pop_back();
                del++;
            }
            
            continue;
        }

        if (data.contains(chari)) {
            charo = data[chari];
        }
        else {
            continue;
        }

        full.push_back(charo);
    }
}

int main()
{

    json data = {
        /*{"a", "a"},
        { "b", "b" },
        { "c", "c" },
        { "d", "d" },
        { "e", "e" },
        { "f", "f" },
        { "g", "g" },
        { "h", "h" },
        { "i", "i" },
        { "j", "j" },
        { "k", "k" },
        { "l", "l" },
        { "m", "m" },
        { "n", "n" },
        { "o", "o" },
        { "p", "p" },
        { "q", "q" },
        { "r", "r" },
        { "s", "s" },
        { "t", "t" },
        { "u", "u" },
        { "v", "v" },
        { "w", "w" },
        { "x", "x" },
        { "y", "y" },
        { "z", "z" }*/

        { "a", "m" },
        { "b", "x" },
        { "c", "j" },
        { "d", "e" },
        { "e", "q" },
        { "f", "z" },
        { "g", "b" },
        { "h", "u" },
        { "i", "k" },
        { "j", "a" },
        { "k", "y" },
        { "l", "d" },
        { "m", "h" },
        { "n", "r" },
        { "o", "s" },
        { "p", "f" },
        { "q", "c" },
        { "r", "w" },
        { "s", "o" },
        { "t", "v" },
        { "u", "i" },
        { "v", "l" },
        { "w", "g" },
        { "x", "t" },
        { "y", "p" },
        { "z", "n" }
    };

    std::ofstream outFile(FILE);
    outFile << data.dump(4);
    outFile.close();

    words.push_back("aardvark"); words.push_back("abacus"); words.push_back("apple"); words.push_back("astronaut"); words.push_back("ball"); words.push_back("balloon"); words.push_back("banana"); words.push_back("bicycle"); words.push_back("candle"); words.push_back("cat"); words.push_back("chrysanthemum"); words.push_back("daisy"); words.push_back("dolphin"); words.push_back("dragon"); words.push_back("elephant"); words.push_back("emerald"); words.push_back("falcon"); words.push_back("forest"); words.push_back("gazelle"); words.push_back("giraffe"); words.push_back("guitar"); words.push_back("hamburger"); words.push_back("honey"); words.push_back("iceberg"); words.push_back("igloo"); words.push_back("jacket"); words.push_back("jellyfish"); words.push_back("kangaroo"); words.push_back("kite"); words.push_back("lantern"); words.push_back("lemon"); words.push_back("lighthouse"); words.push_back("mango"); words.push_back("mermaid"); words.push_back("mountain"); words.push_back("nebula"); words.push_back("notebook"); words.push_back("octopus"); words.push_back("opal"); words.push_back("parrot"); words.push_back("penguin"); words.push_back("quasar"); words.push_back("quilt"); words.push_back("rainbow"); words.push_back("rocket"); words.push_back("sapphire"); words.push_back("squirrel"); words.push_back("starfish"); words.push_back("tiger"); words.push_back("tornado"); words.push_back("umbrella"); words.push_back("unicorn"); words.push_back("vase"); words.push_back("violin"); words.push_back("volcano"); words.push_back("waterfall"); words.push_back("whale"); words.push_back("xenon"); words.push_back("xylophone"); words.push_back("yacht"); words.push_back("yeti"); words.push_back("zebra"); words.push_back("zeppelin"); words.push_back("antelope"); words.push_back("avocado"); words.push_back("balloon"); words.push_back("camera"); words.push_back("dragon"); words.push_back("eagle"); words.push_back("flower"); words.push_back("giraffe"); words.push_back("hamburger"); words.push_back("igloo"); words.push_back("jungle"); words.push_back("kite"); words.push_back("lantern"); words.push_back("mango"); words.push_back("night"); words.push_back("octopus"); words.push_back("penguin"); words.push_back("quilt"); words.push_back("rocket"); words.push_back("squirrel"); words.push_back("tiger"); words.push_back("unicorn"); words.push_back("vase"); words.push_back("waterfall"); words.push_back("x-ray"); words.push_back("yogurt"); words.push_back("zeppelin"); words.push_back("antelope"); words.push_back("butterfly"); words.push_back("cactus"); words.push_back("daisy"); words.push_back("emerald"); words.push_back("fountain"); words.push_back("galaxy"); words.push_back("hedgehog"); words.push_back("iguana"); words.push_back("jewel"); words.push_back("koala"); words.push_back("lighthouse"); words.push_back("mermaid"); words.push_back("nebula"); words.push_back("orchid"); words.push_back("peacock"); words.push_back("quokka"); words.push_back("robot"); words.push_back("sapphire"); words.push_back("tornado"); words.push_back("utopia"); words.push_back("volcano"); words.push_back("windmill"); words.push_back("xenon"); words.push_back("yeti"); words.push_back("zeppelin"); words.push_back("amethyst"); words.push_back("bamboo"); words.push_back("coral"); words.push_back("dolphin"); words.push_back("emerald"); words.push_back("falcon"); words.push_back("gazelle"); words.push_back("horizon"); words.push_back("iceberg"); words.push_back("jellyfish"); words.push_back("kiwi"); words.push_back("lotus"); words.push_back("meteor"); words.push_back("nebula"); words.push_back("opal"); words.push_back("parrot"); words.push_back("quasar"); words.push_back("rainforest"); words.push_back("starfish"); words.push_back("tulip"); words.push_back("universe"); words.push_back("vortex"); words.push_back("whirlpool"); words.push_back("xenon"); words.push_back("yarn"); words.push_back("zephyr"); words.push_back("apple"); words.push_back("bicycle"); words.push_back("candle"); words.push_back("dolphin"); words.push_back("elephant"); words.push_back("forest"); words.push_back("guitar"); words.push_back("honey"); words.push_back("island"); words.push_back("jacket"); words.push_back("kangaroo"); words.push_back("lemon"); words.push_back("mountain"); words.push_back("notebook"); words.push_back("ocean"); words.push_back("piano"); words.push_back("quartz"); words.push_back("rainbow"); words.push_back("sunflower"); words.push_back("turtle"); words.push_back("umbrella"); words.push_back("violin"); words.push_back("whale"); words.push_back("xylophone"); words.push_back("yacht"); words.push_back("zebra"); words.push_back("avocado"); words.push_back("balloon"); words.push_back("camera"); words.push_back("dragon"); words.push_back("eagle"); words.push_back("flower"); words.push_back("giraffe"); words.push_back("hamburger"); words.push_back("igloo"); words.push_back("jungle"); words.push_back("kite"); words.push_back("lantern"); words.push_back("mango"); words.push_back("night"); words.push_back("octopus"); words.push_back("penguin"); words.push_back("quilt"); words.push_back("rocket"); words.push_back("squirrel"); words.push_back("tiger"); words.push_back("unicorn"); words.push_back("vase"); words.push_back("waterfall"); words.push_back("x-ray"); words.push_back("yogurt"); words.push_back("zeppelin"); words.push_back("antelope"); words.push_back("butterfly"); words.push_back("cactus"); words.push_back("daisy"); words.push_back("emerald"); words.push_back("fountain"); words.push_back("galaxy"); words.push_back("hedgehog"); words.push_back("iguana"); words.push_back("jewel"); words.push_back("koala"); words.push_back("lighthouse"); words.push_back("mermaid"); words.push_back("nebula"); words.push_back("orchid"); words.push_back("peacock"); words.push_back("quokka"); words.push_back("robot"); words.push_back("sapphire"); words.push_back("tornado"); words.push_back("utopia"); words.push_back("volcano"); words.push_back("windmill"); words.push_back("xenon"); words.push_back("yeti"); words.push_back("zeppelin"); words.push_back("amethyst"); words.push_back("bamboo"); words.push_back("coral"); words.push_back("dolphin"); words.push_back("emerald"); words.push_back("falcon"); words.push_back("gazelle"); words.push_back("horizon"); words.push_back("iceberg"); words.push_back("jellyfish"); words.push_back("kiwi"); words.push_back("lotus"); words.push_back("meteor"); words.push_back("nebula"); words.push_back("opal"); words.push_back("parrot"); words.push_back("quasar"); words.push_back("rainforest"); words.push_back("starfish"); words.push_back("tulip"); words.push_back("universe"); words.push_back("vortex"); words.push_back("whirlpool"); words.push_back("xenon"); words.push_back("yarn"); words.push_back("zephyr"); words.push_back("apple"); words.push_back("bicycle"); words.push_back("candle"); words.push_back("dolphin"); words.push_back("elephant"); words.push_back("forest"); words.push_back("guitar"); words.push_back("honey"); words.push_back("island"); words.push_back("jacket"); words.push_back("kangaroo"); words.push_back("lemon"); words.push_back("mountain"); words.push_back("notebook"); words.push_back("ocean"); words.push_back("piano"); words.push_back("quartz"); words.push_back("rainbow"); words.push_back("sunflower"); words.push_back("turtle"); words.push_back("umbrella"); words.push_back("violin"); words.push_back("whale"); words.push_back("xylophone"); words.push_back("yacht"); words.push_back("zebra"); words.push_back("avocado"); words.push_back("balloon"); words.push_back("camera"); words.push_back("dragon"); words.push_back("eagle"); words.push_back("flower"); words.push_back("giraffe"); words.push_back("hamburger"); words.push_back("igloo"); words.push_back("jungle"); words.push_back("kite"); words.push_back("lantern"); words.push_back("mango"); words.push_back("night"); words.push_back("octopus");

    game();

    return 0;
}