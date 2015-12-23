Game = {}
Game.Main = function()
	Game.window = Window.Create("TestBed", 100, 100, 800, 600)
	Game.device = GFXDevice.Create(Game.window)
end

Game.Start = function()
	IntroScene()
end
