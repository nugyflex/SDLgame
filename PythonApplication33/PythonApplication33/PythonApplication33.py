import pygame
import math
import sys

import random

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
    visible = True
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
        if self.visible:
            drawRect(self.x, self.y, self.buttonWidth, self.buttonHeight, DarkerLineColour)
            drawRect(self.x, self.y+self.buttonHeight + 2, self.buttonWidth, self.buttonHeight, DarkerLineColour)
            drawRect(self.x + self.buttonWidth + 2,self.y, self.buttonWidth*2, self.buttonHeight*2 + 2, DarkerLineColour)
            drawRect(self.x + self.buttonWidth + 6,self.y+4, self.buttonWidth*2 - 8, self.buttonHeight*2 + 2 - 8, DarkerBackGroundColour)
            game.drawText(str(self.value), self.x + self.buttonWidth*2 + 2, self.y + self.buttonHeight, DarkerLineColour)
    def checkForMouse(self):
        if self.visible:
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
        if self.value == False:
            drawRect(self.x+4, self.y+4, self.width - 8, self.height - 8, BackGroundColour)
            drawRect(self.x+4 + (self.width - 8)/2, self.y+4, (self.width - 8)/2, self.height - 8, LineColour)
            game.drawText("Off", self.x + self.width*2, self.y + self.height/2, DarkerLineColour)
        else:
            drawRect(self.x+4, self.y+4, self.width - 8, self.height - 8, BackGroundColour)
            drawRect(self.x+4, self.y+4, (self.width - 8)/2, self.height - 8, DarkerBackGroundColour)
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
        game.AIMode = 0
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class pvaiButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "pvcButtonMain.png", "pvcButtonAlt.png")
    def run(self):
        game.gameState = 1
        game.AIMode = 1
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
class loadSaveButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "loadButtonMain.png", "loadButtonAlt.png")
    def run(self):
        game.wipeGrid()
        game.readFromSave()
        game.gameState = 2
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class saveAndExitButton(Button):
    def __init__(self, _x, _y):
        Button.__init__(self, _x, _y, 400, 100, "s&qButtonMain.png", "s&qButtonAlt.png")
    def run(self):
        game.writeToSave()
        game.gameState = 0
        #to prevent clicking into next screen
        game.lastMouseLeft = True
class GUIElementWrapper:
    buttons = []
    def addButton(self, _type, _x, _y):
        if _type == "pvp":
            self.buttons.append(pvpButton(_x, _y))
        elif _type == "pvc":
            self.buttons.append(pvaiButton(_x, _y))
        elif _type == "exit":
            self.buttons.append(exitButton(_x, _y))
        elif _type == "menu":
            self.buttons.append(menuButton(_x, _y))
        elif _type == "play":
            self.buttons.append(playButton(_x, _y))
        elif _type == "load":
            self.buttons.append(loadSaveButton(_x, _y))
        elif _type == "save":
            self.buttons.append(saveAndExitButton(_x, _y))
    def addTextBox(self, _x, _y, _name):
        self.buttons.append(TextBox(_x, _y, _name))
    def addToggle(self, _x, _y):
        self.buttons.append(Toggle(_x, _y))
    def addIncrimentalClicker(self, _x, _y, _minValue, _maxValue, _increment):
        self.buttons.append(IncrementalClicker(_x, _y, _minValue, _maxValue, _increment))
    def drawElements(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].draw()
    def updateElements(self):
        for i in range(0, len(self.buttons)):
            self.buttons[i].checkForMouse()
    def clear(self):
        self.buttons = []
class Screen:
    def init(self):
        x = 0
    def deInit(self):
        x = 0
    def update(self):
        x = 0
    def draw(self):
        x = 0
class MenuScreen(Screen):
    tileImage = 0
    def init(self):
        game.GUIElements.addButton("pvp", "centered", 320)
        game.GUIElements.addButton("pvc", "centered", 440)
        game.GUIElements.addButton("load", "centered", 560)
        game.GUIElements.addButton("exit", "centered", 680)
        self.titleImage = pygame.image.load("title.png")
    def draw(self):
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth, game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight, game.screenWidth, game.footerHeight, LineColour)
        gameDisplay.blit(self.titleImage, (150, 100))

