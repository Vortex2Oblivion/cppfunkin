import "engine" for Sprite, Game
import "raylib" for Vector2

class Main {
    static main() {
        var sprite = Sprite.new(100, 100)
        sprite.loadGraphic("assets/images/slungus.png")
        sprite.scale = Vector2.new(2.0, 2.0)
        sprite.centerOrigin()
        System.print(sprite.type)
        Game.add(sprite)
    }
}