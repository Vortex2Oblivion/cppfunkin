import "engine" for Sprite

class Main {
    static main() {
        var vec = Vec3.new(1.1, 2.2, 3.3)
        // Do something with "vec"

        var foo = MyFoo.new(2019, "Hello World")
        System.print("Foo type: %(foo.type) ")
        foo.year = 2020
        return foo
    }
}