class SetupScreen(Screen):
    def init(self):
        if game.AIMode != 0:
            game.GUIElements.addTextBox("centered", 100, "Enter Player Name")
        else:
            game.GUIElements.addTextBox("centered", 100, "Enter Player1's Name")
            game.GUIElements.addTextBox("centered", 200, "Enter Player2's Name")
        game.GUIElements.addToggle("centered", 300)
        game.GUIElements.addIncrimentalClicker("centered", 360, 3, 13, 2)
        game.GUIElements.addButton("menu", "centered", 500)
        game.GUIElements.addButton("play", "centered", 620)
        game.resetBestOf()
        game.wipeGrid()
    def deInit(self):
        game.player1Name = game.GUIElements.buttons[0].text
        if game.AIMode != 0:
            game.player2Name = "AI"
            game.bestOfMode = game.GUIElements.buttons[1].value
            game.bestOfTotalRounds = game.GUIElements.buttons[2].value
        else:
            game.player2Name = game.GUIElements.buttons[1].text
            game.bestOfMode = game.GUIElements.buttons[2].value
            game.bestOfTotalRounds = game.GUIElements.buttons[3].value
        if game.player1Name == "":
            game.player1Name = "Player 1"
        if game.player2Name == "":
            game.player2Name = "Player 2"
    def update(self):
        game.GUIElements.buttons[3].visible = game.GUIElements.buttons[2].value
    def draw(self):
        drawRect(0,0,game.screenWidth, game.screenHeight, BackGroundColour)
        drawRect(0,0,game.screenWidth,game.headerHeight, LineColour)
        drawRect(0,game.screenHeight - game.footerHeight,game.screenWidth,game.footerHeight, LineColour)
        game.drawText("BestOf:", 240, 380, LineColour)
class GameScreen(Screen):
    def init(self):
        game.GUIElements.addButton("save", "centered" ,750)
        #game.resetBestOf()
    def update(self):
        game.testForResult()
        #game.buttonCollection.updateButtons()
        if game.AIMode == 1:
            if game.turn == 1:
                roundedX = int(math.floor((game.mouseX-game.paddingX)/(game.lineWidth+game.spacingX)))
                roundedY = int(math.floor((game.mouseY-game.paddingY)/(game.lineHeight+game.spacingY)))
                if roundedX > -1 and roundedX < 3 and roundedY > -1 and roundedY < 3 and game.mouseLeft == True and game.lastMouseLeft == False:
                    if game.grid[roundedX][roundedY] == 0:
                        if game.turn == 1:
                            game.grid[roundedX][roundedY] = 1
                            game.turn = 2
                            game.lastTime = pygame.time.get_ticks()
            else:
                game.runRandomAI()

        elif game.mouseLeft == True and game.lastMouseLeft == False:
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
            game.drawText(game.player1Name + "'s turn", screenWidth/2, 710, DarkerLineColour)
        else:
            game.drawText(game.player2Name + "'s turn", screenWidth/2, 710, DarkerLineColour)
        if game.bestOfMode:
            game.drawText("Round: " + str(game.bestOfRound + 1) + " (Best of " + str(game.bestOfTotalRounds) + ")", screenWidth/2, 140, DarkerLineColour)
        game.drawText(game.player1Name + ": " + str(game.bestOfScorePlayer1), screenWidth-140, 30, BackGroundColour)
        game.drawText(game.player2Name + ": " + str(game.bestOfScorePlayer2), 140, 30, BackGroundColour)
