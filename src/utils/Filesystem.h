/***
 *
 * Copyright (C) 2017 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#pragma once

#include <string>

#ifndef ACCESSPERMS
#define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO)
#endif

class FileSystem
{
private:
	FileSystem() {}
public:
	FileSystem(const FileSystem&) = delete;
	FileSystem(FileSystem&&) = delete;
	void operator=(const FileSystem&) = delete;
	void operator=(FileSystem&&) = delete;

	static void Init();
	static bool CreateDirectory(const std::string& directoryPath);
	static bool DirectoryExist(const std::string& directoryPath);
	static bool FileExist(const std::string& filePath);
	static void Write(const std::string& file, const char* data, size_t size);
	static int RemoveDirectory(const std::string& directoryPath);
	static int RemoveDirectory(const char* directoryPath);
	static int RemoveFile(const std::string& filePath);
	static int RemoveFile(const char* filePath);

};
