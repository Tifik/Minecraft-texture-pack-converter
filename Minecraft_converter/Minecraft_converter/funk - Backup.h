#pragma once
//#include "opencv2/core/core.hpp"
//#include <boost/filesystem.hpp>

std::string check_file_stat;
std::string ext;
std::vector< std::vector<int> > apos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > npos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > pixel{ 2, std::vector<int>(30, 0) };
namespace fs = boost::filesystem;
using namespace cv;

//newpos(old position, new position, pixel, Mat original picture, Mat manipulated picture, start index(default is 0), end index(default is 0), rotate by 90 degree clock wise(1) anti clock wise(3) set alpha value from old position to 0(2) mirror horizontal(4) (default is 0))
void newpos(std::vector<std::vector<int>>& apos, std::vector<std::vector<int>>& npos, std::vector<std::vector<int>>& pixel, Mat& orig, Mat& manip, int idx = 0, int toidx = 0, int mode = 0)
{
	int i = -1;
	int sc;
	int sr;
	do
	{
		int it = i + 1 + idx;
		int r = apos[0][it];
		int til = r + pixel[0][it];
		int nr = npos[0][it];
		sr = npos[0][it];
		if (mode == 3) sc = npos[1][it];
		else sc = npos[1][it] + pixel[0][it] - 1;

		for (; r < til; r++, ++nr)
		{
			if (mode != 4) sr = npos[0][it];
			if (mode == 3) sr = npos[0][it] + pixel[1][it] - 1;
			if (mode == 4) sc = npos[1][it] + pixel[1][it] - 1;
			int c = apos[1][it];
			int till = c + pixel[1][it];
			int nc = npos[1][it];


			for (; c < till; ++c, ++nc)
			{

				if (mode == 1 || mode == 3 || mode == 4) manip.at<Vec4b>(sr, sc) = orig.at<Vec4b>(r, c);
				else  manip.at<Vec4b>(nr, nc) = orig.at<Vec4b>(r, c);

				if (mode == 2)
				{

					manip.at<Vec4b>(r, c)[3] = 0;

				}

				if (mode == 3) --sr;
				else if (mode != 4) ++sr;
				else --sc;

			}

			if (mode == 3) ++sc;
			else if (mode != 4) --sc;
			else ++sr;

		}
		++i;
	} while (i < (toidx - idx));
}
//load all clock pictures step by step (backwards clock_63; clock_62...) to Mat orig
//picarray(how many pic's, pic name, picture format, Mat manipulated pic, read the pic from path, save the pic in path, 01 flag, if you have 2 pic's you have to set the row )
void picarray(int idx, const std::string& pic_name, const std::string& format, Mat& manip, const std::string path_from, const std::string path_to, int flag = 0, int row = 0)
{
	int i = idx, it = 0;
	int r = 0;
	int rc = 0;

	do
	{
		std::string scount = std::to_string(i - 1);
		std::string pic_it = "";

		if (i < 11 && flag == 1) pic_it = pic_name + "0" + scount + format;

		else if (!flag == 0) pic_it = pic_name + scount + format;

		else pic_it = pic_name + format;

		std::cout << pic_it << "\n";
		Mat orig = imread(path_from + pic_it, IMREAD_UNCHANGED);
		rc = manip.rows / idx;
		if (row > 0) r = row;
		else r = rc * it;

		for (int row = 0; row < orig.rows; ++row)
		{

			for (int col = 0; col < orig.cols; ++col)
			{
				manip.at<Vec4b>(r, col) = orig.at<Vec4b>(row, col);
			}
			++r;
		}
		
		++it; --i;
	} while (i > 0);

	imwrite(path_to, manip);
}

//only pixels with an alpha value of 0 gets overwriten
//pic_over_pic(Mat pic that gets copied, Mat pic wich gets "overwrite", set alpha value to 3 = 1. rotate mode = 2 (default is 0. ignore = 0))
void pic_over_pic(Mat& orig, Mat& manip, int mode = 0)
{
	for (int r = 0; r < orig.rows; ++r)
	{


		for (int c = 0; c < orig.cols; ++c)
		{

			if (mode == 0 && !orig.at<Vec4b>(r, c)[3] == 0)
				manip.at<Vec4b>(r, c) = orig.at<Vec4b>(r, c);

			if (mode == 1 && !orig.at<Vec4b>(r, c)[3] == 0)
				orig.at<Vec4b>(r, c)[3] = 3;

			if (mode == 2 && !orig.at<Vec4b>(r, c)[3] == 0)
				manip.at<Vec4b>(r, c) = orig.at<Vec4b>(r, c);

		}

	}

}

