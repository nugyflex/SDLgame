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
        if self.active:
            if self.hoveredOver:
                gameDisplay.blit(self.altImage, (self.x,self.y))
            else:
                gameDisplay.blit(self.mainImage, (self.x,self.y))
    def checkForMouse(self):
        if self.active:
            global mouseX
            global mouseY
            global mouseLeft
            global lastMouseLeft
            if mouseX > self.x and mouseX < self.x + self.width and mouseY > self.y and mouseY < self.y + self.height:
                if mouseLeft and lastMouseLeft == False:
                    self.run()
                else:
                    self.hoveredOver = True
            else:
                self.hoveredOver = False
class pvpButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "pvpButtonMain.png", "pvpButtonAlt.png")
    def run(self):
        global gameState
        gameState = 1
        self.active = False
class pvcButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "pvcButtonMain.png", "pvcButtonAlt.png")
    def run(self):
        global gameState
        gameState = 1
        self.active = False
class exitButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "exitButtonMain.png", "exitButtonAlt.png")
    def run(self):
        global running
        running = False
        self.active = False
class buttonWrapper:
    buttons = []
    def addButton(self, _type, _x, _y):
        if _type == "pvp":
            self.buttons.append(pvpButton(_x, _y))
        elif _type == "pvc":
            self.buttons.append(pvcButton(_x, _y))
        elif _type == "exit":
            self.buttons.append(exitButton(_x, _y))
    def drawButtons(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].draw()
    def updateButtons(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].checkForMouse()
    def clear():
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

        drawRect(0,0,screenWidth,headerHeight, LineColour)
        drawRect(0,screenHeight - footerHeight,screenWidth,footerHeight, LineColour)

        drawRect(paddingX+spacingX, paddingY, lineWidth, totalHeight, LineColour)
        drawRect(paddingX + 2*spacingX + lineWidth, paddingY, lineWidth, totalHeight, LineColour)
        drawRect(paddingX,paddingY + spacingY,totalWidth,lineHeight, LineColour)
        drawRect(paddingX,paddingY + 2*spacingY + lineHeight,totalWidth,lineHeight, LineColour)
        for i in range(0, 3):
            for j in range(0, 3):
                if grid[i][j] ==1:
                    gameDisplay.blit(imageX, (paddingX + 40 + i*(lineWidth+spacingX),paddingY + 40 + j*(lineHeight+spacingY)))
                elif grid[i][j] == 2:
                    gameDisplay.blit(imageO, (paddingX + 40 + i*(lineWidth+spacingX),paddingY + 40 + j*(lineHeight+spacingY)))
class Game:
    screenWidth = 900
    screenHeight = 900
    
    grid = []
    boardSize = 3
    buttonCollection = buttonWrapper()
    for i in range(0, boardSize):
        grid.append([])
        for j in range(0, boardSize):
            grid[i].append(0)
    paddingX = 200
    paddingY = 200
    totalWidth = 500
    totalHeight = 500
    lineWidth = 20
    lineHeight = 20

    headerHeight = 80
    footerHeight = 50
    menuScreen = MenuScreen()
    gameScreen = GameScreen()
    spacingX = (totalWidth-2*lineWidth)/3
    spacingY = (totalHeight-2*lineHeight)/3
    mouseX = 0
    mouseY = 0
    turn = 0
    mouseLeft = False
    lastMouseLeft = False
    running = True
    #GAMESTATE:
    #0: start menu
    #1: game
    #2: game over
    gameState = 0
    imageX = pygame.image.load('x.png')
    imageO = pygame.image.load('o.png')
    def testForResult(self):
        for i in range(0,self.boardSize):
            for j in range(0,self.boardSize):
                if i < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i+1][j] == self.grid[i+2][j] != 0:
                        print "WINNER"
                        if j < self.boardSize - 2:
                            if self.grid[i][j] == self.grid[i+1][j+1] == self.grid[i+2][j+2] != 0:
                                print "WINNER"
                if j < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i][j+1] == self.grid[i][j+2] != 0:
                        print "WINNER"
                if j < self.boardSize - 2 and i > 1:
                    if self.grid[i][j] == self.grid[i-1][j+1] == self.grid[i-2][j+2] != 0:
                        print "WINNER"
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
        self.pollForInputs()
        self.buttonCollection.updateButtons()
        if self.gameState == 0:
            self.menuScreen.run()
        elif self.gameState == 1:
            self.gameScreen.run
        self.buttonCollection.drawButtons()
        self.testForResult()
        pygame.display.update()
    def start(self):
        while self.running:
            self.mainLoop()
game = Game()




#buttonCollection.addButton("pvp", 100, 100)
#buttonCollection.addButton("pvc", 100, 300)
#buttonCollection.addButton("exit", 100, 500)
game.start()
pygame.display.quit()
pygame.quit()
sys.exit()