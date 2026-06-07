import pygame, os, struct, math, sys, random;
from pygame.locals import *

# Master Atlas Coordinate Mapping
ATLAS_CONFIG = {
    "ui":      {"start_row": 0,  "tile_size": 8},   # Fonts, UI elements
    "world":   {"start_row": 8,  "tile_size": 16},  # Environment tiles
    "objects": {"start_row": 40, "tile_size": 16},  # Chests, doors, entities
    "effects": {"start_row": 56, "tile_size": 16}   # Particles, animations
}

MAP_WIDTH = 15
MAP_HEIGHT = 9
TOTAL_TILES = MAP_WIDTH * MAP_HEIGHT

original_map_data = [i + 1000 for i in range(TOTAL_TILES)]

def RoundToNearest(i, j):
    return i & ~(j-1)

def CreateArray(size, val):
    a = []
    for i in range(0,size):
        a.append(val)
    return a

def load_tilesheet(path, tile_size):
    try:
        sheet = pygame.image.load(path).convert_alpha()
    except pygame.error:
        print(f"Failed to load tilesheet at {path}")
        return []
    sheet_width, sheet_height = sheet.get_size()
    cols = sheet_width // tile_size
    rows = sheet_height // tile_size
    tiles = []
    for y in range(rows):
        for x in range(cols):
            rect = pygame.Rect(x * tile_size, y * tile_size, tile_size, tile_size)
            tiles.append(sheet.subsurface(rect))
    return tiles

def draw_tile(surface, tiles, tile_index, position):
    if 0 <= tile_index < len(tiles):
        surface.blit(tiles[tile_index], position)

class Window(object):
    def __init__(self,title="window",w=1280,h=720):
        pygame.init()
        self.width = w
        self.height = h
        self.scale = 2
        self.title = title
        self.size = (w, h)
        self.window = pygame.display.set_mode(self.size)
        self.buffer = pygame.Surface((w/2,h/2))
        self.deltatime = 0.0;
    def GetBuffer(self):
        return self.buffer
    def DrawTile(self, tiles, tile_index, position):
        if 0 <= tile_index < len(tiles):
            self.buffer.blit(tiles[tile_index], position)
    def Update(self):
        pygame.transform.scale(self.buffer,self.size,self.window)    
        pygame.display.flip()
    def Clear(self):
        self.buffer.fill((0,0,0))

class Room:
    def __init__(self, width=15, height=9):
        self.width = width
        self.height = height
        # 2D array for tiles, list for entity positions
        self.tiles = [[0 for _ in range(width)] for _ in range(height)]
        self.entities = [] 

class Level:
    def __init__(self, grid_width=8, grid_height=8):
        self.grid_width = grid_width
        self.grid_height = grid_height
        self.current_level_id = 0
        #self.rooms = [[Room() for _ in range(grid_width)] for _ in range(grid_height)]
        self.tiles = []
        self.entities = []

    def save_map(filename, map_data):
        # 'H' is 2 bytes. We need to repeat it for every tile in the map.
        # For a 15x9 map, this creates the format string: "=135H"
        format_string = f"={TOTAL_TILES}H"
        # Pack the list of integers into raw binary bytes
        binary_data = struct.pack(format_string, *map_data)
        # Write the raw bytes straight to disk
        with open(filename, "wb") as f:
            f.write(binary_data)
        print(f"Map successfully saved to {filename} ({len(binary_data)} bytes).")

class Tool(object):
    def use(self, grid_x, grid_y, tile_id, room):
        pass

class BrushTool(Tool):
    def use(self, grid_x, grid_y, tile_id, room):
        if 0 <= grid_x < room.width and 0 <= grid_y < room.height:
            room.tiles[grid_y][grid_x] = tile_id

