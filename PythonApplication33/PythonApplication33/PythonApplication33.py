import pygame
import math
import sys
import ctypes

pygame.init()
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
DarkerLineColour = (20, 70, 130)
LineColour = (50, 110, 180)
BackGroundColour = (100, 150, 210)
DarkerBackGroundColour = (90, 140, 200)
screenWidth = 900
screenHeight = 900
gameDisplay = pygame.display.set_mode((screenWidth,screenHeight))
def getTextLength(text, size, font):
    class SIZE(ctypes.Structure):
        _fields_ = [("cx", ctypes.c_long), ("cy", ctypes.c_long)]
    hdc = ctypes.windll.user32.GetDC(0)
    hfont = ctypes.windll.gdi32.CreateFontA(-size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, font)
    hfont_old = ctypes.windll.gdi32.SelectObject(hdc, hfont)
    size = SIZE(0, 0)
    ctypes.windll.gdi32.GetTextExtentPoint32A(hdc, text, len(text), ctypes.byref(size))
    ctypes.windll.gdi32.SelectObject(hdc, hfont_old)
    ctypes.windll.gdi32.DeleteObject(hfont)
    return (size.cx, size.cy)
def drawRect(x, y, width, height, color):
    pygame.draw.rect(gameDisplay, color, [x, y,width ,height])
class IncrementalClicker:
    x = 0
    y = 0
    value = 0
    maxValue = 0
    minValue = 0
    increment = 0
    buttonWidth = 40
    buttonHeight = 50
    def __init__(self, _x, _y, _minValue, _maxValue, _increment):
        if _x == "centered":
            self.x  = screenWidth/2 - 68
        else:
            self.x = _x
        if _y == "centered":
            self.y  = screenHeight/2 - 62
        else:
            self.y = _y
        self.value = _minValue
        self.minValue = _minValue
        self.maxValue = _maxValue
        self.increment = _increment
    def draw(self):
        drawRect(self.x, self.y, self.buttonWidth, self.buttonHeight, DarkerLineColour)
        drawRect(self.x, self.y+self.buttonHeight + 2, self.buttonWidth, self.buttonHeight, DarkerLineColour)
        drawRect(self.x + self.buttonWidth + 2,self.y, self.buttonWidth*2, self.buttonHeight*2 + 2, DarkerLineColour)
        drawRect(self.x + self.buttonWidth + 6,self.y+4, self.buttonWidth*2 - 8, self.buttonHeight*2 + 2 - 8, DarkerBackGroundColour)
        game.drawText(str(self.value), self.x + self.buttonWidth*2 + 2, self.y + self.buttonHeight, DarkerLineColour)
    def checkForMouse(self):
        if game.mouseLeft and game.lastMouseLeft == False:
            if game.mouseX > self.x and game.mouseX < self.x + self.buttonWidth and game.mouseY > self.y and game.mouseY < self.y + self.buttonHeight and self.value + self.increment <= self.maxValue:
                self.value += self.increment
            elif game.mouseX > self.x and game.mouseX < self.x + self.buttonWidth and game.mouseY > self.y+self.buttonHeight + 2 and game.mouseY < self.y + self.buttonHeight*2 + 2 and self.value - self.increment >= self.minValue:
                self.value -= self.increment
class TextBox:
    text = ""
    x = 0
    y = 0
    width = 610
    height = 80
    inFocus = False
    name = "DefaultName"
    def __init__(self, _x, _y, _name):
        if _x == "centered":
            self.x  = screenWidth/2 - self.width/2
        else:
            self.x = _x
        if _y == "centered":
            self.y  = screenHeight/2 - self.height/2
        else:
            self.y = _y
        self.name = _name
    def draw(self):

        drawRect(self.x, self.y, self.width, self.height, LineColour)
        if self.inFocus:
            drawRect(self.x+4, self.y+4, self.width-8, self.height-8, DarkerBackGroundColour)
        else:
            drawRect(self.x+4, self.y+4, self.width-8, self.height-8, BackGroundColour)
        if self.text == "" and self.inFocus == False:
            game.drawText(self.name, self.x + self.width/2, self.y + self.height/2, LineColour)
        else:
            game.drawText(self.text, self.x + self.width/2, self.y + self.height/2, DarkerLineColour)
    def checkForMouse(self):
        if game.mouseLeft and game.lastMouseLeft == False:
            if game.mouseX > self.x and game.mouseX < self.x + self.width and game.mouseY > self.y and game.mouseY < self.y + self.height:
                self.inFocus = True
            else:
                self.inFocus = False
        elif game.mouseX > self.x and game.mouseX < self.x + self.width and game.mouseY > self.y and game.mouseY < self.y + self.height:
            self.hoveredOver = False
        if self.inFocus:
            if game.keyDownString != game.lastKeyDownString:
                fontTest = pygame.font.Font('Roboto-thin.ttf',55)
                textWidth, textHeight = fontTest.size(self.text)
                if game.keyDownString == "BACKSPACE":
                    self.text = self.text[:(len(self.text)-1)]
                elif textWidth < 570:
                    self.text += game.keyDownString
