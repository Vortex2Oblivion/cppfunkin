#include "script.hpp"

#include <sprite.hpp>
#include <raylib-cpp.hpp>

class MyFoo {
    public:
        MyFoo(const int year, const std::string& message) : message(message), year(year), type("MyFoo") {
        }

        std::string message;

        const std::string& getType() const {
            return type;
        }

        int getYear() const {
            return year;
        }

        void setYear(const int value) {
            year = value;
        }

    private:
        int year;
        const std::string type;
};

funkin::Script::Script(const std::string &path) {
    this->path = path;
    
// Create new module
    auto& m = vm.module("mymodule");

    // Declare new class
    auto& cls = m.klass<MyFoo>("MyFoo");

    // Optional constructor with optional name
    cls.ctor<int, const std::string&>("new");

    // Define variables
    cls.var<&MyFoo::message>("message");                // Direct access
    cls.prop<&MyFoo::getYear, &MyFoo::setYear>("year"); // As getter & getter
    cls.propReadonly<&MyFoo::getType>("type");          // Read only variable

    // Append some extra stuff to the "mymodule"
    m.append(R"(
        class Vec3 {
            construct new (x, y, z) {
                _x = x
                _y = y
                _z = z
            }
        }
    )");

    // Runs the code from the std::string as a "main" module
    try {
        vm.runFromFile("main", path);

        // Find the main() function
        // You can look for classes and their functions!
        auto mainClass = vm.find("main", "Main");
        auto main = mainClass.func("main()");

        auto res = main(); // Execute the function

        // Access the return value
        MyFoo* ptr = res.as<MyFoo*>();                     // As a raw pointer
        std::shared_ptr<MyFoo> sptr = res.shared<MyFoo>(); // As a shared ptr
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}

funkin::Script::~Script() {
    TraceLog(LOG_INFO, "SCRIPT: Shutting down Script...");
}