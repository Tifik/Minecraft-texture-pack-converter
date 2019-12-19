#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include "funk.h"
#include "MTC.h"


//#include <cstdlib>
//#include <fstream>

using namespace cv;
using namespace boost::filesystem;
namespace fs = boost::filesystem;

std::string java;
std::string des;
std::string pname;
std::string pack;
std::vector<std::string> newdir;
std::vector<std::string> dir;
std::vector<std::string> java_folder;
std::vector<std::string> win_folder;
std::vector<std::string> file;
std::vector< std::vector<int> > apos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > npos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > pixel{ 2, std::vector<int>(30, 0) };
int it = 1;
int itx = 0;
bool check = true;

int main(int argc, char* argv[])
//namespace Converter
{
	

	java = "C:\\Users\\jojo\\Desktop\\ChromaHills-128x-1.12";
	des = "E:\\minecraft_converter";
	pname = "chroma_hills";

	/*std::cout << "typ in the directory to the texturepack folder: ";
	std::getline(std::cin, java);
	std::cout << "typ in the destination folder: " ;
	std::getline(std::cin , des);
	std::cout << "typ in the texturepack's name: ";
	std::getline(std::cin, pname);*/

	newdir = { java };
	file = { java };
	pack = des + "\\" + pname;

	//calculate the rows and collums to get the right ratio
	Mat temp = imread(java + "\\assets\\minecraft\\textures\\items\\clock_00.png", IMREAD_UNCHANGED);
	Mat nclock(temp.rows * 64, temp.cols, CV_8UC4, Scalar(0, 0, 0, 0)); //länge und breite sind variabel

	temp = imread(java + "\\assets\\minecraft\\textures\\items\\compass_00.png", IMREAD_UNCHANGED);
	Mat ncompas(temp.rows * 32, temp.cols, CV_8UC4, Scalar(0, 0, 0, 0)); //länge und breite sind variabel

	temp = imread(java + "\\assets\\minecraft\\textures\\entity\\sheep\\sheep.png", IMREAD_UNCHANGED);
	int sheep_row = temp.rows;//don't delet
	Mat sheep(temp.rows * 2, temp.cols, CV_8UC4, Scalar(0, 0, 0, 0)); //länge und breite sind variabel

	temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_top_normal.png", IMREAD_UNCHANGED);
	Mat piston(temp.rows * 2, temp.cols * 8, CV_8UC4, Scalar(0, 0, 0, 0)); //länge und breite sind variabel

	temp = imread(java + "\\assets\\minecraft\\textures\\entity\\banner\\base.png", IMREAD_UNCHANGED);
	Mat imbanner(temp.rows * 8, temp.cols * 8, CV_8UC4, Scalar(0, 0, 0, 0)); //länge und breite sind variabel

	temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse\\donkey.png");
	Mat horse2(temp.rows / 2, temp.cols / 2, CV_8UC4, Scalar(0, 0, 0, 0));

	temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse\\armor\\horse_armor_diamond.png");
	Mat horse_armor(temp.rows / 2, temp.cols / 2, CV_8UC4, Scalar(0, 0, 0, 0));


	std::vector<std::string> banner{ "\\base","\\border","\\bricks","\\circle","\\creeper","\\cross","\\curly_border",
								"\\diagonal_left","\\diagonal_right","\\diagonal_up_left","\\diagonal_up_right","\\flower","\\gradient","\\gradient_up",
								"\\half_horizontal","\\half_horizontal_bottom","\\half_vertical","\\half_vertical_right","\\mojang","\\rhombus","\\skull",
								"\\small_stripes","\\square_bottom_left","\\square_bottom_right","\\square_top_left","\\square_top_right","\\straight_cross","\\stripe_bottom",
								"\\stripe_center","\\stripe_downleft","\\stripe_downright","\\stripe_left","\\stripe_middle","\\stripe_right","\\stripe_top",
								"\\triangles_bottom","\\triangles_top","\\triangle_bottom","\\triangle_top" };

	std::vector<std::string> bed{ "\\black","\\blue","\\brown","\\cyan","\\gray","\\green","\\light_blue",
								"\\silver","\\lime","\\magenta","\\orange","\\pink","\\purple","\\red",
								"\\white","\\yellow" };

	std::vector<std::string> old_name{ "\\textures\\painting\\paintings_kristoffer_zetterstrand","\\textures\\blocks\\endframe_eye",
								"\\textures\\blocks\\endframe_side","\\textures\\blocks\\endframe_top","\\textures\\items\\dragon_breath",
								"\\textures\\items\\fish_cod_cooked","\\textures\\items\\fish_cod_raw","\\textures\\items\\knowledge_book",
								"\\textures\\items\\wooden_armorstand","\\textures\\items\\beetroot_seeds","\\textures\\items\\acacia_boat",
								"\\textures\\items\\birch_boat","\\textures\\items\\dark_oak_boat","\\textures\\items\\jungle_boat",
								"\\textures\\items\\oak_boat","\\textures\\items\\spruce_boat","\\textures\\entity\\rabbit\\black",
								"\\textures\\entity\\cat\\black","\\textures\\entity\\chest\\normal_double",
								"\\textures\\models\\armor\\chainmail_layer_1","\\textures\\models\\armor\\chainmail_layer_2",
								"\\textures\\models\\armor\\diamond_layer_1","\\textures\\models\\armor\\diamond_layer_2",
								"\\textures\\models\\armor\\gold_layer_1","\\textures\\models\\armor\\gold_layer_2",
								"\\textures\\models\\armor\\iron_layer_1","\\textures\\models\\armor\\iron_layer_2",
								"\\textures\\models\\armor\\leather_layer_1","\\textures\\models\\armor\\leather_layer_2",
								"\\textures\\models\\armor\\leather_layer_1_overlay","\\textures\\models\\armor\\leather_layer_2_overlay",
								"\\textures\\entity\\armorstand\\wood",
		//old directory; moving files
		"\\textures\\entity\\end_portal","\\textures\\entity\\enderdragon\\dragon","\\textures\\entity\\enderdragon\\dragon_fireball","\\textures\\entity\\illager\\vex_charging",
		"\\textures\\entity\\illager\\vex","\\textures\\entity\\wither\\wither","\\textures\\entity\\bear\\polarbear","\\textures\\entity\\illager\\vindicator",
		"\\textures\\entity\\zombie_pigman","\\textures\\items\\fireworks","\\textures\\entity\\elytra","\\textures\\items\\barrier","\\textures\\items\\structure_void",
		"\\textures\\blocks\\lever" };

	std::vector<std::string> new_name{ "\\textures\\painting\\kz","\\textures\\blocks\\end_portal_frame_eye","\\textures\\blocks\\end_portal_frame_side","\\textures\\blocks\\end_portal_frame_top",
								"\\textures\\items\\dragons_breath","\\textures\\items\\fish_cooked","\\textures\\items\\fish_raw","\\textures\\items\\book_portfolio","\\textures\\items\\armor_stand",
								"\\textures\\items\\seeds_beetroot","\\textures\\items\\boat_acacia","\\textures\\items\\boat_birch","\\textures\\items\\boat_darkoak","\\textures\\items\\boat_jungle",
								"\\textures\\items\\boat_oak","\\textures\\items\\boat_spruce","\\textures\\entity\\rabbit\\blackrabbit","\\textures\\entity\\cat\\blackcat",
								"\\textures\\entity\\chest\\double_normal","\\textures\\models\\armor\\chain_1","\\textures\\models\\armor\\chain_2","\\textures\\models\\armor\\diamond_1",
								"\\textures\\models\\armor\\diamond_2","\\textures\\models\\armor\\gold_1","\\textures\\models\\armor\\gold_2","\\textures\\models\\armor\\iron_1",
								"\\textures\\models\\armor\\iron_2","\\textures\\models\\armor\\leather_1","\\textures\\models\\armor\\leather_2","\\textures\\models\\armor\\cloth_1",
								"\\textures\\models\\armor\\cloth_2","\\textures\\entity\\armor_stand",
		//new directory; moving files
		"\\textures\\blocks\\end_portal","\\textures\\entity\\dragon\\dragon","\\textures\\items\\dragon_fireball","\\textures\\entity\\vex_charging","\\textures\\entity\\vex",
		"\\textures\\entity\\wither_boss","\\textures\\entity\\polarbear","\\textures\\entity\\vindicator","\\textures\\entity\\pig\\pigzombie",
		"\\textures\\entity\\fireworks","\\textures\\models\\armor\\elytra","\\textures\\blocks\\barrier","\\textures\\blocks\\structure_void",
		"\\textures\\items\\lever" };

	std::vector<std::string> horse2_name{ "\\donkey.png","\\horse_black.png","\\horse_brown.png","\\horse_chestnut.png","\\horse_creamy.png","\\horse_darkbrown.png","\\horse_gray.png","\\horse_skeleton.png","\\horse_white.png",
									"\\horse_zombie.png","\\mule.png" };

	std::vector<std::string> horse2_armor_name{ "\\horse_armor_diamond.png","\\horse_armor_iron.png","\\horse_armor_gold.png" };

	//  0   1   2	3	4	5	6	7	8	9
	apos[0] = { 22, 28,  0, 12,  0,  0,  0,  0,  0,  0,	//row 0 - 3 bed, 4 arrow, 5 - 8 piston1
				 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, //9 - 12 piston2, 13 - 16 piston3, 17 silber, 18 piston_top(sticky)_normal, 19 - 62 horse
				 0,  0,  7,  7, 19, 27, 12, 24, 32, 12,
				20, 34, 46, 58, 21, 26, 24, 24, 24, 24,
				13, 19,  4,  2,  0,  8,  8,  8,  8,  1,
				 1, 34, 47,  3, 10, 10, 14, 14,  7, 14,
				51, 34, 55, 15, 15, 35,  0,  0,  0,  0, //63 - 79 horse armor
				 7,  2, 19, 34, 30,  5, 58, 58, 58, 58 };

	apos[1] = { 22,  0, 50, 50,  0,  0,  0,  0,  0,  0,	//colum
				 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				 9, 14,  9, 21, 30, 33,  0, 25, 24,  8,
				 2, 24, 24,  0, 61, 61, 81,102, 86,101,
				92, 92, 74, 77, 88, 98, 98, 98, 98, 72,
				80,  0, 11, 31, 24, 34, 38, 51, 45, 45,
			   100, 98, 96,  1, 20, 24,  0, 11, 12, 23,
				23,  0, 25, 78, 83, 59,  1, 18, 41, 58 };

	pixel[0] = { 6, 16, 12, 12, 10,  4,  4,  4,  4,  4,	//row
				 4,  4,  4,  3,  3,  3,  3, 23, 16, 12,
				 7,  7,  5,  5,  5,  5,  8,  3,  2,  7,
				12, 10, 12, 10,  3,  3,  5,  5,  5,  5,
				 1,  1,  4,  2,  9,  1,  1,  1,  1,  6,
				 6, 11, 11,  7,  4,  4,  4,  4,  7,  4,
				 4,  8,  3, 17, 17, 16, 12, 12, 12, 12,
				 5,  2,  8,  6,  4, 14, 10, 10, 10, 10 };

	pixel[1] = { 16, 44, 12, 12, 16, 16, 16, 16, 16,  8, //colum
				  8,  8,  8,  6,  6,  6,  6, 81, 16, 10,
				  6,  3, 13,  3,  4,  4,  6, 18, 18,  8,
				 22, 20, 20, 64, 15, 15,  6,  6,  2,  2,
				 10,  8,  6,  2, 10,  9,  9,  9,  9,  1,
				  1, 11, 11,  6,  7,  7,  7,  7,  6,  3,
				  8, 16, 16, 18,  4, 20, 12,  1, 12,  1,
				  1,  4, 14, 16,  4,  8, 16, 22, 16, 10 };

	npos[0] = { 0, 22, 38, 38, 10, 16, 16, 16, 16,  4,	//row
				 4,  4,  4, 24, 24, 24, 24, 18,  0, 13,
				13, 13, 20, 20, 25, 25, 12, 30, 33, 35,
				42, 32, 42, 54, 18, 18,  7,  7,  2,  2,
				 1,  1,  5,  7,  0,  9, 10,  9, 10,  9,
				 9, 21, 21, 47, 47, 47, 40, 40, 40, 36,
				21, 25, 33, 35, 35, 32, 13, 13, 13, 13,
				20, 18, 25, 25, 21, 39, 54, 54, 54, 54 };

	npos[1] = { 22,  0,  0, 12,  0,  0, 16, 32, 48, 64,	//colum
				68, 72, 76, 64, 70, 76, 82, 70, 16,  0,
				10, 16, 10, 23,  5,  9,  0,  0,  0,  7,
				 0, 22, 22,  0, 47, 32,  1, 13, 19, 25,
				 7, 21, 29, 32, 35, 26, 26, 45, 45, 32,
				47, 26, 37, 50, 46, 42, 42, 46, 50, 46,
				52, 48, 48,  0, 17, 22,  0, 12, 13, 25,
				25, 19,  0, 48, 52, 55,  0, 16, 38, 54 };



	// create folder structure for badrock
	dir = { "\\models","\\texts","\\textures","\\ui","\\texts\\ja_JP","\\texts\\zh_TW","\\textures\\blocks","\\textures\\colormap","\\textures\\entity","\\textures\\environment",
			"\\textures\\gui","\\textures\\items","\\textures\\map","\\textures\\misc","\\textures\\models","\\textures\\painting","\\textures\\particle","\\textures\\ui","\\ui\\settings_sections",
			"\\texts\\ja_JP\\font","\\texts\\zh_TW\\font","\\textures\\entity\\banner","\\textures\\entity\\bed","\\textures\\entity\\boat","\\textures\\entity\\cat","\\textures\\entity\\chest",
			"\\textures\\entity\\cow","\\textures\\entity\\creeper","\\textures\\entity\\dragon","\\textures\\entity\\endercrystal","\\textures\\entity\\enderman","\\textures\\entity\\fish","\\textures\\entity\\ghast",
			"\\textures\\entity\\horse","\\textures\\entity\\horse2","\\textures\\entity\\illager","\\textures\\entity\\llama","\\textures\\entity\\npc","\\textures\\entity\\parrot","\\textures\\entity\\pig",
			"\\textures\\entity\\pistonarm","\\textures\\entity\\rabbit","\\textures\\entity\\sheep","\\textures\\entity\\shulker","\\textures\\entity\\skeleton","\\textures\\entity\\skulls","\\textures\\entity\\slime",
			"\\textures\\entity\\spider","\\textures\\entity\\vex","\\textures\\entity\\villager","\\textures\\entity\\wither_boss","\\textures\\entity\\wolf","\\textures\\entity\\zombie","\\textures\\entity\\zombie_villager",
			"\\textures\\gui\\achievements","\\textures\\gui\\background","\\textures\\gui\\newgui","\\textures\\models\\armor","\\textures\\entity\\horse\\armor","\\textures\\entity\\horse2\\armor",
			"\\textures\\entity\\llama\\decor","\\textures\\gui\\newgui\\beacon","\\textures\\gui\\newgui\\Bundle","\\textures\\gui\\newgui\\buttons","\\textures\\gui\\newgui\\mob_effects","\\textures\\gui\\newgui\\play_screen","\\textures\\gui\\newgui\\portfolio",
			"\\textures\\gui\\newgui\\settings","\\textures\\gui\\newgui\\storage","\\textures\\gui\\newgui\\buttons\\border","\\textures\\gui\\newgui\\buttons\\borderless","\\textures\\gui\\newgui\\buttons\\checkbox","\\textures\\gui\\newgui\\buttons\\new_checkbox" };

	try
	{
		// ordner structur für win 10 pack erstellen
		//create_directory(pack);
		create_directories(pack + "\\textures\\entity\\dragon\\dragon");
		/*std::filesystem::permissions(pack, std::filesystem::perms::group_all | std::filesystem::perms::others_all | std::filesystem::perms::owner_read, std::filesystem::perm_options::replace);
		{
			for (std::string folder : dir)
			{

				//std::cout << "dir" << "  " << (pack + folder) << std::endl;
				std::filesystem::create_directory(pack + folder);
				std::filesystem::permissions(pack + folder, std::filesystem::perms::group_all | std::filesystem::perms::others_all | std::filesystem::perms::owner_all, std::filesystem::perm_options::replace);
			}

		}*/


		std::cout << "ordner erstellt: " << des << std::endl;
		//pfad von ordner und datein in ein vector speichern (java edition) 
		/*int corect = newdir[0].size();
		for (int i = 0; i < newdir.size(); ++i)
		{
			for (fs::path p : fs::directory_iterator(newdir[i]))
			{

				std::string path_{ p.string() };
				std::string temp = path_;
				temp.erase(0, corect); //delets the destination path characters

				int size = temp.size();
				for (int i = 0; i < size; ++i)
				{

					if (temp.at(i) == '\\') temp.at(i) = '/';

					if (temp.at(i) == '.')
					{

						file.push_back(temp); // /assets/...
						//std::cout << file[it] << "  " << it << std::endl;
						check = false; //++it;
						break;
					}
					else check = true;
				}

				if (check)
				{

					newdir.push_back(path_); //complet path
					//std::cout << newdir[it] << "  " << it << std::endl;
					++it;
				}

			}
		}
		std::cout << "java pack analysed" << std::endl;*/

		std::cout << "from: " << java + "\\assets\\minecraft\\textures" << std::endl << "to  : " << des + "\\" + pname + "\\textures" << std::endl;
		std::filesystem::copy(java + "\\assets\\minecraft\\textures", des + "\\" + pname + "\\textures", std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
		std::cout << "from: " << java + "\\assets\\minecraft\\lang" << std::endl << "to  : " << des + "\\" + pname + "\\texts" << std::endl;
		std::filesystem::copy(java + "\\assets\\minecraft\\lang", des + "\\" + pname + "\\texts", std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
		create_directories(pack + "\\textures\\entity\\horse2\\armor");

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\bed\\black.png", IMREAD_UNCHANGED);
		if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\entity\\bed\\black.tga");

		std::cout << java + "\\assets\\minecraft\\textures\\entity\\bed\\black.png " << std::endl;
		for (int i = 0; i < 4; ++i)
		{

			apos[0][i] *= (temp.rows / 64);
			apos[1][i] *= (temp.cols / 64);
			pixel[0][i] *= (temp.rows / 64);
			pixel[1][i] *= (temp.cols / 64);
			npos[0][i] *= (temp.rows / 64);
			npos[1][i] *= (temp.cols / 64);
			std::cout << "apos : " << apos[0][i] << " " << apos[1][i] << std::endl << "pixel: " << pixel[0][i] << " " << pixel[1][i] << std::endl << "npos : " << npos[0][i] << " " << npos[1][i] << std::endl;
		}


		for (int i = 0; i < 16; ++i)
		{

			temp = imread(java + "\\assets\\minecraft\\textures\\entity\\bed\\" + bed[i] + ".png", IMREAD_UNCHANGED);
			if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\entity\\bed\\" + bed[i] + ".tga", IMREAD_UNCHANGED);
			newpos(apos, npos, pixel, temp, temp, 0, 3, 2);//bed
			imwrite(pack + "\\textures\\entity\\bed" + bed[i] + ".png", temp);

		}


		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\projectiles\\arrow.png", IMREAD_UNCHANGED);
		if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\projectiles\\entity\\arrow.tga", IMREAD_UNCHANGED);

		apos[0][4] *= (temp.rows / 32);
		apos[1][4] *= (temp.cols / 32);
		pixel[0][4] *= (temp.rows / 32);
		pixel[1][4] *= (temp.cols / 32);
		npos[0][4] *= (temp.rows / 32);
		npos[1][4] *= (temp.cols / 32);

		Mat temp2 = imread(java + "\\assets\\minecraft\\textures\\entity\\projectiles\\spectral_arrow.png", IMREAD_UNCHANGED);
		newpos(apos, npos, pixel, temp2, temp, 4, 4);//arrow
		imwrite(pack + "\\textures\\entity\\arrows.png", temp);


		temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_side.png", IMREAD_UNCHANGED);
		if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_side.tga", IMREAD_UNCHANGED);

		for (int i = 5; i < 18; ++i)
		{

			apos[0][i] *= (temp.rows / 16);

			apos[1][i] *= (temp.cols / 16);

			pixel[0][i] *= (temp.rows / 16);
			if (i == 17 && ((temp.rows / 16) - 1) > 0) pixel[0][i] += ((temp.rows / 16) - 1);// silver corection
			if (i >= 13 && i <= 16) pixel[0][i] += (pixel[0][i] / 3);//piston(3) corection

			pixel[1][i] *= (temp.cols / 16);
			if (i == 17 && ((temp.cols / 16) - 1) > 0) pixel[1][i] += ((temp.cols / 16) - 1);// silver corection
			if (i > 12 && i < 17) pixel[1][i] += (pixel[1][i] / 3);//piston(3) corection

			npos[0][i] *= (temp.rows / 16);

			npos[1][i] *= (temp.cols / 16);

		}

		newpos(apos, npos, pixel, temp, piston, 5, 8);//piston(1/5 pistonArm)
		newpos(apos, npos, pixel, temp, piston, 9, 12, 1);//piston(2/5 pistonArm)
		newpos(apos, npos, pixel, temp, piston, 13, 16, 1);//piston(3/5 pistonArm)

		for (int i = 0; i < 4; ++i)//piston(4/5 pistonArm)
		{

			int it = i + 13;
			int oit = i + 9;
			int nr = npos[0][it];
			int r = npos[0][oit];

			for (; r < pixel[1][oit] + npos[0][oit]; ++r)
			{
				int sc = npos[1][it] + 3 * pixel[0][oit] / 4;
				int c = npos[1][oit] + pixel[0][oit] / 4;

				for (; c < npos[1][oit] + pixel[0][it]; ++c)
				{

					piston.at<Vec4b>(nr, sc) = piston.at<Vec4b>(r, c);
					++sc;

				}
				++nr;

			}
			++it;
			++oit;
		}

		for (int r = npos[0][17]; r < pixel[0][17] + 1; ++r)//silber(piston)(5/5 pistonArm)
		{


			for (int c = npos[1][17]; c < pixel[1][17] + 1; ++c)
			{
				piston.at<Vec4b>(r, c)[0] = 135;
				piston.at<Vec4b>(r, c)[1] = 135;
				piston.at<Vec4b>(r, c)[2] = 135;
				piston.at<Vec4b>(r, c)[3] = 255;
			}

		}

		temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_top_normal.png", IMREAD_UNCHANGED);
		if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_top_normal.tga", IMREAD_UNCHANGED);

		apos[0][18] *= (temp.rows / 16);
		apos[1][18] *= (temp.cols / 16);
		pixel[0][18] *= (temp.rows / 16);
		pixel[1][18] *= (temp.cols / 16);
		npos[0][18] *= (temp.rows / 16);
		npos[1][18] *= (temp.cols / 16);

		for (int i = 0; i < 2; ++i)//piston normal
		{
			if (i == 1) npos[1][18] *= 2;
			newpos(apos, npos, pixel, temp, piston, 18, 18);
			if (i == 1) npos[1][18] /= 2;
		}
		fs::create_directory(pack + "\\textures\\entity\\pistonarm");
		imwrite(pack + "\\textures\\entity\\pistonarm\\pistonArm.png", piston);

		temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\piston_top_sticky.png", IMREAD_UNCHANGED);
		newpos(apos, npos, pixel, temp, piston, 18, 18);//piston sticky

		imwrite(pack + "\\textures\\entity\\pistonarm\\pistonArmSticky.png", piston);

		for (int i = 0, nr = 0, nc = 0, it = 0, itx = 0; i < 39; ++i)//banner
		{


			temp = imread(java + "\\assets\\minecraft\\textures\\entity\\banner" + banner[i] + ".png", IMREAD_UNCHANGED);
			if (temp.empty())temp = imread(java + "\\assets\\minecraft\\textures\\entity\\banner" + banner[i] + ".tga", IMREAD_UNCHANGED);

			if (i > 0 && i % 8 == 0)
			{
				it = 0;
				++itx;
			}

			nr = temp.rows * itx;

			for (int r = 0; r < temp.rows; ++r, ++nr)
			{

				nc = it * temp.cols;
				for (int c = 0; nc < temp.cols * (it + 1); ++c, ++nc)
				{
					imbanner.at<Vec4b>(nr, nc) = temp.at<Vec4b>(r, c);
				}

			}
			++it;
		}

		imwrite(pack + "\\textures\\entity\\banner\\banner.png", imbanner);




		format_pic(10, "destroy_stage_", ".png", java + "\\assets\\minecraft\\textures\\blocks\\", pack + "\\textures\\environment");//destroy
		picarray(64, "clock_", ".png", nclock, java + "\\assets\\minecraft\\textures\\items\\", pack + "\\textures\\items\\watch_atlas.png", 1);//clock
		picarray(32, "compass_", ".png", ncompas, java + "\\assets\\minecraft\\textures\\items\\", pack + "\\textures\\items\\compass_atlas.png", 1);//compass
		picarray(1, "sheep", ".png", sheep, java + "\\assets\\minecraft\\textures\\entity\\sheep\\", pack + "\\textures\\entity\\sheep\\sheep.png");//sheep (1/2)
		picarray(1, "sheep_fur", ".png", sheep, java + "\\assets\\minecraft\\textures\\entity\\sheep\\", pack + "\\textures\\entity\\sheep\\sheep.png", 0, sheep_row);//sheep (2/2)

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\pig\\pig.png", IMREAD_UNCHANGED);
		temp2 = imread(java + "\\assets\\minecraft\\textures\\entity\\pig\\pig_saddle.png", IMREAD_UNCHANGED);
		pic_over_pic(temp2, temp);//pig
		imwrite(pack + "\\textures\\entity\\pig\\pig_saddle.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\wolf\\wolf_tame.png", IMREAD_UNCHANGED);
		pic_over_pic(temp, temp, 1);//wolf
		imwrite(pack + "\\textures\\entity\\wolf\\wolf_tame.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\wolf\\wolf_collar.png", IMREAD_UNCHANGED);
		temp2 = imread(pack + "\\textures\\entity\\wolf\\wolf_tame.png", IMREAD_UNCHANGED);
		pic_over_pic(temp, temp2, 2);//wolf
		imwrite(pack + "\\textures\\entity\\wolf\\wolf_tame.png", temp2);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\enderman\\enderman_eyes.png", IMREAD_UNCHANGED);
		pic_over_pic(temp, temp, 1);//enderman
		imwrite(pack + "\\textures\\entity\\enderman\\enderman_eyes.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\enderman\\enderman.png", IMREAD_UNCHANGED);
		temp2 = imread(java + "\\assets\\minecraft\\textures\\entity\\enderman\\enderman_eyes.png", IMREAD_UNCHANGED);
		pic_over_pic(temp2, temp);//enderman
		imwrite(pack + "\\textures\\entity\\enderman\\enderman.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\zombie\\zombie.png", IMREAD_UNCHANGED);
		temp.rows /= 2;//zombie
		imwrite(pack + "\\textures\\entity\\zombie\\zombie.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\zombie\\husk.png", IMREAD_UNCHANGED);
		temp.rows /= 2;//husk
		imwrite(pack + "\\textures\\entity\\zombie\\husk.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\zombie_pigman.png", IMREAD_UNCHANGED);
		temp.rows /= 2;//pigzombie
		imwrite(pack + "\\textures\\entity\\pig\\pigzombie.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\redstone_dust_dot.png", IMREAD_UNCHANGED);
		temp2 = imread(java + "\\assets\\minecraft\\textures\\blocks\\redstone_dust_line1.png", IMREAD_UNCHANGED);
		pic_over_pic(temp2, temp);//redstone_dust_dot
		pic_over_pic(temp2, temp, 2);
		imwrite(pack + "\\textures\\blocks\\redstone_dust_cross.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\blocks\\redstone_dust_line1.png", IMREAD_UNCHANGED);
		rotate(temp, temp, 0);//redstone_dust_line
		imwrite(pack + "\\textures\\blocks\\redstone_dust_line.png", temp);

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse\\donkey.png", IMREAD_UNCHANGED);
		int faktor1 = temp.cols / 128;

		for (int i = 19; i < 63; ++i) //horse
		{

			apos[0][i] *= faktor1;
			apos[1][i] *= faktor1;
			pixel[0][i] *= faktor1;
			pixel[1][i] *= faktor1;
			npos[0][i] *= faktor1;
			npos[1][i] *= faktor1;

		}

		for (int i = 0; i < 11; ++i)//horse
		{

			temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse" + horse2_name[i], IMREAD_UNCHANGED);
			newpos(apos, npos, pixel, temp, horse2, 19, 52);

			// rotate by 180 degree
			int pos = 53;
			int nr = npos[0][pos] + pixel[0][pos] - 1;

			for (int r = apos[0][pos]; r < apos[0][pos] + pixel[0][pos]; ++r)
			{

				int nc = npos[1][pos] + pixel[1][pos] - 1;
				for (int c = apos[1][pos]; c < apos[1][pos] + pixel[1][pos]; ++c)
				{

					horse2.at<Vec4b>(nr, nc) = temp.at<Vec4b>(r, c);
					--nc;

				}

				--nr;

			}

			newpos(apos, npos, pixel, temp, horse2, 54, 54, 3);//horse
			newpos(apos, npos, pixel, temp, horse2, 55, 57, 1);//horse
			newpos(apos, npos, pixel, temp, horse2, 58, 62);//horse
			imwrite(pack + "\\textures\\entity\\horse2\\" + horse2_name[i], horse2);//horse

		}

		temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse\\armor\\horse_armor_diamond.png", IMREAD_UNCHANGED);
		int faktor = temp.cols / 128;

		for (int i = 63; i < 80; ++i) //horse
		{

			apos[0][i] *= faktor;
			apos[1][i] *= faktor;
			pixel[0][i] *= faktor;
			pixel[1][i] *= faktor;
			npos[0][i] *= faktor;
			npos[1][i] *= faktor;

		}

		for (int i = 0; i < 3; ++i)
		{

			temp = imread(java + "\\assets\\minecraft\\textures\\entity\\horse\\armor\\" + horse2_armor_name[i], IMREAD_UNCHANGED);//horse
			newpos(apos, npos, pixel, temp, horse_armor, 63, 66);//horse_armor
			newpos(apos, npos, pixel, temp, horse_armor, 67, 67, 4);//horse_armor
			newpos(apos, npos, pixel, temp, horse_armor, 68, 68);//horse_armor
			newpos(apos, npos, pixel, temp, horse_armor, 69, 69, 4);//horse_armor
			newpos(apos, npos, pixel, temp, horse_armor, 70, 79);//horse_armor
			imwrite(pack + "\\textures\\entity\\horse2\\armor" + horse2_armor_name[i], horse_armor);//horse

		}

		if (!fs::exists(pack + "\\pack_icon.png"))
		{
			fs::copy_file(java + "\\pack.png", pack + "\\pack_icon.png");
		}

		//rename and copy files
		for (int i = 0; i < old_name.size(); ++i)
		{
			if (fs::exists(pack + new_name[i] + ".png") || fs::exists(pack + new_name[i] + ".tga")) continue;

			if (!fs::exists(pack + old_name[i] + ".png"))
			{
				if (!fs::exists(pack + old_name[i] + ".tga"))
				{
					std::cout << "file " << old_name[i] << " not found" << std::endl;
					continue;
				}

				fs::copy_file(pack + old_name[i] + ".tga", pack + new_name[i] + ".tga");

			}

			fs::copy_file(pack + old_name[i] + ".png", pack + new_name[i] + ".png");
		}

		int corect = java.size();
		for (fs::path p : fs::directory_iterator(java))
		{
			std::string file_it{ p.string() };
			file_it.erase(0, corect); //delets the destination path characters 

			if (file_it.find("pack.mcmeta") != std::string::npos)
			{

				std::string mcmeta;
				ifstream Fmcmeta;
				Fmcmeta.open(p.c_str());
				std::string line;
				//std::string description;
				char description[255];

				while (!Fmcmeta.eof())
				{
					std::getline(Fmcmeta, line);
					size_t despos = line.find("description");
					if (despos != std::string::npos)
					{
						std::cout << "line:despos " << despos << std::endl;

						if (size_t first_pos = line.find("\"", despos + 14) != std::string::npos)
						{
							first_pos += despos + 14;																std::cout << "line:fir " << first_pos << std::endl;
							size_t second_pos = line.find("\"", first_pos + 1);										std::cout << "line:sec " << second_pos << std::endl;
							int num = second_pos - first_pos;
							if (num > 254) num = 254;
							line.copy(description, num, first_pos); description[num] = '\0';
							boost::uuids::random_generator gen;
							boost::uuids::uuid uuid_1 = gen();
							boost::uuids::uuid uuid_2 = gen();
							std::cout << boost::lexical_cast<std::string>(uuid_1) << "  " << boost::lexical_cast<std::string>(uuid_2) << std::endl;

							std::ofstream manifest(pack + "\\manifest.json");
							manifest << "{\n\"format_version\": 1, \n\"header\": {\n\"description\": \"" << description << "\", \n\"name\": \"" << pname << "\", \n\"uuid\": \"" << uuid_1 << "\", \n\"version\": [0, 0, 1], \n\"min_engine_version\": [1, 2, 6]\n}, \n\"modules\": [\n{ \n\"description\": \"Example vanilla resource pack\",\n\"type\": \"resources\",\n\"uuid\": \"" << uuid_2 << "\",\n\"version\": [0, 0, 1]\n}\n]\n}";
							//std::cout << "line:" << gen << std::endl;



						}

					}

				}

			}

		}

		//save's the last folder from a path in the vector "folder"(second argument) (../asset/texture/entity "entity" gets saved)
		//get_folder(dir, win_folder, 0);
		//get_folder(newdir, java_folder, 0);

		//compares the directorys from java and bedrock, if a directory is equal to the badrock directory, copy the files from java to badrock
		/*it = 0;
		itx = 0;
		for  (const std::string& win_folder : win_folder)
		{
			//std::cout << java_folder.size() << std::endl;
			for(int i = 0; i < java_folder.size(); ++i )
			{
				//std::cout << "win : " << win_folder << std::endl;
				//std::cout << "java: " << java_folder[i] << std::endl;
				if (win_folder.compare(java_folder[i]) == 0)
				{

					++itx;
					path from = newdir[i];
					path to = pack + dir[it];
					std::cout << "from: " << newdir[i] << std::endl;
					std::cout << "to  : " << pack + dir[it] << "  " << itx << std::endl;
					std::cout << std::endl;
				}
				//std::cout << "textures\\" + win_folder << "  " << "textures\\" + java_folder[i] << std::endl;
			}

			++it;

		}*/


	}

	catch (filesystem_error &e)
	{
		std::cerr << "catched an filesystem error: " << e.what() << '\n';
	}




}