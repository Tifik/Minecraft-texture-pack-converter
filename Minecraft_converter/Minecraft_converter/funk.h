#pragma once

std::string check_file_stat;
std::string ext;
std::vector< std::vector<int> > apos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > npos{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > pixel{ 2, std::vector<int>(30, 0) };
std::vector< std::vector<int> > des_pixel{ 2, std::vector<int>(30, 0) };
bool debug = false;
namespace fs = boost::filesystem;
using namespace cv;

//newpos(old position, new position, pixel, Mat original picture, Mat manipulated picture, start index, end index, rotate by 90 degree clock wise(1) anti clock wise(2) rotate by 180 degree(3))
void newpos(std::vector<std::vector<int>>& apos, std::vector<std::vector<int>>& npos, std::vector<std::vector<int>>& pixel, std::vector<std::vector<int>>& des_pixel, Mat& orig, Mat& manip, int from_idx = 0, int to_idx = 0, int mode = 0)
{

	int res_format;
	int i = from_idx;
	do
	{

		int w_row = des_pixel[0][i];
		int w_col = des_pixel[1][i];

		if (mode == 1 || mode == 2) { w_col = des_pixel[0][i]; w_row = des_pixel[1][i]; }
		
		//std::cout << from_idx << " : " << i << std::endl;
		Mat w_fragment(w_row, w_col, CV_8UC4, Scalar(0, 0, 0, 0));
		Mat j_fragment(pixel[0][i], pixel[1][i], CV_8UC4, Scalar(0, 0, 0, 0));
		//newpos(apos, npos, pixel, orig, j_fragment, i, i, 6);

		for (int r = apos[0][i], nr = 0; r < apos[0][i] + j_fragment.rows; ++r, ++nr)
		{

			for (int c = apos[1][i], nc = 0; c < apos[1][i] + j_fragment.cols; ++c, ++nc)
			{

				j_fragment.at<Vec4b>(nr, nc) = orig.at<Vec4b>(r, c);

			}

		}

		if (des_pixel[0][i] * des_pixel[1][i] < pixel[0][i] * pixel[1][i]) res_format = 3;
		else res_format = 2;
		resize(j_fragment, w_fragment, Size(w_fragment.cols, w_fragment.rows), 0.0, 0.0, res_format);
		//if (i == 39) imshow("TEST", w_fragment); waitKey();
		//newpos(apos, npos, des_pixel, w_fragment, destination, i, i, 5);

		int rc, rr;
		if (mode == 2) rc = npos[1][i];
		else if (mode == 1) rc = npos[1][i] + w_fragment.rows - 1;
		else if (mode == 3) rr = npos[0][i] + w_fragment.rows - 1;

		for (int nr = npos[0][i], r = 0; nr < npos[0][i] + w_fragment.rows; ++r, ++nr)
		{

			if (mode == 1) rr = npos[0][i];
			else if (mode == 2) rr = npos[0][i] + w_fragment.cols - 1;
			else if (mode == 3) rc = npos[1][i] + w_fragment.cols - 1;

			for (int nc = npos[1][i], c = 0; nc < npos[1][i] + w_fragment.cols; ++c, ++nc)
			{

				//if (mode == 3) std::cout << "rr : " << rr << std::endl << "rc : " << rc << std::endl << "r  : " << r << std::endl << "c  : " << c << std::endl << "row: " << w_fragment.rows << std::endl << "col: " << w_fragment.cols << std::endl;
				if (mode == 1 || mode == 2 || mode == 3) manip.at<Vec4b>(rr, rc) = w_fragment.at<Vec4b>(r, c);
				else manip.at<Vec4b>(nr, nc) = w_fragment.at<Vec4b>(r, c);

				if (mode == 3) --rc;
				else if (mode == 2) --rr;
				else if (mode == 1) ++rr;

			}

			if (mode == 3) --rr;
			else if (mode == 2) ++rc;
			else if (mode == 1) --rc;

		}

		++i;

	} while (i <= to_idx);
}
//load all clock pictures step by step (backwards clock_63; clock_62...) to Mat orig
//picarray(how many pic's, pic name, picture format, Mat manipulated pic, read the pic from path, save the pic in path, 01 flag, if you have 2 pic's you have to set the row )
void picarray(int idx, const std::string& pic_name, const std::string& format, Mat& manip, const std::string& path_from, const std::string& path_to, int flag = 0, int row = 0)
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
void format_pic(int idx, const std::string& pic_name, const std::string& format, const std::string& path_from, const std::string& path_to)
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
void scale_correction(int number, int& rows, int& cols, int loop_from, int loop_to)
{

	int row_multiplier = (rows / number);
	int col_multiplier = (cols / number);

	int i = loop_from;
	do
	{
		

		apos[0][i] *= row_multiplier;
		apos[1][i] *= col_multiplier;
		pixel[0][i] *= row_multiplier;
		pixel[1][i] *= col_multiplier;
		npos[0][i] *= row_multiplier;
		npos[1][i] *= col_multiplier;
		des_pixel[0][i] *= row_multiplier;
		des_pixel[1][i] *= col_multiplier;
		++i;

	} while (i <= loop_to);
	
}

void alpha(Mat& pic, int alpha = 150)
{

	for (int r = 0; r < pic.rows; ++r )
	{
	
		for (int c = 0; c < pic.cols; ++c)
		{
		
			if (pic.at<Vec4b>(r, c)[3] >= alpha) /*pic.at<Vec4b>(r, c)[3] = pic.at<Vec4b>(r, c)[3] = 255*/;
			else 
			{

				pic.at<Vec4b>(r, c)[0] = pic.at<Vec4b>(r, c)[0] = 0; 
				pic.at<Vec4b>(r, c)[1] = pic.at<Vec4b>(r, c)[1] = 0;
				pic.at<Vec4b>(r, c)[2] = pic.at<Vec4b>(r, c)[2] = 0;
				pic.at<Vec4b>(r, c)[3] = pic.at<Vec4b>(r, c)[3] = 0;

			}
		
		}
	
	}

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