class TileSelection:
    def __init__(self, tile_size=16, upscale_factor=4):
        self.tile_size = tile_size
        self.upscale = upscale_factor
        self.scaled_tile_size = tile_size * upscale_factor # 64x64px
        
        self.current_layer = "TILES" # Or "OBJECTS"
        self.active_id = 1           # Default brush ID
        
        # Sidebar positioning matrix
        self.sidebar_x_start = 960
        self.sidebar_width = 320

    def handle_input(self, mouse_pos, mouse_click):
        mx, my = mouse_pos
        
        # Check if the click happened strictly inside the Sidebar zone
        if mx >= self.sidebar_x_start:
            if mouse_click[0]: # Left Click
                # Calculate which relative grid slot was clicked in the sidebar
                relative_x = mx - self.sidebar_x_start
                grid_x = relative_x // self.scaled_tile_size
                grid_y = my // self.scaled_tile_size
                
                # TODO: Convert grid_x/y into your texture atlas ID 
                # self.active_id = calculated_id
                print(f"Selected Brush ID from Sidebar grid: {grid_x}, {grid_y}")

    def update(self):
        # Handle toggles like Tab to switch layers
        pass

    def draw(self, surface):
        # Draw the sidebar background, grid outlines, and the texture atlas selection sheet
        pass

class LevelEditor:
    def __init__(self):
        self.window = Window()
        self.world = World()
        self.current_room = self.world.rooms[0][0]
        self.current_tool = BrushTool()
        self.selected_tile_id = 1
        self.mapFile = None
        self.map_rect = pygame.Rect(0, 0, 960, 576)
        self.palette_rect = pygame.Rect(960, 0, 320, 576)
        self.minimap_rect = pygame.Rect(960, 400, 320, 144)
        self.console_rect = pygame.Rect(0, 576, 960, 144)
        self.chunkWidth = 15
        self.chunkHeight = 9
        self.chunkSize = self.chunkWidth * self.chunkHeight
        self.mapWidth = 8
        self.mapHeight = 8
        self.mapSize = self.mapWidth*self.mapHeight
        self.buffer = CreateArray(self.chunkSize, 0)
        #self.loadedChunkBuffer = []
        #self.chunkdirection = 0

    def CreateMapFile(self, path):
        f = open(path,"w")
        for i in range(0,self.mapSize):
            for j in range(0,self.chunkSize):
                f.write("{:<3}".format(str(i)))#ljust(3)#f.write(str(i).zfill(3))
        f.close()

    def LoadChunk(self, i, path):
        self.mapFile = open(path,"r")
        #mult by 3 since we save 3 digits per tile
        self.mapFile.seek(i*(self.chunkSize*3))
        for i in range(0,self.chunkSize):
            self.buffer[i] = int(self.mapFile.read(3).replace(" ",""))
        self.mapFile.close()
    def Update(self):
        #
        pass

    def OpenMap(self, path):
        self.mapFile = open(path,"r")

    def CloseMap(self):
        self.mapFile.close()

    def PrintBuffer(self):
        print(self.buffer)

if __name__ == "__main__":
    window = Window()
    buffer = window.GetBuffer()
    #level = Level()
    #level.CreateMapFile()
    #level.OpenMap("map.txt")
    #level.LoadChunk(4, "map.txt")
    #level.PrintBuffer()

    clock = pygame.time.Clock()
    atlas = load_tilesheet("data/atlas.png", 16)
    font = pygame.font.SysFont("Arial", 14)#font = pygame.font.Font(os.path.join(os.getcwd(),'FreeMonoBold.ttf'),12)
    random.seed(0)

    isRunning = True
    while isRunning:
        window.Clear()
        clock.tick(60)

        window.DrawTile(atlas, 0, (0,0))
        for event in pygame.event.get():
            if event.type == QUIT:
                isRunning = False
            elif event.type == MOUSEBUTTONDOWN and event.button == 1:
                print("test1")
            elif event.type == MOUSEBUTTONDOWN and event.button == 3:
                print("test3")
            pressed = pygame.key.get_pressed()
            if pressed[K_s]:
                pygame.image.save(buffer,'pallette.bmp')
            elif pressed[K_r]:
                pass
            elif pressed[K_q]:
                isRunning = False
        
        buffer.blit(font.render("test",True,(255,255,255)),(8,256))
        window.Update()
        
    pygame.display.quit()
    pygame.quit()
    sys.exit