class Toggle:
    value = False
    x = 0
    y = 0
    width = 80
    height = 30
    def __init__(self, _x, _y):
        if _x == "centered":
            self.x  = screenWidth/2 - self.width/2
        else:
            self.x = _x
        if _y == "centered":
            self.y  = screenHeight/2 - self.height/2
        else:
            self.y = _y
    def draw(self):
        drawRect(self.x, self.y, self.width, self.height, DarkerLineColour)
        drawRect(self.x+4, self.y+4, self.width - 8, self.height - 8, DarkerBackGroundColour)
        if self.value == False:
            drawRect(self.x+4, self.y+4, self.width - 8, self.height - 8, DarkerBackGroundColour)
            drawRect(self.x+4 + (self.width - 8)/2, self.y+4, (self.width - 8)/2, self.height - 8, LineColour)
            game.drawText("Off", self.x + self.width*2, self.y + self.height/2, DarkerLineColour)
        else:
            drawRect(self.x+4, self.y+4, self.width - 8, self.height - 8, BackGroundColour)
            game.drawText("On", self.x + self.width*2, self.y + self.height/2, DarkerLineColour)
    def checkForMouse(self):
        if game.mouseLeft and game.lastMouseLeft == False:
            if game.mouseX > self.x and game.mouseX < self.x + self.width and game.mouseY > self.y and game.mouseY < self.y + self.height:
                if self.value:
                    self.value = False
                else:
                    self.value = True
class Button:
    mainImage = 0
    altImage = 0
    hoveredOver = False
    x = 0
    y = 0
    width = 0
    height = 0
    value = False
    def __init__(self, _x, _y, _width, _height, _mainPath, _altPath):
        if _x == "centered":
            self.x  = screenWidth/2 - _width/2
        else:
            self.x = _x
        if _y == "centered":
            self.y  = screenHeight/2 - _height/2
        else:
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
        Button.__init__(self, _x, _y, 400, 100, "menuButtonMain.png", "menuButtonAlt.png")
    def run(self):
        game.gameState = 0
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class playButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "playButtonMain.png", "playButtonAlt.png")
    def run(self):
        game.gameState = 2
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class nextButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "nextButtonMain.png", "nextButtonAlt.png")
    def run(self):
        game.wipeGrid()
        game.bestOfRound += 1
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
        elif _type == "play":
            self.buttons.append(playButton(_x, _y))
    def addTextBox(self, _x, _y, _name):
        self.buttons.append(TextBox(_x, _y, _name))
    def addToggle(self, _x, _y):
        self.buttons.append(Toggle(_x, _y))
    def addIncrimentalClicker(self, _x, _y, _minValue, _maxValue, _increment):
        self.buttons.append(IncrementalClicker(_x, _y, _minValue, _maxValue, _increment))
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
    def deInit(self):
        print "THIS IS THE BASE CLASS"
    def update(self):
        print "THIS IS THE BASE CLASS"
    def draw(self):
        print "THIS IS THE BASE CLASS"
class MenuScreen(Screen):
    tileImage = 0
    def init(self):
        game.buttonCollection.addButton("pvp", "centered", 320)
        game.buttonCollection.addButton("pvc", "centered", 440)
        game.buttonCollection.addButton("exit", "centered", 560)
        self.titleImage = pygame.image.load("title.png")
    def draw(self):
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth, game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight, game.screenWidth, game.footerHeight, LineColour)
        gameDisplay.blit(self.titleImage, (150, 100))

