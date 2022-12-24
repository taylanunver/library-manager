#ifndef LIBRARYCONTROL_H
#define LIBRARYCONTROL_H

#include <fstream>
#include <string>
#include <vector>

namespace libraryControl {

class Library;

class LibraryResource {
   public:
    // constructor and destructor
    LibraryResource();
    virtual ~LibraryResource();
    // getters
    virtual void getDetails() = 0;
    int getTotalUnits();
    virtual std::string getTitle();
    // setters
    void removeUnits(int units);
    void setAvailableUnits(int units);
    void setTitle(std::string title);
    // other methods
    void checkOut();
    void returnResource();
    void addUnits(int units);
    virtual void save(std::ofstream& file) = 0;

   protected:
    std::string title = "";
    int availableUnits = 0;
    int totalUnits = 0;
};

class Library {
   public:
    Library();
    virtual ~Library();
    void addResource(LibraryResource* resource);
    void addResource();
    void removeResource(LibraryResource* resource, int units);
    void listResources();
    LibraryResource* getResource(unsigned long long);

    // getters
    std::string getName();
    std::string getAddress();
    std::string getPhone();
    std::vector<std::string> getResourceTitles();

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
    friend std::vector<LibraryResource*> searchResources(const std::string&, Library*);
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
};

class Book : public LibraryResource {
   public:
    Book();
    virtual ~Book();
    void getDetails();
    void setAuthor(std::string author);
    void setPublisher(std::string publisher);
    void setDescription(std::string description);
    virtual void save(std::ofstream& file);

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
    void setPublisher(std::string publisher);
    void setDescription(std::string description);
    void setIssue(int issue);
    virtual void save(std::ofstream& file);
    std::string getTitle();

   private:
    std::string publisher;
    std::string description;
    int issue;
};

class Multimedia : public LibraryResource {
   public:
    Multimedia();
    virtual ~Multimedia();
    void getDetails();
    void setPublisher(std::string publisher);
    void setDescription(std::string description);
    void setDuration(int duration);
    virtual void save(std::ofstream& file);

   private:
    std::string publisher;
    int duration;
    std::string description;
    friend int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
};

int loadLibraries(std::string, std::vector<Library*>&);
std::vector<LibraryResource*> searchResources(const std::string& keyword, Library* library);
int saveLibraries(std::string& filename, std::vector<Library*>& libraries);
int askUserResource(LibraryResource*);
void addLibrary(std::vector<Library*>& libraries);
Book* addBook();
Periodical* addPeriodical();
Multimedia* addMultimedia();
}  // namespace libraryControl
#endif  // LIBRARYCONTROL_H