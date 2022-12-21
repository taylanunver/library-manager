#ifndef LIBRARYCONTROL_H
#define LIBRARYCONTROL_H

#include <string>
#include <vector>

namespace libraryControl {

class LibraryResource {
   public:
    // constructor and destructor
    LibraryResource();
    virtual ~LibraryResource();
    // getters
    virtual void getDetails() = 0;
    int getTotalUnits();
    int checkAvailability();
    std::string getTitle();
    // setters
    void removeUnits(int units);
    void setAvailableUnits(int units);
    void setTitle(std::string title);
    // other methods
    void checkOut();
    void returnResource();
    void addUnits(int units);
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);

   protected:
    std::string title = "";
    int availableUnits = 0;
    int totalUnits = 0;
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
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
};

class Periodical : public LibraryResource {
   public:
    Periodical();
    virtual ~Periodical();
    void getDetails();

   private:
    std::string publisher;
    std::string description;
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
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
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
};

class Library {
   public:
    Library();
    virtual ~Library();
    void addResource(LibraryResource* resource);
    void addResource();
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
    friend std::vector<LibraryResource*> searchResources(std::string&, Library*);
    friend int saveLibraries(std::string& filename, std::vector<Library*>&1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000 libraries);
};

int loadLibraries(std::string, std::vector<Library*>&);
std::vector<LibraryResource*> searchResources(std::string& keyword, Library* library);
int saveLibraries(std::string& filename, std::vector<Library*>&1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000 libraries);
}  // namespace libraryControl
#endif  // LIBRARYCONTROL_H