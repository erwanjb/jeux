#include <string>
#include <cstdlib>

class FileSystem
{
private:
  typedef std::string (*Builder) (const std::string& path);

public:
  inline static std::string getPath(const std::string& path)
  {
    static std::string(*pathBuilder)(std::string const &) = getPathBuilder();
    return (*pathBuilder)(path);
  }

private:
  inline static std::string const & getRoot()
  {
    static char const * envRoot = getenv("LOGL_ROOT_PATH");
    static char const * givenRoot = (envRoot != nullptr ? envRoot : "C:/Users/wawan/jeux");
    static std::string root = (givenRoot != nullptr ? givenRoot : "");
    return root;
  }

  //static std::string(*foo (std::string const &)) getPathBuilder()
  inline static Builder getPathBuilder()
  {
    if (getRoot() != "")
      return &FileSystem::getPathRelativeRoot;
    else
      return &FileSystem::getPathRelativeBinary;
  }

  inline static std::string getPathRelativeRoot(const std::string& path)
  {
    return getRoot() + std::string("/") + path;
  }

  inline static std::string getPathRelativeBinary(const std::string& path)
  {
    return "../../../" + path;
  }


};