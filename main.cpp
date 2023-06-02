#include <iostream>
#include <string>

// Interface "Library"
class Library {
public:
    virtual std::string getJournalList() = 0;
    virtual std::string downloadArticle(std::string articleId) = 0;
};

// Implementation of "Library" for internal network
class InternalLibrary : public Library {
public:
    std::string getJournalList() override {
        return "Journal list available";
    }

    std::string downloadArticle(std::string articleId) override {
        return "Downloading article " + articleId;
    }
};

// Implementation of "Library" for external network
class ExternalLibrary : public Library {
public:
    std::string getJournalList() override {
        return "Journal list available";
    }

    std::string downloadArticle(std::string articleId) override {
        return "Access denied. Internal access required to download article " + articleId;
    }
};

// Interface "Reader"
class Reader {
public:
    virtual std::string getAccessLevel() = 0;
    virtual std::string getJournalList() = 0;
    virtual std::string downloadArticle(std::string articleId) = 0;
};

// Implementation of "Reader" for internal network
class InternalReader : public Reader {
private:
    Library* library;

public:
    InternalReader() {
        library = new InternalLibrary();
    }

    ~InternalReader() {
        delete library;
    }

    std::string getAccessLevel() override {
        return "Access: Internal network";
    }

    std::string getJournalList() override {
        return library->getJournalList();
    }

    std::string downloadArticle(std::string articleId) override {
        return library->downloadArticle(articleId);
    }
};

// Implementation of "Reader" for external network
class ExternalReader : public Reader {
private:
    Library* library;

public:
    ExternalReader() {
        library = new ExternalLibrary();
    }

    ~ExternalReader() {
        delete library;
    }

    std::string getAccessLevel() override {
        return "Access: External network";
    }

    std::string getJournalList() override {
        return library->getJournalList();
    }

    std::string downloadArticle(std::string articleId) override {
        return library->downloadArticle(articleId);
    }
};

// Usage example
int main() {
    Reader* internalReader = new InternalReader();
    Reader* externalReader = new ExternalReader();

    std::cout << "Internal Reader:" << std::endl;
    std::cout << internalReader->getAccessLevel() << std::endl;
    std::cout << internalReader->getJournalList() << std::endl;
    std::cout << internalReader->downloadArticle("122") << std::endl;

    std::cout << "-------------------" << std::endl;

    std::cout << "External Reader:" << std::endl;
    std::cout << externalReader->getAccessLevel() << std::endl;
    std::cout << externalReader->getJournalList() << std::endl;
    std::cout << externalReader->downloadArticle("122") << std::endl;

    delete internalReader;
    delete externalReader;

    return 0;
}
