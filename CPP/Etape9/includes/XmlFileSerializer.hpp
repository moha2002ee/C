#ifndef XMLFILESIRIALIZER_HPP
#define XMLFILESIRIALIZER_HPP
#include <fstream>
#include <iostream>
#include "XmlFileSerializerException.h"
using namespace std;

namespace planning
{


	template <typename T>

	class XmlFileSerializer{

	private:
		fstream file;
		string fileName;
		char mode;
		string collectionName;
	public:
		static const char READ = 'R';
		static const char WRITE = 'W';
		XmlFileSerializer() = delete;
		XmlFileSerializer(const string& fn, char m, const string& cn  = "entities");
		XmlFileSerializer(const XmlFileSerializer& fs) = delete;
		~XmlFileSerializer() noexcept;

		string getFilename() const noexcept;
		string getCollectionName() const noexcept;
		bool isReadable() const noexcept;
		bool isWritable() const noexcept;

		XmlFileSerializer<T>& operator=(const XmlFileSerializer& x) = delete;

		void write(const T& val);
		T read();
	 
	};
}
#include "XmlFileSerializer.ipp"

#endif