class SetupScreen(Screen):
    def init(self):

        game.buttonCollection.addTextBox("centered", 100, "Enter Player1's Name")
        game.buttonCollection.addTextBox("centered", 200, "Enter Player2's Name")
        game.buttonCollection.addToggle("centered", 300)
        game.buttonCollection.addIncrimentalClicker("centered", 360, 3, 13, 2)
        game.buttonCollection.addButton("menu", "centered", 500)
        game.buttonCollection.addButton("play", "centered", 620)
    def deInit(self):
        game.player1Name = game.buttonCollection.buttons[0].text
        game.player2Name = game.buttonCollection.buttons[1].text
        game.bestOfMode = game.buttonCollection.buttons[2].value
        game.bestOfTotalRounds = game.buttonCollection.buttons[3].value
    def draw(self):
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)
class GameScreen(Screen):
    def init(self):
        game.wipeGrid()
    def update(self):
        #game.buttonCollection.updateButtons()
        if game.mouseLeft == True and game.lastMouseLeft == False:
            roundedX = int(math.floor((game.mouseX-game.paddingX)/(game.lineWidth+game.spacingX)))
            roundedY = int(math.floor((game.mouseY-game.paddingY)/(game.lineHeight+game.spacingY)))
            if roundedX > -1 and roundedX < 3 and roundedY > -1 and roundedY < 3:
                if game.grid[roundedX][roundedY] == 0:
                    if game.turn == 1:
                        game.grid[roundedX][roundedY] = 1
                        game.turn = 2
                    elif game.turn == 2:
                        game.grid[roundedX][roundedY] = 2
                        game.turn = 1
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
        if game.turn == 1:
            game.drawText(game.player1Name + "'s turn", screenWidth/2, 800, DarkerLineColour)
        else:
            game.drawText(game.player2Name + "'s turn", screenWidth/2, 800, DarkerLineColour)
        if game.bestOfMode:
            game.drawText("Round: " + str(game.bestOfRound + 1) + " (Best of " + str(game.bestOfTotalRounds) + ")", screenWidth/2, 140, DarkerLineColour)
class GameOverScreen(Screen):
    def init(self):
        game.buttonCollection.addButton("menu", "centered", screenHeight/2 + 100)
    def draw(self):
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)
        if game.winner == 1:
            game.drawText(game.player1Name + " wins", screenWidth/2, screenHeight/2 - 100, DarkerLineColour)
        else:
            game.drawText(game.player2Name + " wins", screenWidth/2, screenHeight/2 - 100, DarkerLineColour)
        if game.bestOfMode:
            if game.winner == 1:
                game.drawText(str(game.bestOfScorePlayer1) + " : " + str(game.bestOfScorePlayer2), screenWidth/2, screenHeight/2, DarkerLineColour)
            else:
                game.drawText(str(game.bestOfScorePlayer2) + " : " + str(game.bestOfScorePlayer1), screenWidth/2, screenHeight/2, DarkerLineColour)
