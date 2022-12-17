#ifndef LIBRARYCONTROL_H
#define LIBRARYCONTROL_H

#include <string>
#include <vector>

class LibraryResource {
   public:
    LibraryResource();
    virtual ~LibraryResource();
    virtual void getDetails() = 0;
    int checkAvailability();
    int getTotalUnits();
    void checkOut();
    void returnResource();
    void addUnits(int units);
    void removeUnits(int units);
    void setLibraryId(int id);
    void setAvailableUnits(int units);
    void setTitle(std::string title);
    std::string getTitle();

   protected:
    std::string title = "";
    int availableUnits = 0;
    int totalUnits = 0;
    int libraryId;
};

class Book : public LibraryResource {
   public:
    Book();
    virtual ~Book();
    void getDetails();
    void setAuthor(std::string author);
    void setPublisher(std::string publisher);
    void setDescription(std::string description);

   private:
    std::string author;
    std::string publisher;
    std::string description;
};

class Periodical : public LibraryResource {
   public:
    Periodical();
    virtual ~Periodical();
    void getDetails();

   private:
    std::string publisher;
    std::string description;
};

class Multimedia : public LibraryResource {
   public:
    Multimedia();
    virtual ~Multimedia();
    void getDetails();

   private:
    std::string publisher;
    int duration;
    std::string description;
};

class Library {
   public:
    Library();
    virtual ~Library();
    void addResource(LibraryResource* resource);
    void removeResource(LibraryResource* resource, int units);
    void listResources();

    // getters
    std::string getName();
    std::string getAddress();
    std::string getPhone();
    int getId();

    // setters
    void setName(std::string name);
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setId(int id);

   private:
    std::vector<LibraryResource*> resources;
    int resourceCount;
    std::string name;
    std::string address;
    std::string phone;
    int id;
};

namespace libraryControl {
int loadLibraries(std::string filename, std::vector<Library*>& libraries);
}

#endif  // LIBRARYCONTROL_H