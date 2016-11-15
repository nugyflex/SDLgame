import pygame
import math
import sys

pygame.init()
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
LineColour = (50, 110, 180)
BackGroundColour = (100, 150, 210)
screenWidth = 900
screenHeight = 900
gameDisplay = pygame.display.set_mode((screenWidth,screenHeight))
def drawRect(x, y, width, height, color):
    pygame.draw.rect(gameDisplay, color, [x, y,width ,height])
class Button:
    mainImage = 0
    altImage = 0
    hoveredOver = False
    x = 0
    y = 0
    width = 0
    height = 0
    def __init__(self, _x, _y, _width, _height, _mainPath, _altPath):
        self.x = _x
        self.y = _y
        self.width = _width
        self.height = _height
        self.loadImages(_mainPath, _altPath)
    def loadImages(self, mainPath, altPath):
        self.mainImage = pygame.image.load(mainPath)
        self.altImage = pygame.image.load(altPath)
    def run(self):
        print(self.x)
    def draw(self):
        if self.hoveredOver:
            gameDisplay.blit(self.altImage, (self.x,self.y))
        else:
            gameDisplay.blit(self.mainImage, (self.x,self.y))
    def checkForMouse(self):
        if game.mouseX > self.x and game.mouseX < self.x + self.width and game.mouseY > self.y and game.mouseY < self.y + self.height:
            if game.mouseLeft and game.lastMouseLeft == False:
                self.run()
            else:
                self.hoveredOver = True
        else:
            self.hoveredOver = False
class pvpButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "pvpButtonMain.png", "pvpButtonAlt.png")
    def run(self):
        game.gameState = 1
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class pvcButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "pvcButtonMain.png", "pvcButtonAlt.png")
    def run(self):
        game.gameState = 1
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class exitButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "exitButtonMain.png", "exitButtonAlt.png")
    def run(self):
        game.running = False
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class menuButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "exitButtonMain.png", "exitButtonAlt.png")
    def run(self):
        game.gameState = 0
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class buttonWrapper:
    buttons = []
    def addButton(self, _type, _x, _y):
        if _type == "pvp":
            self.buttons.append(pvpButton(_x, _y))
        elif _type == "pvc":
            self.buttons.append(pvcButton(_x, _y))
        elif _type == "exit":
            self.buttons.append(exitButton(_x, _y))
        elif _type == "menu":
            self.buttons.append(menuButton(_x, _y))
    def drawButtons(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].draw()
    def updateButtons(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].checkForMouse()
    def clear(self):
        self.buttons = []
class Screen:
    def run(self):
        self.update()
        self.draw()
    def init(self):
        print "THIS IS THE BASE CLASS"
    def update(self):
        print "THIS IS THE BASE CLASS"
    def draw(self):
        print "THIS IS THE BASE CLASS"
class MenuScreen(Screen):
    def init(self):
        game.buttonCollection.addButton("pvp", 100, 100)
        game.buttonCollection.addButton("pvc", 100, 300)
        game.buttonCollection.addButton("exit", 100, 500)
    def update(self):
        game.buttonCollection.updateButtons()
    def draw(self):
        game.buttonCollection.drawButtons()
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)
class GameOverScreen(Screen):
    def init(self):
        game.buttonCollection.addButton("menu", 100, 100)
    def update(self):
        game.buttonCollection.updateButtons()
    def draw(self):
        game.buttonCollection.drawButtons()
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)
class GameScreen(Screen):
    def update(self):
        game.buttonCollection.updateButtons()
        if game.mouseLeft == True and game.lastMouseLeft == False:
            roundedX = int(math.floor((game.mouseX-game.paddingX)/(game.lineWidth+game.spacingX)))
            roundedY = int(math.floor((game.mouseY-game.paddingY)/(game.lineHeight+game.spacingY)))
            if roundedX > -1 and roundedX < 3 and roundedY > -1 and roundedY < 3:
                if game.grid[roundedX][roundedY] == 0:
                    if game.turn == 0:
                        game.grid[roundedX][roundedY] = 1
                        game.turn = 1
                    elif game.turn == 1:
                        game.grid[roundedX][roundedY] = 2
                        game.turn = 0
    def draw(self):
        drawRect(0,0,screenWidth,screenHeight, BackGroundColour)

        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)

        drawRect(game.paddingX+game.spacingX, game.paddingY, game.lineWidth, game.totalHeight, LineColour)
        drawRect(game.paddingX + 2*game.spacingX + game.lineWidth, game.paddingY, game.lineWidth, game.totalHeight, LineColour)
        drawRect(game.paddingX,game.paddingY + game.spacingY,game.totalWidth,game.lineHeight, LineColour)
        drawRect(game.paddingX,game.paddingY + 2*game.spacingY + game.lineHeight,game.totalWidth,game.lineHeight, LineColour)
        for i in range(0, 3):
            for j in range(0, 3):
                if game.grid[i][j] ==1:
                    gameDisplay.blit(game.imageX, (game.paddingX + 40 + i*(game.lineWidth+game.spacingX),game.paddingY + 40 + j*(game.lineHeight+game.spacingY)))
                elif game.grid[i][j] == 2:
                    gameDisplay.blit(game.imageO, (game.paddingX + 40 + i*(game.lineWidth+game.spacingX),game.paddingY + 40 + j*(game.lineHeight+game.spacingY)))