//format_pic(how many pic's, pic name, format, read the pic from path, image save path)
void format_pic(int idx, const std::string& pic_name, const std::string& format, const std::string path_from, const std::string path_to)
{


	for (int i = 0; i < idx; ++i)
	{

		std::string count = std::to_string(i);
		std::string pic_it = pic_name + count + format;
		std::cout << pic_it << "\n";
		Mat orig = imread(path_from + pic_it, IMREAD_UNCHANGED);

		for (int r = 0; r < orig.rows; ++r)
		{

			for (int c = 0; c < orig.cols; ++c)
			{

				if (orig.at<Vec4b>(r, c)[3] == 0)
				{
					orig.at<Vec4b>(r, c)[0] = orig.at<Vec4b>(r, c)[0] = 255;
					orig.at<Vec4b>(r, c)[1] = orig.at<Vec4b>(r, c)[1] = 255;
					orig.at<Vec4b>(r, c)[2] = orig.at<Vec4b>(r, c)[2] = 255;
					orig.at<Vec4b>(r, c)[3] = orig.at<Vec4b>(r, c)[3] = 1;
				}
			}

		}
		imwrite(path_to + "\\" + pic_it, orig);
	}


}

//get_folder(path to check, vector wich gets the new folder)
//save's the last folder from a path in the second vector argument (../asset/texture/entity "entity" gets saved)
void get_folder(const std::vector<std::string>& vec, std::vector<std::string>& folder, int flag = 1)
{

	int it = 1;
	int itx = 0;
	for (std::string ordner : vec)
	{
		std::size_t befor_last_found = 0;
		std::size_t last_found = 0;
		std::size_t found;
		

		for (int i = 0; i < it; ++i)
		{

			found = ordner.find('/');

			if (found != std::string::npos)
			{
				ordner.replace(found, 1, " ");
				//std::cout << ordner << '\n';
				befor_last_found = last_found;
				last_found = found;

				++it;
			}

			found = ordner.find('\\');

			if (found != std::string::npos)
			{
				ordner.replace(found, 1, " ");
				//std::cout << ordner << '\n';
				befor_last_found = last_found;
				last_found = found;

				++it;
			}


		}
		if (flag == 1) ordner.replace(0, last_found + 1, "");
		else
		{
			ordner.replace(last_found, 1, "/");
			ordner.replace(0, befor_last_found, "");
		}
		folder.push_back(ordner);
		//std::cout << "folder: " << folder[itx] << '\n';
		++itx;
	}



}

//scale_correction(set the mode to multiplikation(0) or devision(1), number to devide or multiply with, rows, colums, loop from, loop to)
void scale_correction(int mode, int number, int rows, int cols, int loop_from = 0, int loop_to = 0)
{
	if (mode == 0)
	{
		int i = loop_from;
		do
		{
			
			apos[0][i] *= number;
			apos[1][i] *= number;
			pixel[0][i] *= number;
			pixel[1][i] *= number;
			npos[0][i] *= number;
			npos[1][i] *= number;
			++i;

		} while (i < loop_to);

	}

	if (mode == 1)
	{
		int i = loop_from;
		do
		{
		
			apos[0][i] *= (rows / number);
			apos[1][i] *= (cols / number);
			pixel[0][i] *= (rows / number);
			pixel[1][i] *= (cols / number);
			npos[0][i] *= (rows / number);
			npos[1][i] *= (cols / number);
			++i;

		} while (i < loop_to);

	}
}

void pic_scale(Mat& source, Mat& destination, int rows, int cols, std::vector<std::vector<int>>& apos, std::vector<std::vector<int>>& npos, std::vector<std::vector<int>>& pixel)
{



}

	std::string check_file(const std::string& file)
	{
		
		fs::path file_path = file;
		if (fs::is_regular_file(file_path)) { ext = ".png"; check_file_stat = file_path.string(); return check_file_stat; }
		
		file_path.replace_extension(".jpg");

		if (fs::is_regular_file(file_path)) { ext = ".tga"; check_file_stat = file_path.string(); return check_file_stat; }
		return check_file_stat = "no_file";
		
		

	}

	fs::path to_path(std::string string)
	{
		
		fs::path path_ = string;
		return path_;
		
	}