class GameOverScreen(Screen):
    def init(self):
        game.GUIElements.addButton("menu", "centered", screenHeight/2 + 100)
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
    GUIElements = GUIElementWrapper()
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
    AIMode = 1
    lastTime = 0
    AIDelay = 300

    #Drawing variables
    paddingX = 200
    paddingY = 180
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
    keyDownString = "default"
    lastKeyDownString = "default"

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

    
    #save file
    saveFile = open("save.txt", "r+")
    def wipeSave(self):
        self.saveFile = open("save.txt", "r+")
        self.saveFile.truncate()
    def writeToSave(self):
        self.wipeSave()
        for i in range(0, 3):
            for j in range(0, 3):
                self.saveFile.write(str(self.grid[i][j]) + '|')
        if game.bestOfMode:
            self.saveFile.write("y")
        else:
            self.saveFile.write("n")
        self.saveFile.write(str(self.bestOfScorePlayer1))
        self.saveFile.write(str(self.bestOfScorePlayer2))
        self.saveFile.write(str(self.bestOfRound))
        self.saveFile.write(str(self.turn))
        self.saveFile.write(str(self.AIMode))
        self.saveFile.close()
    def isInt(self, _string):
        try: 
            int(_string)
            return True
        except ValueError:
            return False
    def readFromSave(self):
        self.saveFile = open("save.txt", "r+")
        string = self.saveFile.read(24)
        if self.isInt(string[0]):
            self.grid[0][0] = int(string[0])
        if self.isInt(string[2]):
            self.grid[0][1] = int(string[2])
        if self.isInt(string[4]):
            self.grid[0][2] = int(string[4])
        if self.isInt(string[6]):
            self.grid[1][0] = int(string[6])
        if self.isInt(string[8]):
            self.grid[1][1] = int(string[8])
        if self.isInt(string[10]):
            self.grid[1][2] = int(string[10])
        if self.isInt(string[12]):
            self.grid[2][0] = int(string[12])
        if self.isInt(string[14]):
            self.grid[2][1] = int(string[14])
        if self.isInt(string[16]):
            self.grid[2][2] = int(string[16])
        if string[18] == "y":
            self.bestOfMode = True
            self.bestOfScorePlayer1 = int(string[19])
            self.bestOfScorePlayer2 = int(string[20])
            self.bestOfRound = int(string[21])
        else:
            self.bestOfMode = False
        self.turn = int(string[22])
        self.AIMode = int(string[23])
        if self.AIMode != 0:
            self.player2Name = "AI"

    def resetBestOf(self):
        self.bestOfRound = 0
        self.bestOfScorePlayer1 = 0
        self.bestOfScorePlayer2 = 0
    def text_objects(self, _text, _font, _color):
        textSurface = _font.render(_text, True, _color)
        return textSurface, textSurface.get_rect()
    def drawText(self, _string, _x, _y, _color):
        largeText = pygame.font.Font('Roboto-thin.ttf',55)
        TextSurf, TextRect = self.text_objects(_string, largeText, _color)
        TextRect.center = ((_x),(_y))
        gameDisplay.blit(TextSurf, TextRect)
    def runRandomAI(self):
        if pygame.time.get_ticks() > self.lastTime+self.AIDelay:
            while True: 
                x = random.randint(0, 2)
                y = random.randint(0, 2)
                if self.grid[x][y] == 0:
                    self.grid[x][y] = 2
                    break
            self.turn = 1
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
        elif result != 0:
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
    def manageScreens(self):
        if self.gameState != self.lastGameState:
            if self.lastGameState == 0:
                self.menuScreen.deInit()
            elif self.lastGameState == 1:
                self.setupScreen.deInit()
            elif self.lastGameState == 2:
                self.gameScreen.deInit()
            elif self.lastGameState == 3:
                self.gameOverScreen.deInit()
            self.GUIElements.clear()
            if self.gameState == 0:
                self.menuScreen.init()
            elif self.gameState == 1:
                self.setupScreen.init()
            elif self.gameState == 2:
                self.gameScreen.init()
            elif self.gameState == 3:
                self.gameOverScreen.init()
            elif self.gameState == 4:
                self.setupScreenPvAi.init()
    
        self.lastGameState = self.gameState  
    def update(self):
        self.GUIElements.updateElements()
        if self.gameState == 0:
            self.menuScreen.update()
        elif self.gameState == 1:
            self.setupScreen.update()
        elif self.gameState == 2:
            self.gameScreen.update()
        elif self.gameState == 3:
            self.gameOverScreen.update()
        elif self.gameState == 4:
            self.setupScreenPvAi.update()
    def draw(self):
        if self.gameState == 0:
            self.menuScreen.draw()
        elif self.gameState == 1:
            self.setupScreen.draw()
        elif self.gameState == 2:
            self.gameScreen.draw()
        elif self.gameState == 3:
            self.gameOverScreen.draw()
        elif self.gameState == 4:
            self.setupScreenPvAi.draw()
        self.GUIElements.drawElements()
    def mainLoop(self):      
        self.pollForInputs()
        self.manageScreens()
        self.update()
        self.draw()

        pygame.display.update()
    def start(self):
        while self.running:
            self.mainLoop()
game = Game()
game.menuScreen.init()
game.start()
game.saveFile.close()
pygame.display.quit()
pygame.quit()
sys.exit()