class Game:
    screenWidth = 900
    screenHeight = 900
    running = True

    #Game variables
    turn = 0
    boardSize = 3
    grid = []
    buttonCollection = buttonWrapper()
    for i in range(0, boardSize):
        grid.append([])
        for j in range(0, boardSize):
            grid[i].append(0)

    #Drawing variables
    paddingX = 200
    paddingY = 200
    totalWidth = 500
    totalHeight = 500
    lineWidth = 20
    lineHeight = 20
    headerHeight = 80
    footerHeight = 50
    spacingX = (totalWidth-2*lineWidth)/3
    spacingY = (totalHeight-2*lineHeight)/3

    #Screens
    menuScreen = MenuScreen()
    gameScreen = GameScreen()
    gameOverScreen = GameOverScreen()

    #Input variables
    mouseX = 0
    mouseY = 0
    mouseLeft = False
    lastMouseLeft = False
    
    #GAMESTATE:
    #0: start menu
    #1: game
    #2: game over
    gameState = 0
    lastGameState = 0

    #Game images
    imageX = pygame.image.load('x.png')
    imageO = pygame.image.load('o.png')

    def testForResult(self):
        result = 0
        for i in range(0,self.boardSize):
            for j in range(0,self.boardSize):
                if i < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i+1][j] == self.grid[i+2][j] != 0:
                        print "WINNER"
                        result = self.grid[i][j]
                    elif j < self.boardSize - 2:
                        if self.grid[i][j] == self.grid[i+1][j+1] == self.grid[i+2][j+2] != 0:
                            print "WINNER"
                            result = self.grid[i][j]
                if j < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i][j+1] == self.grid[i][j+2] != 0:
                        print "WINNER"
                        result = self.grid[i][j]
                if j < self.boardSize - 2 and i > 1:
                    if self.grid[i][j] == self.grid[i-1][j+1] == self.grid[i-2][j+2] != 0:
                        print "WINNER"
                        result = self.grid[i][j]
        if result != 0:
            game.gameState = 2
            self.wipeGrid()
    def wipeGrid(self):
     for i in range(0, 3):
        for j in range(0, 3):
            self.grid[i][j] = 0
    def pollForInputs(self):
        self.lastMouseLeft = self.mouseLeft
        for event in pygame.event.get():
            (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
            if event.type == pygame.MOUSEBUTTONDOWN:
                self.mouseLeft = True
                (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
                print self.mouseX, self.mouseY
            else:
                (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
                self.mouseLeft = False
            if event.type == pygame.QUIT:
                self.running = False
    def mainLoop(self):
        self.lastGameState = self.gameState
        self.pollForInputs()
        self.buttonCollection.updateButtons()

        if self.gameState == 0:
            self.menuScreen.run()
        elif self.gameState == 1:
            self.gameScreen.run()
        elif self.gameState == 2:
            self.gameOverScreen.run()
        self.buttonCollection.drawButtons()
        self.testForResult()

        if self.gameState != self.lastGameState:
            self.buttonCollection.clear()
            if self.gameState == 0:
                self.menuScreen.init()
            elif self.gameState == 1:
                self.gameScreen.init()
            elif self.gameState == 2:
                self.gameOverScreen.init()
        pygame.display.update()
    def start(self):
        while self.running:
            self.mainLoop()
game = Game()




game.menuScreen.init()
game.start()
pygame.display.quit()
pygame.quit()
sys.exit()