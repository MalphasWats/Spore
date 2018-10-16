from PIL import Image

MAP = "Spore-Level-1"
OFFSET = 0

im = Image.open("doors.png")
pixels = list(im.getdata())

def extract_block(offsetX, offsetY):
    bytes = []
    b = 0
    for x in range(8):
        for y in range(8):
            pixel = pixels[im.width*(y+offsetY*8) + (x+offsetX*8)]
            if pixel == (0, 0, 0) or pixel == (0, 0, 0, 255):
                b = b | (128 >> y)

        bytes.append(b)
        b = 0
    return "{0:#04x}, {1:#04x}, {2:#04x}, {3:#04x}, {4:#04x}, {5:#04x}, {6:#04x}, {7:#04x}, ".format(*bytes)

glyphs = []
for y in range(im.size[1]//8):
    for x in range(im.size[0]//8):
        b = extract_block(x, y)
        if b not in glyphs:
            glyphs.append(b)

f = open('doors.txt', 'w')
for g in glyphs:
    f.write('    ')
    f.write(g)
    f.write('\n')

f.close()
im.close()

exit()

f = open('{}.txt'.format(MAP), 'w')
im = Image.open('{}.png'.format(MAP))

pixels = list(im.getdata())

tiles = []
for y in range(im.size[1]//8):
    for x in range(im.size[0]//8):
        b = extract_block(x, y)
        try:
            if b == "0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ":
                index = 0
            else:
                index = glyphs.index(b) + OFFSET
            tiles.append(index)
        except (ValueError):
            tiles.append(0)
            print("Tile not found: {}, {}".format(x, y))

c_row = []
while len(tiles) > 0:
    row = tiles[0:20]
    tiles = tiles[20:]
    
    for i in range(10):
        c_row.append(row[i*2] * 16 + row[i*2+1])
    
    line = """    {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3},
"""
    f.write(line.format(*row))
    
f.write("\n\n")    

while len(c_row) > 0:
    row = c_row[0:10]
    c_row = c_row[10:]
    
    line = """    {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3}, {:>3},
"""
    f.write(line.format(*row))

f.close()
im.close()

