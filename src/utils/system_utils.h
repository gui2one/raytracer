#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "../pch.h"

#include "linux/limits.h"
#include "unistd.h"
#include "dirent.h"
#include "sys/stat.h"

struct DIR_CONTENT
{
	std::vector<std::string> dir_names;
	std::vector<std::string> file_names;
};


struct SystemUtils{
	public:

		DIR_CONTENT read_directory(std::string dir_path);

		bool check_dir_exists( std::string dir_path, std::string dir_name);

		bool check_file_exists( std::string dir_path, std::string file_name);
	private:
	
};

#endif
