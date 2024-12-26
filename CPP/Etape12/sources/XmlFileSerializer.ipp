namespace planning
{
    template<typename T>
    XmlFileSerializer<T>::XmlFileSerializer(const string& fn, char m, const string& cn)
    {
        fileName = fn;
        mode = m;
        collectionName = cn;

        if(mode == WRITE)
        {
            file.open(fileName, ios::out);
            file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
            file << "<" << collectionName << ">" << endl;
        }
        else if(mode == READ)
        {
            file.open(fileName, ios::in);
            if (!file.is_open())
            {
                throw XmlFileSerializerException("Erreur en mode READ; le fichier n'existe pas sur le disque", XmlFileSerializerException::FILE_NOT_FOUND);
            }
            string line;
            getline(file, line);
            string sCollectionName;
            getline(file, sCollectionName);
            collectionName = sCollectionName.substr(1, sCollectionName.length() - 2);
        }
    }

    template<typename T>
    XmlFileSerializer<T>::~XmlFileSerializer() noexcept
    {
        if(mode == WRITE)
        {
            file << "</" << collectionName << ">" << endl;
        }
        file.close();
    }

    template<typename T>
    string XmlFileSerializer<T>::getFilename() const noexcept
    {
        return fileName;
    }

    template<typename T>
    string XmlFileSerializer<T>::getCollectionName() const noexcept
    {
        return collectionName;
    }

    template<typename T>
    bool XmlFileSerializer<T>::isReadable() const noexcept
    {
        return mode == READ;
    }

    template<typename T>
    bool XmlFileSerializer<T>::isWritable() const noexcept
    {
        return mode == WRITE;
    }

    template<typename T>
    void XmlFileSerializer<T>::write(const T& val)
    {
        if(mode == READ)
        {
            throw XmlFileSerializerException("Erreur; mode doit être WRITE et pas READ", XmlFileSerializerException::NOT_ALLOWED);
        }
        file << val << endl;
    }

    template<typename T>
    T XmlFileSerializer<T>::read()
    {
        string ligne;
        T Val;

        if (mode == WRITE)
        {
            throw XmlFileSerializerException("Erreur; mode doit être READ et pas WRITE", XmlFileSerializerException::NOT_ALLOWED);
        }
        streampos positionActuelle = file.tellg();
        file >> ligne;
        if(ligne == "</" + collectionName + ">")
        {
            throw XmlFileSerializerException("fin du fichier atteinte", XmlFileSerializerException::END_OF_FILE);
        }
        file.seekg(positionActuelle);
        file >> Val;
        return Val;
    }
}