class Game:
    screenWidth = 900
    screenHeight = 900
    running = True

    #Game variables
    turn = 1
    boardSize = 3
    grid = []
    buttonCollection = buttonWrapper()
    for i in range(0, boardSize):
        grid.append([])
        for j in range(0, boardSize):
            grid[i].append(0)
    player1Name = "Player 1"
    player2Name = "Player 2"
    winner = 0
    bestOfMode = True
    bestOfTotalRounds = 3
    bestOfRound = 0
    bestOfScorePlayer1 = 0
    bestOfScorePlayer2 = 0

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
    setupScreen = SetupScreen()
    gameScreen = GameScreen()
    gameOverScreen = GameOverScreen()

    #Input variables
    mouseX = 0
    mouseY = 0
    mouseLeft = False
    lastMouseLeft = False
    isKeyDown = False
    keyDownString = "test"
    lastKeyDownString = "test"

    #GAMESTATE:
    #0: start menu
    #1: setup
    #2: game
    #3: game over
    gameState = 0
    lastGameState = 0

    #Game images
    imageX = pygame.image.load('x.png')
    imageO = pygame.image.load('o.png')
    def resetBestOf(self):
        bestOfMode = False
        bestOfTotalRounds = 3
        bestOfRound = 0
        bestOfScorePlayer1 = 0
        bestOfScorePlayer2 = 0
    def text_objects(self, _text, _font, _color):
        textSurface = _font.render(_text, True, _color)
        return textSurface, textSurface.get_rect()
    def drawText(self, _string, _x, _y, _color):
        largeText = pygame.font.Font('Roboto-thin.ttf',55)
        TextSurf, TextRect = self.text_objects(_string, largeText, _color)
        TextRect.center = ((_x),(_y))
        gameDisplay.blit(TextSurf, TextRect)
    def testForResult(self):
        result = 0
        for i in range(0,self.boardSize):
            for j in range(0,self.boardSize):
                if i < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i+1][j] == self.grid[i+2][j] != 0:
                        result = self.grid[i][j]
                    elif j < self.boardSize - 2:
                        if self.grid[i][j] == self.grid[i+1][j+1] == self.grid[i+2][j+2] != 0:
                            result = self.grid[i][j]
                if j < self.boardSize - 2:
                    if self.grid[i][j] == self.grid[i][j+1] == self.grid[i][j+2] != 0:
                        result = self.grid[i][j]
                if j < self.boardSize - 2 and i > 1:
                    if self.grid[i][j] == self.grid[i-1][j+1] == self.grid[i-2][j+2] != 0:
                        result = self.grid[i][j]
        cellsFilled = 0
        for i in range(0,self.boardSize):
            for j in range(0,self.boardSize):
                if self.grid[i][j] != 0:
                    cellsFilled += 1
        if cellsFilled == 9:
            self.wipeGrid()
        if result != 0:
            if self.bestOfMode:
                self.wipeGrid()
                game.bestOfRound += 1
                if result == 1:
                    game.bestOfScorePlayer1 += 1
                if result == 2:
                    game.bestOfScorePlayer2 += 1
                if self.bestOfScorePlayer1 > self.bestOfTotalRounds/2:
                    self.gameState = 3
                    self.winner = result
                elif self.bestOfScorePlayer2 > self.bestOfTotalRounds/2:
                    self.gameState = 3
                    self.winner = result
            else:
                self.wipeGrid()
                game.gameState = 3
                self.winner = result
    def wipeGrid(self):
     for i in range(0, 3):
        for j in range(0, 3):
            self.grid[i][j] = 0
    def pollForInputs(self):
        self.keyDownString = "temp"
        self.lastKeyDownString = self.keyDownString
        self.lastMouseLeft = self.mouseLeft
        for event in pygame.event.get():
            (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
            if event.type == pygame.MOUSEBUTTONDOWN:
                self.mouseLeft = True
                (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
                #print self.mouseX, self.mouseY
            else:
                (self.mouseX, self.mouseY) = pygame.mouse.get_pos()
                self.mouseLeft = False
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.KEYDOWN:
                self.isKeyDown = True
                self.keyDownString = unichr(event.key)
                #print event.key
                if event.key == 8:
                    self.keyDownString = "BACKSPACE"
                elif int(event.key) < 32 or int(event.key) > 126:
                    self.keyDownString = ""
            else:
                self.isKeyDown = True
    def mainLoop(self):
        self.lastGameState = self.gameState
        self.pollForInputs()
        self.buttonCollection.updateButtons()

        if self.gameState == 0:
            self.menuScreen.draw()
        elif self.gameState == 1:
            self.setupScreen.draw()
        elif self.gameState == 2:
            self.gameScreen.run()
        elif self.gameState == 3:
            self.gameOverScreen.run()
        self.buttonCollection.drawButtons()
        self.testForResult()

        if self.gameState != self.lastGameState:
            if self.lastGameState == 0:
                self.menuScreen.deInit()
            elif self.lastGameState == 1:
                self.setupScreen.deInit()
            elif self.lastGameState == 2:
                self.gameScreen.deInit()
            elif self.lastGameState == 3:
                self.gameOverScreen.deInit()
            self.buttonCollection.clear()
            if self.gameState == 0:
                self.menuScreen.init()
            elif self.gameState == 1:
                self.setupScreen.init()
            elif self.gameState == 2:
                self.gameScreen.init()
            elif self.gameState == 3:
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