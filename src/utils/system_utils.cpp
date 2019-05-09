#include "system_utils.h"

DIR_CONTENT SystemUtils::read_directory(std::string dir_path)
{
	
	
	//~ using namespace std;
	DIR* dir;

	std::string path = dir_path;
	dir = opendir(path.c_str());


	std::vector<std::string> dir_names;
	std::vector<std::string> file_names;
	struct dirent * sd;
	struct stat st_buf;
	int status;
	
	while(sd = readdir(dir))
	{
		std::string check_path = path;
		check_path += "/";
		check_path += sd->d_name;

		status = stat(check_path.c_str(), &st_buf);
		// printf("read dir\n");
		
		//~ printf("name --> %s\n", sd->d_name);
		if( !S_ISREG(st_buf.st_mode)){
			if( !(strcmp(sd -> d_name,".")  == 0 || strcmp(sd -> d_name,"..") == 0)){
				dir_names.push_back(sd->d_name);
			}
			//~ printf("is a dir \n");
		}else{
			if( !(strcmp(sd -> d_name,".") == 0 || strcmp(sd -> d_name,"..") == 0)){
				file_names.push_back(sd->d_name);
			}			
			//~ printf("is a File\n");
		}
	}
	
	closedir(dir);
	//~ pair[0] = dir_names;
	//~ pair[1] = file_names;
	DIR_CONTENT dir_content;
	dir_content.dir_names = dir_names;
	dir_content.file_names = file_names;
	return dir_content;
}

bool SystemUtils::check_dir_exists( std::string dir_path, std::string dir_name){
	
	DIR_CONTENT dir_content = read_directory(dir_path);
	
	for (int i = 0; i < dir_content.dir_names.size(); i++)
	{
		if( strcmp(dir_content.dir_names[i].c_str(), dir_name.c_str()) == 0){
			//~ printf("there is a match !!! \n");
			return true;
		}

	}

	return false;
}

bool SystemUtils::check_file_exists( std::string dir_path, std::string file_name){
	
	DIR_CONTENT dir_content = read_directory(dir_path);
	
	for (int i = 0; i < dir_content.file_names.size(); i++)
	{
		if( strcmp(dir_content.file_names[i].c_str(), file_name.c_str()) == 0){
			//~ printf("there is a match !!! \n");
			return true;
		}

	}

	return false;
}		
