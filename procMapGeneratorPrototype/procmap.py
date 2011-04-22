from PIL import Image, ImageOps, ImageFilter
import math
import sys

f = open( sys.argv[1], 'r' )
lines = [];
for line in f:
  lines.append(line);


sz = 1000 

depthModifier = .25
perlinModifier = 0.25
surroundings = 5
numIterations = 1 


textures = [ 
    [ Image.open( "deepWater.jpg" ).load(), -256 ],
    [ Image.open( "midWater.jpg" ).load(), -40 ],
    [ Image.open( "shallowWater.jpg" ).load(), 50 ],
    [ Image.open( "beach.jpg" ).load(), 80 ],
    [ Image.open( "grass.jpg" ).load(), 110 ],
    [ Image.open( "tundra.jpg" ).load(), 512 ]
    ]


distanceMap = [[]]

for i in range( len(lines) ):
  lines[i] = lines[i].replace( ' ', '' )

for y in range( len(lines) ):
  distanceMap.append([]);
  for x in range( len(lines) ):
    land = 1
    if lines[x][y] == '.':
      land = 0
    dist = 0
    for reach in range( 1, len(lines), 1 ):
      for i in range( -reach, reach+1 ):

        if x+i < 0 or x+i >= len(lines):
          continue

        for j in range( -reach, reach+1):
          if y+j < 0 or y+j >= len(lines):
            continue
          if land:
            if lines[x+i][y+j] == '.':
              dist = reach
              break
          else:
            if lines[x+i][y+j] != '.':
              dist = reach
              break
        if dist > 0:
          break
      if dist > 0:
        break

    distanceMap[y].append( dist )

orgSize = (len(lines),len(lines))
size = (sz,sz)

originalMap = Image.new( "I", size )
oData = originalMap.load()

for y in range( size[1] ):
  oY = int(math.floor( y*orgSize[1]/size[1] ))
  for x in range( size[0] ):
    oX = int(math.floor( x*orgSize[0]/size[0] ))
    if( lines[oX][oY] == '.' ):
      oData[ y,x ] = -20 * distanceMap[oY][oX];
    else:
      oData[ y,x ] = 20 * distanceMap[oY][oX];
    pass

def surroundingValues( texture, x, y ):
  depthVal = 0
  for i in range( -surroundings, surroundings+1 ):
    if x+i >= size[0] or x+i < 0:
      continue
    for j in range( -surroundings, surroundings+1 ):
      if y+j >= size[1] or y+j < 0:
          continue
      if i != 0 or j != 0 :
        depthVal += texture[x+i,y+j]
  return depthVal

biggest = 0
smallest = 0

def getPositive( texture ):
  tData = texture.load()
  rTexture = Image.new( "L", size )
  rData = rTexture.load()

  for x in range( size[0] ):
    for y in range( size[1] ):
      if( tData[x,y] > 0 ):
        rData[x,y] = tData[x,y]
      else:
        rData[x,y] = 0

  return rTexture

def getNegative( texture ):
  tData = texture.load()
  rTexture = Image.new( "L", size )
  rData = rTexture.load()

  for x in range( size[0] ):
    for y in range( size[1] ):
      if( tData[x,y] < 0 ):
        rData[x,y] = tData[x,y] *-1
      else:
        rData[x,y] = 0

  return rTexture


for i in range( numIterations ):
  newMap = originalMap.copy()
  nData = newMap.load()
  oData = originalMap.load()
  biggest = smallest = 0

  for x in range( size[0] ):
    print "{0}/{1}".format( x, size[0] )
    for y in range( size[1] ):
      nData[ x,y ] = surroundingValues( oData, x, y ) * depthModifier
      if nData[ x,y ] > biggest:
        biggest = nData[ x,y ]
      if nData[ x,y ] < smallest:
        smallest = nData[x,y]

  originalMap = newMap.copy();

finalMap = Image.new( "RGB", size )

def normalize( element, small, big, lower, upper ):
  return float(element - small)*float(upper-lower)/float(big-small)+lower;

def sigmoidFunc( value ):
  return value;
  return 1/(1+math.exp( -.333 * value ) )

def interp( depth, x, y ):
  baseTex = -1;
  baseDepth = textures[0][1] - 5000
  while depth >= baseDepth and baseTex+1 < len(textures):
    baseTex+=1
    baseDepth = textures[baseTex][1]
  nextTex = baseTex
  baseTex -= 1
  baseDepth = textures[baseTex][1]
  nextDepth = textures[nextTex][1]

  shit = normalize( depth, smallest, biggest, -256, 256 )
  percentInterp = sigmoidFunc( (depth-baseDepth)/(nextDepth-baseDepth ) )


  c1 = textures[baseTex][0][ x,y ]
  c2 = textures[nextTex][0][ x,y ]
  color1 = [c1[0],c1[1],c1[2]]
  color2 = [(c2[0]-c1[0])*percentInterp,(c2[1]-c1[1])*percentInterp,(c2[2]-c1[2])*percentInterp]
  color3 = (color1[0]+color2[0],color1[1]+color2[1], color1[2]+color2[2])
  return color3;

fData = finalMap.load()
oData = originalMap.load()

for x in range( 0, size[0] ):
  for y in range( 0, size[1] ):
    fData[x,y] = interp( normalize( oData[x,y], smallest, biggest, -256, 256 ), x, y )

finalMap.show()
    
